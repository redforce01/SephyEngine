#include "stdafx.h"
#include "engineSystem.h"

// EngineSystem Pointer For CALLBACK EngineProc
EngineSystem* pEngine;

//=============================================================================
// Main Engine Proc
//=============================================================================
static LRESULT CALLBACK EngineProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	return pEngine->EngineProc(hWnd, Msg, wParam, lParam);
}

EngineSystem::EngineSystem()
{
	pEngineInput		= nullptr;
	engineSceneView		= nullptr;
	engineInspectorView = nullptr;
	engineResourceView	= nullptr;
	engineSetting		= nullptr;

	ZeroMemory(&m_EngineSettingInfo, sizeof(m_EngineSettingInfo));
}

EngineSystem::~EngineSystem()
{
	//engineSetting->SaveEngineSetting();

	SAFE_DELETE(engineSceneView);
	SAFE_DELETE(engineResourceView);
	SAFE_DELETE(engineInspectorView);
	SAFE_DELETE(g_Graphics);
	SAFE_DELETE(g_MainNode);
	SAFE_DELETE(pEngineInput);
	SAFE_DELETE(engineSetting);	
}

//=============================================================================
// Engine Start
// This Function Will Load When WinMain.cpp Start
//=============================================================================
bool EngineSystem::engineStart(HINSTANCE hInstance, int nCmdShow)
{
	engineBootSystem.BootSystemInitialize(hInstance, nCmdShow);

	//FILEMANAGER->initialize();

	engineSetting = new EngineSetting;
	//engineSetting->LoadEngineSetting();

	//m_EngineSettingInfo = engineSetting->GetEngineSettings();
	//engineSetting->RealEngineSetup();

	bool success = false;
	
	// pEngine->Set This Point. 
	// For Static Engine & Game Proc
	::pEngine = this;

	try
	{
		pEngineInput = new EngineInput;

		// Create Engine-Main Window
		if (CreateMainWindow(g_hWndEngine, hInstance, nCmdShow) == false)
			throw(EngineError(engineErrorNS::ENGINE_CORE_ERROR, "Engine Main Window Create Failed"));

		//if (engineMenubar.initialize() == false)
		//	throw(EngineError(engineErrorNS::ENGINE_SYSTEM_MENU_ERROR, "EngineMenubar Create Failed"));

		RECT rc;
		GetClientRect(g_hWndEngine, &rc);
		int height = (rc.bottom - rc.top) / 2;

		//engineSceneView = new EngineSceneView;
		//engineSceneView->initialize(new EngineInput, g_hWndEngine, (HMENU)1, 0, 0, 1280, 720);
		//engineResourceView = new EngineResourceView;
		//engineResourceView->initialize(new EngineInput, g_hWndEngine, (HMENU)2, engineSceneView->getRect().right, 0, 250, rc.bottom - rc.top / 2);
		//engineInspectorView = new EngineInspectorView;
		//engineInspectorView->initialize(new EngineInput, g_hWndEngine, (HMENU)3, engineResourceView->getRect().right, 0, 400, rc.bottom - rc.top);

		//g_hWndScene = engineSceneView->getHwnd();

		success = true;
	}
	catch (const EngineError &err)
	{
		MessageBox(g_hWndEngine, err.getMessage(), "Error", MB_OK);
	}
	
	return success;
}

//=============================================================================
// Engine Run
// Global Graphics Pointer initialize 
// MainNode initialize
// Window Message Loop -> MainNode.Update()
// if has found something problem, It would be catched GameError
//=============================================================================
int EngineSystem::run()
{	
	bEngineStart = true;

	//Graphics Initialize
	g_Graphics = new Graphics;
	g_Graphics->initialize(g_hWndEngine, g_fScreenWidth, g_fScreenHeight, g_bWindowed);

	//Main Node Initialize
	g_MainNode = new MainNode;
	g_MainNode->initialize();

	auto handle = engineBootSystem.GetBootSystemHandle();
	DestroyWindow(handle);
	ShowWindow(g_hWndEngine, SW_SHOWNORMAL);

	MSG msg;
	try {
		// main message loop
		int done = 0;
		while (!done)
		{
			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				// look for quit message
				if (msg.message == WM_QUIT)
					done = 1;

				// decode and pass messages on to WinProc
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else
			{
				g_MainNode->update();			// Main Node Update()  Message Loop -> Update()
			}
		}
		//SAFE_DELETE (game);     // free memory before exit
		return msg.wParam;
	}
	catch (const EngineError &err)
	{
		g_MainNode->release();													// MainNode release
		DestroyWindow(g_hWndEngine);											// Destory Engine Window
		//DestroyWindow(g_hWndScene);
		MessageBox(NULL, err.getMessage(), "Error", MB_OK);
	}
	catch (...)
	{
		g_MainNode->release();													// MainNode release
		DestroyWindow(g_hWndEngine);											// Destory Engine Window
		//DestroyWindow(g_hWndScene);
		MessageBox(NULL, "Unknown error occured in game.", "Error", MB_OK);
	}

	
	return 0;
}

