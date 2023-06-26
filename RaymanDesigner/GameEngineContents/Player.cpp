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
#include "Bullet.h"
#include "Monster.h"
#include "PlayUIManager.h"
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

		//MainRenderer->ChangeAnimation("Test");
		MainRenderer->SetRenderScaleToTexture();
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

	{
		BodyCollsion = CreateCollision(CollisionOrder::PlayerBody);
		BodyCollsion->SetCollisionScale( {120, 240});
		BodyCollsion->SetCollisionType(CollisionType::Rect);
	}


	// SetGroundTexture("StageTestPixel.bmp");

	

	// State = PlayerState::Idle;

	ChanageState(PlayerState::Idle);
	Dir = PlayerDir::Right;
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

	if (true == GameEngineInput::IsPress('L'))
	{
		// GameEngineSound::SoundLoad("C:\\AAAA\\AAAA\\A\\AAA.Mp3");
		// GameEngineSound::SoundPlay("AAA.Mp3");
		// GameEngineSound::PlayBgm("AAA.Mp3");
		// GameEngineSound::StopBgm("AAA.Mp3");

		//GameEngineWindow::MainWindow.AddDoubleBufferingCopyScaleRatio(1.0f * _Delta);

		// Monster::AllMonsterDeath();
	}

	if (true == GameEngineInput::IsPress('Y'))
	{
		//GameEngineWindow::MainWindow.AddDoubleBufferingCopyScaleRatio(-1.0f * _Delta);
		GameEngineLevel::CollisionDebugRenderSwitch();
	}

	if (true == GameEngineInput::IsDown('C'))
	{
		// GameEngineWindow::MainWindow.AddDoubleBufferingCopyScaleRatio(-1.0f * _Delta);
		ChanageState(PlayerState::Debugmode);
	}

	if (true == GameEngineInput::IsDown('V'))
	{
		// GameEngineWindow::MainWindow.AddDoubleBufferingCopyScaleRatio(-1.0f * _Delta);
		DebugMode = false;
		GravityReset();
		ChanageState(PlayerState::Idle);
	}

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
	case PlayerState::Sprint:
		return SprintUpdate(_Delta);
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
		case PlayerState::Sprint:
			SprintStart();
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

	if (true == GameEngineInput::IsDown('W') || true == GameEngineInput::IsFree('S'))
	{
		Dir = PlayerDir::Up;
		return;
	}

	if (true == GameEngineInput::IsDown('S') || true == GameEngineInput::IsFree('W'))
	{
		Dir = PlayerDir::Down;
		return;
	}

	

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
	
	if (DebugMode == true)
	{
		std::string Text1 = "";
		Text1 += "�׽�Ʈ���";
		TextOutA(dc, 2, 3, Text1.c_str(), (int)Text1.size());

		
		std::string Text2 = "";
		Text2 += "(Ű�Է�)";
		TextOutA(dc, 2, 120, Text2.c_str(), (int)Text2.size());

		std::string Text3 = "";
		Text3 += "�׽�Ʈ ����: V";
		TextOutA(dc, 2, 140, Text3.c_str(), (int)Text3.size());

		std::string Text4 = "";
		Text4 += "�׽�Ʈ �̼� Q: -100, E: +100 (�ӵ�:  ";
		Text4 += std::to_string((int)DebugSpeed);
		Text4 += ")";
		TextOutA(dc, 2, 160, Text4.c_str(), (int)Text4.size());

		std::string Text5 = "";
		Text5 += "3: ���������̵� ";
		TextOutA(dc, 2, 180, Text5.c_str(), (int)Text5.size());

		std::string Text6 = "";
		Text6 += "4: ���������̵� ";
		TextOutA(dc, 2, 200, Text6.c_str(), (int)Text6.size());

		std::string Text7 = "";
		Text7 += "WASD: �̵� ";
		TextOutA(dc, 200, 200, Text7.c_str(), (int)Text7.size());

		std::string Text8 = "";
		Text8 += "J: �޸��� ";
		TextOutA(dc, 200, 220, Text8.c_str(), (int)Text8.size());

		std::string Text9 = "";
		Text9 += "Space: ���� ";
		TextOutA(dc, 200, 240, Text9.c_str(), (int)Text9.size());

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
	/*else
	{
		std::string Text1 = "";
		Text1 += "";
		TextOutA(dc, 2, 120, Text1.c_str(), Text1.size());

		std::string Text2 = "";
		Text2 += "����off: 0";
		TextOutA(dc, 2, 140, Text2.c_str(), Text2.size());
	}*/

	

	
}