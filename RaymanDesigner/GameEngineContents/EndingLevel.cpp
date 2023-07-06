#include "EndingLevel.h"
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineBase/GameEnginePath.h>
#include <GameEnginePlatform/GameEngineSound.h>

#include "BackGround.h"
EndingLevel::EndingLevel() 
{
}

EndingLevel::~EndingLevel() 
{
}

void EndingLevel::Start()
{
	//레이맨 디자이너 End
	ResetLiveTime();
	BackGroundPtr = CreateActor<BackGround>();
	BackGroundPtr->Init("EndingScreen.Bmp");

	//엔딩송
	if (nullptr == GameEngineSound::FindSound("EndSong.ogg"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Sound\\");

		GameEngineSound::SoundLoad(FilePath.PlusFilePath("EndSong.ogg"));
	}

	//BGMPlayerToTitleLevel = GameEngineSound::SoundPlay("UbiSoftLogoSong.mp3");
	//SoundPlaying = true;

	//페이드효과
	FObject = CreateActor<FadeObject>();
	FObject->SetFade(true); //어두운데 밝아짐
	FObject->SetValue(255.0);
}

void EndingLevel::Update(float _DeltaTime)
{
	
}


void EndingLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	//사운드 플레이어 전역변수 초기화 + 동시에 음악재생
	//BGMPlayer = GameEngineSound::SoundPlay("EndSong.ogg");
	SoundPlaying = true;
}


