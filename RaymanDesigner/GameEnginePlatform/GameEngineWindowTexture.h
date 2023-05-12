#pragma once
#include <string>
#include <Windows.h>
#include <GameEngineBase/GameEngineMath.h>

// 설명 :
class GameEngineWindowTexture
{
public:
	// constrcuter destructer
	GameEngineWindowTexture();
	~GameEngineWindowTexture();

	// delete Function
	GameEngineWindowTexture(const GameEngineWindowTexture& _Other) = delete;
	GameEngineWindowTexture(GameEngineWindowTexture&& _Other) noexcept = delete;
	GameEngineWindowTexture& operator=(const GameEngineWindowTexture& _Other) = delete;
	GameEngineWindowTexture& operator=(GameEngineWindowTexture&& _Other) noexcept = delete;

	void ResLoad(const std::string& _Path);
	void ResCreate(HDC  _ImageDC)
	{
		ImageDC = _ImageDC;
		ScaleCheck();
	}

	void ResCreate(const float4& _Scale);

	HDC GetImageDC()
	{
		return ImageDC;
	}

	float4 GetScale();

	void BitCopy(GameEngineWindowTexture* _CopyTexture, const float4& _Pos);
	void BitCopy(GameEngineWindowTexture* _CopyTexture, const float4& _Pos, const float4& _Scale);

	void TransCopy(GameEngineWindowTexture* _CopyTexture, const float4& _Pos, const float4& _Scale, const float4& _OtherPos, const float4& _OtherScale, int _TransColor = RGB(255, 0, 255));

protected:

private:
	HBITMAP BitMap;
	HBITMAP OldBitMap;
	HDC ImageDC;

	BITMAP Info;

	void ScaleCheck();
};


// ============= 최종 삭제 주석 ================


//HBITMAP - 비트맵 핸들. 어쨌든 핸들임. typedef HANDLE HBITMAP;
//HDC     - 얘도 어쩄든 핸들.  typedef HANDLE HDC;
//typedef struct tagBITMAP     //BITMAP 구조체
//{
//	LONG        bmType;        //비트맵형식. 이 값은 항상 0을 대입해야함.
//	LONG        bmWidth;       //너비 (가로 픽셀수)
//	LONG        bmHeight;      //높이
//	LONG        bmWidthBytes;  //비트맵의 가로 한줄을 표현하는데 필요한 바이트 수. ( bmWidth * (bmBitsPixel / 8) )
//	WORD        bmPlanes;      //색평면의 수 (보통 다 1. 과거 16비트 색을 사용하는 경우엔 색플랜을 4개쓰는 때도 있었음)
//	WORD        bmBitsPixel;   //한 픽셀의 색을 나타내는데 필요한 비트수 (32비트 색상을 사용하는 경우 이 변수의 값은 32)
//	LPVOID      bmBits;        //비트맵 이미지 패턴이 저장되있는 메모리의 시작주소
//} BITMAP,