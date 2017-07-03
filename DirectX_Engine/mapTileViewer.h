#ifndef _MAPTILEVIEWER_H
#define _MAPTILEVIEWER_H

class MapTileViewer;

#include "systemUIControl.h"
#include "systemUIDialog.h"
#include "mapTileData.h"
#include "mapTilePageLeftButton.h"
#include "mapTilePageRightButton.h"

namespace mapTileViewerNS
{
	const UINT WIDTH = 400;				// width of treeViewer
	const UINT HEIGHT = WINSIZEY;		// height of treeViewer
	const UINT X = WINSIZEX - WIDTH;	// Viewer location X
	const UINT Y = 0;					// Viewer location Y
	const UINT MARGIN = 4;              // text margin from Viewer edge
	const char FONT[] = "Courier New";  // Viewer font
	const int FONT_HEIGHT = 14;         // height of the font in pixels
	const COLOR_ARGB FONT_COLOR = graphicsNS::WHITE;    // color of console text
	const COLOR_ARGB BACK_COLOR = SETCOLOR_ARGB(192, 26, 32, 44);    // backdrop color

	const std::string TILE_FOLDER = "03_Tile";
	const UINT BASIC_TILE_WIDTH = 128;
	const UINT BASIC_TILE_HEIGHT = 64;
	const UINT VIEWER_PAGE_ITEM_MAX = 36;

	const int LEFT_BUTTON_ID = 100;
	const int RIGHT_BUTTON_ID = 101;
	const UINT PAGE_BUTTON_SIZE = 30;
	const UINT PAGE_BUTTON_MARGIN = 0;
}

class MapSystem;
class MapTileViewer : public SystemUIDialog
{
private:
	int m_nViewPage;
	int m_nMaxPage;
	std::vector<MapTileData*> m_arrObjects;
	MapTileData* m_pSelectData;

	MapSystem* m_pMapSystem;
private:
	// PageButton
	MapTilePageLeftButton* m_pLeftButton;
	MapTilePageRightButton* m_pRightButton;

public:
	MapTileViewer();
	~MapTileViewer();

	virtual bool initialize(Graphics* g, Input* i) override;
	virtual void update(float frameTime) override;
	virtual void render() override;

	// ===================================================
	// Member Functions
	// ===================================================
	void increasePage()
	{
		m_nViewPage++;
		if (m_nViewPage > m_nMaxPage)
			m_nViewPage = m_nMaxPage;
	}
	void decreasePage()
	{
		m_nViewPage--;
		if (m_nViewPage < 0)
			m_nViewPage = 0;
	}

	void setMemoryLinkMapSystem(MapSystem* pMapSystem)
	{
		m_pMapSystem = pMapSystem;
	}

};

#endif // !_MAPTILEVIEWER_H
