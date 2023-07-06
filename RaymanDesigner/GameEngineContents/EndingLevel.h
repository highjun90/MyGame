#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEnginePlatform/GameEngineSound.h>
#include "FadeObject.h"

// Ό³Έν :
class EndingLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	EndingLevel();
	~EndingLevel();

	// delete Function
	EndingLevel(const EndingLevel& _Other) = delete;
	EndingLevel(EndingLevel&& _Other) noexcept = delete;
	EndingLevel& operator=(const EndingLevel& _Other) = delete;
	EndingLevel& operator=(EndingLevel&& _Other) noexcept = delete;


	void BGMStop()
	{
		if (SoundPlaying == true)
		{
			BGMPlayer.Stop();
		}
	}


protected:
	void LevelStart(GameEngineLevel* _PrevLevel) override;

private:
	void Start() override;
	void Update(float _Delta) override;

	class BackGround* BackGroundPtr = nullptr;
	FadeObject* FObject = nullptr;

	GameEngineSoundPlayer BGMPlayer;
	bool SoundPlaying = false;
};

