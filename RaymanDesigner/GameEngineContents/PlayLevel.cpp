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
	//���� 

	//���弼��
	if (nullptr == GameEngineSound::FindSound("CandyChateauBGM.ogg"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Sound\\");

		GameEngineSound::SoundLoad(FilePath.PlusFilePath("CandyChateauBGM.ogg"));
	}

	//�����÷��ʼ���
	if (false == ResourcesManager::GetInst().IsLoadTexture("MapRedColor.Bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");

		GameEnginePath FolderPath = FilePath;

		FilePath.MoveChild("ContentsResources\\Texture\\");
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("MapRedColor.bmp"));

		//����� Ÿ�ϸ� �϶�
		//ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Tile.bmp"));
		//ResourcesManager::GetInst().CreateSpriteSheet("Tile.bmp", 24, 40);
	}

	//����̹���
	BackGroundImagePtr = CreateActor<BackGroundImage>();
	BackGroundImagePtr->Init("CandyChateau1200x800.Bmp");

	//����
	BackGroundPtr = CreateActor<BackGround>();
	BackGroundPtr->Init("Test1.Bmp", "MapRedColor.bmp");

	// ī�޶� ���� ���µ� �ʿ��� �������� �ʽ����� ���. ���� �ٲٸ� �� �ʿ� ���缭 ī�޶� ������ ����
	GameEngineWindowTexture* Ptr = ResourcesManager::GetInst().FindTexture("Test1.Bmp");
	if (nullptr == Ptr)
	{
		MsgBoxAssert("�� �ؽ�ó�� �˼��� �����ϴ�.");
	}
	GlobalValue::MapScale = Ptr->GetScale();

	
	LevelPlayer = CreateActor<Player>();
	LevelPlayer->SetGroundTexture("MapRedColor.bmp");

	{
		FadeObject* FObject = CreateActor<FadeObject>();
	}

	CreateActor<PlayUIManager>();
	CreateActor<MrDark>();


	//����� Ÿ�� ���϶�
	/*TileMap* TileObject = CreateActor<TileMap>();

	TileObject->CreateTileMap("Tile.bmp", 20, 20, { 50, 50 }, 0);
	for (size_t y = 0; y < 20; y++)
	{
		for (size_t x = 0; x < 20; x++)
		{
			TileObject->SetTile(x, y, 0);
		}
	}*/



	//================================================= ���⼭���� �ʻ����� �������� �̿��� �ӽüҽ��ڵ�. ������ �ø��� ���� �ʹ� �ɸ��� ==========================================

	////���弼��
	//if (nullptr == GameEngineSound::FindSound("CandyChateauBGM.ogg"))
	//{
	//	GameEnginePath FilePath;
	//	FilePath.SetCurrentPath();
	//	FilePath.MoveParentToExistsChild("ContentsResources");
	//	FilePath.MoveChild("ContentsResources\\Sound\\");

	//	GameEngineSound::SoundLoad(FilePath.PlusFilePath("CandyChateauBGM.ogg"));
	//}

	////�����÷��ʼ���
	//if (false == ResourcesManager::GetInst().IsLoadTexture("MapRedColorDownSize.Bmp"))
	//{
	//	GameEnginePath FilePath;
	//	FilePath.SetCurrentPath();
	//	FilePath.MoveParentToExistsChild("ContentsResources");

	//	GameEnginePath FolderPath = FilePath;

	//	FilePath.MoveChild("ContentsResources\\Texture\\");
	//	ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("MapRedColorDownSize.bmp"));
	//}

	////����̹���
	//BackGroundImagePtr = CreateActor<BackGroundImage>();
	//BackGroundImagePtr->Init("CandyChateau1200x800.Bmp");

	////����
	//BackGroundPtr = CreateActor<BackGround>();
	//BackGroundPtr->Init("Test1DownSize.Bmp", "MapRedColorDownSize.bmp");

	//// ī�޶� ���� ���µ� �ʿ��� �������� �ʽ����� ���. ���� �ٲٸ� �� �ʿ� ���缭 ī�޶� ������ ����
	//GameEngineWindowTexture* Ptr = ResourcesManager::GetInst().FindTexture("Test1DownSize.Bmp");
	//if (nullptr == Ptr)
	//{
	//	MsgBoxAssert("�� �ؽ�ó�� �˼��� �����ϴ�.");
	//}
	//GlobalValue::MapScale = Ptr->GetScale()*4.0f;

	//LevelPlayer = CreateActor<Player>();
	//LevelPlayer->SetGroundTexture("MapRedColorDownSize.bmp");

	//CreateActor<PlayUIManager>();
	//CreateActor<MrDark>();

	// ===================================================================================================================================================================================
}


void PlayLevel::Update(float _Delta)
{
	if (true == GameEngineInput::IsDown(VK_F2))
	{
		GameEngineCore::ChangeLevel("TitleLevel");
	}

	if (true == GameEngineInput::IsDown(VK_F1))
	{
		BackGroundPtr->SwitchRender();
	}

	//���� ������ ���� �����
	/*if (3.0f <= GetLiveTime() )
	{
		Monster* NewMonster = CreateActor<Monster>();
		ResetLiveTime();
	}*/


	//���Ƿ� ���� ���� 1�� �����, 3�ʵ� 1���� ������
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
		MsgBoxAssert("�÷��̾ ���������� �ʾҽ��ϴ�");
	}

	GameEngineSound::SoundPlay("CandyChateauBGM.ogg");

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