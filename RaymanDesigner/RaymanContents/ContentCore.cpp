#include "ContentCore.h"
#include "TitleLevel.h"
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
	GameEngineWindow::MainWindow.SetPosAndScale({ 100, 100 }, { 1280, 720 });

	GameEngineCore::CreateLevel<TitleLevel>("TitleLevel");
	GameEngineCore::CreateLevel<PlayLevel>("PlayLevel");
	GameEngineCore::CreateLevel<EndingLevel>("EndingLevel");

	// �� ������ ȭ�鿡 ������.
	GameEngineCore::ChangeLevel("PlayLevel");
}

// �ൿ�Ѱ�.
void ContentCore::Update(float _Delta)
{
}

// �׷�����.
void ContentCore::Render()
{
}

// �����ȴ�.
void ContentCore::Release()
{
}