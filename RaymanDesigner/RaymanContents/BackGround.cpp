#include "BackGround.h"
#include <GameEngineCore/ResourcesManager.h>
#include <GameEnginePlatform/GameEngineWindow.h>

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
	GameEngineWindowTexture* BackBuffer = GameEngineWindow::MainWindow.GetBackBuffer();
	GameEngineWindowTexture* FindTexture = ResourcesManager::GetInst().FindTexture(FileName);
	// BackBuffer->BitCopy(FindTexture, GetPos());

	BackBuffer->BitCopy(FindTexture, GetPos(), { 100, 100 });

}
void BackGround::Release() {
}


void BackGround::Init(const std::string& _FileName)
{
	FileName = _FileName;

	if (false == ResourcesManager::GetInst().IsLoadTexture(_FileName))
	{
		// 무조건 자동으로 현재 실행중인 위치가 된다.
		// 경로
		// 시작위치 D:\Project\AR47\Winapi\AR47WinApi\Bin\x64\Debug
		// 
		// 시작위치 D:\Project\AR47\Winapi\AR47WinApi\GameEngineApp
		// 도착위치 D:\Project\AR47\Winapi\AR47WinApi\ContentsResources\Texture\Player
		GameEnginePath FilePath;
		// 시작위치 D:\Project\AR47\Winapi\AR47WinApi\GameEngineApp
		FilePath.GetCurrentPath();
		// 시작위치 D:\Project\AR47\Winapi\AR47WinApi

		// ContentsResources

		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Texture\\" + _FileName);

		GameEngineWindowTexture* Text = ResourcesManager::GetInst().TextureLoad(FilePath.GetStringPath());

		// 208

		float4 Scale = Text->GetScale();

		Scale.X *= 5.0f;
		Scale.Y *= 5.0f;

		// SetScale(Scale * 5.0f);

		SetScale(Scale);
	}

}