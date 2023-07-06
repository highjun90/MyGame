#include "GoalPoint.h"
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include "PlayLevel.h"

#include "ContentsEnum.h"

GoalPoint* GoalPoint::MainGoalPoint = nullptr;
bool GoalPoint::GoalPointIsRender = false;
GameEngineCollision* GoalPoint::GoalPointCollision = nullptr;

GoalPoint::GoalPoint()
{
}

GoalPoint::~GoalPoint()
{
}

void GoalPoint::Update(float _Delta)
{

	//플레이어가 키누르면서 렌더껐다끌수있게 해놈
	bool CheckGoalPointUpdate = GoalPoint::GetGoalPointIsRender();
	if (CheckGoalPointUpdate == true)
	{
		GoalRenderer->On();
		GoalPointCollision->On();
	}
	else if(CheckGoalPointUpdate == false)
	{
		GoalRenderer->Off();
		GoalPointCollision->Off();
	}

	//구슬다먹으면 보이게
	PlayLevel* NowLevel = dynamic_cast<PlayLevel*>(GetLevel());
	int RemainedMarble = NowLevel->GetRemainedMarble();
	if (RemainedMarble <= 0)
	{
		GoalRenderer->On();
		GoalPointCollision->On();
	}

}

void GoalPoint::Start()
{
	float4 Pos = GetGoalPointPos();
	SetPos(Pos);

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

	//맨처음엔 렌더, 충돌없음
	GoalRenderer->Off();

	GoalPointCollision = CreateCollision(CollisionOrder::GoalPoint);
	GoalPointCollision->SetCollisionScale({ 10, 2 });
	GoalPointCollision->SetCollisionType(CollisionType::Rect);

	GoalPointCollision->Off();
}