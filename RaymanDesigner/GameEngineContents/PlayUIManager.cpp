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
	// ��ġ�� �ű��� �ʾҴ�.
	// GetPos();
	// ī�޶� �ȿ�����

	//UI ����� HP 
	{
		float4 UISCale = { 70,30 };
		UISCale *= 3.0f;

		GameEngineRenderer* Ptr = CreateUIRenderer("UI_LifeAndHp.bmp", RenderOrder::Play);
		Ptr->SetRenderPos({ 140, 70 });
		Ptr->SetRenderScale(UISCale);
		Ptr->SetTexture("UI_LifeAndHp.bmp");
	}


	//UI ���ϴܱ���
	{
		float4 UISCale = { 63,22 };
		UISCale *= 3.0f;

		GameEngineRenderer* Ptr = CreateUIRenderer("UI_LeftDownMarble.bmp", RenderOrder::Play);
		Ptr->SetRenderPos({ 140, 720 });
		Ptr->SetRenderScale(UISCale);
		Ptr->SetTexture("UI_LeftDownMarble.bmp");
	}
}