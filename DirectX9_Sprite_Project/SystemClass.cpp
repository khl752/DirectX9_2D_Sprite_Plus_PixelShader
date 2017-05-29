#include "SystemClass.h"
#include "Defines.h"
#include "DXClass.h"

SystemClass::SystemClass()
{

}

SystemClass::~SystemClass()
{
}

// ���ø����̼� �� ���� ����
// Update�� GameŬ������ �������̵� �Ǿ� ������ �帧�� �ȴ�..
void SystemClass::Frame()
{
	//��Ÿ �ý��� ������Ʈ
	//...
	UpdateTime();

	//���� ��Ÿ��
	//���� Ŭ���� ������Ʈ �ǽ�
	Update(0.0f);
}

HRESULT SystemClass::InitApplication()
{
	// ��Ÿ �ý��� �ʱ�ȭ
	// ...
	m_pDXClass = new DXClass;							//Temp
	if (FAILED(m_pDXClass->InitD3D(m_hWnd)))			//Temp
	{
		MessageBox(NULL, "D3D�ʱ�ȭ ����", NULL, MB_OK | MB_ICONERROR);
		return E_FAIL;
	}

	//�������̵��� �Լ� (���� Ŭ������ �ʱ�ȭ ����)
	if (FAILED(Init()))
	{
		MessageBox(NULL, "�ʱ�ȭ ����", NULL, MB_OK | MB_ICONERROR);
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

	//���ø����̼��� ����...
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

// ������ ����, ������ �޸� ������ �ǽ�.
void	SystemClass::ShutDownApplication()
{
	//���� Ŭ������ ���� �ǽ�
	Clear();

	SAFE_DELETE(m_pDXClass);

	UnregisterClass(m_WindowName, m_hInstance);
}

//�ý��� Ÿ�� ������Ʈ
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