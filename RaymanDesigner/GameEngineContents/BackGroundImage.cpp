#include "BackGroundImage.h"
#include "ContentsEnum.h"
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRenderer.h>

#pragma comment(lib, "msimg32.lib")




BackGroundImage::BackGroundImage()
{
	

}

BackGroundImage::~BackGroundImage()
{
}

void BackGroundImage::Start()
{
	//SetPos({ 1920, 1200 });
	Renderer = CreateRenderer(RenderOrder::BackGroundImage);
	Renderer->On();
}

void BackGroundImage::Update(float _Delta)
{
	float4 CameraPos = GetLevel()->GetMainCamera()->GetPos();
	float4 AddForRePos = { Scale.X / 2, Scale.Y / 2 };
	SetPos(CameraPos + AddForRePos);

}


void BackGroundImage::Release()
{
}


void BackGroundImage::Init(const std::string& _FileName)
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

	// 원래이미지 사이즈
	/*float4 Scale = { Texture->GetScale() };
	Renderer->SetTexture(_FileName);
	Renderer->SetRenderScale(Scale);
	SetPos({ Scale.hX(), Scale.hY() });*/

	//스크린 크기로 이미지사이즈
	float4 ReScale = { 1280, 800 };
	SetScale(ReScale);
	Renderer->SetTexture(_FileName);
	Renderer->SetRenderScale(this->Scale);


}