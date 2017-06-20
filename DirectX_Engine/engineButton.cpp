#include "stdafx.h"
#include "engineButton.h"

namespace engineButtonNS
{
	constexpr DWORD dwStyle = WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON;
	constexpr char* className = "Engine_Button";
	constexpr char* propName = "Button";	
}

EngineButton::EngineButton()
{
	hWndParent = nullptr;
	hWndThis = nullptr;
	controlId = 0;
}


EngineButton::~EngineButton()
{
}

bool EngineButton::initialize(
	std::string btnName,
	int btnId,
	int x, int y, int width, int height,
	HWND hParent)
{
	bool success = false;
	try
	{
		buttonName = btnName;
		controlId = btnId;
		rcButton = { x, y,width, height };

		success = createNewButton(btnName.c_str(), engineButtonNS::dwStyle, x, y, width, height, hParent, (HMENU)controlId);
		if(!success)
			throw(EngineError(engineErrorNS::ENGINE_INTERFACE_ERROR, "EngineButton CreateNewButton Failed"));
	}
	catch (const EngineError &err)
	{
		MessageBox(g_hWndEngine, err.getMessage(), "Error", MB_OK);
	}

	return success;
}

bool EngineButton::createNewButton(
	const char* buttonName,
	DWORD dwStyle,
	int x, int y,
	int width, int height,
	HWND hParent,
	HMENU hMenu)
{
	bool success = false;

	try
	{
		hWndParent = hParent;
		hWndThis = CreateWindow(TEXT("button"), buttonName, dwStyle, x, y, width, height, hParent, hMenu, GetModuleHandle(NULL), (LPVOID)NULL);

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

	return success;
}