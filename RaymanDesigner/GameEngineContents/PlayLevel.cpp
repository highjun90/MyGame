#include "PlayLevel.h"
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/TileMap.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineSound.h>
#include "Monster.h"
#include "MrDark.h"
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

	if (false == ResourcesManager::GetInst().IsLoadTexture("CandyChateauDebug.Bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");

		GameEnginePath FolderPath = FilePath;

		FilePath.MoveChild("ContentsResources\\Texture\\");
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("CandyChateauDebug.bmp"));

		//배경이 타일맵 일때
		//ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Tile.bmp"));
		//ResourcesManager::GetInst().CreateSpriteSheet("Tile.bmp", 24, 40);
	}


	if (nullptr == GameEngineSound::FindSound("CandyChateauBGM.ogg"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Sound\\");

		GameEngineSound::SoundLoad(FilePath.PlusFilePath("CandyChateauBGM.ogg"));
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

	/*BackGroundPtr = CreateActor<BackGround>();
	BackGroundPtr->Init("CandyChateauExtended01.Bmp", "CandyChateauDebug.bmp");*/

	BackGroundPtr = CreateActor<BackGround>();
	BackGroundPtr->Init("testnow.Bmp", "CandyChateauDebug.bmp");

	//배경이 타일 맵일때
	/*TileMap* TileObject = CreateActor<TileMap>();

	TileObject->CreateTileMap("Tile.bmp", 20, 20, { 50, 50 }, 0);
	for (size_t y = 0; y < 20; y++)
	{
		for (size_t x = 0; x < 20; x++)
		{
			TileObject->SetTile(x, y, 0);
		}
	}*/

	LevelPlayer = CreateActor<Player>();
	LevelPlayer->SetGroundTexture("CandyChateauDebug.bmp");

	CreateActor<PlayUIManager>();
	CreateActor<MrDark>();
}


void PlayLevel::Update(float _Delta)
{
	if (true == GameEngineInput::IsDown('O'))
	{
		GameEngineCore::ChangeLevel("TitleLevel");
	}

	if (true == GameEngineInput::IsDown(VK_F1))
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
	if (3.0f <= GetLiveTime() && true == CreateDarkRayman)
	{
		Monster* NewMonster = CreateActor<Monster>();
		CreateDarkRayman = false;
	}

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

	GameEngineSound::SoundPlay("CandyChateauBGM.ogg");

	LevelPlayer->SetGroundTexture("CandyChateauDebug.bmp");

	//float4 WinScale = GameEngineWindow::MainWindow.GetScale();
	////LevelPlayer->SetPos(WinScale.Half());
	//// 0 0
	//// x y
	//GetMainCamera()->SetPos(LevelPlayer->GetPos() - WinScale.Half());

}

void PlayLevel::LevelEnd(GameEngineLevel* _NextLevel)
{

}