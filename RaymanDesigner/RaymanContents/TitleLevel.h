#pragma once

class TitleLevel
{
public:
	//constructor destructor
	TitleLevel();
	~TitleLevel();

	//delete Function
	TitleLevel(const TitleLevel& _Other) = delete;
	TitleLevel(TitleLevel&& _Other) noexcept = delete;
	TitleLevel& operator=(const TitleLevel& _Other) = delete;
	TitleLevel&& operator=(TitleLevel&& _Other) noexcept = delete;

protected:

private:

};  