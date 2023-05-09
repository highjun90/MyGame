#pragma once
#include <string>
#include <Windows.h>
#include <GameEngineBase/GameEngineMath.h>

// ���� :
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


// ============= ���� ���� �ּ� ================


//HBITMAP - ��Ʈ�� �ڵ�. ��·�� �ڵ���. typedef HANDLE HBITMAP;
//HDC     - �굵 ��� �ڵ�.  typedef HANDLE HDC;
//typedef struct tagBITMAP     //BITMAP ����ü
//{
//	LONG        bmType;        //��Ʈ������
//	LONG        bmWidth;       //�ʺ�
//	LONG        bmHeight;      //����
//	LONG        bmWidthBytes;  //(���ؾȵ�) �� �˻� ���� ����Ʈ ���Դϴ�. �ý��ۿ��� ��Ʈ���� ��Ʈ ���� �ܾ� ���� �迭�� �����Ѵٰ� �����ϱ� ������ �� ���� 2�� ���� �� �־�� �մϴ�.
//	WORD        bmPlanes;      //������� ��
//	WORD        bmBitsPixel;   //�ȼ��� ���� ��Ÿ���µ� �ʿ��� ��Ʈ��
//	LPVOID      bmBits;        //(���ؾȵ�) ��Ʈ���� ��Ʈ�� ��ġ�� ���� ������. 
//} BITMAP,