#include "ContentCore.h"
#include "TitleLevel.h"
#include "TitleLevel2.h"
#include "PlayLevel.h"
#include "EndingLevel.h"
#include <GameEnginePlatform/GameEngineWindow.h>

ContentCore::ContentCore() 
{
}

ContentCore::~ContentCore() 
{
}

void ContentCore::Start() 
{
	GameEngineWindow::MainWindow.SetPosAndScale({100, 100}, { 1920, 1200 });

	GameEngineCore::CreateLevel<TitleLevel>("TitleLevel");
	GameEngineCore::CreateLevel<TitleLevel2>("TitleLevel2");
	GameEngineCore::CreateLevel<PlayLevel>("PlayLevel");
	GameEngineCore::CreateLevel<EndingLevel>("EndingLevel");

	// �� ������ ȭ�鿡 ������.
	GameEngineCore::ChangeLevel("TitleLevel");
}

// �ൿ�Ѱ�.
void ContentCore::Update(float _Delta)
{
}

// �׷�����.
void ContentCore::Render(float _Delta)
{
}

// �����ȴ�.
void ContentCore::Release() 
{
}