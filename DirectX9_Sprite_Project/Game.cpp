#include "BasicHeader.h"
#include "Defines.h"
#include "Sprite2D.h"
#include "Game.h"

ISprite* pSprite = new Sprite2D;
CGame::CGame()
{
}


CGame::~CGame()
{
}

HRESULT CGame::Init()
{
	// 매니저 초기화
	// ...
	m_BitmapManger = new CBitmapManager(m_pDXClass->m_pd3dDevice);
	m_BitmapManger->LoadBitmapfile("Texture/asd.png");
	pSprite->SetTexture("Texture/asd.png");

	return S_OK;
}
void	CGame::Update(float dTime)
{
	
	m_pDXClass->Render(pSprite);
}
void	CGame::Clear()
{
	SAFE_DELETE(pSprite);
	SAFE_DELETE(m_BitmapManger);
}