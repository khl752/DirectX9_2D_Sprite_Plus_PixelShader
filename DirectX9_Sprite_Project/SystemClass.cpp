#include "SystemClass.h"
#include "Defines.h"
#include "DXClass.h"

SystemClass::SystemClass()
{

}

SystemClass::~SystemClass()
{
}

// 어플리케이션 의 메인 루프
// Update가 Game클래스에 오버라이딩 되어 게임의 흐름이 된다..
void SystemClass::Frame()
{
	//기타 시스템 업데이트
	//...
	UpdateTime();

	//게임 런타임
	//하위 클래스 업데이트 실시
	Update(0.0f);
}

HRESULT SystemClass::InitApplication()
{
	// 기타 시스템 초기화
	// ...
	m_pDXClass = new DXClass;							//Temp
	if (FAILED(m_pDXClass->InitD3D(m_hWnd)))			//Temp
	{
		MessageBox(NULL, "D3D초기화 실패", NULL, MB_OK | MB_ICONERROR);
		return E_FAIL;
	}

	//오버라이딩된 함수 (하위 클래스의 초기화 시행)
	if (FAILED(Init()))
	{
		MessageBox(NULL, "초기화 실패", NULL, MB_OK | MB_ICONERROR);
		return E_FAIL;
	}

	return S_OK;
}

HRESULT SystemClass::CreateWnd(const HINSTANCE hInst, WNDPROC winProc)
{
	m_hInstance = hInst;
	UNREFERENCED_PARAMETER(m_hInstance);

	// Register the window class
	WNDCLASSEX wc =
	{
		sizeof(WNDCLASSEX), CS_CLASSDC, winProc, 0L, 0L,
		GetModuleHandle(NULL), NULL, NULL, NULL, NULL,
		m_WindowName, NULL
	};
	RegisterClassEx(&wc);

	// Create the application's window
	m_hWnd = CreateWindow(m_WindowName, m_ApplicationName,
		WS_OVERLAPPEDWINDOW, 0, 0, m_WindowHeight, m_WindowWidth,
		NULL, NULL, wc.hInstance, NULL);

	ShowWindow(m_hWnd, SW_SHOWDEFAULT);
	UpdateWindow(m_hWnd);

	ResizeWindow(m_hWnd, m_WindowWidth, m_WindowHeight);

	SetCursor(LoadCursor(NULL, IDC_ARROW));

	return S_OK;
}

HRESULT	SystemClass::RunApplication(const HINSTANCE hInst, WNDPROC winProc)
{
	CreateWnd(hInst, winProc);

	InitApplication();

	//어플리케이션의 루프...
	while (m_bLoop)
	{
		if (!MessagePump())
		{
			Frame();
		}
	}

	ShutDownApplication();
	
	return S_OK;
}

// 데이터 삭제, 해제등 메모리 정리를 실시.
void	SystemClass::ShutDownApplication()
{
	//하위 클래스의 정리 실시
	Clear();

	SAFE_DELETE(m_pDXClass);

	UnregisterClass(m_WindowName, m_hInstance);
}

//시스템 타임 업데이트
void SystemClass::UpdateTime()
{
	static int tempFPS		= 0;
	static int TotalTime	= 0;
	static int PrevTime		= GetTickCount();

	int CurrentTime = GetTickCount();
	int deltaTime	= CurrentTime - PrevTime;

	m_fDeltaTime = deltaTime * 0.001f;

	++tempFPS;

	TotalTime += deltaTime;
	if (TotalTime >= 1000)
	{
		TotalTime = 0;

		m_nFPS = tempFPS;
		tempFPS = 0;
	}

	PrevTime = CurrentTime;
}