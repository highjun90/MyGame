#include "PlayUIManager.h"

#include "ContentsEnum.h"
#include <GameEngineCore/GameEngineRenderer.h>

PlayUIManager* PlayUIManager::UI = nullptr;

PlayUIManager::PlayUIManager() 
{
	UI = this;
}

PlayUIManager::~PlayUIManager() 
{
}

void PlayUIManager::Start() 
{
	// 위치를 옮기지 않았다.
	// GetPos();
	// 카메라가 안움직여

	//UI 목숨과 HP 
	{
		float4 UISCale = { 70,30 };
		UISCale *= 4.0f;

		GameEngineRenderer* Ptr = CreateUIRenderer("UI_LifeAndHp.bmp", RenderOrder::Play);
		Ptr->SetRenderPos({ 200, 100 });
		Ptr->SetRenderScale(UISCale);
		Ptr->SetTexture("UI_LifeAndHp.bmp");
	}


	//UI 좌하단구슬
	{
		float4 UISCale = { 63,22 };
		UISCale *= 4.0f;

		GameEngineRenderer* Ptr = CreateUIRenderer("UI_LeftDownMarble.bmp", RenderOrder::Play);
		Ptr->SetRenderPos({ 200, 1100 });
		Ptr->SetRenderScale(UISCale);
		Ptr->SetTexture("UI_LeftDownMarble.bmp");
	}
}