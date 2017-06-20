#ifndef _ENGINEBOOT_H
#define _ENGINEBOOT_H

class EngineBoot;

#include "engineWindow.h"
#include "engineINISetting.h"


class EngineBoot : public EngineWindow
{
private:
	EngineINISetting engineSetting;

public:
	EngineBoot();
	~EngineBoot();

	void bootStart();

	virtual bool initialize(EngineInput * input, HWND hParent, HMENU hMenu, int startX, int startY, int width, int height) override;

	// Normal WndProc
	// default setting windows are Using this proc
	virtual LRESULT WndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam) override;
};

#endif // !_ENGINEBOOT_H
