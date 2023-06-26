#include <iostream>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineContents/ContentCore.h>
#include <GameEngineBase/GameEngineMath.h>

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, 
	_In_opt_ HINSTANCE hPrevInstance, 
	_In_ LPWSTR    lpCmdLine, 
	_In_ int       nCmdShow) 
{ 
	GameEngineCore::EngineStart<ContentCore>("RaymanDesigner", hInstance);
	return 0; 
	//int a = 0;
}