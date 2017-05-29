#pragma once
#include "SystemClass.h"

class CGame :
	public SystemClass
{
public:
	//�Ŵ��� Ŭ����
	//...
	CBitmapManager* m_BitmapManger		= nullptr;
public:
	CGame();
	virtual ~CGame();

	virtual HRESULT Init()					override;
	virtual void	Update(float dTime)		override;
	virtual void	Clear()					override;
};

extern CGame* g_pGame;
