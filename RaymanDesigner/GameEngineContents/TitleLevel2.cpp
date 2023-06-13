#include "TitleLevel2.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineBase/GameEnginePath.h>
#include <string>

#include "BackGround.h"

TitleLevel2::TitleLevel2()
{
}

TitleLevel2::~TitleLevel2()
{
}

void TitleLevel2::Start()
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
	BackGroundPtr->Init("TitleScreen.Bmp", "CandyChateauDebug.bmp");
}



void TitleLevel2::Update(float _DeltaTime)
{

	if (true == GameEngineInput::IsDown('P'))
	{
		GameEngineCore::ChangeLevel("PlayLevel");
	}
}

void TitleLevel2::Release()
{

}

