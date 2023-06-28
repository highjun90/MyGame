#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEnginePlatform/GameEngineSound.h>

// 설명 :
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

	void TestLevelFunction()
	{

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
	
	class Player* LevelPlayer = nullptr;

	GameEngineSoundPlayer BGMPlayerToPlayLevel;

	//임의로 추가한 멤버변수
	bool CreateDarkRayman = true;
	bool CreateMrDark = true;
};

