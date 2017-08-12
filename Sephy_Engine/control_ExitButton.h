#ifndef _CONTROLEXITBUTTON_H
#define _CONTROLEXITBUTTON_H

class Control_ExitButton;

#include "systemUIButton.h"

namespace exitButtonNS
{
	const std::string NAME = "EXIT";
	const std::string FILENAME = "ExitButton";
	const char FONT[] = "Courier New";  // console font
	const int FONT_HEIGHT = 12;         // height of the font in pixels
	const COLOR_ARGB FONT_COLOR = graphicsNS::WHITE;    // color of console text
	const int IMAGE_WIDTH = 32;
	const int IMAGE_HEIGHT = 32;
}

class Control_ExitButton : public SystemUIButton
{
private:


public:
	Control_ExitButton();
	~Control_ExitButton();

	bool initialize(Graphics* g, Input* i, int controlID, SystemUIDialog* pDialog, int x, int y, int w, int h, int m);
	virtual void update(float frameTime);
	virtual void render();

public:
	// CALLBACK FUNCTION [STATIC]
	static void functionExit(void * obj);
};

#endif // !_CONTROLEXITBUTTON_H
