#pragma once
#include "PlayActor.h"

enum class PlayerState 
{
	Idle,
	Run,
	Jump,
	Sprint,
	Max, // �Ϲ������� ������� �ʴ� ��.
};

enum class PlayerDir
{
	Right,
	Left,
	Up,
	Down,
	Max,
};

// ���� :
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

protected:
	void StateUpdate(float _Delta);

	void IdleStart();
	void IdleUpdate(float _Delta);


	void RunStart();
	void RunUpdate(float _Delta);

	void SprintStart();
	void SprintUpdate(float _Delta);
	// Ŭ������ ���� �ǰ�.
	
	

	void JumpStart();
	void JumpUpdate(float _Delta);

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

	////////////////////// DebugValue
	float4 LeftCheck = { -100.0f, -50.0f };
	float4 RightCheck = { 100.0f, -50.0f };
	float4 DownCheck = { 0, 100.0f };
};

