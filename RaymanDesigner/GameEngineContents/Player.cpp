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

		//가만히있기 스프라이트 등록
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Idle_Left.bmp"), 5, 3);
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Idle_RIght.bmp"), 5, 3);

		//걷기 스프라이트 등록
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Left_Player.bmp"), 5, 7);
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Right_Player.bmp"), 5, 7);

		//스프린트 스프라이트 등록
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Left_RaymanSprint.bmp"), 31, 1);
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Right_RaymanSprint.bmp"), 31, 1);

		//스프린트점프 스프라이트 등록
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Left_RaymanSprintJump.bmp"), 14, 1);
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Right_RaymanSprintJump.bmp"), 14, 1);

		//점프 스프라이트 등록
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Left_RaymanJump.bmp"), 42, 1);
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Right_RaymanJump.bmp"), 42, 1);

		//승리모션 스프라이트 등록
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Left_RaymanVictory.bmp"), 39, 1);
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Right_RaymanVictory.bmp"), 39, 1);

		//죽기 스프라이트 등록
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Left_RaymanDie.bmp"), 10, 1);
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Right_RaymanDie.bmp"), 10, 1);

		//죽기 빛 스트라이트 등록
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("RaymanDieLight.bmp"), 7, 1);

		//UI 등록
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_LifeAndHp.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_LeftDownMarble.bmp"));

		//선생님코드
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


		//가만히 있기 애니메이션 등록
		MainRenderer->CreateAnimation("Left_Idle", "Idle_Left.bmp", 0, 10, 0.1f, true);
		MainRenderer->CreateAnimation("Right_Idle", "Idle_RIght.bmp", 0, 10, 0.1f, true);

		// MainRenderer->CreateAnimation("Right_Idle", "FolderPlayer");

		//걷기 애니메이션 등록
		MainRenderer->CreateAnimation("Left_Run", "Left_Player.bmp", 0, 31, 0.02f, true);
		MainRenderer->CreateAnimation("Right_Run", "Right_Player.bmp", 0, 31, 0.02f, true);

		//스프린트 애니메이션 등록
		MainRenderer->CreateAnimation("Left_RaymanSprint", "Left_RaymanSprint.bmp", 26, 0, 0.035f, true);
		MainRenderer->CreateAnimation("Right_RaymanSprint", "Right_RaymanSprint.bmp", 0, 26, 0.035f, true);

		//스프린트점프 애니메이션 등록
		MainRenderer->CreateAnimation("Left_RaymanSprintJump", "Left_RaymanSprintJump.bmp", 0, 13, 0.04f, true);
		MainRenderer->CreateAnimation("Right_RaymanSprintJump", "Right_RaymanSprintJump.bmp", 0, 13, 0.04f, true);

		//점프 애니메이션 등록
		MainRenderer->CreateAnimation("Left_RaymanJump", "Left_RaymanJump.bmp", 0, 29, 0.025f, false);
		MainRenderer->CreateAnimation("Right_RaymanJump", "Right_RaymanJump.bmp", 0, 29, 0.025f, false);
		//점프 하강유지 애니메이션 등록
		MainRenderer->CreateAnimation("Left_RaymanJumpHold", "Left_RaymanJump.bmp", 30, 41, 0.04f, true);
		MainRenderer->CreateAnimation("Right_RaymanJumpHold", "Right_RaymanJump.bmp", 30, 41, 0.04f, true);

		//승리모션 애니메이션 등록
		MainRenderer->CreateAnimation("Left_RaymanVictory", "Left_RaymanVictory.bmp", 0, 38, 0.06f, false);
		MainRenderer->CreateAnimation("Right_RaymanVictory", "Right_RaymanVictory.bmp", 0, 38, 0.06f, false);

		//죽기 애니메이션 등록
		MainRenderer->CreateAnimation("Left_RaymanDie", "Left_RaymanDie.bmp", 0, 9, 0.04f, false);
		MainRenderer->CreateAnimation("Right_RaymanDie", "Right_RaymanDie.bmp", 0, 9, 0.04f, false);

		//죽기 빛 애니메이션 등록
		MainRenderer->CreateAnimation("RaymanDieLight", "RaymanDieLight.bmp", 0, 6, 0.08f, false);

	
		MainRenderer->SetRenderScaleToTexture();

		////다크레이맨 스케일 플레이어와 같게 해주기
		//float4 DarkRaymanScale = MainRenderer->GetRenderScale();

		//DarkRaymanPtr->DarkRaymanRenderer->SetRenderScale(DarkRaymanScale);
		//int a = 0;
	
	}

	//hp바 선생님코드
	//{
	//	HPRender = CreateRenderer("HPBar.bmp", RenderOrder::Play);
	//	HPRender->SetRenderPos({ 0, -200 });
	//	HPRender->SetRenderScale({ 40, 40 });
	//	HPRender->SetTexture("HPBar.bmp");
	//	// Ptr->SetText("ㄻ오너ㅏㅣㄻㅇ노ㅓㅏㅣㄻㅇ노ㅓㅏㅣㄻㅇ노ㅓㅏ림ㅇ노러ㅏㅣㅇㅁㄴ로ㅓ마닝", 40);
	//}

	/*{
		GameEngineRenderer* Ptr = CreateRenderer("HPBar.bmp", RenderOrder::Play);
		Ptr->SetRenderPos({ 0, -100 });
		Ptr->SetRenderScale({ 200, 40 });
		Ptr->SetTexture("HPBar.bmp");

	}*/

	//Player의 충돌체하나를 가리키는 포인터
	{
		BodyCollsion = CreateCollision(CollisionOrder::PlayerBody);
		BodyCollsion->SetCollisionScale({ 60, 120 });
		BodyCollsion->SetCollisionType(CollisionType::Rect);
	}

	//ChanageState(PlayerState::Idle);
	ChanageState(PlayerState::JumpHold);
	Dir = PlayerDir::Right;


	//BGM 플레이어를 Level에서 가져오기
	PlayLevel* MyLevel = dynamic_cast<PlayLevel*>(GetLevel());
	MyLevel->GetBGMPlayerToPlayLevel();
	BGMPlayerToPlayer = MyLevel->GetBGMPlayerToPlayLevel();


	//승리사운드 등록
	if (nullptr == GameEngineSound::FindSound("Victory.mp3"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Sound\\");

		GameEngineSound::SoundLoad(FilePath.PlusFilePath("Victory.mp3"));
	}

	//죽기사운드 등록
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

	// 애니메이션 한 싸이클 끝나면 다른 행동을 하게하는 코드
	/*if (true == MainRenderer->IsAnimation("Left_Idle")
		&& true == MainRenderer->IsAnimationEnd())
	{
		
		Dir = PlayerDir::Right;
		ChangeAnimationState(CurState);
	}*/
	//예시는 왼쪽가만히 있는 애니메이션 끝나면 오른쪽 가만히 애니메이션으로 바꾸게 해논것


	void CameraPosToDir();

	std::vector<GameEngineCollision*> _Col;
	if (true == BodyCollsion->Collision(CollisionOrder::MonsterBody, _Col
		, CollisionType::CirCle // 나를 사각형으로 봐줘
		, CollisionType::CirCle // 상대도 사각형으로 봐줘
	))
	{
		for (size_t i = 0; i < _Col.size(); i++)
		{
			GameEngineCollision* Collison = _Col[i];

			GameEngineActor* Actor = Collison->GetActor();

			Actor->Death();
		}
		// 나는 몬스터랑 충돌한거야.
	}

	//골포인트 충돌체크
	std::vector<GameEngineCollision*> _GoalCollisionTest;
	if (true == BodyCollsion->Collision(CollisionOrder::GoalPoint, _GoalCollisionTest
		, CollisionType::Rect // 나를 사각형으로 봐줘
		, CollisionType::Rect // 상대도 사각형으로 봐줘
	))
	{
		ChanageState(PlayerState::Victory);
	}

	//다크레이맨 몸 충돌체크
	std::vector<GameEngineCollision*> _DarkRaymanBodyCol;
	if (true == BodyCollsion->Collision(CollisionOrder::DarkRayManBody, _DarkRaymanBodyCol
		, CollisionType::Rect // 나를 사각형으로 봐줘
		, CollisionType::Rect // 상대도 사각형으로 봐줘
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

	// 디버그 문자열 키고 끄기
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


	//디버그 모드
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


	// 충돌체 표시
	if (true == GameEngineInput::IsDown(VK_F2))
	{
		//GameEngineWindow::MainWindow.AddDoubleBufferingCopyScaleRatio(-1.0f * _Delta);
		GameEngineLevel::CollisionDebugRenderSwitch();
	}


	//시작, 종료지점 순간이동
	if (true == GameEngineInput::IsDown(VK_F3))
	{
		SetPos(DebugStartPoint);
	}
	if (true == GameEngineInput::IsDown(VK_F4))
	{
		float4 EndPoint = { 13200, 2850 };
		SetPos(EndPoint);
	}

	//골포인트 키고 끄기
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

	//디버그점 키고 끄기
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

	//사운드 끄고 키기
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

	

	

	//무적모드

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

	// 코드들이 순차적으로 실행되기 때문에 
	// D를 누른상태로 A를눌렀을때의 방향전환은 가능하지만
	// A를 누른상태로 D를 눌렀을때에는 A의 처리가 먼저 이루어져서 방향전환이 되지않기때문에 문제가 발생했다.

	// 방향을 결정하는 키들이 모두 프리라면 그상태 그대로 유지. 아래의 D가 프리일때 Left가 되는 것을 방지.
	if (true == GameEngineInput::IsFree('A') && true == GameEngineInput::IsFree('D'))
	{
		return;
	}

	// A가 눌렸거나 D가 프리이라면 Left로 방향전환 인데 가만히있어도 Left를 바라보는 현상이 생김.
	if (true == GameEngineInput::IsDown('A') || true == GameEngineInput::IsFree('D'))
	{
		Dir = PlayerDir::Left;
		ChangeAnimationState(CurState);
		return;
	}

	// D가 눌렸거나 A가 프리이면 Right로 방향 전환.
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

	

	// 원래 있던 코드.
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
		C_Key += "C: 문자열 표시";
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
		Text2 += "(키입력)";
		TextOutA(dc, 2, 120, Text2.c_str(), (int)Text2.size());*/



		std::string V_Key = "";
		V_Key += "V: 테스트모드 ";
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
		Text1 += "테스트모드 속도: (";
		Text1 += std::to_string((int)DebugSpeed);
		Text1 += ")";
		TextOutA(dc, 2, 160, Text1.c_str(), (int)Text1.size());

		std::string One_Key = "";
		One_Key += "1: 테스트모드 이속 +100";
		TextOutA(dc, 2, 180, One_Key.c_str(), (int)One_Key.size());

		std::string Two_Key = "";
		Two_Key += "2: 테스트모드 이속 -100";
		TextOutA(dc, 2, 200, Two_Key.c_str(), (int)Two_Key.size());

		

		//조작법
		std::string WASD_Key = "";
		WASD_Key += "WD: 이동 ";
		TextOutA(dc, 2, 260, WASD_Key.c_str(), (int)WASD_Key.size());

		std::string J_Key = "";
		J_Key += "J: 달리기 ";
		TextOutA(dc, 2, 280, J_Key.c_str(), (int)J_Key.size());

		std::string Space_Key = "";
		Space_Key += "Space: 점프 ";
		TextOutA(dc, 2, 300, Space_Key.c_str(), (int)Space_Key.size());





		std::string F1_Key = "";
		F1_Key += "F1: 맵전환 ";
		TextOutA(dc, 1130, 30, F1_Key.c_str(), (int)F1_Key.size());

		std::string F2_Key = "";
		F2_Key += "F2: Collision표시 ";
		TextOutA(dc, 1130, 50, F2_Key.c_str(), (int)F2_Key.size());

		std::string F3_Key = "";
		F3_Key += "F3: 시작지점이동 ";
		TextOutA(dc, 1130, 70, F3_Key.c_str(), (int)F3_Key.size());

		std::string F4_Key = "";
		F4_Key += "F4: 승리지점이동 ";
		TextOutA(dc, 1130, 90, F4_Key.c_str(), (int)F4_Key.size());

		std::string F5_Key = "";
		F5_Key += "F5: 골인표지판 ";
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
		F6_Key += "F6: 확인점 ";
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
		F8_Key += "F8: 도착지 삭제 ";
		TextOutA(dc, 1130, 170, F8_Key.c_str(), (int)F8_Key.size());

		std::string F9_Key = "";
		F9_Key += "F9: 디버그점표시 ";
		TextOutA(dc, 1130, 190, F9_Key.c_str(), (int)F9_Key.size());*/

		
	}

	if (DebugPointIsRender == true)
	{
		//디버그용 하얀점 만들기

		//디버그용 수치확인 변수
		float4 a = GetPos();
		float4 b = GetLevel()->GetMainCamera()->GetPos();
		float4 c = GetPos() - GetLevel()->GetMainCamera()->GetPos();
		//하얀점 만들때 그냥 Actor의 Pos인 GetPos()만 하면 되는거 아닌가? 왜 굳이 카메라 위치를 빼나? 그러면 하얀점이 Actor의 pos보다 카메라 pos만큼 더 멀리 떨어지게 되는거 아냐?
		// -> 


		CollisionData Data;

		Data.Pos = ActorCameraPos();
		Data.Scale = { 5,5 };
		Rectangle(dc, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());

		//왼쪽점
		Data.Pos = ActorCameraPos() + LeftCheck;
		Rectangle(dc, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());

		//오른쪽점
		Data.Pos = ActorCameraPos() + RightCheck;
		Rectangle(dc, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());

		//아래점
		Data.Pos = ActorCameraPos() + DownCheck;
		Rectangle(dc, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());
	}


}