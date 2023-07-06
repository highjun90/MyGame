#include "BlueMarble.h"

#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "ContentsEnum.h"
#include <GameEngineCore/ResourcesManager.h>


#include "Player.h"
#include "PlayLevel.h"

BlueMarble::BlueMarble()
{
}

BlueMarble::~BlueMarble()
{
}

void BlueMarble::Start()
{
	if (false == ResourcesManager::GetInst().IsLoadTexture("BlueMarble.bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Texture\\");

		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("BlueMarble.bmp"), 8, 1);
	}

	MainRenderer = CreateRenderer(RenderOrder::PlayObject);
	MainRenderer->CreateAnimation("BlueMarble", "BlueMarble.bmp", 0, 7, 0.1f, true);

	SetPos({ 1800,2500 });
	MainRenderer->ChangeAnimation("BlueMarble");
	MainRenderer->SetRenderScaleToTexture();
	float4 _MarbleScale = { 100,100 };
	MainRenderer->SetRenderScale(_MarbleScale);

	BodyCollision = CreateCollision(CollisionOrder::BlueMarble);
	BodyCollision->SetCollisionScale({ 45, 45 });
	BodyCollision->SetCollisionType(CollisionType::CirCle);
}

void BlueMarble::Update(float _Delta)
{
	std::vector<GameEngineCollision*> _RaymanCol;
	if (true == BodyCollision->Collision(CollisionOrder::PlayerBody, _RaymanCol
		, CollisionType::CirCle // 나를 사각형으로 봐줘
		, CollisionType::Rect // 상대도 사각형으로 봐줘
	))
	{
		PlayLevel* NowLevel = dynamic_cast<PlayLevel*>(GetLevel());
		NowLevel->AddRemainedMarble(-1);

		BodyCollision->Off();
		MainRenderer->Off();
	}
}