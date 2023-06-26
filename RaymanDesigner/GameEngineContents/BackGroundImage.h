#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <string>



class BackGroundImage : public GameEngineActor
{
public:
	//constructor destructor
	BackGroundImage();
	~BackGroundImage();

	//delete Function
	BackGroundImage(const BackGroundImage& _Other) = delete;
	BackGroundImage(BackGroundImage&& _Other) noexcept = delete;
	BackGroundImage& operator=(const BackGroundImage& _Other) = delete;
	BackGroundImage&& operator=(BackGroundImage&& _Other) noexcept = delete;

	void Init(const std::string& _FileName);


	void SetScale(float4 _Scale)
	{
		Scale = _Scale;
	}

	float4 GetScale()
	{
		return Scale;
	}


protected:

private:
	std::string FileName;
	class GameEngineRenderer* Renderer;

	float4 Scale = float4::ZERO;

	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
};  