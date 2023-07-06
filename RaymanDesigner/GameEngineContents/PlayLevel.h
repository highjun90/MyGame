#pragma once
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEnginePlatform/GameEngineSound.h>

#include "Player.h"
#include "FadeObject.h"
#include "MrDark.h"
#include "DarkRayman.h"
#include "GoalPoint.h"
#include "BlueMarble.h"

// 설명 :
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

	//레벨 끝났는데 다시 호출했는지
	bool RecallLevel = false;

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

		if (RestartTime2 - RestartTime1 > 2.0 && false == FObjectRestart)
		{
			FObjectRestart = true;

			FObject->SetValue(0.0f);
			FObject->SetFade(false); //밝은데 어두워짐
		}


		if (RestartTime2 - RestartTime1 > 5.0)
		{
			LevelPlayer->Restart();  //이 줄이 더이상 ResetGame() 함수에 안들어오게함 
			MrDarkPtr->Restart();
			DarkRaymanPtr->Restart();

			

			//지금 나도 리스타트할꺼 있으면 한다
			Restart();
		}	
	}

	void LevelEnd()
	{
		LevelEnd_Time2 = GetLiveTime();
		if (LevelEnd_Time2 - LevelEnd_Time1 > 4.0 && false == FobjectLevelEnd)
		{
			FobjectLevelEnd = true;

			//ResetGame 어두워지는 효과 두번 겹치는거 방지 (목숨다죽은 상황)
			if (LevelPlayer->GetTotalLife() >= 0)
			{
				FObject->SetValue(0.0f);
				FObject->SetFade(false); //밝은데 어두워짐
			}	
		}

		if (LevelEnd_Time2 - LevelEnd_Time1 > 6.0)
		{
			//음악끄고 모든요소 초기화
			BGMPlayerToPlayLevel.Stop();

			LevelPlayer->Restart();
			MrDarkPtr->Restart();
			DarkRaymanPtr->Restart();

			LevelPlayer->SetVictoryEnd(false);
			LevelPlayer->SetTotalLife(5);
			LevelEnd_Time1 = 0;

			RecallLevel = true;
			GameEngineCore::ChangeLevel("EndingLevel");
			//엔딩레벨로 넘어가야함
		}
	}


	void Restart();
	


	std::vector<BlueMarble* > Marbles;
	int RemainedMarble = 50;

	void AddRemainedMarble(int _num)
	{
		RemainedMarble += _num;
	}
	int GetRemainedMarble()
	{
		return RemainedMarble;
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

	//레이맨 죽어서 재시작시 일정시간이후 다시 시작하는 작업하는데, ResetGame 함수의 Getlivetime 기록용
	float RestartTime1 = 0;
	float RestartTime2 = 0;

	//완전승리 또는 완전패배(목숨다잃음)상황에서 쓰일 GetLiveTime
	float LevelEnd_Time1 = 0;
	float LevelEnd_Time2 = 0;

	//임의로 추가한 멤버변수
	bool CreateDarkRayman = false;
	bool CreateMrDark = true;
	FadeObject* FObject = nullptr;
	bool FObjectRestart = false;
	bool FobjectLevelEnd = false;

	
	//bool FObjectStart = true;
};

