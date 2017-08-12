#include "stdafx.h"
#include "engineInspectorView.h"
#include "mapSystem.h"


namespace engineInspectorViewNS
{
	const char * WINDOW_CLASSNAME = "inspectorView";
	const char * WINDOW_VIEWNAME = "Insecptor";
	const DWORD WINDOW_DWSTYLE = WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_THICKFRAME | WS_CAPTION;
}

EngineInspectorView::EngineInspectorView() : EngineWindow()
{
	saveButton = nullptr;
	loadButton = nullptr;
	TileNameEdit = nullptr;
	TileLocationEdit = nullptr;
	TileImageSize = nullptr;
}


EngineInspectorView::~EngineInspectorView()
{
	SAFE_DELETE(saveButton);
	SAFE_DELETE(loadButton);
	SAFE_DELETE(TileNameEdit);
	SAFE_DELETE(TileLocationEdit);
	SAFE_DELETE(TileImageSize);
}

bool EngineInspectorView::initialize(EngineInput * input, HWND hParent, HMENU hMenu, int startX, int startY, int width, int height)
{
	bool success = false;

	engineViewWS.className = engineInspectorViewNS::WINDOW_CLASSNAME;
	engineViewWS.titleName = engineInspectorViewNS::WINDOW_VIEWNAME;
	engineViewWS.viewName = engineInspectorViewNS::WINDOW_VIEWNAME;
	engineViewWS.startX = startX;
	engineViewWS.startY = startY;
	engineViewWS.width = width;
	engineViewWS.height = height;
	engineViewWS.dwstyle = engineInspectorViewNS::WINDOW_DWSTYLE;
	engineViewWS.hParent = hParent;
	engineViewWS.hMenu = hMenu;

	success = createWindowClass(engineInspectorViewNS::WINDOW_CLASSNAME, input, false, g_wcx, this);
	success = createNewWindow(engineViewWS, false);

	return success;
}

LRESULT EngineInspectorView::WndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	RECT rc;

	switch (Msg)
	{
	case WM_CREATE:
		saveButton = new EngineButton;
		saveButton->initialize("SAVE", 1, 20, 20, 100, 20, hWnd);
		loadButton = new EngineButton;
		saveButton->initialize("LOAD", 2, 130, 20, 100, 20, hWnd);
		TileNameEdit = new EngineEditControl;
		TileNameEdit->initialize("TileEdit", 10, 40, 100, 100, 20, hWnd);
		TileLocationEdit = new EngineEditControl;
		TileLocationEdit->initialize("TileLocation", 11, 40, 120, 100, 20, hWnd);
		TileImageSize = new EngineEditControl;
		TileImageSize->initialize("TileImageSize", 11, 40, 140, 100, 20, hWnd);
		
		return 0;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case 1 :
			saveMapData();
			break;
		case 2:
			loadMapData();
			break;
		case 20:
			switch (HIWORD(wParam))
			{
			case EN_CHANGE:
				break;
			case EN_SETFOCUS:				
				break;
			}
			break;
		}
		return 0;
	case WM_SIZE:		
		GetClientRect(hWndThis, &rc);
		engineViewWS.width = rc.right - rc.left;
		engineViewWS.height = rc.bottom - rc.top;
		return 0;
	} 

	return pEngineInput->messageHandler(hWnd, Msg, wParam, lParam);
}

bool EngineInspectorView::saveMapData()
{
	bool success = false;

	MessageBox(hWndThis, "Save Button!", "Save", MB_OK);

	return success;
}

bool EngineInspectorView::loadMapData()
{
	bool success = false;

	MessageBox(hWndThis, "Load Button!", "Load", MB_OK);

	return success;
}
