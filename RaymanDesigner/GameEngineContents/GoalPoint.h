#pragma once
#include <GameEngineCore/GameEngineActor.h>

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

protected:

private:
	void Start() override;
	void Update(float _Delta) override;


};  