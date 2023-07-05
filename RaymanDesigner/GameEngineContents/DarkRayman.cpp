#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineRenderer.h>

#include "DarkRayman.h"
#include "Player.h"
#include "ContentsEnum.h"

DarkRayman::DarkRayman()
{
}

DarkRayman::~DarkRayman()
{
}

void DarkRayman::Start()
{

	float4 StartPoint = { 1300,2500 };
	SetPos(StartPoint);
	DarkRaymanRenderer = CreateRenderer(190);
	

	if (false == ResourcesManager::GetInst().IsLoadTexture("Left_DarkRaymanIdle.bmp"))
	{

		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");

		GameEnginePath FolderPath = FilePath;

		FilePath.MoveChild("ContentsResources\\Texture\\DarkRayman\\");

		// ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Left_Player.bmp"));

		//가만히있기 스프라이트 등록
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Left_DarkRaymanIdle.bmp"), 11, 1);
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Right_DarkRaymanIdle.bmp"), 11, 1);


		//걷기 스프라이트 등록
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Left_DarkRaymanRun.bmp"), 32, 1);
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Right_DarkRaymanRun.bmp"), 32, 1);

		//스프린트 스프라이트 등록
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Left_DarkRaymanSprint.bmp"), 31, 1);
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Right_DarkRaymanSprint.bmp"), 27, 1);

		//스프린트점프 스프라이트 등록
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Right_DarkRaymanSprintJump.bmp"), 14, 1);
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Left_DarkRaymanSprintJump.bmp"), 14, 1);

		//점프 스프라이트 등록
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Left_DarkRaymanJump.bmp"), 42, 1);
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Right_DarkRaymanJump.bmp"), 42, 1);


	}


	{
		//가만히 있기 애니메이션 등록
		DarkRaymanRenderer->CreateAnimation("Left_DarkRaymanIdle", "Left_DarkRaymanIdle.bmp", 0, 10, 0.1f, true);
		DarkRaymanRenderer->CreateAnimation("Right_DarkRaymanIdle", "Right_DarkRaymanIdle.bmp", 0, 10, 0.1f, true);

		//걷기 애니메이션 등록
		DarkRaymanRenderer->CreateAnimation("Left_DarkRaymanRun", "Left_DarkRaymanRun.bmp", 0, 31, 0.02f, true);
		DarkRaymanRenderer->CreateAnimation("Right_DarkRaymanRun", "Right_DarkRaymanRun.bmp", 0, 31, 0.02f, true);

		//스프린트 애니메이션 등록
		DarkRaymanRenderer->CreateAnimation("Left_DarkRaymanSprint", "Left_DarkRaymanSprint.bmp", 26, 0, 0.035f, true);
		DarkRaymanRenderer->CreateAnimation("Right_DarkRaymanSprint", "Right_DarkRaymanSprint.bmp", 0, 26, 0.035f, true);

		//스프린트점프 애니메이션 등록
		DarkRaymanRenderer->CreateAnimation("Right_DarkRaymanSprintJump", "Right_DarkRaymanSprintJump.bmp", 0, 13, 0.04f, true);
		DarkRaymanRenderer->CreateAnimation("Left_DarkRaymanSprintJump", "Left_DarkRaymanSprintJump.bmp", 0, 13, 0.04f, true);

		//점프 애니메이션 등록
		DarkRaymanRenderer->CreateAnimation("Left_DarkRaymanJump", "Left_DarkRaymanJump.bmp", 0, 29, 0.025f, false);
		DarkRaymanRenderer->CreateAnimation("Right_DarkRaymanJump", "Right_DarkRaymanJump.bmp", 0, 29, 0.025f, false);
		//점프 하강유지 애니메이션 등록
		DarkRaymanRenderer->CreateAnimation("Left_DarkRaymanJumpHold", "Left_DarkRaymanJump.bmp", 30, 41, 0.04f, true);
		DarkRaymanRenderer->CreateAnimation("Right_DarkRaymanJumpHold", "Right_DarkRaymanJump.bmp", 30, 41, 0.04f, true);




	}


	DarkRaymanCollsion = CreateCollision(CollisionOrder::DarkRayManBody);
	DarkRaymanCollsion->SetCollisionScale({ 50, 110 });
	DarkRaymanCollsion->SetCollisionType(CollisionType::Rect);
	DarkRaymanCollsion->Off();

	DarkRaymanRenderer->SetRenderScaleToTexture();

	std::string AniName = "Right_DarkRaymanJumpHold";
	DarkRaymanRenderer->ChangeAnimation(AniName);

	DarkRaymanRenderer->Off();


	//애니메이션 이름 매칭 시키기
	Matching_RaymanAniname.insert({ "Left_Idle","Left_DarkRaymanIdle" });
	Matching_RaymanAniname.insert({ "Right_Idle","Right_DarkRaymanIdle" });

	Matching_RaymanAniname.insert({ "Left_Run","Left_DarkRaymanRun" });
	Matching_RaymanAniname.insert({ "Right_Run","Right_DarkRaymanRun" });

	Matching_RaymanAniname.insert({ "Left_RaymanSprint","Left_DarkRaymanSprint" });
	Matching_RaymanAniname.insert({ "Right_RaymanSprint","Right_DarkRaymanSprint" });

	Matching_RaymanAniname.insert({ "Left_RaymanSprintJump","Left_DarkRaymanSprintJump" });
	Matching_RaymanAniname.insert({ "Right_RaymanSprintJump","Right_DarkRaymanSprintJump" });

	Matching_RaymanAniname.insert({ "Left_RaymanJump","Left_DarkRaymanJump" });
	Matching_RaymanAniname.insert({ "Right_RaymanJump","Right_DarkRaymanJump" });

	Matching_RaymanAniname.insert({ "Left_RaymanJumpHold","Left_DarkRaymanJumpHold" });
	Matching_RaymanAniname.insert({ "Right_RaymanJumpHold","Right_DarkRaymanJumpHold" });

}