//=============================================================================
// Create the window
// Returns: false on error
//=============================================================================
bool EngineSystem::CreateMainWindow(HWND &hWnd, HINSTANCE hInstance, int nCmdShow)
{
	// Fill in the window class structure with parameters 
    // that describe the main window. 
	g_wcx.cbSize = sizeof(g_wcx);									// size of structure 
	g_wcx.style = CS_HREDRAW | CS_VREDRAW;							// redraw if size changes 
	g_wcx.lpfnWndProc = ::EngineProc;								// points to window procedure
	g_wcx.cbClsExtra = 0;											// no extra class memory 
	g_wcx.cbWndExtra = 0;											// no extra window memory 
	g_wcx.hInstance = hInstance;									// handle to instance 
	g_wcx.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	g_wcx.hCursor = LoadCursor(NULL, IDC_ARROW);					// predefined arrow 
	g_wcx.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);		// black background 
	g_wcx.lpszMenuName = NULL;										// name of menu resource 
	g_wcx.lpszClassName = CLASS_NAME;								// name of window class 
	g_wcx.hIconSm = NULL;											// small class icon

	g_hInst = g_wcx.hInstance;										// global hInstance = g_wcx.hInstance

	// Register the window class. 
	// RegisterClassEx returns 0 on error.
	if (RegisterClassEx(&g_wcx) == 0)    // if error
		return false;

	//set up the screen in windowed or fullscreen mode?
	DWORD style;
	if(g_bWindowed)
	//if (FULLSCREEN)
		style = WS_EX_TOPMOST | WS_POPUP;
	else
		style = WS_OVERLAPPEDWINDOW;
	
	// Create window
	hWnd = CreateWindow(
		CLASS_NAME,             // name of the window class
		GAME_TITLE,             // title bar text
		style,                  // window style
		CW_USEDEFAULT,          // default horizontal position of window
		CW_USEDEFAULT,          // default vertical position of window
		g_fScreenWidth,			//WINSIZEX,				// width of window
		g_fScreenHeight,		//WINSIZEY,				// height of the window
		(HWND)NULL,				// no parent window
		(HMENU)NULL,			// no menu
		hInstance,              // handle to application instance
		(LPVOID)NULL);			// no window parameters

	// if there was an error creating the window
	if (!hWnd)
		return false;

	if(!g_bWindowed)
	//if (!FULLSCREEN)             // if window
	{		
		// Adjust window size so client area is GAME_WIDTH x GAME_HEIGHT
		RECT clientRect;
		GetClientRect(hWnd, &clientRect);   // get size of client area of window
		MoveWindow(hWnd,
			g_fWindowPosX,													// STARTX,										// Left
			g_fWindowPosY,													// STARTY,										// Top
			g_fScreenWidth + (g_fScreenWidth - clientRect.right),			// WINSIZEX + (WINSIZEX - clientRect.right),    // Right
			g_fScreenHeight + (g_fScreenHeight - clientRect.bottom),		// WINSIZEY + (WINSIZEY - clientRect.bottom),	// Bottom
			TRUE);															// Repaint the window
	}

	// Show the window
	//ShowWindow(hWnd, nCmdShow);

	return true;
}

//=============================================================================
// Window Event Callback Function
// This Proc Function is Static 
// It will be converted For Engine messageHandler
//=============================================================================
LRESULT EngineSystem::EngineProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{	
	//return (engineInput->messageHandler(hWnd, Msg, wParam, lParam));
	return (g_MainNode->messageHandler(hWnd, Msg, wParam, lParam));
}