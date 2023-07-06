#include "PlayUIManager.h"

#include "ContentsEnum.h"

#include <GameEngineBase/GameEnginePath.h>
#include <GameEngineCore/ResourcesManager.h>
#include "PlayLevel.h"


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

		UI_LifeAndHp = CreateUIRenderer("UI_LifeAndHp.bmp", RenderOrder::PlayUI);
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

		UI_Marble = CreateUIRenderer("UI_Marble.bmp", RenderOrder::PlayUI);
		UI_Marble->SetRenderPos({ 140, 720 });
		UI_Marble->SetRenderScale(UISCale);
	}

	// UI숫자 등록 + 숫자 렌더러들 초기화
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

		UI_LifeNumber1 = CreateUIRenderer("Ui_NumberZero.bmp", RenderOrder::PlayUI);
		float4 _Scale = UI_LifeNumber1->GetRenderScale();
		_Scale.X *= 3;
		_Scale.Y *= 3;
		UI_LifeNumber1->SetRenderScale(_Scale);
		UI_LifeNumber1->SetRenderPos({ 180, 60 });

		UI_LifeNumber2 = CreateUIRenderer("Ui_NumberZero.bmp", RenderOrder::PlayUI);
		UI_LifeNumber2->SetRenderScale(_Scale);
		UI_LifeNumber2->SetRenderPos({ 220, 60 });

		UI_MarbleNumber1 = CreateUIRenderer("Ui_NumberZero.bmp", RenderOrder::PlayUI);
		UI_MarbleNumber1->SetRenderScale(_Scale);
		UI_MarbleNumber1->SetRenderPos({ 170, 720 });

		UI_MarbleNumber2 = CreateUIRenderer("Ui_NumberZero.bmp", RenderOrder::PlayUI);
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

void PlayUIManager::Update(float _Delta)
{
	//목숨 숫자 표기
	int RaymanLife = 0;
	if (Ui_RaymanPtr == nullptr)
	{
		MsgBoxAssert("UI 매니저가 Rayman을 모릅니다 (Update함수)");
	}
	else
	{
		RaymanLife = Ui_RaymanPtr->GetTotalLife();

		if (RaymanLife < 10)
		{
			UI_LifeNumber1->SetTexture("Ui_NumberZero.bmp");

			switch (RaymanLife)
			{
			case 0:
				UI_LifeNumber2->SetTexture("Ui_NumberZero.bmp");
				break;
			case 1:
				UI_LifeNumber2->SetTexture("Ui_NumberOne.bmp");
				break;
			case 2:
				UI_LifeNumber2->SetTexture("Ui_NumberTwo.bmp");
				break;
			case 3:
				UI_LifeNumber2->SetTexture("Ui_NumberThree.bmp");
				break;
			case 4:
				UI_LifeNumber2->SetTexture("Ui_NumberFour.bmp");
				break;
			case 5:
				UI_LifeNumber2->SetTexture("Ui_NumberFive.bmp");
				break;
			case 6:
				UI_LifeNumber2->SetTexture("Ui_NumberSix.bmp");
				break;
			case 7:
				UI_LifeNumber2->SetTexture("Ui_NumberSeven.bmp");
				break;
			case 8:
				UI_LifeNumber2->SetTexture("Ui_NumberEight.bmp");
				break;
			case 9:
				UI_LifeNumber2->SetTexture("Ui_NumberNine.bmp");
				break;
			default:
				break;

			}
		}
	}

	//구슬표기
	PlayLevel* NowLevel = dynamic_cast<PlayLevel*>(GetLevel());
	int RemainedMarble = NowLevel->GetRemainedMarble();

	
	int Render1Num = RemainedMarble / 10;
	int Render2Num = RemainedMarble % 10;
	
	switch (Render1Num)
	{
	case 0:
		UI_MarbleNumber1->SetTexture("Ui_NumberZero.bmp");
		break;
	case 1:
		UI_MarbleNumber1->SetTexture("Ui_NumberOne.bmp");
		break;
	case 2:
		UI_MarbleNumber1->SetTexture("Ui_NumberTwo.bmp");
		break;
	case 3:
		UI_MarbleNumber1->SetTexture("Ui_NumberThree.bmp");
		break;
	case 4:
		UI_MarbleNumber1->SetTexture("Ui_NumberFour.bmp");
		break;
	case 5:
		UI_MarbleNumber1->SetTexture("Ui_NumberFive.bmp");
		break;
	case 6:
		UI_MarbleNumber1->SetTexture("Ui_NumberSix.bmp");
		break;
	case 7:
		UI_MarbleNumber1->SetTexture("Ui_NumberSeven.bmp");
		break;
	case 8:
		UI_MarbleNumber1->SetTexture("Ui_NumberEight.bmp");
		break;
	case 9:
		UI_MarbleNumber1->SetTexture("Ui_NumberNine.bmp");
		break;
	default:
		break;

	}

	switch (Render2Num)
	{
	case 0:
		UI_MarbleNumber2->SetTexture("Ui_NumberZero.bmp");
		break;
	case 1:
		UI_MarbleNumber2->SetTexture("Ui_NumberOne.bmp");
		break;
	case 2:
		UI_MarbleNumber2->SetTexture("Ui_NumberTwo.bmp");
		break;
	case 3:
		UI_MarbleNumber2->SetTexture("Ui_NumberThree.bmp");
		break;
	case 4:
		UI_MarbleNumber2->SetTexture("Ui_NumberFour.bmp");
		break;
	case 5:
		UI_MarbleNumber2->SetTexture("Ui_NumberFive.bmp");
		break;
	case 6:
		UI_MarbleNumber2->SetTexture("Ui_NumberSix.bmp");
		break;
	case 7:
		UI_MarbleNumber2->SetTexture("Ui_NumberSeven.bmp");
		break;
	case 8:
		UI_MarbleNumber2->SetTexture("Ui_NumberEight.bmp");
		break;
	case 9:
		UI_MarbleNumber2->SetTexture("Ui_NumberNine.bmp");
		break;
	default:
		break;

	}

}