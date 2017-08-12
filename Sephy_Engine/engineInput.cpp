#include "stdafx.h"
#include "engineInput.h"


EngineInput::EngineInput()
{
	input = new Input;
}


EngineInput::~EngineInput()
{
	SAFE_DELETE(input);
}

LRESULT EngineInput::messageHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (this == NULL) return 0;

	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_KEYDOWN: case WM_SYSKEYDOWN:    // key down
		input->keyDown(wParam);
		return 0;
	case WM_KEYUP: case WM_SYSKEYUP:        // key up
		input->keyUp(wParam);
		return 0;
	case WM_CHAR:                           // character entered
		input->keyIn(wParam);
		return 0;
	case WM_MOUSEMOVE:                      // mouse moved
		input->mouseIn(lParam);
		return 0;
	case WM_INPUT:                          // raw mouse data in
		input->mouseRawIn(lParam);
		return 0;
	case WM_LBUTTONDOWN:                    // left mouse button down
		input->setMouseLButton(true);
		input->mouseIn(lParam);             // mouse position
		return 0;
	case WM_LBUTTONUP:                      // left mouse button up
		input->setMouseLButton(false);
		input->mouseIn(lParam);             // mouse position
		return 0;
	case WM_MBUTTONDOWN:                    // middle mouse button down
		input->setMouseMButton(true);
		input->mouseIn(lParam);             // mouse position
		return 0;
	case WM_MBUTTONUP:                      // middle mouse button up
		input->setMouseMButton(false);
		input->mouseIn(lParam);             // mouse position
		return 0;
	case WM_RBUTTONDOWN:                    // right mouse button down
		input->setMouseRButton(true);
		input->mouseIn(lParam);             // mouse position
		return 0;
	case WM_RBUTTONUP:                      // right mouse button up
		input->setMouseRButton(false);
		input->mouseIn(lParam);             // mouse position
		return 0;
	case WM_XBUTTONDOWN: case WM_XBUTTONUP: // mouse X button down/up
		input->setMouseXButton(wParam);
		input->mouseIn(lParam);             // mouse position
		return 0;
	case WM_DEVICECHANGE:                   // check for controller insert
		input->checkControllers();
		return 0;
	}
	
	return DefWindowProc(hwnd, msg, wParam, lParam);    // let Windows handle it
}
