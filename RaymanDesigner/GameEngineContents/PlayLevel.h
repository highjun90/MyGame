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

	//���� �����µ� �ٽ� ȣ���ߴ���
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
			FObject->SetFade(false); //������ ��ο���
		}


		if (RestartTime2 - RestartTime1 > 5.0)
		{
			LevelPlayer->Restart();  //�� ���� ���̻� ResetGame() �Լ��� �ȵ������� 
			MrDarkPtr->Restart();
			DarkRaymanPtr->Restart();

			

			//���� ���� ����ŸƮ�Ҳ� ������ �Ѵ�
			Restart();
		}	
	}

	void LevelEnd()
	{
		LevelEnd_Time2 = GetLiveTime();
		if (LevelEnd_Time2 - LevelEnd_Time1 > 4.0 && false == FobjectLevelEnd)
		{
			FobjectLevelEnd = true;

			//ResetGame ��ο����� ȿ�� �ι� ��ġ�°� ���� (��������� ��Ȳ)
			if (LevelPlayer->GetTotalLife() >= 0)
			{
				FObject->SetValue(0.0f);
				FObject->SetFade(false); //������ ��ο���
			}	
		}

		if (LevelEnd_Time2 - LevelEnd_Time1 > 6.0)
		{
			//���ǲ��� ����� �ʱ�ȭ
			BGMPlayerToPlayLevel.Stop();

			LevelPlayer->Restart();
			MrDarkPtr->Restart();
			DarkRaymanPtr->Restart();

			LevelPlayer->SetVictoryEnd(false);
			LevelPlayer->SetTotalLife(5);
			LevelEnd_Time1 = 0;

			RecallLevel = true;
			GameEngineCore::ChangeLevel("EndingLevel");
			//���������� �Ѿ����
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

	//���̸� �׾ ����۽� �����ð����� �ٽ� �����ϴ� �۾��ϴµ�, ResetGame �Լ��� Getlivetime ��Ͽ�
	float RestartTime1 = 0;
	float RestartTime2 = 0;

	//�����¸� �Ǵ� �����й�(���������)��Ȳ���� ���� GetLiveTime
	float LevelEnd_Time1 = 0;
	float LevelEnd_Time2 = 0;

	//���Ƿ� �߰��� �������
	bool CreateDarkRayman = false;
	bool CreateMrDark = true;
	FadeObject* FObject = nullptr;
	bool FObjectRestart = false;
	bool FobjectLevelEnd = false;

	
	//bool FObjectStart = true;
};

