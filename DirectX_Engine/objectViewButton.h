#ifndef _OBJECTVIEWBUTTON_H
#define _OBJECTVIEWBUTTON_H

class ObjectViewButton;

#include "systemUIButton.h"

namespace objectViewButtonNS
{
	const std::string NAME = "OBJECT";
	const std::string FILENAME = "ObjectButton";
	const char FONT[] = "Courier New";  // console font
	const int FONT_HEIGHT = 12;         // height of the font in pixels
	const COLOR_ARGB FONT_COLOR = graphicsNS::WHITE;    // color of console text
	const int IMAGE_WIDTH = 32;
	const int IMAGE_HEIGHT = 26;
}

class MapTileViewer;
class ObjectViewButton : public SystemUIButton
{
private:
	MapTileViewer* m_pMapTileViewer;

public:
	ObjectViewButton();
	~ObjectViewButton();

	virtual bool initialize(Graphics* g, Input* i, int controlID, SystemUIDialog* pDialog, int x, int y, int w, int h, int m) override;
	virtual void update(float frameTime) override;
	virtual void render() override;

	void setMemoryLinkMapTileViewer(MapTileViewer* pMapTileViewer)
	{ m_pMapTileViewer = pMapTileViewer; }
public:
	// CALLBACK FUNCTION [STATIC]
	static void functionObjectView(void * obj);
};


#endif // !_OBJECTVIEWBUTTON_H
