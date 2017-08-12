#ifndef _MAPTILEVIEWER_H
#define _MAPTILEVIEWER_H

class MapTileViewer;

#include "systemUIControl.h"
#include "systemUIDialog.h"
#include "mapTileData.h"
#include "mapTilePageLeftButton.h"
#include "mapTilePageRightButton.h"
#include "objectViewButton.h"
#include "tileViewButton.h"
#include "mapObjectParser.h"

namespace mapTileViewerNS
{
	const UINT WIDTH = 400;				// width of treeViewer
	const UINT HEIGHT = 300;			// height of treeViewer (g_fScreenHeight - 300)
	const UINT X = WIDTH;				// Viewer location X	(g_fScreenWidth - Width)
	const UINT Y = 0;					// Viewer location Y
	const UINT MARGIN = 4;              // text margin from Viewer edge
	const char FONT[] = "Courier New";  // Viewer font
	const int FONT_HEIGHT = 14;         // height of the font in pixels
	const COLOR_ARGB FONT_COLOR = graphicsNS::WHITE;    // color of console text
	const COLOR_ARGB BACK_COLOR = SETCOLOR_ARGB(192, 26, 32, 44);    // backdrop color

	const std::string TILE_FOLDER = "22_MapTool_Texture_Tile";
	const std::string OBJECT_FOLDER = "23_MapTool_Texture_Object";
	const UINT BASIC_TILE_WIDTH = 128;
	const UINT BASIC_TILE_HEIGHT = 64;
	const UINT VIEWER_PAGE_ITEM_MAX = 31;

	// Each Buttons Would be set Using reverse Pos (Standard Height)
	// ex) PAGE_BUTTON_HEIGHT_POS = 50 : mean -> Dialog.Bottom - 50  (vertical)
	// ex2) PAGE_BUTTON_X = 10 : mean -> Dialog.centerX +- 10 (horizontal) by programmer
	// =====================================
	// PAGE BUTTON NAMESPACE - Start
	const int LEFT_BUTTON_ID = 100;
	const UINT LEFT_BUTTON_X = 10;
	const UINT LEFT_BUTTON_Y = 10;			// Not Using Y Pos
	const int RIGHT_BUTTON_ID = 101;
	const UINT RIGHT_BUTTON_X = 20;
	const UINT RIGHT_BUTTON_Y = 20;			// Not Using Y Pos
	const UINT PAGE_BUTTON_SIZE = 30;
	const UINT PAGE_BUTTON_MARGIN = 0;
	const UINT PAGE_BUTTON_HEIGHT_POS = 50;
	// PAGE BUTTON NAMESPACE - End
	// =====================================

	// Print Page Count
	const std::string PAGE_NUMBER = "Page:";
	const UINT PAGE_TEXT_BOX_POS_X = 20;
	const UINT PAGE_TEXT_BOX_POS_Y = 40;

	// =====================================
	// VIEW BUTTON NAMESPACE - Start
	const UINT VIEW_BUTTON_WIDTH = 40;
	const UINT VIEW_BUTTON_HEIGHT = 40;
	const UINT VIEW_BUTTON_MARGIN = 5;
	const UINT OBJECT_VIEW_BUTTON_ID = 102;
	const UINT OBJECT_VIEW_BUTTON_X = WIDTH - 70;
	const UINT OBJECT_VIEW_BUTTON_Y = HEIGHT + 55;	// (g_fScreenHeight - Height + 70)
	const UINT TILE_VIEW_BUTTON_ID = 103;
	const UINT TILE_VIEW_BUTTON_X = WIDTH - 110;
	const UINT TILE_VIEW_BUTTON_Y = HEIGHT + 55;	// (g_fScreenHeight - Height + 55)
	// VIEW BUTTON NAMESPACE - End
	// =====================================
}

enum class MAPTILEVIEWER_VIEW_TYPE
{
	VIEW_MAP_TILE, VIEW_MAP_OBJECT
};


class ObjectControlViewer;
class MapSystem;
class MapTileViewer : public SystemUIDialog
{
private:
	int m_nTileViewPage;
	int m_nTileViewMaxPage;
	int m_nObjectViewPage;
	int m_nObjectViewMaxPage;

	MapTileData* m_pSelectData;
	RECT m_rcPageTextBox;
	MAPTILEVIEWER_VIEW_TYPE m_viewType;

	bool m_bActive;

	// TILE VIEWER TEXTURE IMAGES
	std::vector<MapTileData*> m_arrTiles;
	std::vector<MapTileData*> m_arrObjects;
private:	// OBJECT DATA PARSER
	MapObjectParser* m_pMapObjectParser;

private:	// Forward Pointer
	// MapSystem Forward Pointer 
	MapSystem* m_pMapSystem;
	ObjectControlViewer* m_pObjectControlViewer;
private:	// BUTTON
	// PageButton
	MapTilePageLeftButton* m_pLeftButton;
	MapTilePageRightButton* m_pRightButton;

	// ViewButton
	ObjectViewButton* m_pObjectViewButton;
	TileViewButton* m_pTileViewButton;
public:
	MapTileViewer();
	~MapTileViewer();

	virtual bool initialize(Graphics* g, Input* i) override;
	virtual void update(float frameTime) override;
	virtual void render() override;

	// ===================================================
	// Member Functions
	// ===================================================
	void recogObjectData();
	void increasePage()
	{
		if (m_viewType == MAPTILEVIEWER_VIEW_TYPE::VIEW_MAP_TILE)
		{
			m_nTileViewPage++;
			if (m_nTileViewPage > m_nTileViewMaxPage)
				m_nTileViewPage = m_nTileViewMaxPage;
		}
		else if (m_viewType == MAPTILEVIEWER_VIEW_TYPE::VIEW_MAP_OBJECT)
		{
			m_nObjectViewPage++;
			if (m_nObjectViewPage > m_nObjectViewMaxPage)
				m_nObjectViewPage = m_nObjectViewMaxPage;
		}
	}
	void decreasePage()
	{
		if (m_viewType == MAPTILEVIEWER_VIEW_TYPE::VIEW_MAP_TILE)
		{
			m_nTileViewPage--;
			if (m_nTileViewPage < 0)
				m_nTileViewPage = 0;
		}
		else if (m_viewType == MAPTILEVIEWER_VIEW_TYPE::VIEW_MAP_OBJECT)
		{
			m_nObjectViewPage--;
			if (m_nObjectViewPage < 0)
				m_nObjectViewPage = 0;
		}
	}

	// ===================================================
	// Getter Functions
	// ===================================================
	MapTileData* getSelectObjectData() const
	{
		return m_pSelectData;
	}

	// ===================================================
	// Setter Functions
	// ===================================================
	void setViewType(MAPTILEVIEWER_VIEW_TYPE type)
	{
		m_viewType = type;
	}
		
	// MemoryLink Functions For Forward Pointer
	void setMemoryLinkMapSystem(MapSystem* pMapSystem)
	{ m_pMapSystem = pMapSystem; }
	void setMemoryLinkObjectControlViewer(ObjectControlViewer* pObjectControlViewer)
	{ m_pObjectControlViewer = pObjectControlViewer; }
};

#endif // !_MAPTILEVIEWER_H
