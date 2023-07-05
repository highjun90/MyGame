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

	ResetLiveTime();
	BackGroundPtr = CreateActor<BackGround>();
	BackGroundPtr->Init("TitleScreen.Bmp");



	FObject = CreateActor<FadeObject>();
	FObject->SetFade(true); //¾îµÎ¿îµ¥ ¹à¾ÆÁü
	FObject->SetValue(255.0);
}



void TitleLevel2::Update(float _DeltaTime)
{

	if (AutoLevelChange == false && GetLiveTime() > 5.0)
	{
		FObject->SetValue(0.0f);
		FObject->SetFade(false); //¹àÀºµ¥ ¾îµÎ¿öÁü

		//FObject->SetTimeReset(true);
		AutoLevelChange = true;
	}

	if (true == AutoLevelChange && FObject->GetValue() >= 255.0f)
	{
		//float a = FObject->GetValue();
		//FObject->Off();
		GameEngineCore::ChangeLevel("PlayLevel");
	}

	if (true == GameEngineInput::IsDown('P'))
	{
		GameEngineCore::ChangeLevel("PlayLevel");
	}
}

void TitleLevel2::Release()
{

}

