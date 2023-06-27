#pragma once
#include "PlayActor.h"
#include <GameEnginePlatform/GameEngineSound.h>

#include "DarkRayman.h"

enum class PlayerState 
{
	Idle,
	Run,
	Jump,
	JumpHold,
	Sprint,
	Victory,
	Debugmode,
	Max, // 일반적으로 사용하지 않는 값.
};

enum class PlayerDir
{
	Right,
	Left,
	//Up,
	//Down,
	Max,
};

// 설명 :
class Player : public PlayActor
{
private:
	static Player* MainPlayer;

public:
	static Player* GetMainPlayer() 
	{
		return MainPlayer;
	}


public:
	// constrcuter destructer
	Player();
	~Player();

	// delete Function
	Player(const Player& _Other) = delete;
	Player(Player&& _Other) noexcept = delete;
	Player& operator=(const Player& _Other) = delete;
	Player& operator=(Player&& _Other) noexcept = delete;

	GameEngineRenderer* MainRenderer = nullptr;

	void SetJumpSpeed(float _Speed)
	{
		JumpSpeed = _Speed;
	}

	float GetJumpSpeed()
	{
		return JumpSpeed;
	}

	void CameraPosToDir();

	float DebugSpeed = 300.0f;
	bool DebugMode = false;
	float4 DebugStartPoint = float4::ZERO;


protected:
	void StateUpdate(float _Delta);

	void IdleStart();
	void IdleUpdate(float _Delta);


	void RunStart();
	void RunUpdate(float _Delta);

	void SprintStart();
	void SprintUpdate(float _Delta);

	void JumpStart();
	void JumpUpdate(float _Delta);

	void JumpHoldStart();
	void JumpHoldUpdate(float _Delta);

	void DebugmodeStart();
	void DebugmodeUpdate(float _Delta);

	void VictoryStart();
	void VIctoryUpdate(float _Delta);

	void ChanageState(PlayerState State);

	PlayerState State = PlayerState::Max;
	PlayerDir Dir = PlayerDir::Right;
	std::string CurState = "";
	GameEngineRenderer* HPRender;

	int TestValue = 0;

	GameEngineCollision* BodyCollsion = nullptr;

	void DirCheck();

	void ChangeAnimationState(const std::string& _StateName);

private:
	void LevelStart() override; 

	void Start() override;
	void Update(float _Delta) override;
	void Render(float _Delta) override;

	float JumpSpeed = 300.0f;

	DarkRayman* DarkRaymanToPlayer = nullptr;

	GameEngineSoundPlayer* BGMPlayerToPlayer = nullptr;  //PlayLevel에서 BGMPlayer 가져올 포인터. Player_State 디버그 모드때 이용.
	bool SoundPlaying = true;

	////////////////////// DebugValue
	float4 LeftCheck = { -50.0f, -50.0f };
	float4 RightCheck = { 50.0f, -50.0f };
	float4 DownCheck = { 0, 90.0f };


};