void DarkRayman::Update(float _Delta)
{
	//레이맨 등장 후 일정시간 후 다크레이맨 등장
	float LiveTime = RaymanPtr->GetLiveTime();
	if (LiveTime > 2.0f && Live == true)
	{
		DarkRaymanRenderer->On();
		DarkRaymanCollsion->On();

		SetChase(true);
	}

	//레이맨 충돌시 하는 행동
	std::vector<GameEngineCollision*> _DarkRaymanBodyCol;
	if (true == DarkRaymanCollsion->Collision(CollisionOrder::PlayerBody, _DarkRaymanBodyCol
		, CollisionType::Rect // 나를 사각형으로 봐줘
		, CollisionType::Rect // 상대도 사각형으로 봐줘
	))
	{
		DarkRaymanRenderer->Off();
		//DarkRaymanCollsion->Off();
		ResetLiveTime();

		SetChase(false);
		Live = false;
	}

	

	//지금 등장해서 추적안하고 있으면 레이맨 정보만 추가, 아니면 정보를 바탕으로 레이맨 쫒음
	bool NowChase = GetChase();
	if (Live == true && NowChase == false)
	{
		AddRaymanData();
	}
	else if(Live == true && NowChase == true)
	{
		ChaseRayman();
	}

}


void DarkRayman::Render(float _Delta)
{
	/*if (3.0f <= GetLiveTime())
	{
		DarkRaymanPtr->On();
	}*/

	if (RaymanPtr == nullptr)
	{
		MsgBoxAssert("DarkRayman이 Rayman을 모릅니다");
	}
	else
	{
		float4 DarkRaymanScale = RaymanPtr->MainRenderer->GetRenderScale();
		DarkRaymanRenderer->SetRenderScale(DarkRaymanScale);
	}

}

//레이맨 데이터공간을 새로 만들고 저장
void DarkRayman::AddRaymanData()
{
	PastRaymanData* NowRaymanData = new PastRaymanData();
	NowRaymanData->Pos = RaymanPtr->GetPos();
	NowRaymanData->AnimationName = RaymanPtr->MainRenderer->GetCurAnimation()->Name;
	NowRaymanData->AnimationCurFrame = RaymanPtr->MainRenderer->GetCurAnimation()->CurFrame;

	PastRaymanDatas.push_back(NowRaymanData);
	TotalNum_PastRaymanDatas++;
}


//레이맨 데이터를 기존 공간에 저장
void DarkRayman::AddRaymanData(int _Index)
{
	PastRaymanDatas[_Index]->Pos = RaymanPtr->GetPos();
	PastRaymanDatas[_Index]->AnimationName = RaymanPtr->MainRenderer->GetCurAnimation()->Name;
	PastRaymanDatas[_Index]->AnimationCurFrame = RaymanPtr->MainRenderer->GetCurAnimation()->CurFrame;
}

void DarkRayman::ChaseRayman()
{
	//저장하고있는 데이터 공간을 초과하면 인덱스를 처음으로 보냄
	if (Index_PastRaymanDatas > TotalNum_PastRaymanDatas - 1)
	{
		Index_PastRaymanDatas = 0;
	}

	//자리이동
	float4 ChasePos = PastRaymanDatas[Index_PastRaymanDatas]->Pos;
	SetPos(ChasePos);

	//레이맨의 과거 애니메이션 이름하고 프레임얻기
	std::string ChangeAni01 = PastRaymanDatas[Index_PastRaymanDatas]->AnimationName;
	std::string ChangeAni02 = Matching_RaymanAniname.at(ChangeAni01);
	size_t ChangeFrame = PastRaymanDatas[Index_PastRaymanDatas]->AnimationCurFrame;


	DarkRaymanRenderer->ChangeAnimation(ChangeAni02);




	AddRaymanData(Index_PastRaymanDatas);
	Index_PastRaymanDatas++;
}
