#ifndef _ENGINEEDITCONTROL_H
#define _ENGINEEDITCONTROL_H

class EngineEditControl;

#include <string>

class EngineEditControl
{
private:
	std::string buttonName;
	int controlId;
	RECT rcControl;
	DWORD dwStyle;

	HWND hWndParent;
	HWND hWndThis;

public:
	EngineEditControl();
	EngineEditControl(DWORD style);
	~EngineEditControl();

	bool initialize(
		std::string btnName,
		int btnId,
		int x, int y, int width, int height,
		HWND hParent);

	// create New Button
	bool createEditControl(
		const char* controlName,
		DWORD dwStyle,
		int x, int y,
		int width, int height,
		HWND hParent,
		HMENU hMenu);

	int getId() { return controlId; }
	RECT getRect() { return rcControl; }
};

#endif // !_ENGINEEDITCONTROL_H
