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
	}

	HDC GetImageDC()
	{
		return ImageDC;
	}

	float4 GetScale();

	void BitCopy(GameEngineWindowTexture* _CopyTexture, const float4& Pos);
	void BitCopy(GameEngineWindowTexture* _CopyTexture, const float4& Pos, const float4& Scale);

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
//	LONG        bmType;        //비트맵형식
//	LONG        bmWidth;       //너비
//	LONG        bmHeight;      //높이
//	LONG        bmWidthBytes;  //(이해안됨) 각 검사 줄의 바이트 수입니다. 시스템에서 비트맵의 비트 값이 단어 정렬 배열을 형성한다고 가정하기 때문에 이 값은 2로 나눌 수 있어야 합니다.
//	WORD        bmPlanes;      //색평면의 수
//	WORD        bmBitsPixel;   //픽셀의 색을 나타내는데 필요한 비트수
//	LPVOID      bmBits;        //(이해안됨) 비트맵의 비트값 위치에 대한 포인터. 
//} BITMAP,