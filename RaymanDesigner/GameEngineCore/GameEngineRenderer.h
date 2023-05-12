#pragma once
#include "GameEngineObject.h"
#include <GameEngineBase/GameEngineMath.h>
#include <string>

// 설명 :
class GameEngineActor;
class GameEngineWindowTexture;
class GameEngineRenderer : public GameEngineObject
{
	friend class GameEngineCamera;
	friend class GameEngineActor;

public:
	// constrcuter destructer
	GameEngineRenderer();
	~GameEngineRenderer();

	// delete Function
	GameEngineRenderer(const GameEngineRenderer& _Other) = delete;
	GameEngineRenderer(GameEngineRenderer&& _Other) noexcept = delete;
	GameEngineRenderer& operator=(const GameEngineRenderer& _Other) = delete;
	GameEngineRenderer& operator=(GameEngineRenderer&& _Other) noexcept = delete;

	void SetTexture(const std::string& _Name);

	void SetRenderPos(const float4& _Value)
	{
		RenderPos = _Value;
	}


	void SetRenderScale(const float4& _Value)
	{
		RenderScale = _Value;
		ScaleCheck = true;
	}

	void SetCopyPos(const float4& _Value)
	{
		CopyPos = _Value;
	}

	void SetCopyScale(const float4& _Value)
	{
		CopyScale = _Value;
	}

	void SetRenderScaleToTexture();

	bool IsDeath() override;

protected:

private:
	GameEngineActor* Master = nullptr;
	GameEngineWindowTexture* Texture = nullptr;

	bool ScaleCheck = false;


	float4 RenderPos;
	float4 RenderScale;

	float4 CopyPos;
	float4 CopyScale;

	void Render(class GameEngineCamera* _Camera);
};



//
//// ============ 최종 삭제 주석 ================
//
//// class GameEngineWindowTexture* Texture;      //렌더러가 가진 이미지 
//GameEngineActor* Master;                        //렌더러의 주인 (GameEngineActor)
//bool ScaleCheck;
//
//
//float4 RenderPos;                               //이 변수는 Actor의 위치가 변할때 더할 변화값.
//float4 RenderScale;                             //화면에 그려질 이미지 자체(copyscale과 다르면 비율이 달라지겠지)
//
//float4 CopyPos;                                 //내가 불러올 이미지(texture)자체의 위치와 스케일
//float4 CopyScale;
//
//void Render(class GameEngineCamera* _Camera);