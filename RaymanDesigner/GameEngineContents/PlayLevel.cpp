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
#include "GoalPoint.h"
#include "PlayUIManager.h"
#include "FadeObject.h"

// Contents
#include "Player.h"
#include "BackGround.h"
#include "BackGroundImage.h"
#include "GlobalValue.h"


PlayLevel::PlayLevel()
{
}

PlayLevel::~PlayLevel()
{
}

void PlayLevel::Start() 
{
	//원본 
	////사운드세팅
	//if (nullptr == GameEngineSound::FindSound("CandyChateauBGM.ogg"))
	//{
	//	GameEnginePath FilePath;
	//	FilePath.SetCurrentPath();
	//	FilePath.MoveParentToExistsChild("ContentsResources");
	//	FilePath.MoveChild("ContentsResources\\Sound\\");

	//	GameEngineSound::SoundLoad(FilePath.PlusFilePath("CandyChateauBGM.ogg"));
	//}

	////레드컬러맵세팅 원본
	//if (false == ResourcesManager::GetInst().IsLoadTexture("MapRedColor.Bmp"))
	//{
	//	GameEnginePath FilePath;
	//	FilePath.SetCurrentPath();
	//	FilePath.MoveParentToExistsChild("ContentsResources");

	//	GameEnginePath FolderPath = FilePath;

	//	FilePath.MoveChild("ContentsResources\\Texture\\");
	//	ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("MapRedColor.bmp"));

	//	//배경이 타일맵 일때
	//	//ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Tile.bmp"));
	//	//ResourcesManager::GetInst().CreateSpriteSheet("Tile.bmp", 24, 40);
	//}



	////배경이미지
	//BackGroundImagePtr = CreateActor<BackGroundImage>();
	//BackGroundImagePtr->Init("CandyChateau1200x800.Bmp");

	////배경타일
	//BackGroundPtr = CreateActor<BackGround>();
	//BackGroundPtr->Init("CandyChateauTile.Bmp", "MapRedColor.bmp");

	//// 카메라 오버 막는데 필요한 데이터인 맵스케일 등록. 맵을 바꾸면 그 맵에 맞춰서 카메라가 나가지 않음
	//GameEngineWindowTexture* Ptr = ResourcesManager::GetInst().FindTexture("CandyChateauTile.Bmp");
	//if (nullptr == Ptr)
	//{
	//	MsgBoxAssert("맵 텍스처를 알수가 없습니다.");
	//}
	//GlobalValue::MapScale = Ptr->GetScale();

	//
	//LevelPlayer = CreateActor<Player>();
	//LevelPlayer->SetGroundTexture("MapRedColor.bmp");

	//{
	//	FadeObject* FObject = CreateActor<FadeObject>();
	//}

	//CreateActor<PlayUIManager>();
	//CreateActor<MrDark>();
	//CreateActor<GoalPoint>();

	// 컬러맵 테스트용 코드
	
	//사운드세팅
	if (nullptr == GameEngineSound::FindSound("CandyChateauBGM.ogg"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Sound\\");

		GameEngineSound::SoundLoad(FilePath.PlusFilePath("CandyChateauBGM.ogg"));
	}

	//레드컬러맵세팅 원본
	if (false == ResourcesManager::GetInst().IsLoadTexture("MapRedColorTest02.Bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");

		GameEnginePath FolderPath = FilePath;

		FilePath.MoveChild("ContentsResources\\Texture\\");
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("MapRedColorTest02.bmp"));

	}



	//배경이미지
	BackGroundImagePtr = CreateActor<BackGroundImage>();
	BackGroundImagePtr->Init("CandyChateau1200x800.Bmp");

	//배경타일
	BackGroundPtr = CreateActor<BackGround>();
	BackGroundPtr->Init("CandyChateauTile01.Bmp", "MapRedColorTest02.bmp");

	// 카메라 오버 막는데 필요한 데이터인 맵스케일 등록. 맵을 바꾸면 그 맵에 맞춰서 카메라가 나가지 않음
	GameEngineWindowTexture* Ptr = ResourcesManager::GetInst().FindTexture("CandyChateauTile01.Bmp");
	if (nullptr == Ptr)
	{
		MsgBoxAssert("맵 텍스처를 알수가 없습니다.");
	}
	GlobalValue::MapScale = Ptr->GetScale();


	LevelPlayer = CreateActor<Player>();
	LevelPlayer->SetGroundTexture("MapRedColorTest02.bmp");

	{
		FadeObject* FObject = CreateActor<FadeObject>();
	}

	CreateActor<PlayUIManager>();
	CreateActor<MrDark>();
	CreateActor<GoalPoint>();

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



}


void PlayLevel::Update(float _Delta)
{
	if (true == GameEngineInput::IsDown(VK_F12))
	{
		BGMPlayerToPlayLevel.Stop();
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

	//사운드 플레이어 전역변수 초기화 + 동시에 음악재생
	BGMPlayerToPlayLevel = GameEngineSound::SoundPlay("CandyChateauBGM.ogg");
	BGMPlayerToPlayLevel.SetLoop(10);
	//LevelPlayer->SetGroundTexture("MapRedColor.bmp");
	//float4 WinScale = GameEngineWindow::MainWindow.GetScale();
	////LevelPlayer->SetPos(WinScale.Half());
	//// 0 0
	//// x y
	//GetMainCamera()->SetPos(LevelPlayer->GetPos() - WinScale.Half());

}

void PlayLevel::LevelEnd(GameEngineLevel* _NextLevel)
{

}