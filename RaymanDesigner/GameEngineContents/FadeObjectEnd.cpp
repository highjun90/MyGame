#include "FadeObject.h"
#include <GameEngineBase/GameEnginePath.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>

FadeObject::FadeObject()
{
}

FadeObject::~FadeObject()
{
}

void FadeObject::Start()
{
	if (false == ResourcesManager::GetInst().IsLoadTexture("FADE.bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");

		GameEnginePath FolderPath = FilePath;

		FilePath.MoveChild("ContentsResources\\Texture\\");

		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("FADE.bmp"));
	}

	Render = CreateUIRenderer(200);
	Render->SetTexture("FADE.bmp");
	Render->SetRenderPos(GameEngineWindow::MainWindow.GetScale().Half());
	Render->SetRenderScale(GameEngineWindow::MainWindow.GetScale());
	// Render->SetAlpha(120);
	// Render->SetAlpha();
	// Render->AddAlpha(-Delta * 255.0f);
}

void FadeObject::Update(float _Time)
{
	if (FadeDir)
	{
		Value -= _Time * 300;
		if (0.0f >= Value)
		{
			Death();
			return;
		}
		Render->SetAlpha(static_cast<unsigned char>(Value));
	}
}