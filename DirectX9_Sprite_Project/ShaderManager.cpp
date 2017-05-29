#include "ShaderManager.h"

//DX 셰이더 컴파일러 헤더.
#include "d3dcompiler.h"
//DX 셰이더 컴파일러 라이브러리
#pragma comment(lib, "d3dcompiler")
#include "Game.h"
#include "Defines.h"

ShaderManager::ShaderManager()
{

}


ShaderManager::~ShaderManager()
{
	ShaderRelease();
}


HRESULT ShaderManager::ShaderLoad()
{
	HRESULT hr = S_OK;
	CHAR* filename = "Shader.fx";

	LPD3DXEFFECT	m_pShaderEffect;
	DWORD dwFlags = 0;

#if defined( _DEBUG)
	dwFlags |= D3DXSHADER_DEBUG;
#endif
	LPD3DXBUFFER ppCompilationErrors = NULL;

	//ID3DXEffect 생성
	hr = D3DXCreateEffectFromFile(g_pGame->m_pDXClass->m_pd3dDevice
		, filename
		, NULL
		, NULL
		, dwFlags
		, NULL
		, &m_pShaderEffect
		, &ppCompilationErrors);
	if (FAILED(hr))
	{
		OutputDebugString(reinterpret_cast<TCHAR*>(ppCompilationErrors->GetBufferPointer()));

		ppCompilationErrors->Release();

		return hr;
	}
	else
		m_pEffect = m_pShaderEffect;

	hr = m_pShaderEffect->SetTechnique("SpritePixelShader");
	if (FAILED(hr))
	{
		MessageBox(NULL, "SetTechnique 실패", "Error", MB_OK | MB_ICONERROR);

		return hr;
	}


	//LPCSTR hlsl_ver;
	//DWORD dwShaderFlags = D3DXSHADER_DEBUG;

	//LPD3DXBUFFER pShader	= nullptr;
	//LPD3DXBUFFER pError		= nullptr;
	//
	//LPD3DXCONSTANTTABLE pConstantTable = nullptr;
	//hlsl_ver = D3DXGetPixelShaderProfile(g_pGame->m_pDXClass->m_pd3dDevice);

	//hr = D3DXCompileShaderFromFile(filename, NULL, NULL, "PS_Main", hlsl_ver, dwShaderFlags, &pShader, &pError, &pConstantTable);

	//if (FAILED(hr))
	//{
	//	OutputDebugString(reinterpret_cast<TCHAR*>(pError->GetBufferPointer()));
	//	
	//	pError->Release();

	//	return hr;
	//}

	//hr = g_pGame->m_pDXClass->m_pd3dDevice->CreatePixelShader((DWORD *)pShader->GetBufferPointer(), &m_pPixelShader);
	//if (FAILED(hr))
	//{
	//	MessageBox(NULL, "픽셀 셰이더 생성 실패...", "Error", MB_OK | MB_ICONERROR);
	//}

	//pShader->Release();

	return hr;
}
void	ShaderManager::ShaderRelease()
{
	SAFE_RELEASE(m_pEffect);
	//SAFE_RELEASE(m_pPixelShader);
}
