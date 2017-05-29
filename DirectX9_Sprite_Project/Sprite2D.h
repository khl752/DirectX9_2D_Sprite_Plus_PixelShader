#pragma once
#include "ISprite.h"

struct  TRANS
{
	D3DXVECTOR2 m_Pivot			= D3DXVECTOR2(0.0f, 0.0f);
	D3DXVECTOR3 m_RotateDegree	= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR2 m_RotatePivot	= D3DXVECTOR2(0.0f, 0.0f);
	D3DXVECTOR2 m_Scale			= D3DXVECTOR2(1.0f, 1.0f);
	D3DXVECTOR2 m_ScalePivot	= D3DXVECTOR2(0.0f, 0.0f);
	D3DXVECTOR2 m_Pos			= D3DXVECTOR2(0.0f, 0.0f);
	D3DXVECTOR4 m_Color			= D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);

	RECT m_CustomDrawRect		= {0, 0, 0, 0};
};

class Sprite2D :
	public ISprite
{
protected:
	TEXTURE* _pTexture;
public:
	bool m_bRender	= FALSE;
	//bool m_bUseCustomRect = FALSE;		// ���� �ʿ��Ѱ� �ǹ�.
	
	//���� ���� �����϶� �ּҰ��� �޴� ��������
	//���� ������ ȣ���� ���δ�.
	TRANS* m_pTrans = nullptr;;
public:
	Sprite2D();
	virtual ~Sprite2D();

	virtual BOOL SetTexture(char* key) override;
	virtual BOOL SetTexture(TEXTURE* texture) override;
protected:

	void Update(float dTime) override;
	void Draw(LPD3DXSPRITE pd3dsprite) override;
};

