#pragma once
#include <Windows.h>
#include <string>
#include "GameEngineWindowTexture.h"

// 설명 :
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



// =========== 최종 삭제 주석 ========

// WndProc()
// LRESULT == LONG_PTR == __int64, CALLBACK == __stdcall
// WndProc는 WinMain이 아닌 운영체제가 호출하는 콜백(callback) 함수.
// WPARAM LPARAM - message의 부가정보. 예를들어 message가 WM_CHAR 였다면 어떤 키가 입력되었는지 추가 정보가 필요한데 이럴떄 쓰이는 인자.
// https://hellowoori.tistory.com/9

// HDC - handle device context.

// 윈도우는 크게 3가지 동적 연결 라이브러리를 구성. Kernel, GDI, User.
// DC는 GDI 동적 연결 라이브러리에 속해있음. DC(device context)란? 출력에 필요한 모든 정보를 가진 데이터구조체
