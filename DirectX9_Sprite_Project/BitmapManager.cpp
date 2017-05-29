#include "BitmapManager.h"
#include "ISprite.h"
#include "Defines.h"

CBitmapManager::CBitmapManager(LPDIRECT3DDEVICE9 pd3dDevice)
	: _pD3DDevice(pd3dDevice)
{
	if (pd3dDevice == nullptr)
		MessageBox(NULL, "BitmapManager :: D3DDEVICE is null",nullptr,MB_OK | MB_ICONERROR);
}


CBitmapManager::~CBitmapManager()
{
	RemoveAll();
}


void CBitmapManager::LoadBitmapfile(char* filename, char* key)
{
	TEXTURE* ptexture = nullptr;

	if (key == NULL)
		ptexture = m_BitmapMap[filename];
	else
		ptexture = m_BitmapMap[key];

	//맵에 데이터가 없으면 로드~
	if (ptexture == nullptr)
	{
		ptexture = LoadBitmapFromFile(filename);
	}
}

TEXTURE* CBitmapManager::GetBitmap(char* key)
{
	TEXTURE* ptexture = nullptr;

	ptexture = m_BitmapMap[key];
	
	if (ptexture == nullptr)
	{
		TCHAR buffer[1024] = "\0";
		sprintf_s(buffer, "해당 이미지 없음 : %s", key);
		MessageBox(NULL, buffer, nullptr, MB_OK | MB_ICONERROR);
		return nullptr;
	}

	return ptexture;
}

void CBitmapManager::RemoveAll()
{
	for (auto it = m_BitmapMap.begin(); it != m_BitmapMap.end(); ++it)
	{
		SAFE_RELEASE((*it).second->m_pImage);
		SAFE_DELETE((*it).second);
	}

	m_BitmapMap.clear();
}

TEXTURE* CBitmapManager::LoadBitmapFromFile(char* filename, char* key)
{
	LPDIRECT3DTEXTURE9 texture;
	D3DXIMAGE_INFO info;

	HRESULT hr = S_OK;

	hr = D3DXCreateTextureFromFileEx(_pD3DDevice,
		filename,
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2,
		1,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED,
		D3DX_FILTER_NONE,
		D3DX_FILTER_NONE,
		NULL,
		&info,
		nullptr,
		&texture);

	if (FAILED(hr))
	{
		TCHAR buffer[1024] = "\0";
		sprintf_s(buffer, "Create texture failed : %s", filename);
		MessageBox(NULL, buffer, nullptr, MB_OK | MB_ICONERROR);

		return nullptr;
	}

	TEXTURE* ptexture = new TEXTURE;
	ptexture->m_pImage = texture;
	ptexture->m_Info = info;

	if (key == NULL)
		m_BitmapMap[filename] = ptexture;
	else
		m_BitmapMap[key] = ptexture;

	return ptexture;
}