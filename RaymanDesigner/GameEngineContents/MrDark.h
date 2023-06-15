#pragma once
#include <GameEngineCore/GameEngineActor.h>


class MrDark : public GameEngineActor
{

public:
	//constructor destructor
	MrDark();
	~MrDark();

	//delete Function
	MrDark(const MrDark& _Other) = delete;
	MrDark(MrDark&& _Other) noexcept = delete;
	MrDark& operator=(const MrDark& _Other) = delete;
	MrDark&& operator=(MrDark&& _Other) noexcept = delete;


protected:

private:
	void Start() override;
	void Update(float _Delta) override;
	void Render(float _Delta) override;
};  