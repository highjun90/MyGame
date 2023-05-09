#include <iostream>
#include <GameEngineCore/GameEngineCore.h>
#include <RaymanContents/RaymanCore.h>

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	GameEngineCore::EngineStart<RaymanCore>("RaymanDesigner", hInstance);
	return 0;
}