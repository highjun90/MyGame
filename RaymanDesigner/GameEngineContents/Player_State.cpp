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
	ChangeAnimationState("RaymanJump");
	SetGravityVector(float4::UP * 1100.0f);
}

void Player::JumpHoldStart()
{
	ChangeAnimationState("RaymanJumpHold");
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

	if (true == GameEngineInput::IsPress('A')
		|| true == GameEngineInput::IsPress('D'))
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

	float Speed = 350.0f;

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

	if (true == GameEngineInput::IsPress('A') && GameEngineInput::IsPress(VK_SPACE) && Dir == PlayerDir::Left)
	{
		DirCheck();
		SetJumpSpeed(450.0f);
		ChanageState(PlayerState::Jump);
	}
	else if (true == GameEngineInput::IsPress('D') && GameEngineInput::IsPress(VK_SPACE) && Dir == PlayerDir::Right)
	{
		DirCheck();
		SetJumpSpeed(450.0f);
		ChanageState(PlayerState::Jump);
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

	if (true == GameEngineInput::IsPress('A') && true == GameEngineInput::IsPress('D'))
	{
		Dir = PlayerDir::Right;
		CheckPos = { -30.0f, -50.0f };

		MovePos = { Speed * _Delta, 0.0f };

	}
	else if (true == GameEngineInput::IsPress('D') && true == GameEngineInput::IsPress('A'))
	{
		Dir = PlayerDir::Left;
		CheckPos = { 30.0f, -50.0f };

		MovePos = { -Speed * _Delta, 0.0f };
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
	DirCheck();

	float Speed = GetJumpSpeed();
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



	{
		unsigned int Color = GetGroundColor(RGB(255, 255, 255), CheckPos);

		if (Color == RGB(255, 255, 255))
		{
			// MovePos를 바꿔버리는 방법이 있을것이고.

			if (RGB(255, 255, 255) == GetGroundColor(RGB(255, 255, 255), MovePos))
			{
				float4 XPos = float4::ZERO;
				float4 Dir = MovePos.X <= 0.0f ? float4::RIGHT : float4::LEFT;

				while (RGB(255, 0, 0) != GetGroundColor(RGB(255, 255, 255), MovePos + XPos))
				{
					XPos += Dir;

					if (abs(XPos.X) > 50.0f)
					{
						break;
					}
				}

				float4 YPos = float4::ZERO;
				while (RGB(255, 0, 0) != GetGroundColor(RGB(255, 255, 255), MovePos + YPos))
				{
					YPos.Y += 1;

					if (YPos.Y > 60.0f)
					{
						break;
					}
				}

				if (abs(XPos.X) >= YPos.Y)
				{
					while (RGB(255, 0, 0) != GetGroundColor(RGB(255, 255, 255), MovePos))
					{
						MovePos.Y += 1;
					}
				}

			}

			// 내가 움직이려는 
			// GetGroundColor(RGB(255, 255, 255), MovePos);

			AddPos(MovePos);
			//GetLevel()->GetMainCamera()->AddPos(MovePos);
			//원래는 Play_State에서 카메라 화면 이동했는데 카메라 오버 막는 기능 추가하면서 PlayActor로 기능이 이동함
		}
	}



	//AddPos(MovePos);
	{
		unsigned int Color = GetGroundColor(RGB(255, 255, 255), DownCheck);
		if (RGB(255, 255, 255) != Color)
		{
			ChanageState(PlayerState::Idle);
			return;
		}
	}

	if (MainRenderer->GetCurFrame() == 29)
	{
		ChanageState(PlayerState::JumpHold);
	}
}

void Player::JumpHoldUpdate(float _Delta)
{
	Gravity(_Delta);
	DirCheck();


	float Speed = GetJumpSpeed();
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



	{
		unsigned int Color = GetGroundColor(RGB(255, 255, 255), CheckPos);

		if (Color == RGB(255, 255, 255))
		{
			// MovePos를 바꿔버리는 방법이 있을것이고.

			if (RGB(255, 255, 255) == GetGroundColor(RGB(255, 255, 255), MovePos))
			{
				float4 XPos = float4::ZERO;
				float4 Dir = MovePos.X <= 0.0f ? float4::RIGHT : float4::LEFT;

				while (RGB(255, 0, 0) != GetGroundColor(RGB(255, 255, 255), MovePos + XPos))
				{
					XPos += Dir;

					if (abs(XPos.X) > 50.0f)
					{
						break;
					}
				}

				float4 YPos = float4::ZERO;
				while (RGB(255, 0, 0) != GetGroundColor(RGB(255, 255, 255), MovePos + YPos))
				{
					YPos.Y += 1;

					if (YPos.Y > 60.0f)
					{
						break;
					}
				}

				if (abs(XPos.X) >= YPos.Y)
				{
					while (RGB(255, 0, 0) != GetGroundColor(RGB(255, 255, 255), MovePos))
					{
						MovePos.Y += 1;
					}
				}

			}

			// 내가 움직이려는 
			// GetGroundColor(RGB(255, 255, 255), MovePos);

			AddPos(MovePos);
			//GetLevel()->GetMainCamera()->AddPos(MovePos);
			//원래는 Play_State에서 카메라 화면 이동했는데 카메라 오버 막는 기능 추가하면서 PlayActor로 기능이 이동함
		}
	}



	//AddPos(MovePos);
	{
		unsigned int Color = GetGroundColor(RGB(255, 255, 255), DownCheck);
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


	float Speed = 700.0f;

	float4 MovePos = float4::ZERO;
	float4 CheckPos = float4::ZERO;
	bool DualKeyState = false;
	int FirstInputKey = 0;

	//달리면서 뛰기
	if (true == GameEngineInput::IsPress('A') && GameEngineInput::IsPress(VK_SPACE) && Dir == PlayerDir::Left)
	{
		DirCheck();
		SetJumpSpeed(800.0f);
		ChanageState(PlayerState::Jump);
	}
	else if (true == GameEngineInput::IsPress('D') && GameEngineInput::IsPress(VK_SPACE) && Dir == PlayerDir::Right)
	{
		DirCheck();
		SetJumpSpeed(800.0f);
		ChanageState(PlayerState::Jump);
	}


	if (true == GameEngineInput::IsPress('D') && true == GameEngineInput::IsDown('A'))
	{
		DualKeyState = true;
		FirstInputKey = 1;
	}

	if (true == GameEngineInput::IsPress('A') && true == GameEngineInput::IsDown('D'))
	{
		DualKeyState = true;
		FirstInputKey = 2;
	}


	if (true == GameEngineInput::IsPress('D') && true == GameEngineInput::IsPress('A') )
	{
		if (FirstInputKey == 1)
		{

			CheckPos = { 30.0f, -50.0f };

			MovePos = { Speed * _Delta, 0.0f };
		}
		else if (FirstInputKey == 2)
		{
			CheckPos = { -30.0f, -50.0f };

			MovePos = { -Speed * _Delta, 0.0f };
		}
	}

	if (true == GameEngineInput::IsUp('D') || true == GameEngineInput::IsUp('A'))
	{
		DualKeyState = false;
		FirstInputKey = 0;
	}


	if (DualKeyState == false)
	{

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
	}


	if (true == GameEngineInput::IsUp('A') || true == GameEngineInput::IsUp('D'))
	{
		DirCheck();
		ChanageState(PlayerState::Idle);

		// unsigned int Color = GetGroundColor(RGB(255, 255, 255));

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

	if (true == GameEngineInput::IsDown('Q'))
	{
		DebugSpeed -= 100.0f;
	}
	else if (true == GameEngineInput::IsDown('E'))
	{
		DebugSpeed += 100.0f;
	}
	if (DebugSpeed < 0)
	{
		DebugSpeed = 0;
	}

	if (true == GameEngineInput::IsDown('3'))
	{
		float4 EndPoint = {13200, 2850 };
		SetPos(EndPoint);
	}

	if (true == GameEngineInput::IsDown('4'))
	{
		SetPos(DebugStartPoint);
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
