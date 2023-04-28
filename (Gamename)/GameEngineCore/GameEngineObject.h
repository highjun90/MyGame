#pragma once

class GameEngineObject
{
public:
	//constructor destructor
	GameEngineObject();
	~GameEngineObject();

	//delete Function
	GameEngineObject(const GameEngineObject& _Other) = delete;
	GameEngineObject(GameEngineObject&& _Other) noexcept = delete;
	GameEngineObject& operator=(const GameEngineObject& _Other) = delete;
	GameEngineObject&& operator=(GameEngineObject&& _Other) noexcept = delete;

protected:

private:

};  