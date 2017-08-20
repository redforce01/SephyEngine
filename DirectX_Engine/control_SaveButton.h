#ifndef _CONTROLSAVEBUTTON_H
#define _CONTROLSAVEBUTTON_H

class Control_SaveButton;

#include "systemUIButton.h"

namespace saveButtonNS
{
	const std::string NAME = "SAVE";
	const std::string FILENAME = "SaveButton";
	const char FONT[] = "Courier New";  // console font
	const int FONT_HEIGHT = 10;         // height of the font in pixels
	const COLOR_ARGB FONT_COLOR = graphicsNS::WHITE;    // color of console text
	const int IMAGE_WIDTH = 26;
	const int IMAGE_HEIGHT = 28;
}

class MapSystem;
class Control_SaveButton : public SystemUIButton
{
private:
	MapSystem* m_pMapSystem;
public:
	Control_SaveButton();
	~Control_SaveButton();

	bool initialize(Graphics* g, Input* i, int controlID, SystemUIDialog* pDialog, int x, int y, int w, int h, int m);
	virtual void update(float frameTime);
	virtual void render();

	// MapSystem MemoryLink Connect
	void setMemoryLinkMapSystem(MapSystem* pMapSystem)
	{ m_pMapSystem = pMapSystem; }

public:
	// CALLBACK FUNCTION [STATIC]
	static void functionSave(void * obj);
};

#endif // !_CONTROLSAVEBUTTON_H