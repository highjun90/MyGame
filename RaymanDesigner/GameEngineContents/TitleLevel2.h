#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include "FadeObject.h"


// Ό³Έν :
class TitleLevel2 : public GameEngineLevel
{
public:
	// constrcuter destructer

	TitleLevel2();
	~TitleLevel2();

	// delete Function
	TitleLevel2(const TitleLevel2& _Other) = delete;
	TitleLevel2(TitleLevel2&& _Other) noexcept = delete;
	TitleLevel2& operator=(const TitleLevel2& _Other) = delete;
	TitleLevel2& operator=(TitleLevel2&& _Other) noexcept = delete;

	bool AutoLevelChange = false;

protected:


private:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;


	class BackGround* BackGroundPtr = nullptr;
	FadeObject* FObject = nullptr;



};

