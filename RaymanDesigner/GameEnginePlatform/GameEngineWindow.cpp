#include "GameEngineWindow.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <iostream>



HINSTANCE GameEngineWindow::Instance = nullptr;
GameEngineWindow GameEngineWindow::MainWindow;
bool GameEngineWindow::IsWindowUpdate = true;
bool GameEngineWindow::IsFocusValue = false;

GameEngineWindow::GameEngineWindow()
{
}

GameEngineWindow::~GameEngineWindow()
{
	if (nullptr != BackBuffer)
	{
		delete BackBuffer;
		BackBuffer = nullptr;
	}


	if (nullptr != WindowBuffer)
	{
		delete WindowBuffer;
		WindowBuffer = nullptr;
	}
}

void GameEngineWindow::ClearBackBuffer()
{
	Rectangle(BackBuffer->GetImageDC(), 0, 0, BackBuffer->GetScale().iX(), BackBuffer->GetScale().iY());
}

void GameEngineWindow::DoubleBuffering()
{
	WindowBuffer->BitCopy(BackBuffer, Scale.Half(), BackBuffer->GetScale());
}

void GameEngineWindow::Open(const std::string& _Title, HINSTANCE _hInstance)
{
	Instance = _hInstance;
	Title = _Title;

	if (nullptr == Instance)
	{
		MsgBoxAssert("HInstance없이 윈도우를 만들수는 없습니다.");
		return;
	}

	MyRegisterClass();
	InitInstance();
}


void GameEngineWindow::InitInstance()
{
	//WS_OVERLAPPED | \
    //    WS_CAPTION | \
    //    WS_SYSMENU | \
    //    WS_THICKFRAME | \
    //    WS_MINIMIZEBOX | \
    //    WS_MAXIMIZEBOX


	// int Test = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME ;









	// WS_OVERLAPPEDWINDOW

	hWnd = CreateWindowA("DefaultWindow", Title.c_str(), WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, Instance, nullptr);

	if (!hWnd)
	{
		MsgBoxAssert("윈도우 생성에 실패했습니다.");
		return;
	}

	Hdc = ::GetDC(hWnd);

	WindowBuffer = new GameEngineWindowTexture();
	WindowBuffer->ResCreate(Hdc);

	// 더플버퍼링을 하기 위한 이미지
	BackBuffer = new GameEngineWindowTexture();
	BackBuffer->ResCreate(WindowBuffer->GetScale());

	// CreateDC()

	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);

}

LRESULT CALLBACK GameEngineWindow::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_SETFOCUS:
	{
		IsFocusValue = true;
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	case WM_KILLFOCUS:
	{
		IsFocusValue = false;
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		IsWindowUpdate = false;
		// PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

void GameEngineWindow::MyRegisterClass()
{
	static bool Check = false;

	if (true == Check)
	{
		return;
	}

	WNDCLASSEXA wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	// LRESULT(CALLBACK* WNDPROC)(HWND, unsigned int, unsigned int, unsigned int);
	wcex.lpfnWndProc = GameEngineWindow::WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = Instance;
	wcex.hIcon = nullptr;
	wcex.hCursor = LoadCursor(nullptr, IDC_CROSS);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 2);
	wcex.lpszMenuName = nullptr;
	wcex.lpszClassName = "DefaultWindow";
	wcex.hIconSm = nullptr;

	if (false == RegisterClassExA(&wcex))
	{
		MsgBoxAssert("윈도우 클래스 동록에 실패했습니다.");
		return;
	}

	Check = true;
}

void GameEngineWindow::MessageLoop(HINSTANCE _Inst, void(*_Start)(HINSTANCE), void(*_Update)(), void(*_End)())
{
	// 윈도우가 뜨기전에 로딩해야할 이미지나 사운드 등등을 처리하는 단계
	if (nullptr != _Start)
	{
		_Start(_Inst);
	}

	MSG msg;

	while (IsWindowUpdate)
	{
		// 윈도우에 무슨일이 있는게 아니라 메세지가 있든 없든
		// 동기함수 _getch()
		// <= 키가 눌릴때까지 멈춘다
		// (함수가 제대로 끝날때까지 기다리는 함수들을 동기 함수라고 합니다).
		// GetMessage는 동기 함수에요. 윈도우의 메세지가 발생할때까지 기다린다.
		// 비동기 메세지 함수가 있다. 
		// PeekMessage는 윈도우 메세지가 없으면 0이 리턴되고 그냥 리턴합니다.

		// 프레임과 데드타임이 완성됐다.
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			//if (nullptr != _Update)
			//{
			//	_Update();
			//}

			TranslateMessage(&msg);
			DispatchMessage(&msg);
			continue;
		}

		// 윈도우 메세지가 없는 시간을 데드타임이라고 합니다.
		// 게임은 데드타임에 돌아가는게 보통이다.
		// 게임중에 2가지 종류가 있다. 윈도우를 움직이거나 크기를 줄이면
		// 화면이 정지하는 게임. 
		// 내가 그런 윈도우 메세지를 발생시키는 와중에도 게임은 계속 돌아가는 게임있다.

		// 이게 한바뀌가 도는 것을 프레임
		// FPS
		// 초당 화면이 그려지는 횟수
		// 하드웨어와도 연결이 있다.
		if (nullptr != _Update)
		{
			_Update();
		}

	}


	if (nullptr != _End)
	{
		_End();
	}


	// (int)msg.wParam;

	return;
}

