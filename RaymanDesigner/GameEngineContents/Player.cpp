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
#include "PlayLevel.h"
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

		//점프 스프라이트 등록
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Left_RaymanJump.bmp"), 42, 1);
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Right_RaymanJump.bmp"), 42, 1);


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

		//점프 애니메이션 등록
		MainRenderer->CreateAnimation("Left_RaymanJump", "Left_RaymanJump.bmp", 0, 29, 0.025f, false);
		MainRenderer->CreateAnimation("Right_RaymanJump", "Right_RaymanJump.bmp", 0, 29, 0.025f, false);
		//점프 하강유지 애니메이션 등록
		MainRenderer->CreateAnimation("Left_RaymanJumpHold", "Left_RaymanJump.bmp", 30, 41, 0.04f, true);
		MainRenderer->CreateAnimation("Right_RaymanJumpHold", "Right_RaymanJump.bmp", 30, 41, 0.04f, true);

		//MainRenderer->ChangeAnimation("Test");
		MainRenderer->SetRenderScaleToTexture();
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

	//충돌체하나 가리키는 포인터
	{
		BodyCollsion = CreateCollision(CollisionOrder::PlayerBody);
		BodyCollsion->SetCollisionScale({ 120, 240 });
		BodyCollsion->SetCollisionType(CollisionType::Rect);
	}

	//ChanageState(PlayerState::Idle);
	ChanageState(PlayerState::JumpHold);
	Dir = PlayerDir::Right;


	//BGM 플레이어를 Level에서 가져오기
	PlayLevel* MyLevel = dynamic_cast<PlayLevel*>(GetLevel());
	MyLevel->GetBGMPlayerToPlayLevel();
	BGMPlayerToPlayer = MyLevel->GetBGMPlayerToPlayLevel();
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

	if (true == GameEngineInput::IsPress('L'))
	{
		// GameEngineSound::SoundLoad("C:\\AAAA\\AAAA\\A\\AAA.Mp3");
		// GameEngineSound::SoundPlay("AAA.Mp3");
		// GameEngineSound::PlayBgm("AAA.Mp3");
		// GameEngineSound::StopBgm("AAA.Mp3");

		//GameEngineWindow::MainWindow.AddDoubleBufferingCopyScaleRatio(1.0f * _Delta);

		// Monster::AllMonsterDeath();
	}

	// 충돌체 표시
	if (true == GameEngineInput::IsPress('Y'))
	{
		//GameEngineWindow::MainWindow.AddDoubleBufferingCopyScaleRatio(-1.0f * _Delta);
		GameEngineLevel::CollisionDebugRenderSwitch();
	}

	//디버그 모드
	if (true == GameEngineInput::IsDown('C'))
	{
		// GameEngineWindow::MainWindow.AddDoubleBufferingCopyScaleRatio(-1.0f * _Delta);
		ChanageState(PlayerState::Debugmode);
	}

	//사운드 끄고 키기
	if (true == GameEngineInput::IsDown(VK_F2))
	{
		if (SoundPlaying == true)
		{
			BGMPlayerToPlayer->Stop();
			SoundPlaying = false;
		}
	}
	if (true == GameEngineInput::IsDown(VK_F3))
	{
		if (SoundPlaying == false)
		{
			*(BGMPlayerToPlayer) = GameEngineSound::SoundPlay("CandyChateauBGM.ogg");
			SoundPlaying = true;
		}
	}

	StateUpdate(_Delta);

	CameraFocus();

	// Gravity();
}

void CameraPosToDir()
{
	
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
	
	if (DebugMode == true)
	{
		std::string Text1 = "";
		Text1 += "테스트모드";
		TextOutA(dc, 2, 3, Text1.c_str(), (int)Text1.size());

		
		std::string Text2 = "";
		Text2 += "(키입력)";
		TextOutA(dc, 2, 120, Text2.c_str(), (int)Text2.size());

		std::string Text3 = "";
		Text3 += "테스트 끄기: V";
		TextOutA(dc, 2, 140, Text3.c_str(), (int)Text3.size());

		std::string Text4 = "";
		Text4 += "테스트 이속 Q: -100, E: +100 (속도:  ";
		Text4 += std::to_string((int)DebugSpeed);
		Text4 += ")";
		TextOutA(dc, 2, 160, Text4.c_str(), (int)Text4.size());

		std::string Text5 = "";
		Text5 += "3: 종료지점이동 ";
		TextOutA(dc, 2, 180, Text5.c_str(), (int)Text5.size());

		std::string Text6 = "";
		Text6 += "4: 시작지점이동 ";
		TextOutA(dc, 2, 200, Text6.c_str(), (int)Text6.size());

		std::string Text7 = "";
		Text7 += "WASD: 이동 ";
		TextOutA(dc, 200, 200, Text7.c_str(), (int)Text7.size());

		std::string Text8 = "";
		Text8 += "J: 달리기 ";
		TextOutA(dc, 200, 220, Text8.c_str(), (int)Text8.size());

		std::string Text9 = "";
		Text9 += "Space: 점프 ";
		TextOutA(dc, 200, 240, Text9.c_str(), (int)Text9.size());





		std::string F1_Key = "";
		F1_Key += "F1: 맵전환 ";
		TextOutA(dc, 1130, 30, F1_Key.c_str(), (int)F1_Key.size());

		std::string F2_Key = "";
		F2_Key += "F2: BGM 끄기 ";
		TextOutA(dc, 1130, 50, F2_Key.c_str(), (int)F2_Key.size());

		std::string F3_Key = "";
		F3_Key += "F3: BGM 시작 ";
		TextOutA(dc, 1130, 70, F3_Key.c_str(), (int)F3_Key.size());

		std::string Y_Key = "";
		Y_Key += "Y: 충돌표시 ";
		TextOutA(dc, 1130, 90, Y_Key.c_str(), (int)Y_Key.size());


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
	/*else
	{
		std::string Text1 = "";
		Text1 += "";
		TextOutA(dc, 2, 120, Text1.c_str(), Text1.size());

		std::string Text2 = "";
		Text2 += "글자off: 0";
		TextOutA(dc, 2, 140, Text2.c_str(), Text2.size());
	}*/

	

	
}