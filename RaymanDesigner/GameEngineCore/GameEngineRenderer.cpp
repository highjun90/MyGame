#include "GameEngineRenderer.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>
#include "GameEngineCamera.h"
#include "ResourcesManager.h"
#include "GameEngineActor.h"

GameEngineRenderer::GameEngineRenderer()
{
}

GameEngineRenderer::~GameEngineRenderer()
{
}

void GameEngineRenderer::SetTexture(const std::string& _Name)
{
	Texture = ResourcesManager::GetInst().FindTexture(_Name);

	if (nullptr == Texture)
	{
		MsgBoxAssert("�������� �ʴ� �ؽ�ó�� �����Ϸ��� �߽��ϴ�." + _Name);
	}

	SetCopyPos(float4::ZERO);
	SetCopyScale(Texture->GetScale());

	if (false == ScaleCheck)
	{
		SetRenderScaleToTexture();
	}
}

void GameEngineRenderer::SetRenderScaleToTexture()
{
	RenderScale = Texture->GetScale();
	ScaleCheck = false;
}

void GameEngineRenderer::Render(GameEngineCamera* _Camera)
{
	if (nullptr == Texture)
	{
		MsgBoxAssert("�̹����� �������� ���� ������ �Դϴ�.");
	}

	GameEngineWindowTexture* BackBuffer = GameEngineWindow::MainWindow.GetBackBuffer();

	BackBuffer->TransCopy(Texture, Master->GetPos() + RenderPos - _Camera->GetPos(), RenderScale, CopyPos, CopyScale);

}

bool GameEngineRenderer::IsDeath()
{
	return true == GameEngineObject::IsDeath() || Master->IsDeath();
}




// ========== ���� ���� �ּ� =============

// SetTexture(const std::string& _Name) - ���ҽ��Ŵ������� ���ҽ� ã���� Texture�� ����Ű����
// SetRenderScaleToTexture() - ScaleCheck�� false ��(??) 

//Render()
// Master->GetPos() + RenderPos - _Camera->GetPos(), => �� 3�ܰ�� �и��ؼ� ��������. Master->GetPos()�� Actor�� ��ġ�̴�. _Camera->GetPos() ������ ī�޶��� ��ġ�� ������Ѵ�(������� ��ġ�̹Ƿ�)