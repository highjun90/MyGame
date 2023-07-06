#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineSprite.h>
#include <GameEnginePlatform/GameEngineWindow.h>

#include "Player.h"

// Ό³Έν :
class PlayUIManager : public GameEngineActor
{
public:
	static PlayUIManager* UI;

public:
	// constrcuter destructer
	PlayUIManager();
	~PlayUIManager();

	// delete Function
	PlayUIManager(const PlayUIManager& _Other) = delete;
	PlayUIManager(PlayUIManager&& _Other) noexcept = delete;
	PlayUIManager& operator=(const PlayUIManager& _Other) = delete;
	PlayUIManager& operator=(PlayUIManager&& _Other) noexcept = delete;

	void SetRaymanPtr(Player* _RaymanPtr)
	{
		Ui_RaymanPtr = _RaymanPtr;
	}

	Player* GetRaymanPtr()
	{
		return Ui_RaymanPtr;
	}

protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	GameEngineRenderer* UI_LifeAndHp = nullptr;
	GameEngineRenderer* UI_LifeNumber1 = nullptr;
	GameEngineRenderer* UI_LifeNumber2 = nullptr;

	GameEngineRenderer* UI_Marble = nullptr;
	GameEngineRenderer* UI_MarbleNumber1 = nullptr;
	GameEngineRenderer* UI_MarbleNumber2 = nullptr;

	GameEngineSprite* UI_Numbers = nullptr;

	Player* Ui_RaymanPtr = nullptr;
};

