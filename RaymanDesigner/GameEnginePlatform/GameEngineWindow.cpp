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
		MsgBoxAssert("HInstance���� �����츦 ������� �����ϴ�.");
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
		MsgBoxAssert("������ ������ �����߽��ϴ�.");
		return;
	}

	Hdc = ::GetDC(hWnd);

	WindowBuffer = new GameEngineWindowTexture();
	WindowBuffer->ResCreate(Hdc);

	// ���ù��۸��� �ϱ� ���� �̹���
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
		MsgBoxAssert("������ Ŭ���� ���Ͽ� �����߽��ϴ�.");
		return;
	}

	Check = true;
}

void GameEngineWindow::MessageLoop(HINSTANCE _Inst, void(*_Start)(HINSTANCE), void(*_Update)(), void(*_End)())
{
	// �����찡 �߱����� �ε��ؾ��� �̹����� ���� ����� ó���ϴ� �ܰ�
	if (nullptr != _Start)
	{
		_Start(_Inst);
	}

	MSG msg;

	while (IsWindowUpdate)
	{
		// �����쿡 �������� �ִ°� �ƴ϶� �޼����� �ֵ� ����
		// �����Լ� _getch()
		// <= Ű�� ���������� �����
		// (�Լ��� ����� ���������� ��ٸ��� �Լ����� ���� �Լ���� �մϴ�).
		// GetMessage�� ���� �Լ�����. �������� �޼����� �߻��Ҷ����� ��ٸ���.
		// �񵿱� �޼��� �Լ��� �ִ�. 
		// PeekMessage�� ������ �޼����� ������ 0�� ���ϵǰ� �׳� �����մϴ�.

		// �����Ӱ� ����Ÿ���� �ϼ��ƴ�.
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

		// ������ �޼����� ���� �ð��� ����Ÿ���̶�� �մϴ�.
		// ������ ����Ÿ�ӿ� ���ư��°� �����̴�.
		// �����߿� 2���� ������ �ִ�. �����츦 �����̰ų� ũ�⸦ ���̸�
		// ȭ���� �����ϴ� ����. 
		// ���� �׷� ������ �޼����� �߻���Ű�� ���߿��� ������ ��� ���ư��� �����ִ�.

		// �̰� �ѹٲ ���� ���� ������
		// FPS
		// �ʴ� ȭ���� �׷����� Ƚ��
		// �ϵ����͵� ������ �ִ�.
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
	// Window���� LP �����Ͷ�� �� Long Pointer
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

// ===== ���� ���� �ּ� =======

// Open()�Լ� - ȣ��� �� ������ Ŭ���� ����ϰ� ���������ִ� �۾����� ���ִ� �Լ�

// MyRegisterClass()�Լ� - �� ������ Ŭ���� ���
//WNDCLASSEXA wcex;                                 // window class extension ascii
//wcex.cbSize = sizeof(WNDCLASSEX);                 // WNDCLASSEX ����ü�� ũ��
//wcex.style = CS_HREDRAW | CS_VREDRAW;             // class ��Ÿ��
//wcex.lpfnWndProc = GameEngineWindow::WndProc;     // WndProc(�޼����� ó���� �Լ��̸�)�� �������Լ�������. 
//wcex.cbClsExtra = 0;                              // Ŭ���� ���и޸�
//wcex.cbWndExtra = 0;                              // ������ ���и޸�
//wcex.hInstance = Instance;                        // ������ ���� ���α׷��� ������ȣ
//wcex.hIcon = nullptr;                             // ������Ŭ������ �ڵ�. Null�̸� �⺻ ������ ����
//wcex.hCursor = LoadCursor(nullptr, IDC_CROSS);    // Ŀ��Ŭ������ �ڵ�. NULL�� �ϸ� ���콺�� ���� â���� �̵��Ҷ����� ����� ��������� �������(..) 
//wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 2);  // ����� �׸��� �귯��Ŭ������ �ڵ�. 
//wcex.lpszMenuName = nullptr;                      // Null �̸� ������ â�� �⺻�޴��� ����.
//wcex.lpszClassName = "DefaultWindow";             // ���� ������ ������Ŭ���� (wcex)�� �̸�
//wcex.hIconSm = nullptr;                           // ���� ������ �ڵ�. null�̸� hIcon ���� ������ ũ���� �������� �˻�.

//InitInstance()�Լ� - ������ ���� �� ���

//CreateWindowA(     -  ������ â �����
//"DefaultWindow", Title.c_str(), WS_OVERLAPPEDWINDOW,
//CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, Instance, nullptr);
//HWND CreateWindow(
//	LPCTSTR lpClassName,     //������ Ŭ������ Ÿ���̸�
//	LPCTSTR lpWindowName,    //������ ���� ǥ�õ� ����
//	DWORD dwStyle,           //������ ��Ÿ��
//	int x,                   //������ x��ǥ
//	int y,                   //������ y��ǥ
//	int nWidth,              //������ x�ʺ�
//	int nHeight,             //������ y�ʺ�
//	HWND hWndParent,         //������ �����츦 ���� �θ��ڵ�. �˾�������(� ������ ǥ���ϱ����� ���ڱ� ǥ���ϴ� �� ������)(�˾�:Ƣ�����) �� null ���
//	HMENU hMenu,             //�˾������쿡�� �޴��� �ڵ��� ����. null�� ���� �޴��� ���ٴ� ��. (�ڽ������� �ĺ��� �� �ٸ��ǹ̷� ���Ǵ� ��쵵 �ִ���)
//	HINSTANCE hInstance,     //������ ������ �ν��Ͻ� �ڵ�
//	LPVOID lpParam);         //���ʿ����. ���� - �������α׷��� MDI Ŭ���̾�� ������ ���� ��  CLIENTCREATESTRUCT ����ü�� �����ؾ���. MDI Ŭ���̾�Ʈ �����찡 MDI �ڽ� �����츦 �����ϸ� MDICREATESTRUCT ����ü�� ����. (MDI: ���߹����������̽�). �����ҽ� null.
                              
//WndProc() �Լ� ����
// PAINTSTRUCT ps; - ����ü. 
//typedef struct tagPAINTSTRUCT {
//	HDC  hdc;                //�׸��⿡ ���� DC �ڵ鰪
//	BOOL fErase;             //����� ��������� �ƴ���. ���� false
//	RECT rcPaint;            //�׸����� �簢����. ����ü�̰� �ȿ� long �ڷ��� 4�� ����. ��� ��ǥ��.
//	BOOL fRestore;           //������ ���ڴ� �ü�� ����ý����̶�µ� ���������� ���ǰ� msdn���� �ڼ��� �������.
//	BOOL fIncUpdate;
//	BYTE rgbReserved[32];
//} PAINTSTRUCT,
 
// WM_SETFOCUS - ���� �ڽ��� �����찡 �ֻ�ܿ� ������� �����ϴ��� �˷���.  
// DefWindowProc() - ����ڰ� �޼��� ó���� ��� ���� ���� ���������� �ʾҴٸ�, �̸� �����찡 �����س��� �޼���ó�� �Լ��� �� �Լ��� �޼����� ó���Ѵ�.

// BeginPaint(HWND hwnd, LPPAINTSTRUCT ps) - PAINTSTRUCT���� ���� ������ �������� ���ڷ� ���� hwnd�� �׸� �׸��� �ִ� DC �ڵ鰪�� ��ȯ����.

//GetMessage()�� PeekMessage() - �Ѵ� �޼��� ť�κ��� �޼����� ��������, GetMessage�� ����ȭ�Լ��̰� PeekMessage�� �޼��� ���ٸ� �ٷ� �����ع���
//BOOL PeekMessageA(
//	[out]          LPMSG lpMsg,          // �޼��� ������ ������ MSG ����ü�� ������
//	[in, optional] HWND  hWnd,           // �޽����� �˻��� â�� ���� �ڵ�. â�� ���� �����忡 ���ؾ� ��. null�̸� ���� �����忡 ���� ��� â�� �޼����� hwnd ���� NULL�� ���� �������� �޽��� ť�� �ִ� ��� �޽����� �˻�. �� â �޼����� ������ �޼��� ���ó����
//	[in]           UINT  wMsgFilterMin,  // wMsgFilterMin, wMsgFilterMax �� �˻��� �޼��� ������ ù��°, ������ �޼�����. �Ѵ� 0�̸� ��밡���� ��� �޼��� ��ȯ(�� �������͸� ������� �޼��� ó������)
//	[in]           UINT  wMsgFilterMax,
//	[in]           UINT  wRemoveMsg      // �޼��� ó�� �������. PM_REMOVE: �޼��� ó���� ť���� �޼��� ����
//);


//TranslateMessage(&msg); - msg�� �´� ���� �޼����� ��ȯ.
//DispatchMessage(&msg); - â ���ν����� �޽����� ����ġ ��.

//BOOL AdjustWindowRect(           //���ϴ� Ŭ���̾�Ʈ �簢�� ũ�⸦ ������� (title bar, sizing border ���� ������ Client area(���� �׷��� ����)�� ũ�⸦ ���)
//	[in, out] LPRECT lpRect,       //RECT����ü ������ (���� ���ϴ� ���� Ŭ���̾�Ʈ ����ũ��)
//	[in]      DWORD  dwStyle,      //����ϰ���� â ��Ÿ��. 
//	[in]      BOOL   bMenu         //â�� �޴��� �ִ��� ����.
//);

//BOOL SetWindowPos(                        //�ڽ�, �˾� �Ǵ� �ֻ��� â�� ũ��,��ġ,z���� ���� �������ִ� �Լ�.
//	[in]           HWND hWnd,               //â�� �ڵ�
//	[in, optional] HWND hWndInsertAfter,    //�������. z���� ��ġ�� â �տ� ���� â�� �ڵ�(z���� -  Z Order: ������ â�� ���ı���.) 
//	[in]           int  X,                  // x��ǥ
//	[in]           int  Y,                  // y��ǥ
//	[in]           int  cx,                 // x�ʺ� (��ǥ�� �ƴ�!!)
//	[in]           int  cy,                 // y�ʺ�
//	[in]           UINT uFlags              // âũ������ �� ��ġ���� �÷���. SWP_NOZORDER: ���� Z���� ����.
//);


// void ClearBackBuffer(); - ȭ�鿡 �ܻ� ���°� ó�� (�̹��� ��ġ�� �ٲ�� ���� ��ġ�� ���� �׸��� �����ֱ�) ���? �׳� ���ȭ���� ��°�� �����°���.