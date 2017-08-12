#include "stdafx.h"
#include "engineWindow.h"

EngineWindow* pEngineWindow;
static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

EngineWindow::EngineWindow()
{
	hWndThis = nullptr;
	hWndParent = nullptr;
	bChildWindow = false;
	bShowHide = true;
	rcThis = { 0, 0, 0, 0 };

	pEngineInput = nullptr;
	ZeroMemory(&engineViewWS, sizeof(engineViewWS));
}

EngineWindow::~EngineWindow()
{
	SAFE_DELETE(pEngineInput);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	return pEngineWindow->WndProc(hWnd, msg, wParam, lParam);
}

bool EngineWindow::createWindowClass(
	const char * const ClassName,
	EngineInput * input,
	bool bNewWindow,
	WNDCLASSEX wndClassEx,
	EngineWindow* pEngineWindow)
{
	bool success = false;

	::pEngineWindow = pEngineWindow;
	engineViewWS.className = ClassName;
	pEngineInput = input;

	try
	{
		if (bNewWindow)
		{
			WNDCLASSEX wcx;

			wcx.cbSize = sizeof(wcx);
			wcx.cbClsExtra = 0;
			wcx.cbWndExtra = 0;
			//wcx.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
			wcx.hbrBackground = CreateSolidBrush(RGB(64, 64, 64));
			wcx.hCursor = LoadCursor(NULL, IDI_APPLICATION);
			wcx.hIcon = LoadIcon(NULL, IDI_APPLICATION);
			wcx.hInstance = GetModuleHandle(NULL);
			wcx.lpfnWndProc = ::WndProc;
			wcx.lpszClassName = ClassName;
			wcx.lpszMenuName = NULL;
			wcx.style = CS_HREDRAW | CS_VREDRAW;
			wcx.hIconSm = NULL;

			// Register the window class.
			// RegisterClassEx returns 0 on error.
			if (RegisterClassEx(&wcx) == 0)    // if error
				throw(EngineError(engineErrorNS::ENGINE_INTERFACE_ERROR, "wndClassEx RegisterClassEx Failed"));

			success = true;
		}
		else
		{
			wndClassEx.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
			//wndClassEx.hbrBackground = CreateSolidBrush(RGB(64, 64, 64));
			wndClassEx.lpfnWndProc = ::WndProc;
			wndClassEx.lpszClassName = ClassName;

			// Register the window class.
			// RegisterClassEx returns 0 on error.
			if (RegisterClassEx(&wndClassEx) == 0)    // if error
				throw(EngineError(engineErrorNS::ENGINE_INTERFACE_ERROR, "wndClassEx RegisterClassEx Failed"));

			success = true;
		}
	}
	catch (const EngineError &err)
	{
		MessageBox(g_hWndEngine, err.getMessage(), "Error", MB_OK);
	}
	
	return success;
}

bool EngineWindow::createNewWindow(
	const char * const TitleName,
	const char * const PropertyName,
	DWORD style,
	int x, int y,
	int width, int height,
	HWND hParentWnd, HMENU hMenu)
{
	bool success = false;

	try
	{
		engineViewWS.titleName = TitleName;
		engineViewWS.propName = PropertyName;

		hWndThis = CreateWindow(
			engineViewWS.className,		// name of window class
			engineViewWS.titleName,		// title bar Text
			style,					// Window Style
			x,						// Start X
			y,						// Start Y
			width,					// Window Width
			height,					// Window Height
			hParentWnd,				// HWND Parent
			hMenu,					// HMENU
			GetModuleHandle(NULL),	// hInstance
			(LPVOID)NULL);			// no Window Parameters

		// if there was an error creating the window
		if (!hWndThis)
			throw(EngineError(engineErrorNS::ENGINE_INTERFACE_ERROR, "Engine CreateNewWindow hWndThis = NULL"));

		/* Not Using This Code */
		// if this window is child
		//if (bChildWindow)
		//{
		//	// Save instance Pointer on window property
		//	// SetProp(hWnd, propName, (HANDLE)this);
		//	SetProp(hWndThis, windowEx.propName, (HANDLE)this);
		//}
		
		RECT rcEngine;
		GetClientRect(g_hWndEngine, &rcEngine);

		RECT rcWindow;
		AdjustWindowRect(&rcWindow, style, false);
		SetWindowPos(hWndThis, NULL, x, y, rcWindow.right - rcWindow.left, rcWindow.bottom - rcWindow.top, style);
		rcThis = RectMake(x, y, width, height);
		
		engineViewWS.basicX = x;
		engineViewWS.basicY = y;

		ENGINE_WINDOW_MANAGER->addWindow(engineViewWS.titleName, this);

		success = true;
	}
	catch (const EngineError &err)
	{
		MessageBox(g_hWndEngine, err.getMessage(), "Error", MB_OK);
	}
	
	return success;
}

bool EngineWindow::createNewTabControl(DWORD dwStyle, int x, int y, int width, int height, HWND hParent, HMENU hMenu)
{
	bool success = false;

	try
	{
		hWndParent = hParent;
		hWndThis = CreateWindow(WC_TABCONTROL, "", dwStyle, x, y, width, height, hParent, hMenu, GetModuleHandle(NULL), (LPVOID)NULL);

		if (!hWndThis)
		{
			throw(EngineError(engineErrorNS::ENGINE_INTERFACE_ERROR, "EngineWindow Create TabControl Failed"));
		}

		success = true;
	}
	catch (const EngineError &err)
	{
		MessageBox(g_hWndEngine, err.getMessage(), "Error", MB_OK);
	}

	return success;
}

void EngineWindow::setShowHide()
{
	bShowHide = !bShowHide;
	if (bShowHide)
		ShowWindow(this->hWndThis, SW_SHOW);
	else
		ShowWindow(this->hWndThis, SW_HIDE);
}

void EngineWindow::windowPosUpdate()
{
	SetWindowPos(hWndThis, HWND_TOP, engineViewWS.startX, engineViewWS.startY, engineViewWS.width, engineViewWS.height, SWP_NOZORDER);
}


