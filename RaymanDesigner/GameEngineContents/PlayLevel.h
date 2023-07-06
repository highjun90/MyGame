#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEnginePlatform/GameEngineSound.h>

#include "Player.h"
#include "FadeObject.h"
#include "MrDark.h"
#include "DarkRayman.h"
#include "GoalPoint.h"

// ���� :
class DarkRayman;
class PlayLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	PlayLevel();
	~PlayLevel();

	// delete Function
	PlayLevel(const PlayLevel& _Other) = delete;
	PlayLevel(PlayLevel&& _Other) noexcept = delete;
	PlayLevel& operator=(const PlayLevel& _Other) = delete;
	PlayLevel& operator=(PlayLevel&& _Other) noexcept = delete;

	GameEngineSoundPlayer* GetBGMPlayerToPlayLevel()
	{
		return &BGMPlayerToPlayLevel;
	}

	DarkRayman* GetDarkRaymanPtr()
	{
		return DarkRaymanPtr;
	}

	void ResetGame()
	{
		RestartTime2 = GetLiveTime();

		if (RestartTime2 - RestartTime1 > 5.0)
		{
			LevelPlayer->Restart();
			MrDarkPtr->Restart();
			DarkRaymanPtr->Restart();

			RestartTime1 = 0;
		}	
	}

protected:
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

private:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;

	class BackGroundImage* BackGroundImagePtr = nullptr;
	class BackGround* BackGroundPtr = nullptr;
	class BackGround* BackGroundDivisionPtr[5];
	
	 Player* LevelPlayer = nullptr;
	class DarkRayman* DarkRaymanPtr = nullptr;
	class MrDark* MrDarkPtr = nullptr;
	class GoalPoint* GoalPointPtr = nullptr;
	class PlayUIManager* PlayUIManagerPtr = nullptr;


	GameEngineSoundPlayer BGMPlayerToPlayLevel;

	//���̸� �׾ ����۽� �����ð����� �ٽ� �����ϴ� �۾��ϴµ�, Getlivetime ��Ͽ�
	float RestartTime1 = 0;
	float RestartTime2 = 0;

	//���Ƿ� �߰��� �������
	bool CreateDarkRayman = false;
	bool CreateMrDark = true;
	FadeObject* FObject = nullptr;
};

