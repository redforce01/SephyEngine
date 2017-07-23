#include "stdafx.h"
#include "mapTileViewer.h"
#include "mapSystem.h"
#include "objectControlViewer.h"


MapTileViewer::MapTileViewer()
{
	fontColor = mapTileViewerNS::FONT_COLOR;
	backColor = mapTileViewerNS::BACK_COLOR;

	m_nTileViewPage			= 0;
	m_nTileViewMaxPage		= 0;
	m_nObjectViewPage		= 0;
	m_nObjectViewMaxPage	= 0;
	m_pSelectData			= nullptr;
	m_pMapSystem			= nullptr;
	m_pObjectControlViewer	= nullptr;
	m_pMapObjectParser		= nullptr;
	m_bActive				= false;
	m_viewType = MAPTILEVIEWER_VIEW_TYPE::VIEW_MAP_TILE;
}


MapTileViewer::~MapTileViewer()
{
	for (auto iter : m_arrTiles)
	{
		SAFE_DELETE(iter);
	}
	m_arrTiles.clear();
	for (auto iter : m_arrObjects)
	{
		SAFE_DELETE(iter);
	}
	m_arrObjects.clear();

	SAFE_DELETE(m_pLeftButton);
	SAFE_DELETE(m_pRightButton);
	SAFE_DELETE(m_pObjectViewButton);
	SAFE_DELETE(m_pTileViewButton);
	SAFE_DELETE(m_pMapObjectParser);
	SAFE_DELETE(m_pSelectData);
}

