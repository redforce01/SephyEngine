#ifndef _ENGINEINPUT_H
#define _ENGINEINPUT_H
#define WIN32_LEAN_AND_MEAN

class EngineInput;

#include "input.h"

class EngineInput
{
protected:
	Input* input;

public:
	EngineInput();
	~EngineInput();

	LRESULT messageHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
};

#endif // !_ENGINEINPUT_H
