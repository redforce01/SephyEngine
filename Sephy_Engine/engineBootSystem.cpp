#include "stdafx.h"
#include "engineBootSystem.h"

EngineBootSystem* pBootSystem;

static LRESULT CALLBACK EngineBootProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	return pBootSystem->EngineProc(hWnd, Msg, wParam, lParam);
}

EngineBootSystem::EngineBootSystem()
{
	bEngineBooted	= false;
	pBootSystem		= this;
	rcLog = RectMake(engineBootSystemNS::BOOTLOG_BOX_X, engineBootSystemNS::BOOTLOG_BOX_Y,
		engineBootSystemNS::BOOTLOG_BOX_WIDTH, engineBootSystemNS::BOOTLOG_BOX_HEIGHT);
}

EngineBootSystem::~EngineBootSystem()
{	
	SAFE_DELETE(bootGraphics);
	if (bootThread.joinable())
		bootThread.join();
}

//====================================================
// Engine Boot Function - static void function
//  + Work On Boot Thread
//====================================================
void EngineBootSystem::EngineBoot()
{
	FILEMANAGER->initialize();

	ENGINE_BOOT_LOG->setLog("Engine Settings Load");
	pBootSystem->engineSetting->LoadEngineSetting();
	pBootSystem->m_EngineSettingInfo = pBootSystem->engineSetting->GetEngineSettings();
	pBootSystem->engineSetting->RealEngineSetup();
	ENGINE_BOOT_LOG->setLog("Engine Settings Setup To MainEngine");
	pBootSystem->bEngineBooted = true;
}

void EngineBootSystem::BootSystemInitialize(HINSTANCE hInst, int nCmdShow)
{
	
	CreateMainWindow(hWndBootSystem, hInst, nCmdShow);
	BootSystemRun();
}

int EngineBootSystem::BootSystemRun()
{

	bootGraphics = new Graphics;
	bootGraphics->initialize(hWndBootSystem, engineBootSystemNS::BOOTSYSTEM_SCREEN_WIDTH, engineBootSystemNS::BOOTSYSTEM_SCREEN_HEIGHT, false);
	bootTexture.initialize(pBootSystem->bootGraphics, engineBootSystemNS::BOOTSYSTEM_IMAGE_FILEPATH);
	bootImage.initialize(pBootSystem->bootGraphics, 0, 0, 0, &bootTexture);
	dxFont.initialize(bootGraphics, engineBootSystemNS::FONT_HEIGHT, false, false, engineBootSystemNS::FONT);
	dxFont.setFontColor(engineBootSystemNS::FONT_COLOR);
	engineSetting = new EngineSetting;
	bootThread = std::thread(EngineBoot);

	MSG msg;
	int done = 0;
	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				done = 1;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{	
			if (SUCCEEDED(bootGraphics->beginScene()))
			{
				bootGraphics->beginScene();
				bootGraphics->spriteBegin();
				bootImage.draw();				
				dxFont.print(ENGINE_BOOT_LOG->getLog(), rcLog, DT_LEFT | DT_VCENTER);
				bootGraphics->spriteEnd();
				bootGraphics->endScene();
				if (bEngineBooted)
					return msg.wParam;
			}

			//display the back buffer on the screen
			bootGraphics->showBackbuffer();
		}
	}
	return msg.wParam;
}

bool EngineBootSystem::CreateMainWindow(HWND &hWnd, HINSTANCE hInstance, int nCmdShow)
{
	// Fill in the window class structure with parameters 
	// that describe the main window. 
	WNDCLASSEX wcx;

	wcx.cbSize = sizeof(wcx);									// size of structure 
	wcx.style = CS_HREDRAW | CS_VREDRAW;						// redraw if size changes 
	wcx.lpfnWndProc = ::EngineBootProc;							// points to window procedure
	wcx.cbClsExtra = 0;											// no extra class memory 
	wcx.cbWndExtra = 0;											// no extra window memory 
	wcx.hInstance = hInstance;									// handle to instance 
	wcx.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wcx.hCursor = LoadCursor(NULL, IDC_ARROW);					// predefined arrow 
	wcx.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);	// black background 
	wcx.lpszMenuName = NULL;									// name of menu resource 
	wcx.lpszClassName = engineBootSystemNS::CLASS_NAME;			// name of window class 
	wcx.hIconSm = NULL;											// small class icon

	// Register the window class. 
	// RegisterClassEx returns 0 on error.
	if (RegisterClassEx(&wcx) == 0)    // if error
		return false;

	//set up the screen in windowed or fullscreen mode?
	DWORD style;
	style = WS_BORDER | WS_POPUP;

	// Create window
	hWnd = CreateWindow(
		engineBootSystemNS::CLASS_NAME,					// name of the window class
		engineBootSystemNS::CLASS_NAME,					// title bar text
		style,											// window style
		CW_USEDEFAULT,									// default horizontal position of window
		CW_USEDEFAULT,									// default vertical position of window
		engineBootSystemNS::BOOTSYSTEM_SCREEN_WIDTH,	// width of window
		engineBootSystemNS::BOOTSYSTEM_SCREEN_HEIGHT,	// height of the window
		(HWND)NULL,										// no parent window
		(HMENU)NULL,									// no menu
		hInstance,										// handle to application instance
		(LPVOID)NULL);									// no window parameters

								// if there was an error creating the window
	if (!hWnd)
		return false;

	int clientWidth = engineBootSystemNS::BOOTSYSTEM_SCREEN_WIDTH;
	int clientHeight = engineBootSystemNS::BOOTSYSTEM_SCREEN_HEIGHT;
		
	int width = GetSystemMetrics(SM_CXSCREEN);
	int height = GetSystemMetrics(SM_CYSCREEN);
	int monitorCount = GetSystemMetrics(SM_CMONITORS);
	
	if (monitorCount > 1)
	{
		width = width / monitorCount;
	}

	int startX = 0;
	int startY = 0;
	if (monitorCount == 1)
		startX = (width / 2) - (clientWidth / 2);
	else
		startX = width - (clientWidth / 2);
	startY = (height / 2) - (clientHeight / 2);
	MoveWindow(hWnd,
		startX,
		startY,
		clientWidth,
		clientHeight, TRUE);
	
	// Show the window
	ShowWindow(hWnd, nCmdShow);

	return true;
}

LRESULT EngineBootSystem::EngineProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, Msg, wParam, lParam);
}
