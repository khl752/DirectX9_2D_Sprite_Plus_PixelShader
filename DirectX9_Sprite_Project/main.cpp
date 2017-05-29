//-----------------------------------------------------------------------------
// File: DirectX9_Sprite_Project.cpp
//
// Desc: In this tutorial, we are rendering some DirectX9_Sprite_Project. This introduces the
//       concept of the vertex buffer, a Direct3D object used to store
//       DirectX9_Sprite_Project. DirectX9_Sprite_Project can be defined any way we want by defining a
//       custom structure and a custom FVF (flexible vertex format). In this
//       tutorial, we are using DirectX9_Sprite_Project that are transformed (meaning they
//       are already in 2D window coordinates) and lit (meaning we are not
//       using Direct3D lighting, but are supplying our own colors).
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//-----------------------------------------------------------------------------
#pragma warning( disable : 4996 ) // disable deprecated warning 
#include "Game.h"

//-----------------------------------------------------------------------------
// Name: Render()
// Desc: Draws the scene
//-----------------------------------------------------------------------------

// Desc: The window's main message handler
static LRESULT WINAPI MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			g_pGame->m_bLoop = false;
			return 0;
		}
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

// Desc: The application's entry point
//-----------------------------------------------------------------------------
extern CGame* g_pGame = nullptr;
INT WINAPI wWinMain(HINSTANCE hInst, HINSTANCE, LPWSTR, INT)
{
	CGame game;
	g_pGame = &game;

	return game.RunApplication(hInst, MsgProc);
}