bool MapTileViewer::initialize(Graphics * g, Input * i)
{
	bool success = false;
	try
	{
		success = SystemUIDialog::initializeDialog(g, i,
			g_fScreenWidth - mapTileViewerNS::X,
			mapTileViewerNS::Y,
			mapTileViewerNS::WIDTH,
			g_fScreenHeight - mapTileViewerNS::HEIGHT,
			mapTileViewerNS::MARGIN);

		if (success == false)
			throw("SystemUIDialog initialized Failed");

		success = m_dxFont.initialize(g, mapTileViewerNS::FONT_HEIGHT, false, false, mapTileViewerNS::FONT);
		if (success == false)
			throw("MapTileViewer DxFont initialized Failed");
		m_rcPageTextBox = RectMake(g_fScreenWidth - mapTileViewerNS::X + mapTileViewerNS::PAGE_TEXT_BOX_POS_X,
			g_fScreenHeight - mapTileViewerNS::HEIGHT - mapTileViewerNS::PAGE_TEXT_BOX_POS_Y,
			mapTileViewerNS::WIDTH - (mapTileViewerNS::MARGIN * 2), mapTileViewerNS::FONT_HEIGHT);
		
		// ===========================================
		// Initialize TILE Images For Tile View - Start
		auto arrTileImages = FILEMANAGER->getFileListInFolder(mapTileViewerNS::TILE_FOLDER);

		int startX, startY;
		startX = startY = 0;

		startX = this->getDialogX() + this->getDialogMargin();
		startY = this->getDialogY() + this->getDialogMargin();

		int arrCount = 0;
		for (auto iter : *arrTileImages)
		{
			MapTileData* newData = new MapTileData;
			newData->initialize(g, iter->fileName, startX, startY);
			startX += mapTileViewerNS::BASIC_TILE_WIDTH;
			if (arrCount % 3 == 0 && arrCount != 0)
			{
				startX = this->getDialogX() + this->getDialogMargin();
				startY += mapTileViewerNS::BASIC_TILE_HEIGHT;
			}

			arrCount++;
			m_arrTiles.emplace_back(newData);

			if (arrCount % mapTileViewerNS::VIEWER_PAGE_ITEM_MAX == 0 && arrCount != 0)
			{
				startX = this->getDialogX() + this->getDialogMargin();
				startY = this->getDialogY() + this->getDialogMargin();
			}

			if (arrCount >= mapTileViewerNS::VIEWER_PAGE_ITEM_MAX)
			{
				m_nTileViewMaxPage++;
				arrCount = 0;
			}
		}
		// Initialize Images For Tile View - End
		// ===========================================

		// ===========================================
		// MAP OBJECT PARSER - LOAD OBJECT DATA
		m_pMapObjectParser = new MapObjectParser;
		auto vObjectData = m_pMapObjectParser->loadObjectData();

		// ===========================================
		// Initialize OBJECT Images For Tile View - Start
		auto arrObjectImages = FILEMANAGER->getFileListInFolder(mapTileViewerNS::OBJECT_FOLDER);
		startX = startY = 0;

		startX = this->getDialogX() + this->getDialogMargin();
		startY = this->getDialogY() + this->getDialogMargin();

		arrCount = 0;
		for (auto iter : *arrObjectImages)
		{
			MapTileData* newData = new MapTileData;
			newData->initialize(g, iter->fileName, startX, startY);
			newData->setObjectable(true);
			newData->setScale(0.5);
			startX += mapTileViewerNS::BASIC_TILE_WIDTH;
			if (arrCount % 3 == 0 && arrCount != 0)
			{
				startX = this->getDialogX() + this->getDialogMargin();
				startY += mapTileViewerNS::BASIC_TILE_HEIGHT;
			}

			arrCount++;
			m_arrObjects.emplace_back(newData);

			if (arrCount % mapTileViewerNS::VIEWER_PAGE_ITEM_MAX == 0 && arrCount != 0)
			{
				startX = this->getDialogX() + this->getDialogMargin();
				startY = this->getDialogY() + this->getDialogMargin();
			}

			if (arrCount >= mapTileViewerNS::VIEWER_PAGE_ITEM_MAX)
			{
				m_nObjectViewMaxPage++;
				arrCount = 0;
			}
		}
		// Initialize Images For OBJECT View - End
		// ===========================================

		int halfWidth = this->getDialogWidth() / 2;
		int dialogBottom = this->getDialogRECT().bottom;
		int dialogRight = this->getDialogRECT().right;

		m_pLeftButton = new MapTilePageLeftButton;
		m_pLeftButton->initialize(g, i, mapTileViewerNS::LEFT_BUTTON_ID, this,
			halfWidth - (mapTileViewerNS::PAGE_BUTTON_SIZE * 2),
			dialogBottom - mapTileViewerNS::PAGE_BUTTON_HEIGHT_POS,
			mapTileViewerNS::PAGE_BUTTON_SIZE, mapTileViewerNS::PAGE_BUTTON_SIZE,
			mapTileViewerNS::MARGIN);
		m_pLeftButton->setMemoryLinkMapTileViewer(this);

		m_pRightButton = new MapTilePageRightButton;
		m_pRightButton->initialize(g, i, mapTileViewerNS::RIGHT_BUTTON_ID, this,
			halfWidth + mapTileViewerNS::PAGE_BUTTON_SIZE,
			dialogBottom - mapTileViewerNS::PAGE_BUTTON_HEIGHT_POS,
			mapTileViewerNS::PAGE_BUTTON_SIZE, mapTileViewerNS::PAGE_BUTTON_SIZE,
			mapTileViewerNS::MARGIN);
		m_pRightButton->setMemoryLinkMapTileViewer(this);

		m_pObjectViewButton = new ObjectViewButton;
		m_pObjectViewButton->initialize(g, i, mapTileViewerNS::OBJECT_VIEW_BUTTON_ID, this,
			mapTileViewerNS::OBJECT_VIEW_BUTTON_X,
			g_fScreenHeight - mapTileViewerNS::OBJECT_VIEW_BUTTON_Y,
			mapTileViewerNS::VIEW_BUTTON_WIDTH, mapTileViewerNS::VIEW_BUTTON_HEIGHT,
			mapTileViewerNS::VIEW_BUTTON_MARGIN);
		m_pObjectViewButton->setMemoryLinkMapTileViewer(this);

		m_pTileViewButton = new TileViewButton;
		m_pTileViewButton->initialize(g, i, mapTileViewerNS::TILE_VIEW_BUTTON_ID, this,
			mapTileViewerNS::TILE_VIEW_BUTTON_X,
			g_fScreenHeight - mapTileViewerNS::TILE_VIEW_BUTTON_Y,
			mapTileViewerNS::VIEW_BUTTON_WIDTH, mapTileViewerNS::VIEW_BUTTON_HEIGHT,
			mapTileViewerNS::VIEW_BUTTON_MARGIN);
		m_pTileViewButton->setMemoryLinkMapTileViewer(this);
	}
	catch (...)
	{
		MessageBox(g_hWndEngine, "MapTileViewer Initialized Failed", "Error", MB_OK);
	}

	return success;
}

