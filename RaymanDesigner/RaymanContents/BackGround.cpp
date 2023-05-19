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
	SetPos({ 640, 360 });
}


void BackGround::Update(float _Delta) {
}
void BackGround::Render()
{
	//GameEngineWindowTexture* FindTexture = ResourcesManager::GetInst().FindTexture(FileName);

	//if (nullptr == FindTexture)
	//{
	//	return;
	//}

	//GameEngineWindowTexture* BackBuffer = GameEngineWindow::MainWindow.GetBackBuffer();

	//float4 Scale = FindTexture->GetScale();

	//// 720

	//Scale *= 2.0f;

	////                BackBuffer�� �׸����� ��ġ     ũ��    
	//// BackBuffer->TransCopy(FindTexture, GetPos(), Scale, { 0,0 }, FindTexture->GetScale());                                              
	////                             ī���Ϸ��� �̹�����       ������ġ ũ��
	//// BackBuffer->TransCopy(FindTexture, GetPos(), Scale, { 0,0 }, FindTexture->GetScale());                                              
	//BackBuffer->TransCopy(FindTexture, GetPos(), Scale, { 0,0 }, FindTexture->GetScale());

}
void BackGround::Release()
{
}


void BackGround::Init(const std::string& _FileName)
{
	FileName = _FileName;

	if (false == ResourcesManager::GetInst().IsLoadTexture(_FileName))
	{
		// ������ �ڵ����� ���� �������� ��ġ�� �ȴ�.
		// ���
		// ������ġ D:\Project\AR47\Winapi\AR47WinApi\Bin\x64\Debug
		// 
		// ������ġ D:\Project\AR47\Winapi\AR47WinApi\GameEngineApp
		// ������ġ D:\Project\AR47\Winapi\AR47WinApi\ContentsResources\Texture\Player
		GameEnginePath FilePath;
		// ������ġ D:\Project\AR47\Winapi\AR47WinApi\GameEngineApp
		FilePath.SetCurrentPath();
		// ������ġ D:\Project\AR47\Winapi\AR47WinApi

		// ContentsResources

		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Texture\\" + _FileName);

		GameEngineWindowTexture* Text = ResourcesManager::GetInst().TextureLoad(FilePath.GetStringPath());

		// 208

		float4 Scale = Text->GetScale();

		Scale.X *= 3.0f;
		Scale.Y *= 3.0f;

		// SetScale(Scale * 5.0f);

		GameEngineRenderer* Render = CreateRenderer(_FileName, RenderOrder::BackGround);
		Render->SetRenderScale(Scale);
	}

}