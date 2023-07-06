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
	//���̸� �����̳� End
	ResetLiveTime();
	BackGroundPtr = CreateActor<BackGround>();
	BackGroundPtr->Init("EndingScreen.Bmp");

	//������
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

	//���̵�ȿ��
	FObject = CreateActor<FadeObject>();
	FObject->SetFade(true); //��ο �����
	FObject->SetValue(255.0);
}

void EndingLevel::Update(float _DeltaTime)
{
	
}


void EndingLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	//���� �÷��̾� �������� �ʱ�ȭ + ���ÿ� �������
	//BGMPlayer = GameEngineSound::SoundPlay("EndSong.ogg");
	SoundPlaying = true;
}


