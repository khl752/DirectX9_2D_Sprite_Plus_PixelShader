#pragma once
#include "d3dx9.h"

struct TEXTURE
{
	LPDIRECT3DTEXTURE9 m_pImage;
	D3DXIMAGE_INFO m_Info;
};

__interface ISprite
{
	//BOOL SetParents()		// TODO : 자동화를 위해 생성시, 의도한 시점 에서 위치, 회전, 스케일 등의 정보를 자동으로 받아올 대상이 필요하다.
	BOOL SetTexture(char* key);
	BOOL SetTexture(TEXTURE* texture);

	void Draw(LPD3DXSPRITE pd3dsprite);
	void Update(float dTime);
};