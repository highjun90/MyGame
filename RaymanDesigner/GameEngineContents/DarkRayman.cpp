#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>

#include "DarkRayman.h"
#include "Player.h"


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

		//�������ֱ� ��������Ʈ ���
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Left_DarkRaymanIdle.bmp"), 11, 1);
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Right_DarkRaymanIdle.bmp"), 11, 1);


		//�ȱ� ��������Ʈ ���
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Left_DarkRaymanRun.bmp"), 32, 1);
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Right_DarkRaymanRun.bmp"), 32, 1);

		//������Ʈ ��������Ʈ ���
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Left_DarkRaymanSprint.bmp"), 31, 1);
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Right_DarkRaymanSprint.bmp"), 27, 1);

		//���� ��������Ʈ ���
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Left_DarkRaymanJump.bmp"), 42, 1);
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Right_DarkRaymanJump.bmp"), 42, 1);


	}


	{
		//������ �ֱ� �ִϸ��̼� ���
		DarkRaymanRenderer->CreateAnimation("Left_DarkRaymanIdle", "Left_DarkRaymanIdle.bmp", 0, 10, 0.1f, true);
		DarkRaymanRenderer->CreateAnimation("Right_DarkRaymanIdle", "Right_DarkRaymanIdle.bmp", 0, 10, 0.1f, true);

		//�ȱ� �ִϸ��̼� ���
		DarkRaymanRenderer->CreateAnimation("Left_DarkRaymanRun", "Left_DarkRaymanRun.bmp", 0, 31, 0.02f, true);
		DarkRaymanRenderer->CreateAnimation("Right_DarkRaymanRun", "Right_DarkRaymanRun.bmp", 0, 31, 0.02f, true);

		//������Ʈ �ִϸ��̼� ���
		DarkRaymanRenderer->CreateAnimation("Left_DarkRaymanSprint", "Left_DarkRaymanSprint.bmp", 26, 0, 0.035f, true);
		DarkRaymanRenderer->CreateAnimation("Right_DarkRaymanSprint", "Right_DarkRaymanSprint.bmp", 0, 26, 0.035f, true);

		//���� �ִϸ��̼� ���
		DarkRaymanRenderer->CreateAnimation("Left_DarkRaymanJump", "Left_DarkRaymanJump.bmp", 0, 29, 0.025f, false);
		DarkRaymanRenderer->CreateAnimation("Right_DarkRaymanJump", "Right_DarkRaymanJump.bmp", 0, 29, 0.025f, false);
		//���� �ϰ����� �ִϸ��̼� ���
		DarkRaymanRenderer->CreateAnimation("Left_DarkRaymanJumpHold", "Left_DarkRaymanJump.bmp", 30, 41, 0.04f, true);
		DarkRaymanRenderer->CreateAnimation("Right_DarkRaymanJumpHold", "Right_DarkRaymanJump.bmp", 30, 41, 0.04f, true);

	}


	DarkRaymanRenderer->SetRenderScaleToTexture();

	std::string AniName = "Left_DarkRaymanJumpHold";
	DarkRaymanRenderer->ChangeAnimation(AniName);

	DarkRaymanRenderer->Off();


	//�ִϸ��̼� �̸� ��Ī ��Ű��
	Matching_RaymanAniname.insert({ "Left_Idle","Left_DarkRaymanIdle" });
	Matching_RaymanAniname.insert({ "Right_Idle","Right_DarkRaymanIdle" });

	Matching_RaymanAniname.insert({ "Left_Run","Left_DarkRaymanRun" });
	Matching_RaymanAniname.insert({ "Right_Run","Right_DarkRaymanRun" });

	Matching_RaymanAniname.insert({ "Left_RaymanSprint","Left_DarkRaymanSprint" });
	Matching_RaymanAniname.insert({ "Right_RaymanSprint","Right_DarkRaymanSprint" });

	Matching_RaymanAniname.insert({ "Left_RaymanSprintJump","" });
	Matching_RaymanAniname.insert({ "Right_RaymanSprintJump","" });

	Matching_RaymanAniname.insert({ "Left_RaymanJump","" });
	Matching_RaymanAniname.insert({ "Right_RaymanJump","" });

	Matching_RaymanAniname.insert({ "Left_RaymanJumpHold","" });
	Matching_RaymanAniname.insert({ "Right_RaymanJumpHold","" });

	Matching_RaymanAniname.insert({ "Left_RaymanVictory","" });
	Matching_RaymanAniname.insert({ "Right_RaymanVictory","" });
}


void DarkRayman::Update(float _Delta)
{
	//���̸� ���� �� �����ð� �� ��ũ���̸� ����
	if (RaymanPtr == nullptr)
	{
		MsgBoxAssert("DarkRayman�� Rayman�� �𸨴ϴ�");
	}
	else
	{
		float LiveTime = RaymanPtr->GetLiveTime();

		if (LiveTime > 3.0f)
		{
			DarkRaymanRenderer->On();
			SetChase(true);
		}

	}

	//���� �����ؼ� �������ϰ� ������ ���̸� ������ �߰�, �ƴϸ� ������ �������� ���̸� �i��
	bool NowChase = GetChase();
	if (NowChase == false)
	{
		AddRaymanData();
	}
	else
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
		MsgBoxAssert("DarkRayman�� Rayman�� �𸨴ϴ�");
	}
	else
	{
		float4 DarkRaymanScale = RaymanPtr->MainRenderer->GetRenderScale();
		DarkRaymanRenderer->SetRenderScale(DarkRaymanScale);
	}

}

//���̸� �����Ͱ����� ���� ����� ����
void DarkRayman::AddRaymanData()
{
	PastRaymanData* NowRaymanData = new PastRaymanData();
	NowRaymanData->Pos = RaymanPtr->GetPos();
	NowRaymanData->AnimationName = RaymanPtr->MainRenderer->GetCurAnimation()->Name;
	NowRaymanData->AnimationCurFrame = RaymanPtr->MainRenderer->GetCurAnimation()->CurFrame;

	PastRaymanDatas.push_back(NowRaymanData);
	TotalNum_PastRaymanDatas++;
}


//���̸� �����͸� ���� ������ ����
void DarkRayman::AddRaymanData(int _Index)
{
	PastRaymanDatas[_Index]->Pos = RaymanPtr->GetPos();
	PastRaymanDatas[_Index]->AnimationName = RaymanPtr->MainRenderer->GetCurAnimation()->Name;
	PastRaymanDatas[_Index]->AnimationCurFrame = RaymanPtr->MainRenderer->GetCurAnimation()->CurFrame;
}

void DarkRayman::ChaseRayman()
{
	//�����ϰ��ִ� ������ ������ �ʰ��ϸ� �ε����� ó������ ����
	if (Index_PastRaymanDatas > TotalNum_PastRaymanDatas - 1)
	{
		Index_PastRaymanDatas = 0;
	}

	//�ڸ��̵�
	float4 ChasePos = PastRaymanDatas[Index_PastRaymanDatas]->Pos;
	SetPos(ChasePos);

	//���̸��� ���� �ִϸ��̼� �̸��ϰ� �����Ӿ��
	std::string ChangeAni01 = PastRaymanDatas[Index_PastRaymanDatas]->AnimationName;
	std::string ChangeAni02 = Matching_RaymanAniname.at(ChangeAni01);
	size_t ChangeFrame = PastRaymanDatas[Index_PastRaymanDatas]->AnimationCurFrame;







	AddRaymanData(Index_PastRaymanDatas);
	Index_PastRaymanDatas++;
}
