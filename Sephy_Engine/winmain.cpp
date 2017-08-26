#include "stdafx.h"

// winmain.cpp : 응용 프로그램에 대한 진입점을 정의합니다.
#define _CRTDBG_MAP_ALLOC       // for detecting memory leaks
#define WIN32_LEAN_AND_MEAN


#include <stdlib.h>             // for detecting memory leaks
#include <crtdbg.h>             // for detecting memory leaks

#include "engineSystem.h"
// Function prototypes
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int);
// Engine Instance
EngineSystem engine;
//=============================================================================
// Global Extern Variables
//=============================================================================
// Extern Varialbes For Engine - Start
HWND g_hWndEngine		= nullptr;
HWND g_hWndScene		= nullptr;
HWND g_hWndGame			= nullptr;
HINSTANCE g_hInst		= nullptr;
Graphics* g_Graphics	= nullptr;
Input* g_Input			= nullptr;
MainNode* g_MainNode	= nullptr;
WNDCLASSEX g_wcx;
bool g_EngineShutDown	= false;
std::string	g_strEngineKey;
// End - Extern Varialbes For Engine
//=============================================================================
// Extern Variables For Display - Start
float g_fWindowPosX		= 0.f;
float g_fWindowPosY		= 0.f;
float g_fScreenWidth	= 0.f;
float g_fScreenHeight	= 0.f;
bool g_bWindowed		= false;
// End - Extern Variables For Display
//=============================================================================
// Extern Variables For Sound - Start
float g_fSoundMasterVolume	= 0.f;
float g_fSoundEffectVolume	= 0.f;
float g_fSoundBGMVolume		= 0.f;
// End - Extern Variables For Sound
//=============================================================================
// Extern Variables For Debug - Start
bool g_bDebugMode			= false;
std::string g_strDebugSceneName;
// End - Extern Variables For Debug
//=============================================================================

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