#include "Player.h"
#include <Windows.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEnginePath.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/ResourcesManager.h>

Player::Player()
{
}

Player::~Player()
{
}


void Player::Start()
{


	if (false == ResourcesManager::GetInst().IsLoadTexture("Player_Idle.Bmp"))
	{
		// 무조건 자동으로 현재 실행중인 위치가 된다.
		GameEnginePath FilePath;

		FilePath.GetCurrentPath();

		ResourcesManager::GetInst().TextureLoad("Player_Idle.Bmp");
	}



	SetPos({ 200, 200 });
	SetScale({ 100, 100 });
}

void Player::Update(float _Delta)
{
	// 아주 어리석은 절대로 아마 안될 계산을 하는것이다.
	// Player->GetPos() == Monster->GetPos();
	// float Time = GameEngineTime::MainTimer.GetDeltaTime();

	AddPos({ 100.0f * _Delta, 0.0f });
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