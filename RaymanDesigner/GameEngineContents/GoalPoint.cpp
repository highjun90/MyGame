#include "GoalPoint.h"
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include "ContentsEnum.h"



GoalPoint::GoalPoint()
{
}

GoalPoint::~GoalPoint()
{
}

void GoalPoint::Update(float _Delta)
{
	
}

void GoalPoint::Start()
{
	SetPos({ 1750 , 2690 });

	if (false == ResourcesManager::GetInst().IsLoadTexture("GoalPoint.bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Texture\\Player\\");
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("GoalPoint.bmp"));
	}

	{
		GoalRenderer = CreateRenderer("GoalPoint.bmp", RenderOrder::Play);
	}

}