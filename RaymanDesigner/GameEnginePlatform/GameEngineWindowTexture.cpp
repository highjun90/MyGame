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
		MsgBoxAssert("이미지 로드에 실패했습니다." + _Path);
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

	//// 특정 DC에 연결된 색상을
	//// 특정 DC에 고속복사하는 함수입니다.
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

// ======= 최종 삭제 주석 ===========

//리마인드 - HANDLE 은 운영체제가 무엇인가 식별하기 위한 키값을 핸들이라고 한다. 핸들번호는 운영체제가 정하고 중복될 수 없음.

//HANDLE LoadImageA(                    //새로 로드된 이미지의 핸들을 반환해준다. 실패하면 null 반환
//	[in, optional] HINSTANCE hInst,   //로드할 이미지를 가질 응용프로그램
//	[in]           LPCSTR    name,    //로드할 이미지 파일경로
//	[in]           UINT      type,    //로드할 이미지 형식. IMAGE_BITMAP: 비트맵로드
//	[in]           int       cx,      //이미지 너비설정. 0이면 실제 리소스 너비.
//	[in]           int       cy,      //이미지 높이설정. 0이면 실제 리소스 높이.
//	[in]           UINT      fuLoad   //여러가지 옵션. LR_LOADFROMFILE: 지정된 파일에서 독립실행형 이미지를 로드.
//);
//
//HDC CreateCompatibleDC(        //지정된 디바이스와 호환되는 DC를 만든다. 성공하면 메모리 DC의 핸들 반환, 실패는 null
//	[in] HDC hdc               //인자가 null이면 애플리케이션의 현재 화면에 호환되는 메모리 DC를 만듬
//);
//
//HGDIOBJ SelectObject(          //지정된 DC(디바이스 컨텍스트)로 개체를 선택합니다. 새 개체는 동일한 형식의 이전 개체를 대체합니다.
//	[in] HDC     hdc,
//	[in] HGDIOBJ h
//);
//
//int GetObject(                 //지정된 그래픽 개체에 대한 정보를 저장
//	[in]  HANDLE h,            //그래픽개체의 핸들.
//	[in]  int    c,            //버퍼에 쓸 정보의 바이트 수
//	[out] LPVOID pv            //그래픽개체의 정보를 저장할 버퍼의 포인터.
//);
//
//BOOL BitBlt(                   //이미지를 화면에 출력해주는 함수
//	[in] HDC   hdc,            //이미지가 출력될 위치의 핸들
//	[in] int   x,              //출력될 이미지의 x좌표
//	[in] int   y,              //                y좌표
//	[in] int   cx,             //원본이미지에서 잘라올 x 너비
//	[in] int   cy,             //                      y 높이
//	[in] HDC   hdcSrc,         //이미지의 핸들
//	[in] int   x1,             //원본이미지에서 x 시작좌표. 여기서 cx 너비만큼 자름
//	[in] int   y1,             //               y                  cy
//	[in] DWORD rop             //이미지 출력방식. SRCCOPY: 원본이미지 출력
//);