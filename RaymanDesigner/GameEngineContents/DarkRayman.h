#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <string>


class DarkRayman : public GameEngineActor
{
public:
	//constructor destructor
	DarkRayman();
	~DarkRayman();

	//delete Function
	DarkRayman(const DarkRayman& _Other) = delete;
	DarkRayman(DarkRayman&& _Other) noexcept = delete;
	DarkRayman& operator=(const DarkRayman& _Other) = delete;
	DarkRayman&& operator=(DarkRayman&& _Other) noexcept = delete;

	void SetPosToPlayer(float4 _Pos)
	{
		PastPosToPlayer = _Pos;
	}

	float4 GetPosToPlayer()
	{
		return PastPosToPlayer;
	}

protected:

private:
	void Start() override;
	void Update(float _Delta) override;

	float4 PastPosToPlayer = float4::ZERO;
	std::string PastAnimationToPlayer = "";
	size_t PastFrameToPlayer = 0;


};  