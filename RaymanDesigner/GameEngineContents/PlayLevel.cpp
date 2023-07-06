#include "PlayLevel.h"

#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/TileMap.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineSound.h>

#include "PlayUIManager.h"
// Contents
#include "BackGround.h"
#include "BackGroundImage.h"
#include "GlobalValue.h"
#include "MapDeathArea.h"

PlayLevel::PlayLevel()
{
	//그냥 포인터 초기화
	for (int i = 0; i < 5; i++)
	{
		BackGroundDivisionPtr[i] = nullptr;
	}

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

	////레드컬러맵세팅 원본
	//if (false == ResourcesManager::GetInst().IsLoadTexture("MapRedColorTest02.Bmp"))
	//{
	//	GameEnginePath FilePath;
	//	FilePath.SetCurrentPath();
	//	FilePath.MoveParentToExistsChild("ContentsResources");

	//	GameEnginePath FolderPath = FilePath;

	//	FilePath.MoveChild("ContentsResources\\Texture\\");
	//	ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("MapRedColorTest02.bmp"));

	//}

	//배경이미지 등록
	BackGroundImagePtr = CreateActor<BackGroundImage>();
	//BackGroundImagePtr->Init("CandyChateau1200x800.Bmp");
	BackGroundImagePtr->Init("CandyChateau1480x987.Bmp");

	//분할된 레드맵 리소스 등록
	if (false == ResourcesManager::GetInst().IsLoadTexture("CandyChateauRed1.Bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");

		GameEnginePath FolderPath = FilePath;

		FilePath.MoveChild("ContentsResources\\Texture\\");

		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("CandyChateauRed0.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("CandyChateauRed1.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("CandyChateauRed2.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("CandyChateauRed3.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("CandyChateauRed4.bmp"));


		//회색 처리된 레드맵
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("MapGrayColor.bmp"));
	}

	//분할된 타일맵 리소스 등록
	for (int i = 0; i < 5; i++)
	{
		std::string TilemapName = "CandyChateauTile";
		TilemapName += std::to_string((int)i);
		TilemapName += ".bmp";

		std::string RedmapName = "CandyChateauRed";
		RedmapName += std::to_string((int)i);
		RedmapName += ".bmp";

		BackGroundDivisionPtr[i] = CreateActor<BackGround>();
		BackGroundDivisionPtr[i]->Init(TilemapName, RedmapName);


		//맵들을 X좌표쪽으로 밀어주는 코드 (겹침방지), 원본맵 X픽셀값이 16000, 1/5 하면 3200.
		float _X =3200.0f * (float)i;             
		float4 _Pos4 = {_X,0};
		BackGroundDivisionPtr[i]->AddPos(_Pos4);
	}

	// 카메라 오버 막는데 필요한 데이터인 맵스케일 등록. 맵을 바꾸면 그 맵에 맞춰서 카메라가 나가지 않음
	GameEngineWindowTexture* Ptr = ResourcesManager::GetInst().FindTexture("CandyChateauTile0.Bmp");
	if (nullptr == Ptr)
	{
		MsgBoxAssert("맵 텍스처를 알수가 없습니다.");
	}
	GlobalValue::MapScale = Ptr->GetScale();
	GlobalValue::MapScale.X = GlobalValue::MapScale.X * 5; //원본맵을 수직으로 5분할 했으므로 X를 5배 늘려줌


	//충돌확인 맵은 통짜, 따로있음 어떻게 이어붙이는가? 
	LevelPlayer = CreateActor<Player>();
	LevelPlayer->SetGroundTexture("MapGrayColor.bmp");

	//검은화면
	{
		FObject = CreateActor<FadeObject>();
	}

	PlayUIManagerPtr = CreateActor<PlayUIManager>();
	PlayUIManagerPtr->SetRaymanPtr(LevelPlayer);

	MrDarkPtr = CreateActor<MrDark>();

	DarkRaymanPtr = CreateActor<DarkRayman>();
	DarkRaymanPtr->SetRaymanPtr(LevelPlayer);

	GoalPointPtr = CreateActor<GoalPoint>();

	CreateActor<MapDeathArea>();
}


void PlayLevel::Update(float _Delta)
{
	if (true == GameEngineInput::IsDown('0'))
	{
		BGMPlayerToPlayLevel.Stop();
		GameEngineCore::ChangeLevel("EndingLevel");
	}

	if (true == GameEngineInput::IsDown(VK_F12))
	{
		BGMPlayerToPlayLevel.Stop();
		GameEngineCore::ChangeLevel("TitleLevel");
	}

	if (true == GameEngineInput::IsDown(VK_F1))
	{
		BackGroundDivisionPtr[0]->SwitchRender();
		BackGroundDivisionPtr[1]->SwitchRender();
		BackGroundDivisionPtr[2]->SwitchRender();
		BackGroundDivisionPtr[3]->SwitchRender();
		BackGroundDivisionPtr[4]->SwitchRender();

	}

	if (LevelPlayer->GetLoseGame() == true)
	{

	}

	//원본 선생님 몬스터 만들기
	/*if (3.0f <= GetLiveTime() )
	{
		Monster* NewMonster = CreateActor<Monster>();
		ResetLiveTime();
	}*/


	//임의로 만든 몬스터 1개 만들기, 3초뒤 1마리 나오게
	/*if (3.0f <= GetLiveTime() && true == CreateDarkRayman)
	{
		Monster* NewMonster = CreateActor<Monster>();
		CreateDarkRayman = false;
	}*/

	//레이맨 죽으면 재시작
	if (true == LevelPlayer->GetLoseGame())
	{

		//재시작 맨처음 시간 기록
		if (RestartTime1 == 0)
		{
			RestartTime1 = GetLiveTime();
		}


		ResetGame();
	}
	
	//레이맨 승리하거나 목숨이 0개 이하로 떨어지면 종료레벨로 바꿈
	if (true == LevelPlayer->GetVictoryEnd() || 0 > LevelPlayer->GetTotalLife())
	{
		//재시작 맨처음 시간 기록
		if (LevelEnd_Time1 == 0)
		{
			LevelEnd_Time1 = GetLiveTime();
		}
		LevelEnd();
	}

	if (RecallLevel == true)
	{
		FObject->SetFade(true); //어두운데 밝아짐
		FObject->SetValue(255.0);
		RecallLevel == false;
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
}

void PlayLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
	FObject->SetValue(0.0f);
	FObject->SetFade(false); //밝은데 어두워짐
}

void PlayLevel::Restart()
{
	RestartTime2 = GetLiveTime();
	if (RestartTime2 - RestartTime1 > 5.0 && FObjectRestart == true)
	{
		FObject->SetFade(true); //어두운데 밝아짐
		FObject->SetValue(255.0);
	}

	//기타 초기설정 초기화
	FObjectRestart = false;
	RestartTime1 = 0;
}

