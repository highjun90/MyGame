#pragma once
#include <GameEngineCore/GameEngineActor.h>

// ���� :
class PlayActor : public GameEngineActor
{
public:
	// constrcuter destructer
	PlayActor();
	~PlayActor();

	// delete Function
	PlayActor(const PlayActor& _Other) = delete;
	PlayActor(PlayActor&& _Other) noexcept = delete;
	PlayActor& operator=(const PlayActor& _Other) = delete;
	PlayActor& operator=(PlayActor&& _Other) noexcept = delete;

	void Gravity(float _Delta);

	void CameraFocus();

	void GravityReset() 
	{
		GravityVector = float4::ZERO;
	}


	void GravityOff() 
	{
		IsGravity = false;
	}

	void SetGroundTexture(const std::string& _GroundTextureName);

	void SetGroundTextureDIvision(const std::string& _GroundTextureName, int _Order);

	// �� ��ġ���� 
	int GetGroundColor(unsigned int _DefaultColor, float4 _Pos = float4::ZERO);

	int GetGroundColorFromDivision(unsigned int _DefaultColor, float4 _Pos = float4::ZERO);

	// ����� �ڽ� ����µ� ����ϰ�����
	float4 ActorCameraPos();

	void SetGravityVector(float4 _GravityVector)
	{
		GravityVector = _GravityVector;
	}

protected:

private:
	class GameEngineWindowTexture* GroundTexture = nullptr;
	class GameEngineWindowTexture* GroundTextureDivision[5];

	bool IsGravity = true;

	float GravityPower = 3000.0f;
	float4 GravityVector = float4::ZERO;

};

