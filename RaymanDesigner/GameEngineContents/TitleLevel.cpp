#include "TitleLevel.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineBase/GameEnginePath.h>
#include <string>


TitleLevel::TitleLevel()
{
}

TitleLevel::~TitleLevel()
{
}

void TitleLevel::Start()
{
	//{
	//	GameEnginePath FilePath;
	//	FilePath.SetCurrentPath();
	//	FilePath.MoveParentToExistsChild("ContentsResources");
	//	FilePath.MoveChild("ContentsResources\\Texture\\");

	//	const std::string FileString = FilePath.GetStringPath() + "UbiSoftLogo.bmp";

	//	//*(TitleLevel::TitleTexture).ResLoad(FileString);
	//	TitleTexture->ResLoad(FileString);
	//}

	//GameEngineWindowTexture* BackBuffer = GameEngineWindow::MainWindow.GetBackBuffer();

	//BackBuffer->BitCopy(TitleTexture, { 0, 0 }, TitleTexture->GetScale());
}

void TitleLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	//{
	//	GameEnginePath FilePath;
	//	FilePath.SetCurrentPath();
	//	FilePath.MoveParentToExistsChild("ContentsResources");
	//	FilePath.MoveChild("ContentsResources\\Texture\\");

	//	const std::string FileString = FilePath.GetStringPath() + "UbiSoftLogo.bmp";

	//	//*(TitleLevel::TitleTexture).ResLoad(FileString);
	//	TitleTexture.ResLoad(FileString);


	//	const float4 Pos = float4::ZERO;
	//	GameEngineWindow::MainWindow.GetWindowBuffer()->BitCopy(&TitleTexture, Pos);
	//}

}



void TitleLevel::Update(float _DeltaTime)
{

	if (true == GameEngineInput::IsDown('P'))
	{
		GameEngineCore::ChangeLevel("PlayLevel");
	}
}