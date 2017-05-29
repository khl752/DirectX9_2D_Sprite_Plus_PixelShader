#pragma once
#include "d3dx9.h"

struct TEXTURE
{
	LPDIRECT3DTEXTURE9 m_pImage;
	D3DXIMAGE_INFO m_Info;
};

__interface ISprite
{
	//BOOL SetParents()		// TODO : �ڵ�ȭ�� ���� ������, �ǵ��� ���� ���� ��ġ, ȸ��, ������ ���� ������ �ڵ����� �޾ƿ� ����� �ʿ��ϴ�.
	BOOL SetTexture(char* key);
	BOOL SetTexture(TEXTURE* texture);

	void Draw(LPD3DXSPRITE pd3dsprite);
	void Update(float dTime);
};