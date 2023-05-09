#pragma once

class Player
{
public:
	//constructor destructor
	Player();
	~Player();

	//delete Function
	Player(const Player& _Other) = delete;
	Player(Player&& _Other) noexcept = delete;
	Player& operator=(const Player& _Other) = delete;
	Player&& operator=(Player&& _Other) noexcept = delete;

protected:

private:

};  