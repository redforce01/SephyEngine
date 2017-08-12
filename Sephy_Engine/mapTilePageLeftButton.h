#ifndef _MAPTILEPAGELEFTBUTTON_H
#define _MAPTILEPAGELEFTBUTTON_H

class MapTilePageLeftButton;

#include "systemUIButton.h"

namespace pageLeftButtonNS
{
	const std::string NAME = "LEFT";
	const std::string FILENAME = "PageLeftButton";
	const char FONT[] = "Courier New";  // console font
	const int FONT_HEIGHT = 10;         // height of the font in pixels
	const COLOR_ARGB FONT_COLOR = graphicsNS::WHITE;    // color of console text
	const int IMAGE_WIDTH = 22;
	const int IMAGE_HEIGHT = 20;
}

class MapTileViewer;
class MapTilePageLeftButton : public SystemUIButton
{
private:
	MapTileViewer* m_pMapTileViewer;

public:
	MapTilePageLeftButton();
	~MapTilePageLeftButton();

	bool initialize(Graphics* g, Input* i, int controlID, SystemUIDialog* pDialog, int x, int y, int w, int h, int m);
	virtual void update(float frameTime) override;
	virtual void render() override;

	// Memory Link Point Set
	void setMemoryLinkMapTileViewer(MapTileViewer* pMapTileViewer)
	{ m_pMapTileViewer = pMapTileViewer; }
public:
	// CALLBACK FUNCTION [STATIC]
	static void functionLeft(void * obj);
};

#endif // !_MAPTILEPAGELEFTBUTTON_H
