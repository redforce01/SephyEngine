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
	const UINT HEIGHT = WINSIZEY - 300;	// height of treeViewer
	const UINT X = WINSIZEX - WIDTH;	// Viewer location X
	const UINT Y = 0;					// Viewer location Y
	const UINT MARGIN = 4;              // text margin from Viewer edge
	const char FONT[] = "Courier New";  // Viewer font
	const int FONT_HEIGHT = 14;         // height of the font in pixels
	const COLOR_ARGB FONT_COLOR = graphicsNS::WHITE;    // color of console text
	const COLOR_ARGB BACK_COLOR = SETCOLOR_ARGB(192, 26, 32, 44);    // backdrop color

	const std::string TILE_FOLDER = "22_Tile";
	const UINT BASIC_TILE_WIDTH = 128;
	const UINT BASIC_TILE_HEIGHT = 64;
	const UINT VIEWER_PAGE_ITEM_MAX = 31;

	const int LEFT_BUTTON_ID = 100;
	const UINT LEFT_BUTTON_X = 10;
	const UINT LEFT_BUTTON_Y = 10;

	const int RIGHT_BUTTON_ID = 101;
	const UINT RIGHT_BUTTON_X = 20;
	const UINT RIGHT_BUTTON_Y = 20;
	const UINT PAGE_BUTTON_SIZE = 30;
	const UINT PAGE_BUTTON_MARGIN = 0;
	const UINT PAGE_BUTTON_HEIGHT_POS = 50;

	const std::string PAGE_NUMBER = "Page:";
	const UINT PAGE_TEXT_BOX_POS_X = 20;
	const UINT PAGE_TEXT_BOX_POS_Y = 40;
}

class ObjectControlViewer;
class MapSystem;
class MapTileViewer : public SystemUIDialog
{
private:
	int m_nViewPage;
	int m_nMaxPage;
	std::vector<MapTileData*> m_arrObjects;
	MapTileData* m_pSelectData;
	RECT m_rcPageTextBox;

	// MapSystem Forward Pointer 
	MapSystem* m_pMapSystem;
	ObjectControlViewer* m_pObjectControlViewer;
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

	// ===================================================
	// Getter Functions
	// ===================================================
	MapTileData* getSelectObjectData() const
	{
		return m_pSelectData;
	}
	
	// MemoryLink Functions For Forward Pointer
	void setMemoryLinkMapSystem(MapSystem* pMapSystem)
	{ m_pMapSystem = pMapSystem; }
	void setMemoryLinkObjectControlViewer(ObjectControlViewer* pObjectControlViewer)
	{ m_pObjectControlViewer = pObjectControlViewer; }
};

#endif // !_MAPTILEVIEWER_H
