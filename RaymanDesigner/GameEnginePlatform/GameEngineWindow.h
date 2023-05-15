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

	GameEngineWindowTexture* GetWindowBuffer()
	{
		return WindowBuffer;
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

	void ClearBackBuffer();
	void DoubleBuffering();

	static bool IsFocus()
	{
		return IsFocusValue;
	}

protected:

private:
	static bool IsWindowUpdate;
	static bool IsFocusValue;
	static HINSTANCE Instance;
	std::string Title = "";
	HWND hWnd = nullptr;


	float4 Scale;
	GameEngineWindowTexture* WindowBuffer = nullptr;

	GameEngineWindowTexture* BackBuffer = nullptr;

	// 2차원 배열 형식의 색깔들의 집합이 존재하고
	// 거기에 그림을 그리거나 수정할수 있는 권한을 HDC
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

//IsFocus(), IsFocusValue - 현재 윈도우 창이 최상단에 위치되어서 동작하는지 알려줌. 이걸로 다른 윈도우 창에서 딴짓할때 어떻게 동작할지 조정함
