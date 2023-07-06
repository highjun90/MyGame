#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <string>
#include <vector>
#include <map>

#include "Player.h"

class Player;
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

	GameEngineRenderer* DarkRaymanRenderer = nullptr;
	GameEngineCollision* DarkRaymanCollsion = nullptr;

	void SetRaymanPtr(Player* _RaymanPtr) 
	{
		RaymanPtr = _RaymanPtr;
	}

	Player* GetRaymanPtr()
	{
		return RaymanPtr;
	}

	class PastRaymanData
	{
	public:
		float4 Pos = float4::ZERO;
		//float4 Scale = float4::ZERO;
		std::string AnimationName = "";
		size_t AnimationCurFrame = 0;
	};


	void SetChase(bool _Chase)
	{
		Chase = _Chase;
	}
	bool GetChase()
	{
		return Chase;
	}

	void SetRecordRayman(bool _Record)
	{
		RecordRayman = _Record;
	}
	bool GetRecordRayman()
	{
		return RecordRayman;
	}

	void RecordRaymanData();
	void AddRaymanData();
	void AddRaymanData(int _Index);
	void ChaseRayman();

	void Die();

	void Restart();

protected:

private:
	void Start() override;
	void Update(float _Delta) override;
	void Render(float _Delta) override;

	class Player* RaymanPtr = nullptr;

	bool Live = true;
	bool RecordRayman = true;
	bool Chase = false;
	

	std::vector<PastRaymanData*> PastRaymanDatas;
	int TotalNum_PastRaymanDatas = 0;
	int Index_PastRaymanDatas = 0;


	std::map<std::string, std::string> Matching_RaymanAniname;
};  