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

	BackGroundPtr = CreateActor<BackGround>();
	BackGroundPtr->Init("UbiSoftLogo.Bmp");
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



