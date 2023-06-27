#include "MrDark.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "ContentsEnum.h"
#include <GameEngineCore/ResourcesManager.h>
#include "Player.h"


MrDark::MrDark()
{

}

MrDark::~MrDark()
{

}


void MrDark::Update(float _Delta)
{
	// Player::MainPlayer = nullptr;

	//float4 Dir = Player::GetMainPlayer()->GetPos() - GetPos();

	//Dir.Normalize();

	// Dir <= 거리가 일정하지 않다는 게 문제에요.

	// Dir *= 0.1f;

	//AddPos(Dir * _Delta * 300.0f);

	

	if (MainRenderer->GetCurFrame() >= 13)
	{
		AddPos({ 0, -10 });
	}


	if (GetLiveTime() > 2.0f)
	{
		this->Off();
	}

	
}

void MrDark::Start()
{
	SetPos({ 1750 , 2690 });
	

	if (false == ResourcesManager::GetInst().IsLoadTexture("MrDark.bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Texture\\Player\\");
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("MrDark.bmp"));

		//미스터다크 스프라이트 등록
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("MrDark.bmp"), 5, 4);
	}

	{
		MainRenderer = CreateRenderer(100);

		//미스터 다크 애니메이션 등록
		MainRenderer->CreateAnimation("MrDarkAnimation", "MrDark.bmp", 0, 18, 0.05f, false);
		//MainRenderer->SetRenderScaleToTexture();

		MainRenderer->ChangeAnimation("MrDarkAnimation");
	}


	//ChanageState(PlayerState::Idle);
	//Dir = PlayerDir::Right;

}

void MrDark::Render(float _Delta)
{
	std::string Text = "";

	Text += "플레이어 테스트 값 : ";
	Text += std::to_string(0);

	HDC dc = GameEngineWindow::MainWindow.GetBackBuffer()->GetImageDC();
	//TextOutA(dc, 2, 3, Text.c_str(), Text.size());

}