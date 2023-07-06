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

	//�÷��̾ Ű�����鼭 �������ٲ����ְ� �س�
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

	//�����ٸ����� ���̰�
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

	//��ó���� ����, �浹����
	GoalRenderer->Off();

	GoalPointCollision = CreateCollision(CollisionOrder::GoalPoint);
	GoalPointCollision->SetCollisionScale({ 10, 2 });
	GoalPointCollision->SetCollisionType(CollisionType::Rect);

	GoalPointCollision->Off();
}