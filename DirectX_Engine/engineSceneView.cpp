#include "stdafx.h"
#include "engineSceneView.h"

namespace engineSceneViewNS
{
	const char * WINDOW_CLASSNAME = "sceneView";
	const char * WINDOW_VIEWNAME = "Scene";
	const DWORD WINDOW_DWSTYLE = WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_THICKFRAME | WS_CAPTION;
}

EngineSceneView::EngineSceneView() : EngineWindow()
{
}


EngineSceneView::~EngineSceneView()
{
}

bool EngineSceneView::initialize(EngineInput * input, HWND hParent, HMENU hMenu, int startX, int startY, int width, int height)
{
	bool success = false;

	engineViewWS.className = engineSceneViewNS::WINDOW_CLASSNAME;
	engineViewWS.titleName = engineSceneViewNS::WINDOW_VIEWNAME;
	engineViewWS.viewName = engineSceneViewNS::WINDOW_VIEWNAME;
	engineViewWS.startX = startX;
	engineViewWS.startY = startY;
	engineViewWS.width = width;
	engineViewWS.height = height;
	engineViewWS.dwstyle = engineSceneViewNS::WINDOW_DWSTYLE;
	engineViewWS.hParent = hParent;
	engineViewWS.hMenu = hMenu;

	success = createWindowClass(engineSceneViewNS::WINDOW_CLASSNAME, input, true, g_wcx, this);
	success = createNewWindow(engineViewWS, false);

	return success;
}

LRESULT EngineSceneView::WndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	switch (Msg)
	{
	case WM_SIZE:
		RECT rc;
		GetClientRect(hWndThis, &rc);
		engineViewWS.width = rc.right - rc.left;
		engineViewWS.height = rc.bottom - rc.top;

		//Graphics* reGraphic = new Graphics;
		//reGraphic->initialize(hWnd, this->getWidth(), this->getHeight(), false);
		//g_Graphics = reGraphic;

		return 0;
	}

	return pEngineInput->messageHandler(hWnd, Msg, wParam, lParam);
}
