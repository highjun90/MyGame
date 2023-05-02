#pragma once

class ContentCore
{
public:
	//constructor destructor
	ContentCore();
	~ContentCore();

	//delete Function
	ContentCore(const ContentCore& _Other) = delete;
	ContentCore(ContentCore&& _Other) noexcept = delete;
	ContentCore& operator=(const ContentCore& _Other) = delete;
	ContentCore&& operator=(ContentCore&& _Other) noexcept = delete;

protected:

private:

};  