#include "stdafx.h"

// winmain.cpp : 응용 프로그램에 대한 진입점을 정의합니다.
#define _CRTDBG_MAP_ALLOC       // for detecting memory leaks
#define WIN32_LEAN_AND_MEAN


#include <stdlib.h>             // for detecting memory leaks
#include <crtdbg.h>             // for detecting memory leaks

#include "engineSystem.h"

// Function prototypes
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int); 
EngineSystem engine;

//extern HWND g_hWndEngine;
//extern HWND g_hWndGame;
//extern HWND g_hWndScene;
//extern HINSTANCE g_hInst;
//extern MainNode* g_MainNode;
//extern Graphics* g_Graphics;
//extern WNDCLASSEX g_wcx;
//extern bool g_EngineShutDown;

//global
HWND g_hWndEngine		= nullptr;
HWND g_hWndScene		= nullptr;
HWND g_hWndGame			= nullptr;
HINSTANCE g_hInst		= nullptr;
Graphics* g_Graphics	= nullptr;
MainNode* g_MainNode	= nullptr;
WNDCLASSEX g_wcx;
bool g_EngineShutDown	= false;
//=============================================================================
// Starting point for a Windows application
//=============================================================================
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    LPSTR lpCmdLine, int nCmdShow)
{
    // Check for memory leak if debug build
    #if defined(DEBUG) | defined(_DEBUG)
        _CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
    #endif

	if (!engine.engineStart(hInstance, nCmdShow))
		return 1;
	
    return engine.run();
}