#include "Player.h"
#include "ContentsEnum.h"
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEnginePlatform/GameEngineWindow.h>

void Player::IdleStart()
{
	ChangeAnimationState("Idle");

	// MainRenderer->ChangeAnimation("Right_Idle");
}

void Player::RunStart()
{
	ChangeAnimationState("Run");
	// MainRenderer->ChangeAnimation("Right_Run");
}

void Player::JumpStart()
{
	// 애니메이션 해야하는데 귀찮음

	SetGravityVector(float4::UP * 1000.0f);
}

void Player::SprintStart()
{
	ChangeAnimationState("RaymanSprint");
	// MainRenderer->ChangeAnimation("Right_Run");
}


void Player::IdleUpdate(float _Delta)
{
	if (true == MainRenderer->IsAnimationEnd())
	{
		++TestValue;
	}

	{
		unsigned int Color = GetGroundColor(RGB(255, 255, 255), DownCheck);
		if (RGB(255, 255, 255) == Color)
		{
			Gravity(_Delta);
		}
		else
		{
			unsigned int CheckColor = GetGroundColor(RGB(255, 255, 255), float4::UP);

			while (CheckColor != RGB(255, 255, 255))
			{
				CheckColor = GetGroundColor(RGB(255, 255, 255), float4::UP);
				AddPos(float4::UP);
			}


			GravityReset();
		}
	}


	if (true == GameEngineInput::IsDown('A')
		|| true == GameEngineInput::IsDown('W')
		|| true == GameEngineInput::IsDown('S')
		|| true == GameEngineInput::IsDown('D'))
	{
		DirCheck();
		ChanageState(PlayerState::Run);
		return;
	}

	if (true == GameEngineInput::IsPress(VK_SPACE))
	{
		ChanageState(PlayerState::Jump);
		return;
	}

	// 줄줄이 사탕으로 
	//if (true)
	//{
	//	ChanageState(PlayerState::Idle);
	//}

}


void Player::RunUpdate(float _Delta)
{
	// 중력 적용 
	{
		unsigned int Color = GetGroundColor(RGB(255, 255, 255), DownCheck);
		if (RGB(255, 255, 255) == Color)
		{
			Gravity(_Delta);
		}
		else
		{
			int a = 0;
			unsigned int CheckColor = GetGroundColor(RGB(255, 255, 255), float4::UP);

			while (CheckColor != RGB(255, 255, 255))
			{
				CheckColor = GetGroundColor(RGB(255, 255, 255), float4::UP);
				AddPos(float4::UP);
			}


			GravityReset();
		}

	}


	DirCheck();

	float Speed = 300.0f;

	float4 MovePos = float4::ZERO;
	float4 CheckPos = float4::ZERO;

	if (true == GameEngineInput::IsPress('A') && GameEngineInput::IsPress('J') && Dir == PlayerDir::Left)
	{
		DirCheck();
		ChanageState(PlayerState::Sprint);
	}
	else if (true == GameEngineInput::IsPress('D') && GameEngineInput::IsPress('J') && Dir == PlayerDir::Right)
	{
		DirCheck();
		ChanageState(PlayerState::Sprint);
	}

	if (true == GameEngineInput::IsPress('A') && Dir == PlayerDir::Left)
	{
		CheckPos = { -30.0f, -50.0f };

		MovePos = { -Speed * _Delta, 0.0f };

		// unsigned int Color = GetGroundColor(RGB(255, 255, 255));

	} else if (true == GameEngineInput::IsPress('D') && Dir == PlayerDir::Right)
	{
		CheckPos = { 30.0f, -50.0f };

		MovePos = { Speed * _Delta, 0.0f };
	}

	

	//if (true == GameEngineInput::IsPress('W'))
	//{
	//	MovePos = { 0.0f, -Speed * _Delta };
	//}
	//if (true == GameEngineInput::IsPress('S'))
	//{
	//	MovePos = { 0.0f, Speed * _Delta };
	//}

	if (MovePos == float4::ZERO)
	{
		DirCheck();
		ChanageState(PlayerState::Idle);
	}

	{
		unsigned int Color = GetGroundColor(RGB(255, 255, 255), CheckPos);

		if (Color == RGB(255, 255, 255))
		{
			AddPos(MovePos);
			GetLevel()->GetMainCamera()->AddPos(MovePos);
		}
	}


}


void Player::JumpUpdate(float _Delta)
{
	Gravity(_Delta);

	//for (size_t i = 0; i < 1000000; i++)
	//{
	//	++A;
	//}

	{
		unsigned int Color = GetGroundColor(RGB(255, 255, 255));
		if (RGB(255, 255, 255) != Color)
		{
			ChanageState(PlayerState::Idle);
			return;
		}
	}

}


