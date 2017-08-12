#ifndef _FREEPOSITIONBUTTON_H
#define _FREEPOSITIONBUTTON_H

class FreePositionButton;

#include "systemUIButton.h"

namespace freePositionButtonNS
{
	const std::string NAME = "FREE";
	const std::string FILENAME_ON = "FreePositionOn";
	const std::string FILENAME_OFF = "FreePositionOff";
	const char FONT[] = "Courier New";  // console font
	const int FONT_HEIGHT = 10;         // height of the font in pixels
	const COLOR_ARGB FONT_COLOR = graphicsNS::WHITE;    // color of console text
	const UINT ON_IMAGE_WIDTH = 32;
	const UINT ON_IMAGE_HEIGHT = 32;
	const UINT OFF_IMAGE_WIDTH = 24;
	const UINT OFF_IMAGE_HEIGHT = 32;

}

class ObjectControlViewer;
class FreePositionButton : public SystemUIButton
{
private:
	ObjectControlViewer* m_pObjectControlViewer;

public:
	FreePositionButton();
	~FreePositionButton();

	virtual bool initialize(Graphics* g, Input* i, int controlID, SystemUIDialog* pDialog, int x, int y, int w, int h, int m) override;
	virtual void update(float frameTime) override;
	virtual void render() override;

	// ObjectControlViewer Pointer MemoryLink Setup 
	void setMemoryLinkObjectControlViewer(ObjectControlViewer* pObjectControlViewer)
	{ m_pObjectControlViewer = pObjectControlViewer; }
public:
	// CALLBACK FUNCTION [STATIC]
	static void functionFreePosition(void * obj);
};

#endif // !_FREEPOSITIONBUTTON_H