void GameEngineWindow::SetPosAndScale(const float4& _Pos, const float4& _Scale)
{
	// Window에서 LP 포인터라는 뜻 Long Pointer
	Scale = _Scale;

	if (nullptr != BackBuffer)
	{
		delete BackBuffer;
		BackBuffer = new GameEngineWindowTexture();
		BackBuffer->ResCreate(Scale);
	}

	//                200           200
	RECT Rc = { 0, 0, _Scale.iX(), _Scale.iY() };


	AdjustWindowRect(&Rc, WS_OVERLAPPEDWINDOW, FALSE);

	//                          100        100         500          500
	SetWindowPos(hWnd, nullptr, _Pos.iX(), _Pos.iY(), Rc.right - Rc.left, Rc.bottom - Rc.top, SWP_NOZORDER);
}

// ===== 최종 삭제 주석 =======

// Open()함수 - 호출시 내 윈도우 클래스 등록하고 윈도우띄어주는 작업까지 해주는 함수

// MyRegisterClass()함수 - 내 윈도우 클래스 등록
//WNDCLASSEXA wcex;                                 // window class extension ascii
//wcex.cbSize = sizeof(WNDCLASSEX);                 // WNDCLASSEX 구조체의 크기
//wcex.style = CS_HREDRAW | CS_VREDRAW;             // class 스타일
//wcex.lpfnWndProc = GameEngineWindow::WndProc;     // WndProc(메세지를 처리할 함수이름)를 가지는함수포인터. 
//wcex.cbClsExtra = 0;                              // 클래스 여분메모리
//wcex.cbWndExtra = 0;                              // 윈도우 여분메모리
//wcex.hInstance = Instance;                        // 윈도우 응용 프로그램의 고유번호
//wcex.hIcon = nullptr;                             // 아이콘클래스의 핸들. Null이면 기본 아이콘 제공
//wcex.hCursor = LoadCursor(nullptr, IDC_CROSS);    // 커서클래스의 핸들. NULL로 하면 마우스가 어플 창으로 이동할때마다 모양을 명시적으로 해줘야함(..) 
//wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 2);  // 배경을 그리는 브러시클래스의 핸들. 
//wcex.lpszMenuName = nullptr;                      // Null 이면 윈도우 창의 기본메뉴가 없음.
//wcex.lpszClassName = "DefaultWindow";             // 내가 정의한 윈도우클래스 (wcex)의 이름
//wcex.hIconSm = nullptr;                           // 작은 아이콘 핸들. null이면 hIcon 에서 적절한 크기의 아이콘을 검색.

//InitInstance()함수 - 윈도우 생성 및 출력

//CreateWindowA(     -  윈도우 창 만들기
//"DefaultWindow", Title.c_str(), WS_OVERLAPPEDWINDOW,
//CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, Instance, nullptr);
//HWND CreateWindow(
//	LPCTSTR lpClassName,     //윈도우 클래스의 타입이름
//	LPCTSTR lpWindowName,    //윈도우 제목에 표시될 내용
//	DWORD dwStyle,           //윈도우 스타일
//	int x,                   //윈도우 x좌표
//	int y,                   //윈도우 y좌표
//	int nWidth,              //윈도우 x너비
//	int nHeight,             //윈도우 y너비
//	HWND hWndParent,         //생성할 윈도우를 가질 부모핸들. 팝업윈도우(어떤 내용을 표시하기위해 갑자기 표시하는 새 윈도우)(팝업:튀어나오다) 는 null 사용
//	HMENU hMenu,             //팝업윈도우에선 메뉴의 핸들을 뜻함. null은 사용될 메뉴가 없다는 뜻. (자식윈도우 식별자 등 다른의미로 사용되는 경우도 있다함)
//	HINSTANCE hInstance,     //윈도우 생성할 인스턴스 핸들
//	LPVOID lpParam);         //알필요없음. 설명 - 응용프로그램이 MDI 클라이언드 윈도우 생성 시  CLIENTCREATESTRUCT 구조체를 지정해야함. MDI 클라이언트 윈도우가 MDI 자식 윈도우를 생성하면 MDICREATESTRUCT 구조체를 지정. (MDI: 다중문서인터페이스). 사용안할시 null.
                              
