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
	if (false == ResourcesManager::GetInst().IsLoadTexture("Test.Bmp"))
	{
		SetPos({ 960,400 });

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
		
		
		FolderPath.MoveChild("ContentsResources\\Texture\\");
		ResourcesManager::GetInst().CreateSpriteFolder("FolderPlayer", FolderPath.PlusFilePath("FolderPlayer"));

		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Test.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("HPBar.bmp"));

		//UI 등록
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_LifeAndHp.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_LeftDownMarble.bmp"));
	}

	{

		MainRenderer = CreateRenderer(200);

		// MainRenderer->SetRenderScale({ 200, 200 });
		// MainRenderer->SetSrite("Left_Player.bmp");

		MainRenderer->CreateAnimation("Test", "FolderPlayer");


		//가만히 있기 애니메이션 등록
		MainRenderer->CreateAnimation("Left_Idle", "Idle_Left.bmp", 0, 10, 0.1f, true);
		MainRenderer->CreateAnimation("Right_Idle", "Idle_RIght.bmp", 0, 10, 0.1f, true);

		// MainRenderer->CreateAnimation("Right_Idle", "FolderPlayer");

		//걷기 애니메이션 등록
		MainRenderer->CreateAnimation("Left_Run", "Left_Player.bmp", 0, 31, 0.02f, true);
		MainRenderer->CreateAnimation("Right_Run", "Right_Player.bmp", 0, 31, 0.02f, true);


		MainRenderer->ChangeAnimation("Test");
		MainRenderer->SetRenderScaleToTexture();
	}

	//{
	//	GameEngineRenderer* Ptr = CreateUIRenderer(200);
	//	Ptr->SetRenderPos({ 100, -300 });
	//	Ptr->SetRenderScale({ 200, 40 });
	//	Ptr->SetTexture("HPBar.bmp");
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

	if (true == GameEngineInput::IsPress('Y'))
	{
		//GameEngineWindow::MainWindow.AddDoubleBufferingCopyScaleRatio(-1.0f * _Delta);
		GameEngineLevel::CollisionDebugRenderSwitch();
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
	std::string Text = "";

	Text += "플레이어 테스트 값 : ";
	Text += std::to_string(TestValue);

	HDC dc = GameEngineWindow::MainWindow.GetBackBuffer()->GetImageDC();
	//TextOutA(dc, 2, 3, Text.c_str(), Text.size());

	


	

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