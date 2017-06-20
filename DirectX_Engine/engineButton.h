#ifndef _ENGINEBUTTON_H
#define _ENGINEBUTTON_H
#define WIN32_LEAN_AND_MEAN

class engineButton;

#include <string>

class EngineButton
{
protected:
	std::string buttonName;
	int controlId;
	RECT rcButton;

	HWND hWndParent;
	HWND hWndThis;

public:
	EngineButton();
	~EngineButton();

	bool initialize(
		std::string btnName,
		int btnId,		
		int x, int y, int width, int height,
		HWND hParent);

	// create New Button
	bool createNewButton(
		const char* buttonName,
		DWORD dwStyle,
		int x, int y,
		int width, int height,
		HWND hParent,
		HMENU hMenu);

	int getId() { return controlId; }
	RECT getRect() { return rcButton; }
};

#endif // !_ENGINEBUTTON_H
