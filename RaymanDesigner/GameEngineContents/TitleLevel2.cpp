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


	BackGroundPtr = CreateActor<BackGround>();
	BackGroundPtr->Init("TitleScreen.Bmp");
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

