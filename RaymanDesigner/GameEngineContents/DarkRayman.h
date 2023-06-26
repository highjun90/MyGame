#pragma once

class DarkRayman
{
public:
	//constructor destructor
	DarkRayman();
	~DarkRayman();

	//delete Function
	DarkRayman(const DarkRayman& _Other) = delete;
	DarkRayman(DarkRayman&& _Other) noexcept = delete;
	DarkRayman& operator=(const DarkRayman& _Other) = delete;
	DarkRayman&& operator=(DarkRayman&& _Other) noexcept = delete;

protected:

private:

};  