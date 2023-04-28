#pragma once

class GameEngineLevel
{
public:
	//constructor destructor
	GameEngineLevel();
	~GameEngineLevel();

	//delete Function
	GameEngineLevel(const GameEngineLevel& _Other) = delete;
	GameEngineLevel(GameEngineLevel&& _Other) noexcept = delete;
	GameEngineLevel& operator=(const GameEngineLevel& _Other) = delete;
	GameEngineLevel&& operator=(GameEngineLevel&& _Other) noexcept = delete;

protected:

private:

};  