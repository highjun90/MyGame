#pragma once

enum class UpdateOrder
{
	Player,
	Monster,
};

enum class RenderOrder
{
	BackGroundImage,
	BackGround,
	Play,
	PlayUI,
	Fade
};

// ������Ŀ 
enum class CollisionOrder
{
	Map,
	Potal,
	PlayerBody,
	PlayerLie,
	MonsterBody,
	DarkRayManBody,
	GoalPoint
};