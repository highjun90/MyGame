#include "BackGround.h"
#include "ContentsEnum.h"
#include <GameEngineCore/ResourcesManager.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRenderer.h>

#pragma comment(lib, "msimg32.lib")

BackGround::BackGround()
{
}

BackGround::~BackGround()
{
}

void BackGround::Start() 
{
	//SetPos({ 1920, 1200 });
	Renderer = CreateRenderer(RenderOrder::BackGround);

	DebugRenderer = CreateRenderer(RenderOrder::BackGround);

	Renderer->On();
	DebugRenderer->Off();
}


void BackGround::Update(float _Delta) {
}

void BackGround::Release() 
{
}


void BackGround::Init(const std::string& _FileName, const std::string& _DebugFileName)
{
	FileName = _FileName;

	if (false == ResourcesManager::GetInst().IsLoadTexture(_FileName))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Texture\\" + _FileName);

		GameEngineWindowTexture* Text = ResourcesManager::GetInst().TextureLoad(FilePath.GetStringPath());
	}

	GameEngineWindowTexture* Texture = ResourcesManager::GetInst().FindTexture(_FileName);
	float4 Scale = { Texture->GetScale() };

	//원본코드 
	Renderer->SetTexture(_FileName);
	Renderer->SetRenderScale(Scale);
	DebugRenderer->SetTexture(_DebugFileName);
	DebugRenderer->SetRenderScale(Scale);
	SetPos({ Scale.hX(), Scale.hY() });

	
	//스케일 확대해주는 임시코드
	/*float4 TestScale = { Scale.X * 4.0f , Scale.Y * 4.0f};
	Renderer->SetTexture(_FileName);
	Renderer->SetRenderScale(TestScale);
	DebugRenderer->SetTexture(_DebugFileName);
	DebugRenderer->SetRenderScale(TestScale);
	SetPos({ TestScale.hX(), TestScale.hY() });*/
}

void BackGround::Init(const std::string& _FileName)
{
	DebugRenderer = nullptr;

	FileName = _FileName;

	if (false == ResourcesManager::GetInst().IsLoadTexture(_FileName))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Texture\\" + _FileName);

		GameEngineWindowTexture* Text = ResourcesManager::GetInst().TextureLoad(FilePath.GetStringPath());
	}

	GameEngineWindowTexture* Texture = ResourcesManager::GetInst().FindTexture(_FileName);
	float4 Scale = { Texture->GetScale() };
	Renderer->SetTexture(_FileName);
	Renderer->SetRenderScale(Scale);
	//SetPos({ 0, 0});
	SetPos({ Scale.hX(), Scale.hY() });

}

void BackGround::SwitchRender()
{
	SwitchRenderValue = !SwitchRenderValue;

	if (SwitchRenderValue)
	{
		Renderer->On();
		DebugRenderer->Off();
	}
	else {
		Renderer->Off();
		DebugRenderer->On();
	}
}