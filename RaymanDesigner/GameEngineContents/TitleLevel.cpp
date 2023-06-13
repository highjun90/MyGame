#include "TitleLevel.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineBase/GameEnginePath.h>
#include <string>

#include "BackGround.h"

TitleLevel::TitleLevel()
{
}

TitleLevel::~TitleLevel()
{
}

void TitleLevel::Start()
{
	if (false == ResourcesManager::GetInst().IsLoadTexture("CandyChateauDebug.Bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");

		GameEnginePath FolderPath = FilePath;

		FilePath.MoveChild("ContentsResources\\Texture\\");
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("CandyChateauDebug.bmp"));

	}

	BackGroundPtr = CreateActor<BackGround>();
	BackGroundPtr->Init("UbiSoftLogo.Bmp", "CandyChateauDebug.bmp");
}



void TitleLevel::Update(float _DeltaTime)
{

	if (true == GameEngineInput::IsDown('P'))
	{
		GameEngineCore::ChangeLevel("TitleLevel2");
	}
}

void TitleLevel::Release()
{

}

