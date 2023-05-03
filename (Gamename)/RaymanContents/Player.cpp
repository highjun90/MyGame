#include "Player.h"
#include <Windows.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEnginePlatform/GameEngineWindow.h>

Player::Player()
{
}

Player::~Player()
{
}


void Player::Start()
{
	SetPos({ 200, 200 });
	SetScale({ 100, 100 });
}

void Player::Update()
{
	// 아주 어리석은 절대로 아마 안될 계산을 하는것이다.
	// Player->GetPos() == Monster->GetPos();

	GameEngineTime::MainTimer;

	float Time = GameEngineTime::MainTimer.GetDeltaTime();

	AddPos({ 100.0f, 0.0f });
}

void Player::Render()
{
	//SetPos({ 200, 200 });
	//SetScale({ 100, 100 });

	HDC WindowDC = GameEngineWindow::MainWindow.GetHDC();

	Rectangle(WindowDC,
		GetPos().iX() - GetScale().ihX(),
		GetPos().iY() - GetScale().ihY(),
		GetPos().iX() + GetScale().ihX(),
		GetPos().iY() + GetScale().ihY()
	);

	// 그려야죠?
}

void Player::Release()
{
}