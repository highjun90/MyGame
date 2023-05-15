#include "Bullet.h"
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCore.h>

Bullet::Bullet()
{
}

Bullet::~Bullet()
{
}

void Bullet::Start()
{
	Renderer = CreateRenderer();
}

void Bullet::Update(float _Delta)
{

	// Bullet자체가 
	AddPos(Dir * _Delta * Speed);

	if (1.0f < GetLiveTime())
	{
		if (nullptr != Renderer)
		{
			// Death();
			Renderer->Death();
			Renderer = nullptr;
		}
	}

}

void Bullet::Render()
{

}


// === 최종 삭제 주석

// Update() - Dir  방향으로 speed만큼 이동시킴. 단, GetLiveTime이 1 이상이면 삭제

