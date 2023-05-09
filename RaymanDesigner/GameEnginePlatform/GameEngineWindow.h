#pragma once
#include <Windows.h>
#include <string>
#include "GameEngineWindowTexture.h"

// ���� :
class GameEngineWindow
{
public:
	static GameEngineWindow MainWindow;

	// constrcuter destructer
	GameEngineWindow();
	~GameEngineWindow();

	// delete Function
	GameEngineWindow(const GameEngineWindow& _Other) = delete;
	GameEngineWindow(GameEngineWindow&& _Other) noexcept = delete;
	GameEngineWindow& operator=(const GameEngineWindow& _Other) = delete;
	GameEngineWindow& operator=(GameEngineWindow&& _Other) noexcept = delete;

	void Open(const std::string& _Title, HINSTANCE _hInstance);

	static void MessageLoop(HINSTANCE _Inst, void(*_Start)(HINSTANCE), void(*_Update)(), void(*_End)());

	HDC GetHDC()
	{
		return Hdc;
	}

	float4 GetScale()
	{
		return Scale;
	}

	GameEngineWindowTexture* GetBackBuffer()
	{
		return BackBuffer;
	}

	void SetPosAndScale(const float4& _Pos, const float4& _Scale);

	static void WindowLoopOff()
	{
		IsWindowUpdate = false;
	}

protected:

private:
	static bool IsWindowUpdate;
	static HINSTANCE Instance;
	std::string Title = "";
	HWND hWnd = nullptr;


	float4 Scale;
	GameEngineWindowTexture* BackBuffer = nullptr;

	HDC Hdc = nullptr;

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	void InitInstance();
	void MyRegisterClass();
};



// =========== ���� ���� �ּ� ========

// WndProc()
// LRESULT == LONG_PTR == __int64, CALLBACK == __stdcall
// WndProc�� WinMain�� �ƴ� �ü���� ȣ���ϴ� �ݹ�(callback) �Լ�.
// WPARAM LPARAM - message�� �ΰ�����. ������� message�� WM_CHAR ���ٸ� � Ű�� �ԷµǾ����� �߰� ������ �ʿ��ѵ� �̷��� ���̴� ����.
// https://hellowoori.tistory.com/9

// HDC - handle device context.

// ������� ũ�� 3���� ���� ���� ���̺귯���� ����. Kernel, GDI, User.
// DC�� GDI ���� ���� ���̺귯���� ��������. DC(device context)��? ��¿� �ʿ��� ��� ������ ���� �����ͱ���ü
