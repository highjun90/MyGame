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

	// 가장기본적인 물리는 모든힘이 다 +진게 나의 이동 방햐이 된다.
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
	



	//카메라 이동하는 기능있고 카메라 오버기능 막는것도 있음. 원래는 Player_State에 있었음
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
		MsgBoxAssert("존재하지 않는 텍스처로 픽셀충돌을 하려고 했습니다.");
	}

}

void PlayActor::SetGroundTextureDIvision(const std::string& _GroundTextureName, int _Order)
{
	GroundTextureDivision[_Order] = ResourcesManager::GetInst().FindTexture(_GroundTextureName);

	if (nullptr == GroundTextureDivision[_Order])
	{
		MsgBoxAssert("존재하지 않는 텍스처로 픽셀충돌을 하려고 했습니다.");
	}

}

int PlayActor::GetGroundColor(unsigned int _DefaultColor, float4 _Pos)
{
	if (nullptr == GroundTexture)
	{
		MsgBoxAssert("땅 체크용 텍스처가 존재하지 않습니다.");
	}

	return GroundTexture->GetColor(_DefaultColor, GetPos() + _Pos);
}


int PlayActor::GetGroundColorFromDivision(unsigned int _DefaultColor, float4 _Pos)
{




	if (nullptr == GroundTexture)
	{
		MsgBoxAssert("땅 체크용 텍스처가 존재하지 않습니다.");
	}

	return GroundTexture->GetColor(_DefaultColor, GetPos() + _Pos);
}


// Actor 위치에서 카메라 위치를 빼는 백터 ==  
float4 PlayActor::ActorCameraPos()
{
	return GetPos() - GetLevel()->GetMainCamera()->GetPos();
}