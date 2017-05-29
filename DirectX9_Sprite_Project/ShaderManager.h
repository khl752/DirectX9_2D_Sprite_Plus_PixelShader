#pragma once
#include "BasicHeader.h"

class ShaderManager
{
public:
	//IDirect3DPixelShader9* m_pPixelShader	= nullptr;
	//IDirect3DVertexDeclaration9* m_pDec		= nullptr;
	ID3DXEffect* m_pEffect					= nullptr;
public:
	ShaderManager();
	virtual ~ShaderManager();

	HRESULT ShaderLoad();
	void	ShaderRelease();
};

