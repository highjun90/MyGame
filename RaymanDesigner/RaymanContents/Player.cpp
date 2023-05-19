#include "Player.h"
#include "ContentsEnum.h"
#include <Windows.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEnginePath.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>
#include "Bullet.h"
#include <GameEnginePlatform/GameEngineInput.h>

Player::Player()
{
}

Player::~Player()
{
}


void Player::Start()
{
	if (false == ResourcesManager::GetInst().IsLoadTexture("Test.Bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");

		GameEnginePath FolderPath = FilePath;

		FilePath.MoveChild("ContentsResources\\Texture\\Player\\");

		// ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Left_Player.bmp"));

		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Left_Player.bmp"), 5, 17);
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Right_Player.bmp"), 5, 17);


		FolderPath.MoveChild("ContentsResources\\Texture\\");
		ResourcesManager::GetInst().CreateSpriteFolder("FolderPlayer", FolderPath.PlusFilePath("FolderPlayer"));

		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Test.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("HPBar.bmp"));
	}

	{
		MainRenderer = CreateRenderer(RenderOrder::Play);
		// MainRenderer->SetRenderScale({ 200, 200 });
		// MainRenderer->SetSprite("Left_Player.bmp");


		MainRenderer->CreateAnimation("Left_Idle", "Left_Player.bmp", 0, 2, 0.1f, true);
		MainRenderer->CreateAnimation("Right_Idle", "Right_Player.bmp", 0, 2, 0.1f, true);

		MainRenderer->CreateAnimation("Left_Run", "Left_Player.bmp", 3, 6, 0.1f, true);
		MainRenderer->CreateAnimation("Right_Run", "Right_Player.bmp", 3, 6, 0.1f, true);

		MainRenderer->ChangeAnimation("Left_Idle");
		MainRenderer->SetRenderScaleToTexture();
	}

	{
		GameEngineRenderer* Ptr = CreateRenderer("HPBar.bmp", RenderOrder::Play);
		Ptr->SetRenderPos({ 0, -100 });
		Ptr->SetRenderScale({ 200, 40 });
		Ptr->SetTexture("HPBar.bmp");
	}

	// State = PlayerState::Idle;

	ChanageState(PlayerState::Idle);

	// GetLevel()->GetMainCamera()->SetPos({ -WinScale.hX(), -WinScale.hY() });
}

void Player::Update(float _Delta)
{
	StateUpdate(_Delta);
}

void Player::StateUpdate(float _Delta)
{
	switch (State)
	{
	case PlayerState::Idle:
		return IdleUpdate(_Delta);
	case PlayerState::Run:
		return RunUpdate(_Delta);
	default:
		break;
	}

}

void Player::ChanageState(PlayerState _State)
{
	if (_State != State)
	{
		switch (_State)
		{
		case PlayerState::Idle:
			IdleStart();
			break;
		case PlayerState::Run:
			RunStart();
			break;
		default:
			break;
		}
	}

	State = _State;
}



// ==삭제 ==

// FilePath는 말그대로 이미지 한장(파일하나) 경로.  FolderPath는 이미지 폴더(파일여러개)경로