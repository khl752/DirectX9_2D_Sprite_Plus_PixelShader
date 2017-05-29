#pragma once
#include "BasicHeader.h"
#include "ISprite.h"
#include "ShaderManager.h"

class DXClass
{
public:
	LPDIRECT3D9             m_pD3D				= nullptr; // Used to create the D3DDevice
	LPDIRECT3DDEVICE9       m_pd3dDevice		= nullptr; // Our rendering device
	LPD3DXSPRITE			m_pd3dSprite		= nullptr;
	ShaderManager* m_pShader = nullptr;


	BOOL					m_bVSync	= FALSE;
public:
	DXClass();
	virtual ~DXClass();

	//2D Render
	VOID	Render(ISprite* sprite)
	{
		// Clear the backbuffer to a blue color
		m_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);

		// Begin the scene
		if (SUCCEEDED(m_pd3dDevice->BeginScene()))
		{
			sprite->Draw(m_pd3dSprite);

			// End the scene
			m_pd3dDevice->EndScene();
		}

		// Present the backbuffer contents to the display
		m_pd3dDevice->Present(NULL, NULL, NULL, NULL);
	}


	// Desc: Initializes Direct3D
	// 프로그램 시작시 한번만 실행
	HRESULT InitD3D(HWND hWnd);

	// 메모리 해제
	// 프로그램 종료시 한번만 실행
	VOID	CleanUp();
};

