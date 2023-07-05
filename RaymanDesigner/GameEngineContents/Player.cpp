#include "Player.h"
#pragma region Headers

#include "ContentsEnum.h"
#include <Windows.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEnginePath.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>
#include <GameEnginePlatform/GameEngineSound.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "Bullet.h"
#include "Monster.h"
#include "PlayUIManager.h"
#include "PlayLevel.h"
#include "GoalPoint.h"
#include <GameEnginePlatform/GameEngineInput.h>

#pragma endregion

Player* Player::MainPlayer = nullptr;

Player::Player() 
{
}

Player::~Player() 
{
}


void Player::Start()
{
	if (false == ResourcesManager::GetInst().IsLoadTexture("Idle_RIght.bmp"))
	{
		DebugStartPoint = { 1300,2500 };
		//DebugStartPoint = { 0,0 };
		SetPos(DebugStartPoint);

		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");

		GameEnginePath FolderPath = FilePath;

		FilePath.MoveChild("ContentsResources\\Texture\\Player\\");

		// ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Left_Player.bmp"));

		//�������ֱ� ��������Ʈ ���
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Idle_Left.bmp"), 5, 3);
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Idle_RIght.bmp"), 5, 3);

		//�ȱ� ��������Ʈ ���
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Left_Player.bmp"), 5, 7);
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Right_Player.bmp"), 5, 7);

		//������Ʈ ��������Ʈ ���
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Left_RaymanSprint.bmp"), 31, 1);
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Right_RaymanSprint.bmp"), 31, 1);

		//������Ʈ���� ��������Ʈ ���
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Left_RaymanSprintJump.bmp"), 14, 1);
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Right_RaymanSprintJump.bmp"), 14, 1);

		//���� ��������Ʈ ���
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Left_RaymanJump.bmp"), 42, 1);
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Right_RaymanJump.bmp"), 42, 1);

		//�¸���� ��������Ʈ ���
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Left_RaymanVictory.bmp"), 39, 1);
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Right_RaymanVictory.bmp"), 39, 1);

		//�ױ� ��������Ʈ ���
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Left_RaymanDie.bmp"), 10, 1);
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Right_RaymanDie.bmp"), 10, 1);

		//�ױ� �� ��Ʈ����Ʈ ���
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("RaymanDieLight.bmp"), 7, 1);

		//UI ���
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_LifeAndHp.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_LeftDownMarble.bmp"));

		//�������ڵ�
	/*	FolderPath.MoveChild("ContentsResources\\Texture\\");
		ResourcesManager::GetInst().CreateSpriteFolder("FolderPlayer", FolderPath.PlusFilePath("FolderPlayer"));

		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Test.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("HPBar.bmp"));*/
	}

	{

		MainRenderer = CreateRenderer(200);

		// MainRenderer->SetRenderScale({ 200, 200 });
		// MainRenderer->SetSrite("Left_Player.bmp");
		//MainRenderer->CreateAnimation("Test", "FolderPlayer");


		//������ �ֱ� �ִϸ��̼� ���
		MainRenderer->CreateAnimation("Left_Idle", "Idle_Left.bmp", 0, 10, 0.1f, true);
		MainRenderer->CreateAnimation("Right_Idle", "Idle_RIght.bmp", 0, 10, 0.1f, true);

		// MainRenderer->CreateAnimation("Right_Idle", "FolderPlayer");

		//�ȱ� �ִϸ��̼� ���
		MainRenderer->CreateAnimation("Left_Run", "Left_Player.bmp", 0, 31, 0.02f, true);
		MainRenderer->CreateAnimation("Right_Run", "Right_Player.bmp", 0, 31, 0.02f, true);

		//������Ʈ �ִϸ��̼� ���
		MainRenderer->CreateAnimation("Left_RaymanSprint", "Left_RaymanSprint.bmp", 26, 0, 0.035f, true);
		MainRenderer->CreateAnimation("Right_RaymanSprint", "Right_RaymanSprint.bmp", 0, 26, 0.035f, true);

		//������Ʈ���� �ִϸ��̼� ���
		MainRenderer->CreateAnimation("Left_RaymanSprintJump", "Left_RaymanSprintJump.bmp", 0, 13, 0.04f, true);
		MainRenderer->CreateAnimation("Right_RaymanSprintJump", "Right_RaymanSprintJump.bmp", 0, 13, 0.04f, true);

		//���� �ִϸ��̼� ���
		MainRenderer->CreateAnimation("Left_RaymanJump", "Left_RaymanJump.bmp", 0, 29, 0.025f, false);
		MainRenderer->CreateAnimation("Right_RaymanJump", "Right_RaymanJump.bmp", 0, 29, 0.025f, false);
		//���� �ϰ����� �ִϸ��̼� ���
		MainRenderer->CreateAnimation("Left_RaymanJumpHold", "Left_RaymanJump.bmp", 30, 41, 0.04f, true);
		MainRenderer->CreateAnimation("Right_RaymanJumpHold", "Right_RaymanJump.bmp", 30, 41, 0.04f, true);

		//�¸���� �ִϸ��̼� ���
		MainRenderer->CreateAnimation("Left_RaymanVictory", "Left_RaymanVictory.bmp", 0, 38, 0.06f, false);
		MainRenderer->CreateAnimation("Right_RaymanVictory", "Right_RaymanVictory.bmp", 0, 38, 0.06f, false);

		//�ױ� �ִϸ��̼� ���
		MainRenderer->CreateAnimation("Left_RaymanDie", "Left_RaymanDie.bmp", 0, 9, 0.04f, false);
		MainRenderer->CreateAnimation("Right_RaymanDie", "Right_RaymanDie.bmp", 0, 9, 0.04f, false);

		//�ױ� �� �ִϸ��̼� ���
		MainRenderer->CreateAnimation("RaymanDieLight", "RaymanDieLight.bmp", 0, 6, 0.08f, false);

	
		MainRenderer->SetRenderScaleToTexture();

		////��ũ���̸� ������ �÷��̾�� ���� ���ֱ�
		//float4 DarkRaymanScale = MainRenderer->GetRenderScale();

		//DarkRaymanPtr->DarkRaymanRenderer->SetRenderScale(DarkRaymanScale);
		//int a = 0;
	
	}

	//hp�� �������ڵ�
	//{
	//	HPRender = CreateRenderer("HPBar.bmp", RenderOrder::Play);
	//	HPRender->SetRenderPos({ 0, -200 });
	//	HPRender->SetRenderScale({ 40, 40 });
	//	HPRender->SetTexture("HPBar.bmp");
	//	// Ptr->SetText("�����ʤ��Ӥ�����ä��Ӥ�����ä��Ӥ�����ä������뷯���Ӥ������Τø���", 40);
	//}

	/*{
		GameEngineRenderer* Ptr = CreateRenderer("HPBar.bmp", RenderOrder::Play);
		Ptr->SetRenderPos({ 0, -100 });
		Ptr->SetRenderScale({ 200, 40 });
		Ptr->SetTexture("HPBar.bmp");

	}*/

	//Player�� �浹ü�ϳ��� ����Ű�� ������
	{
		BodyCollsion = CreateCollision(CollisionOrder::PlayerBody);
		BodyCollsion->SetCollisionScale({ 60, 120 });
		BodyCollsion->SetCollisionType(CollisionType::Rect);
	}

	//ChanageState(PlayerState::Idle);
	ChanageState(PlayerState::JumpHold);
	Dir = PlayerDir::Right;


	//BGM �÷��̾ Level���� ��������
	PlayLevel* MyLevel = dynamic_cast<PlayLevel*>(GetLevel());
	MyLevel->GetBGMPlayerToPlayLevel();
	BGMPlayerToPlayer = MyLevel->GetBGMPlayerToPlayLevel();


	//�¸����� ���
	if (nullptr == GameEngineSound::FindSound("Victory.mp3"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Sound\\");

		GameEngineSound::SoundLoad(FilePath.PlusFilePath("Victory.mp3"));
	}

	//�ױ���� ���
	if (nullptr == GameEngineSound::FindSound("RaymanDie.mp3"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Sound\\");

		GameEngineSound::SoundLoad(FilePath.PlusFilePath("RaymanDie.mp3"));
	}
}

void Player::Update(float _Delta)
{

	// �ִϸ��̼� �� ����Ŭ ������ �ٸ� �ൿ�� �ϰ��ϴ� �ڵ�
	/*if (true == MainRenderer->IsAnimation("Left_Idle")
		&& true == MainRenderer->IsAnimationEnd())
	{
		
		Dir = PlayerDir::Right;
		ChangeAnimationState(CurState);
	}*/
	//���ô� ���ʰ����� �ִ� �ִϸ��̼� ������ ������ ������ �ִϸ��̼����� �ٲٰ� �س��


	void CameraPosToDir();

	std::vector<GameEngineCollision*> _Col;
	if (true == BodyCollsion->Collision(CollisionOrder::MonsterBody, _Col
		, CollisionType::CirCle // ���� �簢������ ����
		, CollisionType::CirCle // ��뵵 �簢������ ����
	))
	{
		for (size_t i = 0; i < _Col.size(); i++)
		{
			GameEngineCollision* Collison = _Col[i];

			GameEngineActor* Actor = Collison->GetActor();

			Actor->Death();
		}
		// ���� ���Ͷ� �浹�Ѱž�.
	}

	//������Ʈ �浹üũ
	std::vector<GameEngineCollision*> _GoalCollisionTest;
	if (true == BodyCollsion->Collision(CollisionOrder::GoalPoint, _GoalCollisionTest
		, CollisionType::Rect // ���� �簢������ ����
		, CollisionType::Rect // ��뵵 �簢������ ����
	))
	{
		ChanageState(PlayerState::Victory);
	}

	//��ũ���̸� �� �浹üũ
	std::vector<GameEngineCollision*> _DarkRaymanBodyCol;
	if (true == BodyCollsion->Collision(CollisionOrder::DarkRayManBody, _DarkRaymanBodyCol
		, CollisionType::Rect // ���� �簢������ ����
		, CollisionType::Rect // ��뵵 �簢������ ����
	))
	{
		ChanageState(PlayerState::Die);
	}



	if (true == GameEngineInput::IsPress('L'))
	{
		// GameEngineSound::SoundLoad("C:\\AAAA\\AAAA\\A\\AAA.Mp3");
		// GameEngineSound::SoundPlay("AAA.Mp3");
		// GameEngineSound::PlayBgm("AAA.Mp3");
		// GameEngineSound::StopBgm("AAA.Mp3");

		//GameEngineWindow::MainWindow.AddDoubleBufferingCopyScaleRatio(1.0f * _Delta);

		// Monster::AllMonsterDeath();
	}

	// ����� ���ڿ� Ű�� ����
	if (true == GameEngineInput::IsDown('C'))
	{
		if (DebugModeText == false)
		{
			DebugModeText = true;
		}
		else if (DebugModeText == true)
		{
			DebugModeText = false;
		}
	}


	//����� ���
	if (true == GameEngineInput::IsDown('V'))
	{
		if (DebugMode == false)
		{
			DebugMode = true;
			BodyCollsion->Off();
			ChanageState(PlayerState::Debugmode);
		}
		else if(DebugMode == true)
		{
			GravityReset();

			DebugMode = false;
			BodyCollsion->On();
			ChanageState(PlayerState::JumpHold);
		}
		
	}


	// �浹ü ǥ��
	if (true == GameEngineInput::IsDown(VK_F2))
	{
		//GameEngineWindow::MainWindow.AddDoubleBufferingCopyScaleRatio(-1.0f * _Delta);
		GameEngineLevel::CollisionDebugRenderSwitch();
	}


	//����, �������� �����̵�
	if (true == GameEngineInput::IsDown(VK_F3))
	{
		SetPos(DebugStartPoint);
	}
	if (true == GameEngineInput::IsDown(VK_F4))
	{
		float4 EndPoint = { 13200, 2850 };
		SetPos(EndPoint);
	}

	//������Ʈ Ű�� ����
	if (true == GameEngineInput::IsDown(VK_F5))
	{
		bool GoalPointRender = GoalPoint::GetGoalPointIsRender();

		if (GoalPointRender == false)
		{
			GoalPoint::ChangeGoalPointRenderTrue();

			GameEngineCollision* GoalCollision = GoalPoint::GetGoalPointCollision();
			GoalCollision->On();
		}
		else if (GoalPointRender == true)
		{
			GoalPoint::ChangeGoalPointRenderFalse();

			GameEngineCollision* GoalCollision = GoalPoint::GetGoalPointCollision();
			GoalCollision->Off();
		}

	}

	//������� Ű�� ����
	if (true == GameEngineInput::IsDown(VK_F6))
	{
		if (DebugPointIsRender == false)
		{
			DebugPointIsRender = true;
		}
		else if (DebugPointIsRender == true)
		{
			DebugPointIsRender = false;
		}
	}

	//���� ���� Ű��
	if (true == GameEngineInput::IsDown(VK_F7))
	{
		if (SoundPlaying == false)
		{
			*(BGMPlayerToPlayer) = GameEngineSound::SoundPlay("CandyChateauBGM.ogg");
			SoundPlaying = true;
		}
		else if (SoundPlaying == true)
		{
			BGMPlayerToPlayer->Stop();
			SoundPlaying = false;
		}

	}

	

	

	//�������

	StateUpdate(_Delta);

	CameraFocus();

	// Gravity();
}


void Player::StateUpdate(float _Delta)
{
	switch (State)
	{
	case PlayerState::Idle:
		return IdleUpdate(_Delta);
	case PlayerState::Run:
		return RunUpdate(_Delta);
	case PlayerState::Jump:
		return JumpUpdate(_Delta);
	case PlayerState::JumpHold:
		return JumpHoldUpdate(_Delta);
	case PlayerState::Sprint:
		return SprintUpdate(_Delta);
	case PlayerState::SprintJump:
		return SprintJumpUpdate(_Delta);
	case PlayerState::Victory:
		return VictoryUpdate(_Delta);
	case PlayerState::Die:
		return DieUpdate(_Delta);
	case PlayerState::Debugmode:
		return DebugmodeUpdate(_Delta);
	default:
		break;
	}

}

void Player::ChanageState(PlayerState _State)
{
	if (_State != State)
	{
		switch (_State)
		{
		case PlayerState::Idle:
			IdleStart();
			break;
		case PlayerState::Run:
			RunStart();
			break;
		case PlayerState::Jump:
			JumpStart();
			break;
		case PlayerState::JumpHold:
			JumpHoldStart();
			break;
		case PlayerState::Sprint:
			SprintStart();
			break;
		case PlayerState::SprintJump:
			SprintJumpStart();
			break;
		case PlayerState::Victory:
			VictoryStart();
			break;
		case PlayerState::Die:
			DieStart();
			break;
		case PlayerState::Debugmode:
			DebugmodeStart();
			break;
		default:
			break;
		}
	}

	State = _State;
}


void Player::DirCheck()
{

	// �ڵ���� ���������� ����Ǳ� ������ 
	// D�� �������·� A������������ ������ȯ�� ����������
	// A�� �������·� D�� ������������ A�� ó���� ���� �̷������ ������ȯ�� �����ʱ⶧���� ������ �߻��ߴ�.

	// ������ �����ϴ� Ű���� ��� ������� �׻��� �״�� ����. �Ʒ��� D�� �����϶� Left�� �Ǵ� ���� ����.
	if (true == GameEngineInput::IsFree('A') && true == GameEngineInput::IsFree('D'))
	{
		return;
	}

	// A�� ���Ȱų� D�� �����̶�� Left�� ������ȯ �ε� �������־ Left�� �ٶ󺸴� ������ ����.
	if (true == GameEngineInput::IsDown('A') || true == GameEngineInput::IsFree('D'))
	{
		Dir = PlayerDir::Left;
		ChangeAnimationState(CurState);
		return;
	}

	// D�� ���Ȱų� A�� �����̸� Right�� ���� ��ȯ.
	if (true == GameEngineInput::IsDown('D') || true == GameEngineInput::IsFree('A'))
	{
		Dir = PlayerDir::Right;
		ChangeAnimationState(CurState);
		return;
	}

	/*if (true == GameEngineInput::IsDown('W') || true == GameEngineInput::IsFree('S'))
	{
		Dir = PlayerDir::Up;
		return;
	}

	if (true == GameEngineInput::IsDown('S') || true == GameEngineInput::IsFree('W'))
	{
		Dir = PlayerDir::Down;
		return;
	}*/

	

	// ���� �ִ� �ڵ�.
	/*PlayerDir CheckDir = PlayerDir::Left;

	if (true == GameEngineInput::IsDown('A'))
	{
		CheckDir = PlayerDir::Left;
	}
	else if (true == GameEngineInput::IsDown('D'))
	{
		CheckDir = PlayerDir::Right;
	}

	bool ChangeDir = false;

	if (CheckDir != PlayerDir::Max)
	{
		Dir = CheckDir;
		ChangeDir = true;
	}

	if (CheckDir != PlayerDir::Max && true == ChangeDir)
	{
		ChangeAnimationState(CurState);
	}*/

}

void Player::ChangeAnimationState(const std::string& _StateName)
{
	// "Idle"
	// _StateName

	std::string AnimationName;


	switch (Dir)
	{
	case PlayerDir::Right:
		AnimationName = "Right_";
		break;
	case PlayerDir::Left:
		AnimationName = "Left_";
		break;
	//case PlayerDir::Up:
	//	AnimationName = "Right_";
	//	break;
	//case PlayerDir::Down:
	//	AnimationName = "Right_";
	//	break;

	default:
		break;
	}

	AnimationName += _StateName;

	CurState = _StateName;

	MainRenderer->ChangeAnimation(AnimationName);
}



void Player::LevelStart() 
{
	MainPlayer = this;
}

void Player::Render(float _Delta)
{

	HDC dc = GameEngineWindow::MainWindow.GetBackBuffer()->GetImageDC();
	
	if (DebugModeText == true)
	{
		
		std::string C_Key = "";
		C_Key += "C: ���ڿ� ǥ��";
		TextOutA(dc, 2, 3, C_Key.c_str(), (int)C_Key.size());

		

		std::string PlayerColState = "";
		PlayerColState += "Plyaer Collision: ";
		if (DebugMode == false)
		{
			PlayerColState += "(OFF)";
		}
		else if (DebugMode == true)
		{
			PlayerColState += "(ON)";
		}
		TextOutA(dc, 2, 23, PlayerColState.c_str(), (int)PlayerColState.size());
		
		
		/*std::string Text2 = "";
		Text2 += "(Ű�Է�)";
		TextOutA(dc, 2, 120, Text2.c_str(), (int)Text2.size());*/



		std::string V_Key = "";
		V_Key += "V: �׽�Ʈ��� ";
		if (DebugMode == false)
		{
			V_Key += "(OFF)";
		}
		else if (DebugMode == true)
		{
			V_Key += "(ON)";
		}
		TextOutA(dc, 2, 140, V_Key.c_str(), (int)V_Key.size());

		std::string Text1 = "";
		Text1 += "�׽�Ʈ��� �ӵ�: (";
		Text1 += std::to_string((int)DebugSpeed);
		Text1 += ")";
		TextOutA(dc, 2, 160, Text1.c_str(), (int)Text1.size());

		std::string One_Key = "";
		One_Key += "1: �׽�Ʈ��� �̼� +100";
		TextOutA(dc, 2, 180, One_Key.c_str(), (int)One_Key.size());

		std::string Two_Key = "";
		Two_Key += "2: �׽�Ʈ��� �̼� -100";
		TextOutA(dc, 2, 200, Two_Key.c_str(), (int)Two_Key.size());

		

		//���۹�
		std::string WASD_Key = "";
		WASD_Key += "WD: �̵� ";
		TextOutA(dc, 2, 260, WASD_Key.c_str(), (int)WASD_Key.size());

		std::string J_Key = "";
		J_Key += "J: �޸��� ";
		TextOutA(dc, 2, 280, J_Key.c_str(), (int)J_Key.size());

		std::string Space_Key = "";
		Space_Key += "Space: ���� ";
		TextOutA(dc, 2, 300, Space_Key.c_str(), (int)Space_Key.size());





		std::string F1_Key = "";
		F1_Key += "F1: ����ȯ ";
		TextOutA(dc, 1130, 30, F1_Key.c_str(), (int)F1_Key.size());

		std::string F2_Key = "";
		F2_Key += "F2: Collisionǥ�� ";
		TextOutA(dc, 1130, 50, F2_Key.c_str(), (int)F2_Key.size());

		std::string F3_Key = "";
		F3_Key += "F3: ���������̵� ";
		TextOutA(dc, 1130, 70, F3_Key.c_str(), (int)F3_Key.size());

		std::string F4_Key = "";
		F4_Key += "F4: �¸������̵� ";
		TextOutA(dc, 1130, 90, F4_Key.c_str(), (int)F4_Key.size());

		std::string F5_Key = "";
		F5_Key += "F5: ����ǥ���� ";
		bool GoalPointRender = GoalPoint::GetGoalPointIsRender();
		if (GoalPointRender == false)
		{
			F5_Key += "(OFF)";
		}
		else if (GoalPointRender == true)
		{
			F5_Key += "(ON)";
		}
		TextOutA(dc, 1130, 110, F5_Key.c_str(), (int)F5_Key.size());

		std::string F6_Key = "";
		F6_Key += "F6: Ȯ���� ";
		if (DebugPointIsRender == false)
		{
			F6_Key += "(OFF)";
		}
		else if (DebugPointIsRender == true)
		{
			F6_Key += "(ON)";
		}
		TextOutA(dc, 1130, 130, F6_Key.c_str(), (int)F6_Key.size());

		std::string F7_Key = "";
		F7_Key += "F7: BGM ";
		if (SoundPlaying == false)
		{
			F7_Key += "(OFF)";
		}
		else if (SoundPlaying == true)
		{
			F7_Key += "(ON)";
		}
		TextOutA(dc, 1130, 150, F7_Key.c_str(), (int)F7_Key.size());

	/*	std::string F8_Key = "";
		F8_Key += "F8: ������ ���� ";
		TextOutA(dc, 1130, 170, F8_Key.c_str(), (int)F8_Key.size());

		std::string F9_Key = "";
		F9_Key += "F9: �������ǥ�� ";
		TextOutA(dc, 1130, 190, F9_Key.c_str(), (int)F9_Key.size());*/

		
	}

	if (DebugPointIsRender == true)
	{
		//����׿� �Ͼ��� �����

		//����׿� ��ġȮ�� ����
		float4 a = GetPos();
		float4 b = GetLevel()->GetMainCamera()->GetPos();
		float4 c = GetPos() - GetLevel()->GetMainCamera()->GetPos();
		//�Ͼ��� ���鶧 �׳� Actor�� Pos�� GetPos()�� �ϸ� �Ǵ°� �ƴѰ�? �� ���� ī�޶� ��ġ�� ����? �׷��� �Ͼ����� Actor�� pos���� ī�޶� pos��ŭ �� �ָ� �������� �Ǵ°� �Ƴ�?
		// -> 


		CollisionData Data;

		Data.Pos = ActorCameraPos();
		Data.Scale = { 5,5 };
		Rectangle(dc, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());

		//������
		Data.Pos = ActorCameraPos() + LeftCheck;
		Rectangle(dc, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());

		//��������
		Data.Pos = ActorCameraPos() + RightCheck;
		Rectangle(dc, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());

		//�Ʒ���
		Data.Pos = ActorCameraPos() + DownCheck;
		Rectangle(dc, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());
	}


}