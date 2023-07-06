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
	PlayObject,
	Play,
	PlayUI,
	Fade
};

// ÇïÅ×ÀÌÄ¿ 
enum class CollisionOrder
{
	Map,
	Potal,
	PlayerBody,
	PlayerLie,
	BlueMarble,
	MonsterBody,
	DarkRayManBody,
	GoalPoint,
	DeathArea,
};