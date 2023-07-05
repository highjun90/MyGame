#include "TitleLevel.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineBase/GameEnginePath.h>
#include <GameEnginePlatform/GameEngineSound.h>
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
	//유비소프트 로고 이미지
	ResetLiveTime();
	BackGroundPtr = CreateActor<BackGround>();
	BackGroundPtr->Init("UbiSoftLogo.Bmp");

	//유비소프트 로고송
	if (nullptr == GameEngineSound::FindSound("UbiSoftLogoSong.mp3"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Sound\\");

		GameEngineSound::SoundLoad(FilePath.PlusFilePath("UbiSoftLogoSong.mp3"));
	}

	//BGMPlayerToTitleLevel = GameEngineSound::SoundPlay("UbiSoftLogoSong.mp3");
	//SoundPlaying = true;

	//페이드효과
	FObject = CreateActor<FadeObject>();
	FObject->SetFade(true); //어두운데 밝아짐
	FObject->SetValue(255.0);
}



void TitleLevel::Update(float _DeltaTime)
{
	if (AutoLevelChange == false && GetLiveTime() > 2.0)
	{
		FObject->SetValue(0.0f);
		FObject->SetFade(false); //밝은데 어두워짐
		
		//FObject->SetTimeReset(true);
		AutoLevelChange = true;
	}

	if (true == AutoLevelChange && FObject->GetValue() >= 255.0f)
	{
		//float a = FObject->GetValue();
		//FObject->Off();
		GameEngineCore::ChangeLevel("TitleLevel2");
	}

	if (true == GameEngineInput::IsDown('P'))
	{
		GameEngineCore::ChangeLevel("TitleLevel2");
	}
}

void TitleLevel::Release()
{

}


void TitleLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	//사운드 플레이어 전역변수 초기화 + 동시에 음악재생
	BGMPlayer = GameEngineSound::SoundPlay("UbiSoftLogoSong.mp3");
	SoundPlaying = true;
}


void TitleLevel::LevelEnd(GameEngineLevel* _NextLevel)
{

}

