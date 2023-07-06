#include "PlayUIManager.h"

#include "ContentsEnum.h"

#include <GameEngineBase/GameEnginePath.h>
#include <GameEngineCore/ResourcesManager.h>


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
	/*{
		float4 UISCale = { 70,30 };
		UISCale *= 3.0f;

		GameEngineRenderer* Ptr = CreateUIRenderer("UI_LifeAndHp.bmp", RenderOrder::Play);
		Ptr->SetRenderPos({ 140, 70 });
		Ptr->SetRenderScale(UISCale);
		Ptr->SetTexture("UI_LifeAndHp.bmp");
	}*/


	//UI 좌하단구슬
	/*{
		float4 UISCale = { 63,22 };
		UISCale *= 3.0f;

		GameEngineRenderer* Ptr = CreateUIRenderer("UI_LeftDownMarble.bmp", RenderOrder::Play);
		Ptr->SetRenderPos({ 140, 720 });
		Ptr->SetRenderScale(UISCale);
		Ptr->SetTexture("UI_LeftDownMarble.bmp");
	}*/



	//목숨,Hp Ui
	{
		//텍스쳐가 없으면 등록한다
		if (false == ResourcesManager::GetInst().IsLoadTexture("UI_LifeAndHp.bmp"))
		{
			GameEnginePath FilePath;
			FilePath.SetCurrentPath();
			FilePath.MoveParentToExistsChild("ContentsResources");
			//FilePath.MoveChild("ContentsResources\\Texture\\");
			FilePath.MoveChild("ContentsResources\\Texture\\Ui\\UI_LifeAndHp.bmp");
			//GameEngineWindowTexture* Text = ResourcesManager::GetInst().TextureLoad(FilePath.GetStringPath());

			GameEngineWindowTexture* Test = ResourcesManager::GetInst().TextureLoad(FilePath.GetStringPath());
		}

		//등록한 텍스쳐를 가져온다
		GameEngineWindowTexture* Texture = ResourcesManager::GetInst().FindTexture("UI_LifeAndHp.bmp");

		float4 UISCale = { 70,30 };
		UISCale *= 3.0f;

		UI_LifeAndHp = CreateUIRenderer("UI_LifeAndHp.bmp", 1000);
		UI_LifeAndHp->SetRenderPos({ 140, 70 });
		UI_LifeAndHp->SetRenderScale(UISCale);
	//	UI_LifeAndHp->SetTexture("UI_LifeAndHp.bmp");
	}

	// 구슬 Ui
	{
		if (false == ResourcesManager::GetInst().IsLoadTexture("UI_Marble.bmp"))
		{
			GameEnginePath FilePath;
			FilePath.SetCurrentPath();
			FilePath.MoveParentToExistsChild("ContentsResources");
			FilePath.MoveChild("ContentsResources\\Texture\\Ui\\UI_Marble.bmp");

			GameEngineWindowTexture* Test = ResourcesManager::GetInst().TextureLoad(FilePath.GetStringPath());
		}

		GameEngineWindowTexture* Texture = ResourcesManager::GetInst().FindTexture("UI_Marble.bmp");

		float4 UISCale = { 63,22 };
		UISCale *= 3.0f;

		UI_Marble = CreateUIRenderer("UI_Marble.bmp", 1000);
		UI_Marble->SetRenderPos({ 140, 720 });
		UI_Marble->SetRenderScale(UISCale);
	}

	// UI숫자 등록
	{
		if (false == ResourcesManager::GetInst().IsLoadTexture("UI_NumberOne.bmp"))
		{
			GameEnginePath FilePath;
			FilePath.SetCurrentPath();
			FilePath.MoveParentToExistsChild("ContentsResources");
			FilePath.MoveChild("ContentsResources\\Texture\\Ui\\");

			GameEngineWindowTexture* Test = ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_NumberZero.bmp"));
			ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_NumberOne.bmp"));
			ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_NumberTwo.bmp"));
			ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_NumberThree.bmp"));
			ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_NumberFour.bmp"));
			ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_NumberFive.bmp"));
			ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_NumberSix.bmp"));
			ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_NumberSeven.bmp"));
			ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_NumberEight.bmp"));
			ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_NumberNine.bmp"));
		}

		//GameEngineWindowTexture* Texture = ResourcesManager::GetInst().FindTexture("Ui_NumberZero.bmp");
		UI_LifeNumber1 = CreateUIRenderer("Ui_NumberZero.bmp", 1000);
		float4 _Scale = UI_LifeNumber1->GetRenderScale();
		_Scale.X *= 3;
		_Scale.Y *= 3;
		UI_LifeNumber1->SetRenderScale(_Scale);
		UI_LifeNumber1->SetRenderPos({ 180, 60 });

		UI_LifeNumber2 = CreateUIRenderer("Ui_NumberZero.bmp", 1000);
		UI_LifeNumber2->SetRenderScale(_Scale);
		UI_LifeNumber2->SetRenderPos({ 220, 60 });

		UI_MarbleNumber1 = CreateUIRenderer("Ui_NumberZero.bmp", 1000);
		UI_MarbleNumber1->SetRenderScale(_Scale);
		UI_MarbleNumber1->SetRenderPos({ 170, 720 });

		UI_MarbleNumber2 = CreateUIRenderer("Ui_NumberZero.bmp", 1000);
		UI_MarbleNumber2->SetRenderScale(_Scale);
		UI_MarbleNumber2->SetRenderPos({ 210, 720 });
	}




	//// Ui 숫자 스프라이트 등록
	//{
	//	if (false == ResourcesManager::GetInst().IsLoadTexture("UI_Number.bmp"))
	//	{
	//		GameEnginePath FilePath;
	//		FilePath.SetCurrentPath();
	//		FilePath.MoveParentToExistsChild("ContentsResources");
	//		FilePath.MoveChild("ContentsResources\\Texture\\Ui\\");
	//
	//		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("UI_Number.bmp"), 10, 1);
	//	}

	//	UI_Numbers = ResourcesManager::GetInst().FindSprite("UI_Number.bmp");

	//}


}