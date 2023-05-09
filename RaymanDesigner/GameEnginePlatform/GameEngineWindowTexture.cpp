#include "GameEngineWindowTexture.h"
#include <Windows.h>
#include <GameEngineBase/GameEngineDebug.h>


GameEngineWindowTexture::GameEngineWindowTexture()
{
}

GameEngineWindowTexture::~GameEngineWindowTexture()
{
}

void GameEngineWindowTexture::ResLoad(const std::string& _Path)
{

	HANDLE ImageHandle = LoadImageA(nullptr, _Path.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	if (nullptr == ImageHandle)
	{
		MsgBoxAssert("�̹��� �ε忡 �����߽��ϴ�." + _Path);
		return;
	}

	BitMap = static_cast<HBITMAP>(ImageHandle);

	ImageDC = CreateCompatibleDC(nullptr);

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
//
//HDC CreateCompatibleDC(        //������ ����̽��� ȣȯ�Ǵ� DC�� �����. �����ϸ� �޸� DC�� �ڵ� ��ȯ, ���д� null
//	[in] HDC hdc               //���ڰ� null�̸� ���ø����̼��� ���� ȭ�鿡 ȣȯ�Ǵ� �޸� DC�� ����
//);
//
//HGDIOBJ SelectObject(          //������ DC(����̽� ���ؽ�Ʈ)�� ��ü�� �����մϴ�. �� ��ü�� ������ ������ ���� ��ü�� ��ü�մϴ�.
//	[in] HDC     hdc,
//	[in] HGDIOBJ h
//);
//
//int GetObject(                 //������ �׷��� ��ü�� ���� ������ ����
//	[in]  HANDLE h,            //�׷��Ȱ�ü�� �ڵ�.
//	[in]  int    c,            //���ۿ� �� ������ ����Ʈ ��
//	[out] LPVOID pv            //�׷��Ȱ�ü�� ������ ������ ������ ������.
//);
//
//BOOL BitBlt(                   //�̹����� ȭ�鿡 ������ִ� �Լ�
//	[in] HDC   hdc,            //�̹����� ��µ� ��ġ�� �ڵ�
//	[in] int   x,              //��µ� �̹����� x��ǥ
//	[in] int   y,              //                y��ǥ
//	[in] int   cx,             //�����̹������� �߶�� x �ʺ�
//	[in] int   cy,             //                      y ����
//	[in] HDC   hdcSrc,         //�̹����� �ڵ�
//	[in] int   x1,             //�����̹������� x ������ǥ. ���⼭ cx �ʺ�ŭ �ڸ�
//	[in] int   y1,             //               y                  cy
//	[in] DWORD rop             //�̹��� ��¹��. SRCCOPY: �����̹��� ���
//);