#include "MapDeathArea.h"
#include "ContentsEnum.h"
MapDeathArea::MapDeathArea()
{
}

MapDeathArea::~MapDeathArea()
{
}

void MapDeathArea::Start()
{
	float4 StartPoint = { 9500, 4500 };
	SetPos(StartPoint);

	DeathAreaCollision = CreateCollision(CollisionOrder::DeathArea);
	DeathAreaCollision->SetCollisionScale({ 10000, 100});
	DeathAreaCollision->SetCollisionType(CollisionType::Rect);
	DeathAreaCollision->On();
}

void MapDeathArea::Update(float _Delta)
{


}