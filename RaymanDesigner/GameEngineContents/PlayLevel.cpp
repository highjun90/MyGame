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

	//구슬 초기화
	BlueMarble* MarblePtr1 = CreateActor<BlueMarble>();
	MarblePtr1->SetPos({ 1700,2700 });

	BlueMarble* MarblePtr2 = CreateActor<BlueMarble>();
	MarblePtr2->SetPos({ 1600, 2700 });

	BlueMarble* MarblePtr3 = CreateActor<BlueMarble>();
	MarblePtr3->SetPos({ 900, 2700 });

	BlueMarble* MarblePtr4 = CreateActor<BlueMarble>();
	MarblePtr4->SetPos({ 300, 2300 });

	BlueMarble* MarblePtr5 = CreateActor<BlueMarble>();
	MarblePtr5->SetPos({ 500, 2100 });

	BlueMarble* MarblePtr6 = CreateActor<BlueMarble>();
	MarblePtr6->SetPos({ 1700, 1700 });

	BlueMarble* MarblePtr7 = CreateActor<BlueMarble>();
	MarblePtr7->SetPos({ 780, 1450 });

	BlueMarble* MarblePtr8 = CreateActor<BlueMarble>();
	MarblePtr8->SetPos({ 182, 1236 });

	BlueMarble* MarblePtr9 = CreateActor<BlueMarble>();
	MarblePtr9->SetPos({ 1161, 927 });

	BlueMarble* MarblePtr10 = CreateActor<BlueMarble>();
	MarblePtr10->SetPos({ 2227, 779 });

	BlueMarble* MarblePtr11 = CreateActor<BlueMarble>();
	MarblePtr11->SetPos({ 3088, 949 });

	BlueMarble* MarblePtr12 = CreateActor<BlueMarble>();
	MarblePtr12->SetPos({ 3598, 950 });

	BlueMarble* MarblePtr13 = CreateActor<BlueMarble>();
	MarblePtr13->SetPos({ 4106, 950 });

	BlueMarble* MarblePtr14 = CreateActor<BlueMarble>();
	MarblePtr14->SetPos({ 2423, 1389 });

	BlueMarble* MarblePtr15 = CreateActor<BlueMarble>();
	MarblePtr15->SetPos({ 3736, 1415 });

	BlueMarble* MarblePtr16 = CreateActor<BlueMarble>();
	MarblePtr16->SetPos({ 3925, 1460 });

	BlueMarble* MarblePtr17 = CreateActor<BlueMarble>();
	MarblePtr17->SetPos({ 4119, 1577 });

	BlueMarble* MarblePtr18 = CreateActor<BlueMarble>();
	MarblePtr18->SetPos({ 6263, 1277 });

	BlueMarble* MarblePtr19 = CreateActor<BlueMarble>();
	MarblePtr19->SetPos({ 7156, 1207 });

	BlueMarble* MarblePtr20 = CreateActor<BlueMarble>();
	MarblePtr20->SetPos({ 7295, 1915 });

	BlueMarble* MarblePtr21 = CreateActor<BlueMarble>();
	MarblePtr21->SetPos({ 3598, 2451 });

	BlueMarble* MarblePtr22 = CreateActor<BlueMarble>();
	MarblePtr22->SetPos({ 2427, 2683 });

	BlueMarble* MarblePtr23 = CreateActor<BlueMarble>();
	MarblePtr23->SetPos({ 2427, 2520 });

	BlueMarble* MarblePtr24 = CreateActor<BlueMarble>();
	MarblePtr24->SetPos({ 4037, 3023 });

	BlueMarble* MarblePtr25 = CreateActor<BlueMarble>();
	MarblePtr25->SetPos({ 4193, 3023 });

	BlueMarble* MarblePtr26 = CreateActor<BlueMarble>();
	MarblePtr26->SetPos({ 4402, 3023 });

	BlueMarble* MarblePtr27 = CreateActor<BlueMarble>();
	MarblePtr27->SetPos({ 5870, 3079 });

	BlueMarble* MarblePtr28 = CreateActor<BlueMarble>();
	MarblePtr28->SetPos({ 7001, 3415 });

	BlueMarble* MarblePtr29 = CreateActor<BlueMarble>();
	MarblePtr29->SetPos({ 7774, 3270 });

	BlueMarble* MarblePtr30 = CreateActor<BlueMarble>();
	MarblePtr30->SetPos({ 8840, 2957 });

	BlueMarble* MarblePtr31 = CreateActor<BlueMarble>();
	MarblePtr31->SetPos({ 7690, 1924 });

	BlueMarble* MarblePtr32 = CreateActor<BlueMarble>();
	MarblePtr32->SetPos({ 8754, 1428 });

	BlueMarble* MarblePtr33 = CreateActor<BlueMarble>();
	MarblePtr33->SetPos({ 9680, 1341 });

	BlueMarble* MarblePtr34 = CreateActor<BlueMarble>();
	MarblePtr34->SetPos({ 10906, 950 });

	BlueMarble* MarblePtr35 = CreateActor<BlueMarble>();
	MarblePtr35->SetPos({ 10335, 1426 });

	BlueMarble* MarblePtr36 = CreateActor<BlueMarble>();
	MarblePtr36->SetPos({ 11281, 1360 });

	BlueMarble* MarblePtr37 = CreateActor<BlueMarble>();
	MarblePtr37->SetPos({ 11813, 1613 });

	BlueMarble* MarblePtr38 = CreateActor<BlueMarble>();
	MarblePtr38->SetPos({ 12207, 1465 });

	//
	BlueMarble* MarblePtr39 = CreateActor<BlueMarble>();
	MarblePtr39->SetPos({ 11501, 2315 });

	BlueMarble* MarblePtr40 = CreateActor<BlueMarble>();
	MarblePtr40->SetPos({ 12181, 2280 });

	BlueMarble* MarblePtr41 = CreateActor<BlueMarble>();
	MarblePtr41->SetPos({ 11968, 2539 });

	BlueMarble* MarblePtr42 = CreateActor<BlueMarble>();
	MarblePtr42->SetPos({ 11758, 2929 });

	BlueMarble* MarblePtr43 = CreateActor<BlueMarble>();
	MarblePtr43->SetPos({ 12192, 3226 });

	BlueMarble* MarblePtr44 = CreateActor<BlueMarble>();
	MarblePtr44->SetPos({ 11967, 3226 });

	BlueMarble* MarblePtr45 = CreateActor<BlueMarble>();
	MarblePtr45->SetPos({ 11161, 3623 });

	BlueMarble* MarblePtr46 = CreateActor<BlueMarble>();
	MarblePtr46->SetPos({ 11752, 3682 });

	BlueMarble* MarblePtr47 = CreateActor<BlueMarble>();
	MarblePtr47->SetPos({ 11949, 3617 });

	BlueMarble* MarblePtr48 = CreateActor<BlueMarble>();
	MarblePtr48->SetPos({ 12145, 3711 });

	BlueMarble* MarblePtr49 = CreateActor<BlueMarble>();
	MarblePtr49->SetPos({ 13329, 3352 });

	BlueMarble* MarblePtr50 = CreateActor<BlueMarble>();
	MarblePtr50->SetPos({ 13159, 2866 });

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
		RecallLevel = false;
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

