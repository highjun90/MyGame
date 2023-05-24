#include "PlayLevel.h"
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include "Monster.h"
#include "PlayUIManager.h"


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

	if (false == ResourcesManager::GetInst().IsLoadTexture("Test.Bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");

		GameEnginePath FolderPath = FilePath;

		FilePath.MoveChild("ContentsResources\\Texture\\");
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("StageTestPixel.bmp"));
	}



	// ResourcesManager::GetInst().TextureLoad("AAA.Png", 경로);

	// 플레이 레벨이 만들어졌다.
	// 이 레벨에는 뭐가 있어야지?
	// 플레이어 만들고
	// 맵만들고
	// 몬스터 만들고
	// 액터

	// 자기 임의대로 만들겠다는 것이고 xxxxx
	// Player* NewPlayer = new Player();

	BackGroundPtr = CreateActor<BackGround>();
	BackGroundPtr->Init("StageTest.Bmp", "StageTestPixel.bmp");

	LevelPlayer = CreateActor<Player>();
	LevelPlayer->SetGroundTexture("StageTestPixel.bmp");

	CreateActor<PlayUIManager>();

}


void PlayLevel::Update(float _Delta)
{
	if (true == GameEngineInput::IsDown('O'))
	{
		GameEngineCore::ChangeLevel("TitleLevel");
	}

	if (true == GameEngineInput::IsDown('J'))
	{
		BackGroundPtr->SwitchRender();
	}

	//원본 선생님 몬스터 만들기
	/*if (3.0f <= GetLiveTime() )
	{
		Monster* NewMonster = CreateActor<Monster>();
		ResetLiveTime();
	}*/

	//임의로 만든 몬스터 1개 만들기, 3초뒤 1마리 나오게
	if (3.0f <= GetLiveTime() && true == DarkMonsterCreate)
	{
		Monster* NewMonster = CreateActor<Monster>();
		DarkMonsterCreate = false;
	}


	// GameEngineCore::ChangeLevel("TitleLevel");
}
void PlayLevel::Release() 
{
}

void PlayLevel::LevelStart(GameEngineLevel* _PrevLevel) 
{
	if (nullptr == LevelPlayer)
	{
		MsgBoxAssert("플레이어를 세팅해주지 않았습니다");
	}

	LevelPlayer->SetGroundTexture("StageTestPixel.bmp");

	//float4 WinScale = GameEngineWindow::MainWindow.GetScale();
	////LevelPlayer->SetPos(WinScale.Half());
	//// 0 0
	//// x y
	//GetMainCamera()->SetPos(LevelPlayer->GetPos() - WinScale.Half());

}

void PlayLevel::LevelEnd(GameEngineLevel* _NextLevel)
{

}