#include "PlayLevel.h"
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineWindow.h>


// Contents
#include "Player.h"
#include "BackGround.h"

PlayLevel::PlayLevel()
{
}

PlayLevel::~PlayLevel()
{
}

void PlayLevel::Start()
{
	// ResourcesManager::GetInst().TextureLoad("AAA.Png", ���);

	// �÷��� ������ ���������.
	// �� �������� ���� �־����?
	// �÷��̾� �����
	// �ʸ����
	// ���� �����
	// ����

	// �ڱ� ���Ǵ�� ����ڴٴ� ���̰� xxxxx
	// Player* NewPlayer = new Player();

	BackGround* Back = CreateActor<BackGround>();
	Back->Init("CandyChateau.bmp");

	LevelPlayer = CreateActor<Player>();
}


void PlayLevel::Update(float _Delta)
{
	if (true == GameEngineInput::IsDown('O'))
	{
		GameEngineCore::ChangeLevel("TitleLevel");
	}

	// GameEngineCore::ChangeLevel("TitleLevel");
}
void PlayLevel::Render()
{
}
void PlayLevel::Release()
{
}

void PlayLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	if (nullptr == LevelPlayer)
	{
		MsgBoxAssert("�÷��̾ ���������� �ʾҽ��ϴ�");
	}

	float4 WinScale = GameEngineWindow::MainWindow.GetScale();
	//LevelPlayer->SetPos(WinScale.Half());
	// 0 0
	// x y
	GetMainCamera()->SetPos(LevelPlayer->GetPos() - WinScale.Half());

}

void PlayLevel::LevelEnd(GameEngineLevel* _NextLevel)
{

}

// ========= ���� ���� �ּ� ===========

//Start() - �� �����, �÷��̾� ����� ����.

//LevelStart() - �� ������ ī�޶� ������ ����