//WndProc() 함수 내부
// PAINTSTRUCT ps; - 구조체. 
//typedef struct tagPAINTSTRUCT {
//	HDC  hdc;                //그리기에 사용될 DC 핸들값
//	BOOL fErase;             //배경을 지울것인지 아닌지. 보통 false
//	RECT rcPaint;            //그리기할 사각영역. 구조체이고 안에 long 자료형 4개 가짐. 모두 좌표값.
//	BOOL fRestore;           //나머지 인자는 운영체제 예약시스템이라는데 내부적으로 사용되고 msdn에도 자세한 설명없음.
//	BOOL fIncUpdate;
//	BYTE rgbReserved[32];
//} PAINTSTRUCT,
 
// WM_SETFOCUS - 현재 자신의 윈도우가 최상단에 띄어져서 동작하는지 알려줌.  
// DefWindowProc() - 사용자가 메세지 처리를 어떻게 할지 직접 정의해주지 않았다면, 미리 윈도우가 정의해놓은 메세지처리 함수인 이 함수로 메세지를 처리한다.

// BeginPaint(HWND hwnd, LPPAINTSTRUCT ps) - PAINTSTRUCT에서 받은 정보를 바탕으로 인자로 넣은 hwnd에 그림 그릴수 있는 DC 핸들값을 반환해줌.

//GetMessage()와 PeekMessage() - 둘다 메세지 큐로부터 메세지를 가져오나, GetMessage는 동기화함수이고 PeekMessage는 메세지 없다면 바로 리턴해버림
//BOOL PeekMessageA(
//	[out]          LPMSG lpMsg,          // 메세지 정보를 수신한 MSG 구조체의 포인터
//	[in, optional] HWND  hWnd,           // 메시지를 검색할 창에 대한 핸들. 창은 현재 스레드에 속해야 함. null이면 현재 스레드에 속한 모든 창의 메세지와 hwnd 값이 NULL인 현재 스레드의 메시지 큐에 있는 모든 메시지를 검색. 즉 창 메세지와 스레드 메세지 모두처리됨
//	[in]           UINT  wMsgFilterMin,  // wMsgFilterMin, wMsgFilterMax 는 검사할 메세지 범위의 첫번째, 마지막 메세지값. 둘다 0이면 사용가능한 모든 메세지 반환(즉 범위필터링 방식으로 메세지 처리안함)
//	[in]           UINT  wMsgFilterMax,
//	[in]           UINT  wRemoveMsg      // 메세지 처리 방식지정. PM_REMOVE: 메세지 처리후 큐에서 메세지 제거
//);


//TranslateMessage(&msg); - msg에 맞는 문자 메세지로 변환.
//DispatchMessage(&msg); - 창 프로시저에 메시지를 디스패치 함.

//BOOL AdjustWindowRect(           //원하는 클라이언트 사각형 크기를 계산해줌 (title bar, sizing border 등을 제외한 Client area(순수 그래픽 영역)의 크기를 계산)
//	[in, out] LPRECT lpRect,       //RECT구조체 포인터 (내가 원하는 순수 클라이언트 영역크기)
//	[in]      DWORD  dwStyle,      //계산하고싶은 창 스타일. 
//	[in]      BOOL   bMenu         //창에 메뉴가 있는지 여부.
//);

//BOOL SetWindowPos(                        //자식, 팝업 또는 최상위 창의 크기,위치,z순서 등을 변경해주는 함수.
//	[in]           HWND hWnd,               //창의 핸들
//	[in, optional] HWND hWndInsertAfter,    //쓸모없음. z순서 위치의 창 앞에 오는 창의 핸들(z순서 -  Z Order: 윈도우 창의 정렬기준.) 
//	[in]           int  X,                  // x좌표
//	[in]           int  Y,                  // y좌표
//	[in]           int  cx,                 // x너비 (좌표가 아님!!)
//	[in]           int  cy,                 // y너비
//	[in]           UINT uFlags              // 창크기조정 및 위치지정 플래그. SWP_NOZORDER: 현재 Z순서 유지.
//);


// void ClearBackBuffer(); - 화면에 잔상 남는거 처리 (이미지 위치가 바뀌면 이전 위치에 남은 그림들 지워주기) 어떻게? 그냥 흰색화면을 통째로 덮어씌우는것임.