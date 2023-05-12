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
		MsgBoxAssert("존재하지 않는 텍스처를 세팅하려고 했습니다." + _Name);
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
		MsgBoxAssert("이미지를 세팅하지 않은 랜더러 입니다.");
	}

	GameEngineWindowTexture* BackBuffer = GameEngineWindow::MainWindow.GetBackBuffer();

	BackBuffer->TransCopy(Texture, Master->GetPos() + RenderPos - _Camera->GetPos(), RenderScale, CopyPos, CopyScale);

}

bool GameEngineRenderer::IsDeath()
{
	return true == GameEngineObject::IsDeath() || Master->IsDeath();
}




// ========== 최종 삭제 주석 =============

// SetTexture(const std::string& _Name) - 리소스매니저에서 리소스 찾은후 Texture가 가리키게함
// SetRenderScaleToTexture() - ScaleCheck가 false 면(??) 

//Render()
// Master->GetPos() + RenderPos - _Camera->GetPos(), => 총 3단계로 분리해서 생각하자. Master->GetPos()는 Actor의 위치이다. _Camera->GetPos() 고정된 카메라의 위치를 빼줘야한다(상대적인 위치이므로)