#include "DXClass.h"
#include "Defines.h"


DXClass::DXClass()
{
}


DXClass::~DXClass()
{
	CleanUp();
}

HRESULT DXClass::InitD3D(HWND hWnd)
{
	// Create the D3D object.
	if (NULL == (m_pD3D = Direct3DCreate9(D3D_SDK_VERSION)))
	{
		MessageBox(NULL, "Direct3D 积己 角菩", NULL, MB_OK | MB_ICONERROR);
		return E_FAIL;
	}

	// Set up the structure used to create the D3DDevice 
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.BackBufferCount = 1;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.BackBufferWidth = 1280;
	d3dpp.BackBufferHeight = 720;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.FullScreen_RefreshRateInHz = m_bVSync ? 60 : 0;
	
	// Create the D3DDevice
	if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp, &m_pd3dDevice)))
	{
		MessageBox(NULL, "D3DDevice 积己 角菩", NULL, MB_OK | MB_ICONERROR);
		return E_FAIL;
	}

	// Sprite
	if (FAILED(D3DXCreateSprite(m_pd3dDevice, &m_pd3dSprite)))
		return E_FAIL;

	//Shader Load
	m_pShader = new ShaderManager();
	m_pShader->ShaderLoad();

	return S_OK;
}

VOID DXClass::CleanUp()
{
	SAFE_DELETE(m_pShader);
	SAFE_RELEASE(m_pd3dSprite);
	SAFE_RELEASE(m_pd3dDevice);
	SAFE_RELEASE(m_pD3D);
}