void Player::SprintUpdate(float _Delta)
{

	// 중력 적용 
	{
		unsigned int Color = GetGroundColor(RGB(255, 255, 255), DownCheck);
		if (RGB(255, 255, 255) == Color)
		{
			Gravity(_Delta);
		}
		else
		{
			int a = 0;
			unsigned int CheckColor = GetGroundColor(RGB(255, 255, 255), float4::UP);

			while (CheckColor != RGB(255, 255, 255))
			{
				CheckColor = GetGroundColor(RGB(255, 255, 255), float4::UP);
				AddPos(float4::UP);
			}


			GravityReset();
		}

	}


	DirCheck();

	float Speed = 600.0f;

	float4 MovePos = float4::ZERO;
	float4 CheckPos = float4::ZERO;


	if (true == GameEngineInput::IsPress('A') && Dir == PlayerDir::Left)
	{
		CheckPos = { -30.0f, -50.0f };

		MovePos = { -Speed * _Delta, 0.0f };

		// unsigned int Color = GetGroundColor(RGB(255, 255, 255));

	}
	else if (true == GameEngineInput::IsPress('D') && Dir == PlayerDir::Right)
	{
		CheckPos = { 30.0f, -50.0f };

		MovePos = { Speed * _Delta, 0.0f };
	}

	if (true == GameEngineInput::IsUp('J') )
	{
		DirCheck();
		ChanageState(PlayerState::Run);

		// unsigned int Color = GetGroundColor(RGB(255, 255, 255));

	}

	//if (true == GameEngineInput::IsPress('W'))
	//{
	//	MovePos = { 0.0f, -Speed * _Delta };
	//}
	//if (true == GameEngineInput::IsPress('S'))
	//{
	//	MovePos = { 0.0f, Speed * _Delta };
	//}

	if (MovePos == float4::ZERO)
	{
		DirCheck();
		ChanageState(PlayerState::Idle);
	}

	{
		unsigned int Color = GetGroundColor(RGB(255, 255, 255), CheckPos);

		if (Color == RGB(255, 255, 255))
		{
			AddPos(MovePos);
			GetLevel()->GetMainCamera()->AddPos(MovePos);
		}
	}

}

void Player::DebugmodeStart()
{
	ChangeAnimationState("Idle");
	DebugMode = true;
}

void Player::DebugmodeUpdate(float _Delta)
{
	

	DirCheck();



	float4 MovePos = float4::ZERO;


	if (true == GameEngineInput::IsPress('W') && true == GameEngineInput::IsPress('A') )
	{
		MovePos = { -DebugSpeed * _Delta, -DebugSpeed * _Delta };
	}
	else if (true == GameEngineInput::IsPress('W') && true == GameEngineInput::IsPress('D') )
	{
		MovePos = { DebugSpeed * _Delta, -DebugSpeed * _Delta };
	}
	else if (true == GameEngineInput::IsPress('S') && true == GameEngineInput::IsPress('A'))
	{
		MovePos = { -DebugSpeed * _Delta, DebugSpeed * _Delta };
	}
	else if (true == GameEngineInput::IsPress('S') && true == GameEngineInput::IsPress('D'))
	{
		MovePos = { DebugSpeed * _Delta, DebugSpeed * _Delta };
	}
	else if (true == GameEngineInput::IsPress('A') && Dir == PlayerDir::Left)
	{
		MovePos = { -DebugSpeed * _Delta, 0.0f };
	}
	else if (true == GameEngineInput::IsPress('D') && Dir == PlayerDir::Right)
	{
		MovePos = { DebugSpeed * _Delta, 0.0f };
	}
	else if (true == GameEngineInput::IsPress('W'))
	{
		MovePos = { 0.0f, -DebugSpeed * _Delta };
	}
	else if (true == GameEngineInput::IsPress('S'))
	{
		MovePos = { 0.0f, DebugSpeed * _Delta };
	}

	if (true == GameEngineInput::IsDown('1'))
	{
		DebugSpeed -= 100.0f;
	}
	else if (true == GameEngineInput::IsDown('2'))
	{
		DebugSpeed += 100.0f;
	}
	if (DebugSpeed < 0)
	{
		DebugSpeed = 0;
	}

	
	/*if (true == GameEngineInput::IsPress('W') && true == GameEngineInput::IsPress('A'))
	{
		MovePos = { -Speed * _Delta, -Speed * _Delta };
	}
	else if (true == GameEngineInput::IsPress('W') && true == GameEngineInput::IsPress('D'))
	{
		MovePos = { Speed * _Delta, -Speed * _Delta };
	}*/

	AddPos(MovePos);
	GetLevel()->GetMainCamera()->AddPos(MovePos);

	if (true == GameEngineInput::IsPress(VK_SPACE))
	{
		return;
	}


	// 줄줄이 사탕으로 
	//if (true)
	//{
	//	ChanageState(PlayerState::Idle);
	//}

}
