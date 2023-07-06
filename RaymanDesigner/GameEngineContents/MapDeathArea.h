#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineCollision.h>

class MapDeathArea : public GameEngineActor
{
public:
	//constructor destructor
	MapDeathArea();
	~MapDeathArea();

	//delete Function
	MapDeathArea(const MapDeathArea& _Other) = delete;
	MapDeathArea(MapDeathArea&& _Other) noexcept = delete;
	MapDeathArea& operator=(const MapDeathArea& _Other) = delete;
	MapDeathArea&& operator=(MapDeathArea&& _Other) noexcept = delete;

	GameEngineCollision* DeathAreaCollision = nullptr;


protected:

private:	
	void Start() override;
	void Update(float _Delta) override;
};  