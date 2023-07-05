#pragma once
#include "PlayActor.h"


class FadeObjectReverse : public PlayActor
{
public:
	//constructor destructor
	FadeObjectReverse();
	~FadeObjectReverse();

	//delete Function
	FadeObjectReverse(const FadeObjectReverse& _Other) = delete;
	FadeObjectReverse(FadeObjectReverse&& _Other) noexcept = delete;
	FadeObjectReverse& operator=(const FadeObjectReverse& _Other) = delete;
	FadeObjectReverse&& operator=(FadeObjectReverse&& _Other) noexcept = delete;


	/*void SetFade(bool _Fade)
	{
		FadeDir = _Fade;
	}

	float GetValue()
	{
		return Value;
	}*/
protected:

private:

};  