#pragma once
#include "GameEngineObject.h"
#include <GameEngineBase/GameEngineMath.h>
#include <string>

// ���� :
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
//// ============ ���� ���� �ּ� ================
//
//// class GameEngineWindowTexture* Texture;      //�������� ���� �̹��� 
//GameEngineActor* Master;                        //�������� ���� (GameEngineActor)
//bool ScaleCheck;
//
//
//float4 RenderPos;                               //�� ������ Actor�� ��ġ�� ���Ҷ� ���� ��ȭ��.
//float4 RenderScale;                             //ȭ�鿡 �׷��� �̹��� ��ü(copyscale�� �ٸ��� ������ �޶�������)
//
//float4 CopyPos;                                 //���� �ҷ��� �̹���(texture)��ü�� ��ġ�� ������
//float4 CopyScale;
//
//void Render(class GameEngineCamera* _Camera);