#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineCollision.h>

class GoalPoint : public GameEngineActor
{
public:
	//constructor destructor
	GoalPoint();
	~GoalPoint();

	//delete Function
	GoalPoint(const GoalPoint& _Other) = delete;
	GoalPoint(GoalPoint&& _Other) noexcept = delete;
	GoalPoint& operator=(const GoalPoint& _Other) = delete;
	GoalPoint&& operator=(GoalPoint&& _Other) noexcept = delete;

	GameEngineRenderer* GoalRenderer = nullptr;

	GameEngineRenderer* GetGoalRenderer()
	{
		return GoalRenderer;
	}

	static void ChangeGoalPointRenderTrue()
	{
		GoalPointIsRender = true;
	}
	static void ChangeGoalPointRenderFalse()
	{
		GoalPointIsRender = false;
	}
	static bool GetGoalPointIsRender()
	{
		return GoalPointIsRender;
	}

	static GameEngineCollision* GetGoalPointCollision()
	{
		return GoalPointCollision;
	}

	float4 GetGoalPointPos()
	{
		return GoalPointPos;
	}


protected:

private:
	void Start() override;
	void Update(float _Delta) override;

	static GoalPoint* MainGoalPoint;
    static bool GoalPointIsRender;
	static GameEngineCollision* GoalPointCollision;

	float4 GoalPointPos = { 12883, 2854 };
};  