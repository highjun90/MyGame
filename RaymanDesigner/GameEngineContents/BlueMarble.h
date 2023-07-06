#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineCollision.h>

class BlueMarble : public GameEngineActor
{
public:
	//constructor destructor
	BlueMarble();
	~BlueMarble();

	//delete Function
	BlueMarble(const BlueMarble& _Other) = delete;
	BlueMarble(BlueMarble&& _Other) noexcept = delete;
	BlueMarble& operator=(const BlueMarble& _Other) = delete;
	BlueMarble&& operator=(BlueMarble&& _Other) noexcept = delete;

	GameEngineRenderer* MainRenderer = nullptr;
	GameEngineCollision* BodyCollision = nullptr;
protected:

private:
	void Start() override;
	void Update(float _Delta) override;
};  