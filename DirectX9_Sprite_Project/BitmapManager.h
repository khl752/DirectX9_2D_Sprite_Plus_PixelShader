#pragma once
#include "BasicHeader.h"

//TEXTURE ���� ���� :: ������ġ(ISprite.h)
struct TEXTURE;
class CBitmapManager
{
private:
	LPDIRECT3DDEVICE9 _pD3DDevice	= nullptr;
	std::map<std::string, TEXTURE*> m_BitmapMap;
public:
	CBitmapManager(LPDIRECT3DDEVICE9 pd3dDevice);
	virtual ~CBitmapManager();

	// Key���� NULL�� ��� filename�� Key�� ��� ����.
	void	 LoadBitmapfile(char* filename, char* key = NULL);

	// key���� filename���� �Է��ϸ� �ش� ������ �ε��Ѵ�.
	// key���� �Է������� �ε�� �̹����� ������ nullptr�� ��ȯ�Ѵ�.
	TEXTURE* GetBitmap(char* key);

	void RemoveAll();
protected:
	TEXTURE* LoadBitmapFromFile(char* filename, char* key = NULL);
};

