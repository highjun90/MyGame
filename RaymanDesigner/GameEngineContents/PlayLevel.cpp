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
	//�׳� ������ �ʱ�ȭ
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
	//���� 
	////���弼��
	//if (nullptr == GameEngineSound::FindSound("CandyChateauBGM.ogg"))
	//{
	//	GameEnginePath FilePath;
	//	FilePath.SetCurrentPath();
	//	FilePath.MoveParentToExistsChild("ContentsResources");
	//	FilePath.MoveChild("ContentsResources\\Sound\\");

	//	GameEngineSound::SoundLoad(FilePath.PlusFilePath("CandyChateauBGM.ogg"));
	//}

	////�����÷��ʼ��� ����
	//if (false == ResourcesManager::GetInst().IsLoadTexture("MapRedColor.Bmp"))
	//{
	//	GameEnginePath FilePath;
	//	FilePath.SetCurrentPath();
	//	FilePath.MoveParentToExistsChild("ContentsResources");

	//	GameEnginePath FolderPath = FilePath;

	//	FilePath.MoveChild("ContentsResources\\Texture\\");
	//	ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("MapRedColor.bmp"));

	//	//����� Ÿ�ϸ� �϶�
	//	//ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Tile.bmp"));
	//	//ResourcesManager::GetInst().CreateSpriteSheet("Tile.bmp", 24, 40);
	//}



	////����̹���
	//BackGroundImagePtr = CreateActor<BackGroundImage>();
	//BackGroundImagePtr->Init("CandyChateau1200x800.Bmp");

	////���Ÿ��
	//BackGroundPtr = CreateActor<BackGround>();
	//BackGroundPtr->Init("CandyChateauTile.Bmp", "MapRedColor.bmp");

	//// ī�޶� ���� ���µ� �ʿ��� �������� �ʽ����� ���. ���� �ٲٸ� �� �ʿ� ���缭 ī�޶� ������ ����
	//GameEngineWindowTexture* Ptr = ResourcesManager::GetInst().FindTexture("CandyChateauTile.Bmp");
	//if (nullptr == Ptr)
	//{
	//	MsgBoxAssert("�� �ؽ�ó�� �˼��� �����ϴ�.");
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

	// �÷��� �׽�Ʈ�� �ڵ�
	
	//���弼��
	if (nullptr == GameEngineSound::FindSound("CandyChateauBGM.ogg"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Sound\\");

		GameEngineSound::SoundLoad(FilePath.PlusFilePath("CandyChateauBGM.ogg"));
	}

	////�����÷��ʼ��� ����
	//if (false == ResourcesManager::GetInst().IsLoadTexture("MapRedColorTest02.Bmp"))
	//{
	//	GameEnginePath FilePath;
	//	FilePath.SetCurrentPath();
	//	FilePath.MoveParentToExistsChild("ContentsResources");

	//	GameEnginePath FolderPath = FilePath;

	//	FilePath.MoveChild("ContentsResources\\Texture\\");
	//	ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("MapRedColorTest02.bmp"));

	//}

	//����̹��� ���
	BackGroundImagePtr = CreateActor<BackGroundImage>();
	//BackGroundImagePtr->Init("CandyChateau1200x800.Bmp");
	BackGroundImagePtr->Init("CandyChateau1480x987.Bmp");

	//���ҵ� ����� ���ҽ� ���
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


		//ȸ�� ó���� �����
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("MapGrayColor.bmp"));
	}

	//���ҵ� Ÿ�ϸ� ���ҽ� ���
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


		//�ʵ��� X��ǥ������ �о��ִ� �ڵ� (��ħ����), ������ X�ȼ����� 16000, 1/5 �ϸ� 3200.
		float _X =3200.0f * (float)i;             
		float4 _Pos4 = {_X,0};
		BackGroundDivisionPtr[i]->AddPos(_Pos4);
	}

	// ī�޶� ���� ���µ� �ʿ��� �������� �ʽ����� ���. ���� �ٲٸ� �� �ʿ� ���缭 ī�޶� ������ ����
	GameEngineWindowTexture* Ptr = ResourcesManager::GetInst().FindTexture("CandyChateauTile0.Bmp");
	if (nullptr == Ptr)
	{
		MsgBoxAssert("�� �ؽ�ó�� �˼��� �����ϴ�.");
	}
	GlobalValue::MapScale = Ptr->GetScale();
	GlobalValue::MapScale.X = GlobalValue::MapScale.X * 5; //�������� �������� 5���� �����Ƿ� X�� 5�� �÷���


	//�浹Ȯ�� ���� ��¥, �������� ��� �̾���̴°�? 
	LevelPlayer = CreateActor<Player>();
	LevelPlayer->SetGroundTexture("MapGrayColor.bmp");

	//����ȭ��
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

	//���� ������ ���� �����
	/*if (3.0f <= GetLiveTime() )
	{
		Monster* NewMonster = CreateActor<Monster>();
		ResetLiveTime();
	}*/


	//���Ƿ� ���� ���� 1�� �����, 3�ʵ� 1���� ������
	/*if (3.0f <= GetLiveTime() && true == CreateDarkRayman)
	{
		Monster* NewMonster = CreateActor<Monster>();
		CreateDarkRayman = false;
	}*/

	//���̸� ������ �����
	if (true == LevelPlayer->GetLoseGame())
	{

		//����� ��ó�� �ð� ���
		if (RestartTime1 == 0)
		{
			RestartTime1 = GetLiveTime();
		}


		ResetGame();
	}
	
	//���̸� �¸��ϰų� ����� 0�� ���Ϸ� �������� ���᷹���� �ٲ�
	if (true == LevelPlayer->GetVictoryEnd() || 0 > LevelPlayer->GetTotalLife())
	{
		//����� ��ó�� �ð� ���
		if (LevelEnd_Time1 == 0)
		{
			LevelEnd_Time1 = GetLiveTime();
		}
		LevelEnd();
	}

	if (RecallLevel == true)
	{
		FObject->SetFade(true); //��ο �����
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
		MsgBoxAssert("�÷��̾ ���������� �ʾҽ��ϴ�");
	}

	//���� �÷��̾� �������� �ʱ�ȭ + ���ÿ� �������
	BGMPlayerToPlayLevel = GameEngineSound::SoundPlay("CandyChateauBGM.ogg");
	BGMPlayerToPlayLevel.SetLoop(10);
}

void PlayLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
	FObject->SetValue(0.0f);
	FObject->SetFade(false); //������ ��ο���
}

void PlayLevel::Restart()
{
	RestartTime2 = GetLiveTime();
	if (RestartTime2 - RestartTime1 > 5.0 && FObjectRestart == true)
	{
		FObject->SetFade(true); //��ο �����
		FObject->SetValue(255.0);
	}

	//��Ÿ �ʱ⼳�� �ʱ�ȭ
	FObjectRestart = false;
	RestartTime1 = 0;
}

