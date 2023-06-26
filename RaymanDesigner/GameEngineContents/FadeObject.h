#pragma once
#include "PlayActor.h"

// Ό³Έν :
class FadeObject : public PlayActor
{
public:
	// constrcuter destructer
	FadeObject();
	~FadeObject();

	// delete Function
	FadeObject(const FadeObject& _Other) = delete;
	FadeObject(FadeObject&& _Other) noexcept = delete;
	FadeObject& operator=(const FadeObject& _Other) = delete;
	FadeObject& operator=(FadeObject&& _Other) noexcept = delete;

	void SetFade(bool _Fade)
	{
		FadeDir = _Fade;
	}

	float GetValue()
	{
		return Value;
	}

protected:

private:
	float Value = 255.0f;
	bool FadeDir = true;
	GameEngineRenderer* Render;

	void Start() override;
	void Update(float _Time) override;
};

