#include "GameEngineWindowTexture.h"
#include <Windows.h>
#include <GameEngineBase/GameEngineDebug.h>
#include "GameEngineWindow.h"

#pragma comment(lib, "msimg32.lib")


GameEngineWindowTexture::GameEngineWindowTexture()
{
}

GameEngineWindowTexture::~GameEngineWindowTexture()
{
}

void GameEngineWindowTexture::ResLoad(const std::string& _Path)
{
	// �ܼ��� ��Ʈ�ʸ� �ε��ϴ� �Լ��� �ƴ϶� �츮���� �׳� HANDLE�� �ش�
	// ������ ������δ� Ŀ�� �����ܵ �̳༮���� �ε��Ҽ� �־���? �ϴµ� �׷��� 

	// LoadBitmapA()

	// LPCSTR == const char*

	HANDLE ImageHandle = LoadImageA(nullptr, _Path.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	if (nullptr == ImageHandle)
	{
		MsgBoxAssert("�̹��� �ε忡 �����߽��ϴ�." + _Path);
		return;
	}

	// �̹����� �ڵ��� ���̰�.
	BitMap = static_cast<HBITMAP>(ImageHandle);

	// ���� ������ ���Ӱ� ������ �Ѵ�.
	// Window���� ���� DC
	ImageDC = CreateCompatibleDC(nullptr);
	// �̹����� ���� ������ ����� ����

	// ImageDC ���ѿ�
	// BitMap 2������ ���� ������ �����ض�.
	// ��� �̹� ��������ڸ��� ���ο� 1,1 �̹����� ����Ǿ��ְ�
	// ���� �ε��� �̹����� �� 1,1¥���� �о�� ��ü�ϴ� �۾��� �ϴµ�.
	// �� �Լ��� ���ϰ��� ������ ����Ǿ��ִ� �ָ� �������ִ°�.
	OldBitMap = static_cast<HBITMAP>(SelectObject(ImageDC, BitMap));

	ScaleCheck();
}

void GameEngineWindowTexture::ResCreate(const float4& _Scale)
{
	// �׳� ����ִ� ��� �̹����� �ϳ� ����� �Լ��ΰſ���.
	HANDLE ImageHandle = CreateCompatibleBitmap(GameEngineWindow::MainWindow.GetHDC(), _Scale.iX(), _Scale.iY());

	if (nullptr == ImageHandle)
	{
		MsgBoxAssert("�̹��� ������ �����߽��ϴ�.");
		return;
	}

	// �̹����� �ڵ��� ���̰�.
	BitMap = static_cast<HBITMAP>(ImageHandle);

	// ���� ������ ���Ӱ� ������ �Ѵ�.
	// Window���� ���� DC
	ImageDC = CreateCompatibleDC(nullptr);
	// �̹����� ���� ������ ����� ����

	// ImageDC ���ѿ�
	// BitMap 2������ ���� ������ �����ض�.
	// ��� �̹� ��������ڸ��� ���ο� 1,1 �̹����� ����Ǿ��ְ�
	// ���� �ε��� �̹����� �� 1,1¥���� �о�� ��ü�ϴ� �۾��� �ϴµ�.
	// �� �Լ��� ���ϰ��� ������ ����Ǿ��ִ� �ָ� �������ִ°�.
	OldBitMap = static_cast<HBITMAP>(SelectObject(ImageDC, BitMap));

	ScaleCheck();
}

void GameEngineWindowTexture::ScaleCheck()
{
	GetObject(BitMap, sizeof(BITMAP), &Info);

	BITMAP OldInfo;

	GetObject(OldBitMap, sizeof(BITMAP), &OldInfo);
}

float4 GameEngineWindowTexture::GetScale()
{

	return { static_cast<float>(Info.bmWidth), static_cast<float>(Info.bmHeight) };
}



void GameEngineWindowTexture::BitCopy(GameEngineWindowTexture* _CopyTexture, const float4& _Pos)
{
	BitCopy(_CopyTexture, _Pos, _CopyTexture->GetScale());
}

void GameEngineWindowTexture::BitCopy(
	GameEngineWindowTexture* _CopyTexture,
	const float4& _Pos,
	const float4& _Scale)
{
	HDC CopyImageDC = _CopyTexture->GetImageDC();

	//// Ư�� DC�� ����� ������
	//// Ư�� DC�� ��Ӻ����ϴ� �Լ��Դϴ�.
	BitBlt(ImageDC,
		_Pos.iX() - _Scale.ihX(),
		_Pos.iY() - _Scale.ihY(),
		_Scale.iX(),
		_Scale.iY(),
		CopyImageDC,
		0,
		0,
		SRCCOPY);

}

void GameEngineWindowTexture::TransCopy(GameEngineWindowTexture* _CopyTexture, const float4& _Pos, const float4& _Scale, const float4& _OtherPos, const float4& _OtherScale, int _TransColor/* = RGB(255, 0, 255)*/)
{
	HDC CopyImageDC = _CopyTexture->GetImageDC();

	//// Ư�� DC�� ����� ������
	//// Ư�� DC�� ��Ӻ����ϴ� �Լ��Դϴ�.
	TransparentBlt(ImageDC,
		_Pos.iX() - _Scale.ihX(),
		_Pos.iY() - _Scale.ihY(),
		_Scale.iX(),
		_Scale.iY(),
		CopyImageDC,
		_OtherPos.iX(), // ī���Ϸ��� �̹����� ������ x
		_OtherPos.iY(), // ī���Ϸ��� �̹����� ������ y
		_OtherScale.iX(), // �׺κк��� ������  x
		_OtherScale.iY(), // �׺κк��� ������  y
		_TransColor
	);

}
// ======= ���� ���� �ּ� ===========

//�����ε� - HANDLE �� �ü���� �����ΰ� �ĺ��ϱ� ���� Ű���� �ڵ��̶�� �Ѵ�. �ڵ��ȣ�� �ü���� ���ϰ� �ߺ��� �� ����.

//HANDLE LoadImageA(                    //���� �ε�� �̹����� �ڵ��� ��ȯ���ش�. �����ϸ� null ��ȯ
//	[in, optional] HINSTANCE hInst,   //�ε��� �̹����� ���� �������α׷�
//	[in]           LPCSTR    name,    //�ε��� �̹��� ���ϰ��
//	[in]           UINT      type,    //�ε��� �̹��� ����. IMAGE_BITMAP: ��Ʈ�ʷε�
//	[in]           int       cx,      //�̹��� �ʺ���. 0�̸� ���� ���ҽ� �ʺ�.
//	[in]           int       cy,      //�̹��� ���̼���. 0�̸� ���� ���ҽ� ����.
//	[in]           UINT      fuLoad   //�������� �ɼ�. LR_LOADFROMFILE: ������ ���Ͽ��� ���������� �̹����� �ε�.
//);

//HDC CreateCompatibleDC(        // DC�� Ư���� ��κ� �� ���������� �����ġ�ʹ� ������ �ȵ� DC�� �����ؾ��Ҷ� ���. �����ϸ� �޸� DC(CreateCompatibleDC�� ������� DC�� Memory DC�����)�� �ڵ� ��ȯ, ���д� null
//	[in] HDC hdc                 // ���ڰ� null�̸� ���ø����̼��� ���� ȭ�鿡 ȣȯ�Ǵ� �޸� DC�� ����
//);                             //https://blog.naver.com/tipsware/220995733415
  
//HBITMAP CreateCompatibleBitmap(  // ������ DC�� ����� ����̽��� ȣȯ�Ǵ� ��Ʈ��������. �Լ������� ȣȯ�Ǵ� ��Ʈ�� �ڵ��� ��ȯ, ���д� null
//	[in] HDC hdc,                  // DC�� �ڵ�
//	[in] int cx,                   // ��Ʈ�ʳʺ�
//	[in] int cy                    // ��Ʈ�ʳ���
//);
//������ CreateBitmap() �Լ��� �ִµ� �̰����ڰ� 5���� �׷��� �� �Լ��� DDB(��ġ��������Ʈ��)�̿��� DC�� ������ ���� ����. ���� ���ʿ� DC�� ȣȯ�ǰ� ��Ʈ���� ����°� ���� ���ϰ� �����ϴ� �װ� CreateCompatibleBitmap. https://blog.naver.com/tipsware/220985029852

//HGDIOBJ SelectObject(          //DC�� ����� Object�� �����Ҷ� �����. hdc�� ����Ű�� object�� h�� ������.
//	[in] HDC     hdc,
//	[in] HGDIOBJ h
//);
//
//int GetObject(                //������ �׷��� ��ü�� ���� ������ ����
//	[in]  HANDLE h,            //�׷��Ȱ�ü�� �ڵ�.
//	[in]  int    c,            //���ۿ� �� ������ ����Ʈ ��
//	[out] LPVOID pv            //�׷��Ȱ�ü�� ������ ������ ������ ������.
//);

//BOOL BitBlt(                 //�̹����� ȭ�鿡 ������ִ� �Լ�
//	[in] HDC   hdc,            //�̹����� ��µ� ��ġ�� �ڵ�
//	[in] int   x,              // �̹����� ��µ� �ڵ�ȭ���� ������ �𼭸� x��ǥ
//	[in] int   y,              //                                          y��ǥ
//	[in] int   cx,             // ��µ� �̹����� x�ʺ�
//	[in] int   cy,             //                 y ����
//	[in] HDC   hdcSrc,         //�̹����� �ڵ�
//	[in] int   x1,             //�����̹������� ������ x��ǥ. 
//	[in] int   y1,             //                      y                  
//	[in] DWORD rop             //�̹��� ��¹��. SRCCOPY: �����̹��� ���
//);                          


//BOOL TransparentBlt(          //BitBlt�� �̹����� �������� �ȼ��� 1:1�� �����ؼ� ����ϴ� ��ɸ� �����Ƿ�, �̹����� ȭ�� ������ ���� Ȯ��� ��Ҹ� �� �� ����. �̹��� �״�� ���縦 �ϴ� ��쿣 BltBlt�� ����ص� ������ �̸̹� Ȯ�� ����ϰ� �ʹٸ�? �� �Լ��� �Ἥ �̹����� Ȯ�� ����Ҽ� �ִ�. (����� BitBlt�� ����ϰڴٸ� �̹����� �׿��°� �����ؼ� �������� ���ۿ� ����.)
//	[in] HDC  hdcDest,        // �̹����� ��µ� �ڵ�
//	[in] int  xoriginDest,    // �����ġ. ������ �𼭸��� x��ǥ
//	[in] int  yoriginDest,    //                           y��ǥ
//	[in] int  wDest,          // �����ġ�κ��� x �ʺ�
//	[in] int  hDest,          //                y �ʺ�
//	[in] HDC  hdcSrc,         // �����̹����ڵ�
//	[in] int  xoriginSrc,     // �����̹����� ������ x��ǥ
//	[in] int  yoriginSrc,     //                     y��ǥ
//	[in] int  wSrc,           // �����̹����� ������ x��ǥ ������ �ʺ�
//	[in] int  hSrc,           //                     y
//	[in] UINT crTransparent   // �������� ó���� ���� ��Ʈ���� RGB ��. ����(255,0,255) ����Ÿ�� ������. �� ���� �����ļ� ���� ���鶧 �Ⱦ��� ���̱⶧��. ��, �̹����� �������� ó���ϰ� �����κ��� ����Ÿ�� ���� �����س����� ����Ҷ� �����ϰ� ����
//);