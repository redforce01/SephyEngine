#ifndef _TILEVIEWBUTTON_H
#define _TILEVIEWBUTTON_H

class TileViewButton;

#include "systemUIButton.h"

namespace tileViewButtonNS
{
	const std::string NAME = "TILE";
	const std::string FILENAME = "TileButton";
	const char FONT[] = "Courier New";  // console font
	const int FONT_HEIGHT = 12;         // height of the font in pixels
	const COLOR_ARGB FONT_COLOR = graphicsNS::WHITE;    // color of console text
	const int IMAGE_WIDTH = 32;
	const int IMAGE_HEIGHT = 32;
}

class MapTileViewer;
class TileViewButton : public SystemUIButton
{
private:
	MapTileViewer* m_pMapTileViewer;

public:
	TileViewButton();
	~TileViewButton();

	virtual bool initialize(Graphics* g, Input* i, int controlID, SystemUIDialog* pDialog, int x, int y, int w, int h, int m) override;
	virtual void update(float frameTime) override;
	virtual void render() override;
	
	void setMemoryLinkMapTileViewer(MapTileViewer* pMapTileViewer)
	{ m_pMapTileViewer = pMapTileViewer; }

public:
	// CALLBACK FUNCTION [STATIC]
	static void functionTileView(void * obj);
};

#endif // !_TILEVIEWBUTTON_H
