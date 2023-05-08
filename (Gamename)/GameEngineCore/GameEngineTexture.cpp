#include "GameEngineTexture.h"
#include <Windows.h>
#include <GameEngineBase/GameEngineDebug.h>

GameEngineTexture::GameEngineTexture()
{
}

GameEngineTexture::~GameEngineTexture()
{
}

void GameEngineTexture::ResLoad(const std::string& _Path)
{
	// 단순히 비트맵만 로드하는 함수가 아니라서 우리에게 그냥 HANDLE을 준다
	// 선생님 기억으로는 커서 아이콘등도 이녀석으로 로드할수 있었나? 하는데 그래서 

	// LoadBitmapA()

	// LPCSTR == const char*

	HANDLE ImageHandle = LoadImageA(nullptr, _Path.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	if (nullptr == ImageHandle)
	{
		MsgBoxAssert("이미지 로드에 실패했습니다." + _Path);
		return;
	}

	// 이미지의 핸들일 뿐이고.
	BitMap = static_cast<HBITMAP>(ImageHandle);

	// 없던 권한을 새롭게 만들어야 한다.
	// Window에서 얻어온 DC
	ImageDC = CreateCompatibleDC(nullptr);
	// 이미지의 수정 권한을 만들어 내고

	// ImageDC 권한에
	// BitMap 2차원의 색깔 집합을 연결해라.
	// 사실 이미 만들어지자마자 내부에 1,1 이미지와 연결되어있고
	// 내가 로드한 이미지를 그 1,1짜리를 밀어내고 교체하는 작업을 하는데.
	// 이 함수의 리턴값이 기존에 연결되어있던 애를 리턴해주는것.
	OldBitMap = static_cast<HBITMAP>(SelectObject(ImageDC, BitMap));

	ScaleCheck();
}

void GameEngineTexture::ScaleCheck()
{
	GetObject(BitMap, sizeof(BITMAP), &Info);

	BITMAP OldInfo;

	GetObject(OldBitMap, sizeof(BITMAP), &OldInfo);
}