#include "stdafx.h"
#include "engineEditControl.h"

namespace engineEditControlNS
{
	constexpr DWORD dwStyle = WS_TABSTOP | WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL | ES_LEFT;
	constexpr char* className = "Engine_Button";
	constexpr char* propName = "Button";
}

EngineEditControl::EngineEditControl()
{
	hWndParent = nullptr;
	hWndThis = nullptr;
	controlId = 0;
	dwStyle =  engineEditControlNS::dwStyle;
}

EngineEditControl::EngineEditControl(DWORD style)
{
	hWndParent = nullptr;
	hWndThis = nullptr;
	controlId = 0;
	dwStyle = style;
}

EngineEditControl::~EngineEditControl()
{
}

bool EngineEditControl::initialize(std::string controlName, int btnId, int x, int y, int width, int height, HWND hParent)
{
	bool success = false;

	try
	{
		buttonName = controlName;
		controlId = btnId;
		rcControl = { x, y,width, height };

		success = createEditControl(controlName.c_str(), dwStyle, x, y, width, height, hParent, (HMENU)controlId);
		if (!success)
			throw(EngineError(engineErrorNS::ENGINE_INTERFACE_ERROR, "EngineButton CreateNewButton Failed"));
	}
	catch (const EngineError &err)
	{
		MessageBox(g_hWndEngine, err.getMessage(), "Error", MB_OK);
	}

	return success;
}

bool EngineEditControl::createEditControl(const char * controlName, DWORD dwStyle, int x, int y, int width, int height, HWND hParent, HMENU hMenu)
{
	bool success = false;

	try
	{
		hWndParent = hParent;
		hWndThis = CreateWindow(TEXT("edit"), controlName, dwStyle, x, y, width, height, hParent, hMenu, GetModuleHandle(NULL), (LPVOID)NULL);

		if (!hWndThis)
		{
			throw(EngineError(engineErrorNS::ENGINE_INTERFACE_ERROR, "EngineWindow CreateButton Failed"));
		}

		success = true;
	}
	catch (const EngineError &err)
	{
		MessageBox(g_hWndEngine, err.getMessage(), "Error", MB_OK);
	}
}
