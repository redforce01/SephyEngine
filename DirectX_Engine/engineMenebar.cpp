#include "stdafx.h"
#include "engineMenebar.h"


EngineMenuBar::EngineMenuBar()
{
}


EngineMenuBar::~EngineMenuBar()
{
}

//=============================================================================
// Setting Default Engine Menubar
//=============================================================================
bool EngineMenuBar::initialize()
{
	bool success = false;

	HMENU hMenubar;
	HMENU hMenu;

	hMenubar = CreateMenu();
	hMenu = CreateMenu();

	try
	{
		AppendMenu(hMenu, MF_STRING, engineMenubarNS::default_Menu_QUIT, TEXT("&Quit"));
		AppendMenu(hMenubar, MF_POPUP, (UINT_PTR)hMenu, TEXT("&File"));
		if (SetMenu(g_hWndEngine, hMenubar) == false)
			throw(EngineError(engineErrorNS::ENGINE_SYSTEM_MENU_ERROR, "EngineMenubar Attach Failed"));

		AppendMenu(hMenubar, MF_POPUP, engineMenubarNS::default_Menubar_EDIT, TEXT("&Edit"));
		if(SetMenu(g_hWndEngine, hMenubar) == false)
			throw(EngineError(engineErrorNS::ENGINE_SYSTEM_MENU_ERROR, "EngineMenubar Attach Failed"));

		AppendMenu(hMenubar, MF_POPUP, engineMenubarNS::default_Menubar_OBJECT, TEXT("&Object"));
		if(SetMenu(g_hWndEngine, hMenubar) == false)
			throw(EngineError(engineErrorNS::ENGINE_SYSTEM_MENU_ERROR, "EngineMenubar Attach Failed"));

		AppendMenu(hMenubar, MF_POPUP, engineMenubarNS::default_Menubar_WINDOW, TEXT("&Window"));
		if(SetMenu(g_hWndEngine, hMenubar) == false)
			throw(EngineError(engineErrorNS::ENGINE_SYSTEM_MENU_ERROR, "EngineMenubar Attach Failed"));

		AppendMenu(hMenubar, MF_POPUP, engineMenubarNS::default_Menubar_HELP, TEXT("&Help"));
		if(SetMenu(g_hWndEngine, hMenubar) == false)
			throw(EngineError(engineErrorNS::ENGINE_SYSTEM_MENU_ERROR, "EngineMenubar Attach Failed"));

		success = true;
	}
	catch (const EngineError &err)
	{
		MessageBox(g_hWndEngine, err.getMessage(), "Error", MB_OK);
	}
	
	return success;
}
