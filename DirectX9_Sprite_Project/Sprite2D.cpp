#include "Sprite2D.h"
#include "Game.h"
#include "Defines.h"

Sprite2D::Sprite2D()
{
	m_pTrans = new TRANS;
}


Sprite2D::~Sprite2D()
{
	SAFE_DELETE(m_pTrans);
}

// 이미지 데이터는 SetTexture를 하기 전에 이미 불러와져 있어야 합니다. (BitmapManager::LoadBitmapfile(filename, key)
BOOL Sprite2D::SetTexture(char* key)
{
	// TODO : 텍스처 로드
	_pTexture = g_pGame->m_BitmapManger->GetBitmap(key);

	if (_pTexture == nullptr)
		return FALSE;

	m_bRender = TRUE;
	m_pTrans->m_CustomDrawRect.left		= 0;
	m_pTrans->m_CustomDrawRect.top		= 0;
	m_pTrans->m_CustomDrawRect.right	= _pTexture->m_Info.Width;
	m_pTrans->m_CustomDrawRect.bottom	= _pTexture->m_Info.Height;

	m_pTrans->m_Pivot.x = -(FLOAT)(_pTexture->m_Info.Width / 2);
	m_pTrans->m_Pivot.y = -(FLOAT)(_pTexture->m_Info.Height / 2);

	m_pTrans->m_RotatePivot = m_pTrans->m_ScalePivot = m_pTrans->m_Pivot;

	return TRUE;
}

BOOL Sprite2D::SetTexture(TEXTURE* texture)
{
	if (texture != nullptr)
	{
		_pTexture = texture;

		m_bRender = TRUE;
		m_pTrans->m_CustomDrawRect.left		= 0;
		m_pTrans->m_CustomDrawRect.top		= 0;	
		m_pTrans->m_CustomDrawRect.right	= _pTexture->m_Info.Width;
		m_pTrans->m_CustomDrawRect.bottom	= _pTexture->m_Info.Height;

		m_pTrans->m_Pivot.x = -(FLOAT)(_pTexture->m_Info.Width / 2);
		m_pTrans->m_Pivot.y = -(FLOAT)(_pTexture->m_Info.Height / 2);

		m_pTrans->m_RotatePivot = m_pTrans->m_ScalePivot = m_pTrans->m_Pivot;

		return TRUE;
	}

	return FALSE;
}

void Sprite2D::Update(float dTime)
{

}

void Sprite2D::Draw(LPD3DXSPRITE pd3dsprite)
{
	if (!m_bRender)
		return;

	D3DXMATRIX mWorld;
	D3DXMATRIX mTx;
	D3DXMATRIX mPivot;
	D3DXMATRIX mScale;
	D3DXMATRIX mRotate;

	D3DXMatrixIdentity(&mWorld);
	D3DXMatrixIdentity(&mPivot);
	D3DXMatrixIdentity(&mScale);
	D3DXMatrixIdentity(&mRotate);
	D3DXMatrixIdentity(&mTx);

	D3DXMatrixTranslation(&mScale, m_pTrans->m_ScalePivot.x, m_pTrans->m_ScalePivot.y, 0.0f);
	D3DXMatrixScaling(&mScale, m_pTrans->m_Scale.x, m_pTrans->m_Scale.y, 0.0f);

	mWorld *= mScale;

	D3DXMatrixTranslation(&mRotate, m_pTrans->m_RotatePivot.x, m_pTrans->m_RotatePivot.y, 0.0f);
	D3DXMatrixRotationYawPitchRoll(&mRotate, D3DXToRadian(m_pTrans->m_RotateDegree.x), D3DXToRadian(m_pTrans->m_RotateDegree.y), D3DXToRadian(m_pTrans->m_RotateDegree.z));

	mWorld *= mRotate;

	D3DXMatrixTranslation(&mTx, m_pTrans->m_Pos.x + m_pTrans->m_Pivot.x,
								m_pTrans->m_Pos.y + m_pTrans->m_Pivot.y,
								0.0f);

	mWorld *= mTx;

	g_pGame->m_pDXClass->m_pShader->m_pEffect->SetMatrix("mWorldTrans", &mWorld);

	pd3dsprite->Begin(D3DXSPRITE_ALPHABLEND);

	g_pGame->m_pDXClass->m_pShader->m_pEffect->Begin(NULL, NULL);
	g_pGame->m_pDXClass->m_pShader->m_pEffect->BeginPass(0);


	pd3dsprite->Draw(_pTexture->m_pImage, &m_pTrans->m_CustomDrawRect, NULL, NULL, D3DXCOLOR(m_pTrans->m_Color));
	
	g_pGame->m_pDXClass->m_pShader->m_pEffect->EndPass();
	g_pGame->m_pDXClass->m_pShader->m_pEffect->End();

	pd3dsprite->End();
}