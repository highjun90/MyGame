#include "Player.h"
#include <Windows.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEnginePath.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/ResourcesManager.h>

Player::Player()
{
}

Player::~Player()
{
}


void Player::Start()
{


	if (false == ResourcesManager::GetInst().IsLoadTexture("Test.Bmp"))
	{
		// ������ �ڵ����� ���� �������� ��ġ�� �ȴ�.
		// ���
		// ������ġ D:\Project\AR47\Winapi\AR47WinApi\Bin\x64\Debug
		// 
		// ������ġ D:\Project\AR47\Winapi\AR47WinApi\GameEngineApp
		// ������ġ D:\Project\AR47\Winapi\AR47WinApi\ContentsResources\Texture\Player
		GameEnginePath FilePath;
		// ������ġ D:\Project\AR47\Winapi\AR47WinApi\GameEngineApp
		FilePath.GetCurrentPath();
		// ������ġ D:\Project\AR47\Winapi\AR47WinApi

		// ContentsResources

		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Texture\\Player\\Test.Bmp");

		ResourcesManager::GetInst().TextureLoad(FilePath.GetStringPath());
	}


	SetPos({ 200, 200 });
	SetScale({ 100, 100 });
}

void Player::Update(float _Delta)
{
	// ���� ����� ����� �Ƹ� �ȵ� ����� �ϴ°��̴�.
	// Player->GetPos() == Monster->GetPos();
	// float Time = GameEngineTime::MainTimer.GetDeltaTime();

	AddPos({ 100.0f * _Delta, 0.0f });
}

void Player::Render()
{
	//SetPos({ 200, 200 });
	//SetScale({ 100, 100 });

	HDC WindowDC = GameEngineWindow::MainWindow.GetHDC();
	GameEngineTexture* FindTexture = ResourcesManager::GetInst().FindTexture("Test.Bmp");
	HDC ImageDC = FindTexture->GetImageDC();

	// Ư�� DC�� ����� ������
	// Ư�� DC�� ��Ӻ����ϴ� �Լ��Դϴ�.

	BitBlt(WindowDC, 100, 100, 500, 500, ImageDC, 0, 0, SRCCOPY);

	//Rectangle(WindowDC, 
	//	GetPos().iX() - GetScale().ihX(),
	//	GetPos().iY() - GetScale().ihY(),
	//	GetPos().iX() + GetScale().ihX(),
	//	GetPos().iY() + GetScale().ihY()
	//);

	// �׷�����?
}

void Player::Release()
{
}