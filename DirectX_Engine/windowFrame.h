#pragma once
#include <string>
#include "constants.h"
#include "textDX.h"
#include "graphics.h"
#include "input.h"
#include "game.h"

namespace windowFrameNS
{

}

class WindowFrame : public Game
{
protected:
	Graphics*	graphics;					// graphics system
	Input*		input;						// input system
	float       x, y;						// screen location
	UINT        height;						// window height, calculated in print()
	UINT        width;						// window width
	std::string text;						// window text
	COLOR_ARGB  borderColor;				// border color (a,r,g,b)
	COLOR_ARGB  backColor;					// background color (a,r,g,b)
	bool    initialized;					// true when initialized successfully
	bool    visible;						// true to display
	HWND    hWndChild;						// handle to window
	HWND	hWndParent;
	float   screenRatioX, screenRatioY;

public:
	WindowFrame();
	~WindowFrame();

	bool initialize(Graphics *g, Input *in, HWND hWnd, float startX, float startY, UINT windowWidth, UINT windowHeight, std::string windowName);
	void update();      // must override pure virtual from Game
	void ai();          // "
	void collisions();  // "
	void render();      // "

	bool createMainWindow(HWND hWnd);

	static LRESULT WndProcChild(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);


	// Return visible.
	bool getVisible() { return visible; }

	// Set border color
	void setBorderColor(COLOR_ARGB bc) { borderColor = bc; }

	// Set background color
	void setBackColor(COLOR_ARGB bc) { backColor = bc; }

	// Set visible;
	void setVisible(bool v) { visible = v; }
};

