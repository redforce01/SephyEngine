#ifndef _MAPTILEVIEWER_H
#define _MAPTILEVIEWER_H

class MapTileViewer;

#include "systemUIControl.h"
#include "systemUIDialog.h"

namespace mapTileViewerNS
{
	const UINT WIDTH = 400;				// width of treeViewer
	const UINT HEIGHT = 400;			// height of treeViewer
	const UINT X = WINSIZEX - WIDTH;	// Viewer location X
	const UINT Y = 0;					// Viewer location Y
	const UINT MARGIN = 4;              // text margin from Viewer edge
	const char FONT[] = "Courier New";  // Viewer font
	const int FONT_HEIGHT = 14;         // height of the font in pixels
	const COLOR_ARGB FONT_COLOR = graphicsNS::WHITE;    // color of console text
	const COLOR_ARGB BACK_COLOR = SETCOLOR_ARGB(192, 97, 97, 97);    // backdrop color
}

class MapTileViewer : public SystemUIDialog
{
private:
	std::string m_strName;
	std::string m_strExp;
	std::string m_strSize;
	std::string m_strLocation;
private:


public:
	MapTileViewer();
	~MapTileViewer();

	virtual bool initialize(Graphics* g, Input* i) override;
	virtual void update(float frameTime) override;
	virtual void render() override;
};

#endif // !_MAPTILEVIEWER_H