void MapTileViewer::update(float frameTime)
{
	if (getVisible() == false)
		return;

	SystemUIDialog::update(frameTime);

	if (getMouseOver() == false)
		return;

	if (m_pInput->getMouseLButton())
	{
		if (m_viewType == MAPTILEVIEWER_VIEW_TYPE::VIEW_MAP_TILE)
		{
			int arrCount = 0;
			int pageItemStart = mapTileViewerNS::VIEWER_PAGE_ITEM_MAX * m_nTileViewPage;
			int pageItemEnd = mapTileViewerNS::VIEWER_PAGE_ITEM_MAX * (m_nTileViewPage + 1);

			for (auto iter : m_arrTiles)
			{
				if (arrCount >= pageItemStart && arrCount < pageItemEnd)
				{
					if (PtInRect(&iter->getTileDataRECT(), m_pInput->getMousePt()))
					{
						iter->setSelected(true);
						m_pSelectData = iter;
						m_pSelectData->setObjectable(false);
						m_pMapSystem->setMapTileData(m_pSelectData);
						m_pObjectControlViewer->setSelectObjectData(m_pSelectData);
						m_pInput->setMouseLButton(false);
					}
					else
						iter->setSelected(false);
				}
				arrCount++;
			}
		}
		else if (m_viewType == MAPTILEVIEWER_VIEW_TYPE::VIEW_MAP_OBJECT)
		{
			int arrCount = 0;
			int pageItemStart = mapTileViewerNS::VIEWER_PAGE_ITEM_MAX * m_nObjectViewPage;
			int pageItemEnd = mapTileViewerNS::VIEWER_PAGE_ITEM_MAX * (m_nObjectViewPage + 1);

			for (auto iter : m_arrObjects)
			{
				if (arrCount >= pageItemStart && arrCount < pageItemEnd)
				{
					if (PtInRect(&iter->getTileDataRECT(), m_pInput->getMousePt()))
					{
						iter->setSelected(true);
						//m_pSelectData = iter;

						if (m_pSelectData)
						{
							ZeroMemory(&m_pSelectData, sizeof(m_pSelectData));
							SAFE_DELETE(m_pSelectData);
						}
						
						m_pSelectData = new MapTileData;
						m_pSelectData->initialize(m_pGraphics, iter->getTextureName(), 0, 0);
						m_pSelectData->setObjectable(true);

						m_pMapSystem->setMapTileData(m_pSelectData);
						m_pObjectControlViewer->setSelectObjectData(m_pSelectData);
						m_pInput->setMouseLButton(false);
					}
					else
						iter->setSelected(false);
				}
				arrCount++;
			}
		}
	}
	
	m_pLeftButton->update(frameTime);
	m_pRightButton->update(frameTime);
	m_pObjectViewButton->update(frameTime);
	m_pTileViewButton->update(frameTime);
}

void MapTileViewer::render()
{
	if (m_bVisible == false)
		return;

	SystemUIDialog::render();
	
	
	if (m_viewType == MAPTILEVIEWER_VIEW_TYPE::VIEW_MAP_TILE)
	{
		int arrCount = 0;
		int pageItemStart = mapTileViewerNS::VIEWER_PAGE_ITEM_MAX * m_nTileViewPage;
		int pageItemEnd = mapTileViewerNS::VIEWER_PAGE_ITEM_MAX * (m_nTileViewPage + 1);

		for (auto iter : m_arrTiles)
		{
			if(arrCount >= pageItemStart && arrCount < pageItemEnd)
				iter->draw();
			arrCount++;
		}
	}
	else if (m_viewType == MAPTILEVIEWER_VIEW_TYPE::VIEW_MAP_OBJECT)
	{
		int arrCount = 0;
		int pageItemStart = mapTileViewerNS::VIEWER_PAGE_ITEM_MAX * m_nObjectViewPage;
		int pageItemEnd = mapTileViewerNS::VIEWER_PAGE_ITEM_MAX * (m_nObjectViewPage + 1);

		for (auto iter : m_arrObjects)
		{
			if (arrCount >= pageItemStart && arrCount < pageItemEnd)
				iter->draw();
			arrCount++;
		}
	}

	// Button Render
	m_pLeftButton->render();
	m_pRightButton->render();
	m_pObjectViewButton->render();
	m_pTileViewButton->render();

	// Page Number Draw
	m_pGraphics->spriteBegin();

	if (m_viewType == MAPTILEVIEWER_VIEW_TYPE::VIEW_MAP_TILE)
	{
		std::string strPage = mapTileViewerNS::PAGE_NUMBER;
		strPage += std::to_string(m_nTileViewPage);
		strPage += " /";
		strPage += std::to_string(m_nTileViewMaxPage);
		m_dxFont.print(strPage, m_rcPageTextBox, DT_LEFT);
	}
	else if (m_viewType == MAPTILEVIEWER_VIEW_TYPE::VIEW_MAP_OBJECT)
	{
		std::string strPage = mapTileViewerNS::PAGE_NUMBER;
		strPage += std::to_string(m_nObjectViewPage);
		strPage += " /";
		strPage += std::to_string(m_nObjectViewMaxPage);
		m_dxFont.print(strPage, m_rcPageTextBox, DT_LEFT);
	}
	
	m_pGraphics->spriteEnd();

}

void MapTileViewer::recogObjectData()
{
}
