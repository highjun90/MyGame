#include "PlayActor.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/ResourcesManager.h>
#include "GlobalValue.h"

PlayActor::PlayActor() 
{
}

PlayActor::~PlayActor() 
{
	
}

void PlayActor::Gravity(float _Delta) 
{
	if (false == IsGravity)
	{
		return;
	}

	// ����⺻���� ������ ������� �� +���� ���� �̵� ������ �ȴ�.
	GravityVector += float4::DOWN * GravityPower * _Delta;

	if (GravityVector.Y > 1200)
	{
		GravityVector -= float4::DOWN * GravityPower * _Delta;
	}

	AddPos(GravityVector * _Delta);
}

void PlayActor::CameraFocus() 
{
	float4 WindowScale = GameEngineWindow::MainWindow.GetScale();
	GetLevel()->GetMainCamera()->SetPos(GetPos() + float4{ -WindowScale.hX(), -WindowScale.hY() -100.0f });
	



	//ī�޶� �̵��ϴ� ����ְ� ī�޶� ������� ���°͵� ����. ������ Player_State�� �־���
	float4 CameraPos = GetLevel()->GetMainCamera()->GetPos();
	if (0 >= CameraPos.X)
	{
		CameraPos.X = 0.0f;
	}
	if (0 >= CameraPos.Y)
	{
		CameraPos.Y = 0.0f;
	}
	if (GlobalValue::MapScale.X <= CameraPos.X + WindowScale.X)
	{
		CameraPos.X = GlobalValue::MapScale.X - WindowScale.X;
	}
	if (GlobalValue::MapScale.Y <= CameraPos.Y + WindowScale.Y)
	{
		CameraPos.Y = GlobalValue::MapScale.Y - WindowScale.Y;
	}
	GetLevel()->GetMainCamera()->SetPos(CameraPos);
	
}


void PlayActor::SetGroundTexture(const std::string& _GroundTextureName)
{
	GroundTexture = ResourcesManager::GetInst().FindTexture(_GroundTextureName);

	if (nullptr == GroundTexture)
	{
		MsgBoxAssert("�������� �ʴ� �ؽ�ó�� �ȼ��浹�� �Ϸ��� �߽��ϴ�.");
	}

}

void PlayActor::SetGroundTextureDIvision(const std::string& _GroundTextureName, int _Order)
{
	GroundTextureDivision[_Order] = ResourcesManager::GetInst().FindTexture(_GroundTextureName);

	if (nullptr == GroundTextureDivision[_Order])
	{
		MsgBoxAssert("�������� �ʴ� �ؽ�ó�� �ȼ��浹�� �Ϸ��� �߽��ϴ�.");
	}

}

int PlayActor::GetGroundColor(unsigned int _DefaultColor, float4 _Pos)
{
	if (nullptr == GroundTexture)
	{
		MsgBoxAssert("�� üũ�� �ؽ�ó�� �������� �ʽ��ϴ�.");
	}

	return GroundTexture->GetColor(_DefaultColor, GetPos() + _Pos);
}


int PlayActor::GetGroundColorFromDivision(unsigned int _DefaultColor, float4 _Pos)
{




	if (nullptr == GroundTexture)
	{
		MsgBoxAssert("�� üũ�� �ؽ�ó�� �������� �ʽ��ϴ�.");
	}

	return GroundTexture->GetColor(_DefaultColor, GetPos() + _Pos);
}


// Actor ��ġ���� ī�޶� ��ġ�� ���� ���� ==  
float4 PlayActor::ActorCameraPos()
{
	return GetPos() - GetLevel()->GetMainCamera()->GetPos();
}