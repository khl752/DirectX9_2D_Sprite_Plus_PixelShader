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

	//WNDPROC는 CreateClient에서 WindowCalss를 생성할때 Main proc로 설정된다.
	HRESULT	RunApplication(const HINSTANCE hInst, WNDPROC winProc);
protected:
	//오버라이딩 될 함수들...
	//-------------------------
	virtual HRESULT	Init() { return S_OK; }
	virtual	void	Update(float dTime) {}
	virtual void	Clear() {}
private:

	// 프레임마다 업데이트 되는 함수
	//-------------------------

	//SystemTime
	void UpdateTime();

	//프레임 Loop
	void Frame();
	
	// 윈도우 메세지가 없으면 FALSE를 반환
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

	//프로그램 시작시 한번만 실행
	//-------------------------
	HRESULT CreateWnd(const HINSTANCE hInst, WNDPROC winProc);
	virtual HRESULT InitApplication();
	//-------------------------

	//프로그램 종료시 한번만 실행
	//-------------------------
	void	ShutDownApplication();
	//-------------------------


	//각종 함수
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