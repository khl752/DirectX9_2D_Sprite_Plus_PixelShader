#pragma once
#include "BasicHeader.h"
#include "UserDefinedHeader.h"

class SystemClass
{
public:
	//Graphic Class
	DXClass* m_pDXClass;
public:
	TCHAR*			m_WindowName		= "2DSprite_Game";
	TCHAR*			m_ApplicationName	= "2D_Sprite_Shader_Project";

	UINT			m_WindowWidth	= 1280;
	UINT			m_WindowHeight	= 720;

	HWND			m_hWnd			= NULL;
	HINSTANCE		m_hInstance		= NULL;
	BOOL			m_bLoop			= TRUE;

	FLOAT			m_fDeltaTime	= 0.0f;
	INT				m_nFPS			= 0;
public:
	SystemClass();
	virtual ~SystemClass();

	//WNDPROC�� CreateClient���� WindowCalss�� �����Ҷ� Main proc�� �����ȴ�.
	HRESULT	RunApplication(const HINSTANCE hInst, WNDPROC winProc);
protected:
	//�������̵� �� �Լ���...
	//-------------------------
	virtual HRESULT	Init() { return S_OK; }
	virtual	void	Update(float dTime) {}
	virtual void	Clear() {}
private:

	// �����Ӹ��� ������Ʈ �Ǵ� �Լ�
	//-------------------------

	//SystemTime
	void UpdateTime();

	//������ Loop
	void Frame();
	
	// ������ �޼����� ������ FALSE�� ��ȯ
	BOOL	MessagePump()
	{
		MSG msg;
		ZeroMemory(&msg, sizeof(msg));

		if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				m_bLoop = FALSE;

			TranslateMessage(&msg);
			DispatchMessage(&msg);

			return TRUE;
		}

		return FALSE;
	}
	//-------------------------

	//���α׷� ���۽� �ѹ��� ����
	//-------------------------
	HRESULT CreateWnd(const HINSTANCE hInst, WNDPROC winProc);
	virtual HRESULT InitApplication();
	//-------------------------

	//���α׷� ����� �ѹ��� ����
	//-------------------------
	void	ShutDownApplication();
	//-------------------------


	//���� �Լ�
	//-------------------------
	void ResizeWindow(HWND hWnd, UINT width, UINT height)
	{
		RECT oldrc;
		DWORD style = (DWORD) ::GetWindowLong(hWnd, GWL_STYLE);
		DWORD exstyle = (DWORD) ::GetWindowLong(hWnd, GWL_EXSTYLE);

		::GetWindowRect(hWnd, &oldrc);

		RECT newrc;
		newrc.left = 0;
		newrc.top = 0;
		newrc.right = width;
		newrc.bottom = height;

		::AdjustWindowRectEx(&newrc, style, NULL, exstyle);


		int newWidth = (newrc.right - newrc.left);
		int newHeight = (newrc.bottom - newrc.top);

		::SetWindowPos(hWnd, HWND_NOTOPMOST,
			oldrc.left, oldrc.top, newWidth, newHeight, SWP_SHOWWINDOW);
	}
};