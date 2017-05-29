#pragma once
#include "BasicHeader.h"

//TEXTURE 전방 선언 :: 선언위치(ISprite.h)
struct TEXTURE;
class CBitmapManager
{
private:
	LPDIRECT3DDEVICE9 _pD3DDevice	= nullptr;
	std::map<std::string, TEXTURE*> m_BitmapMap;
public:
	CBitmapManager(LPDIRECT3DDEVICE9 pd3dDevice);
	virtual ~CBitmapManager();

	// Key값이 NULL일 경우 filename이 Key값 대신 들어간다.
	void	 LoadBitmapfile(char* filename, char* key = NULL);

	// key값을 filename으로 입력하면 해당 파일을 로드한다.
	// key값을 입력했을때 로드된 이미지가 없으면 nullptr을 반환한다.
	TEXTURE* GetBitmap(char* key);

	void RemoveAll();
protected:
	TEXTURE* LoadBitmapFromFile(char* filename, char* key = NULL);
};

