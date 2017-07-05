#include "stdafx.h"
#include "mapTileViewer.h"
#include "mapSystem.h"


MapTileViewer::MapTileViewer()
{
	fontColor = mapTileViewerNS::FONT_COLOR;
	backColor = mapTileViewerNS::BACK_COLOR;
	m_nViewPage = 0;
	m_nMaxPage = 0;
	m_pSelectData = nullptr;
	m_pMapSystem = nullptr;
}


MapTileViewer::~MapTileViewer()
{
	for (auto iter : m_arrObjects)
	{
		SAFE_DELETE(iter);
	}
	m_arrObjects.clear();

	SAFE_DELETE(m_pLeftButton);
	SAFE_DELETE(m_pRightButton);
}

bool MapTileViewer::initialize(Graphics * g, Input * i)
{
	bool success = false;
	try
	{
		success = SystemUIDialog::initializeDialog(g, i, mapTileViewerNS::X, mapTileViewerNS::Y, mapTileViewerNS::WIDTH, mapTileViewerNS::HEIGHT, mapTileViewerNS::MARGIN);
		if (success == false)
			throw("SystemUIDialog initialized Failed");

		auto arrImages = FILEMANAGER->getFileListInFolder(mapTileViewerNS::TILE_FOLDER);

		int startX, startY;
		startX = startY = 0;

		startX = this->getDialogX() + this->getDialogMargin();
		startY = this->getDialogY() + this->getDialogMargin();

		int arrCount = 0;
		for (auto iter : *arrImages)
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
			m_arrObjects.emplace_back(newData);

			if (arrCount % mapTileViewerNS::VIEWER_PAGE_ITEM_MAX == 0 && arrCount != 0)
			{
				startX = this->getDialogX() + this->getDialogMargin();
				startY = this->getDialogY() + this->getDialogMargin();
			}

			if (arrCount >= mapTileViewerNS::VIEWER_PAGE_ITEM_MAX)
			{
				m_nMaxPage++;
				arrCount = 0;
			}

		}

		int halfWidth = this->getDialogWidth() / 2;
		m_pLeftButton = new MapTilePageLeftButton;
		m_pLeftButton->initialize(g, i, mapTileViewerNS::LEFT_BUTTON_ID, this,
			halfWidth - mapTileViewerNS::PAGE_BUTTON_SIZE,
			WINSIZEY - 200,
			mapTileViewerNS::PAGE_BUTTON_SIZE, mapTileViewerNS::PAGE_BUTTON_SIZE,
			mapTileViewerNS::MARGIN);
		m_pLeftButton->setMemoryLinkMapTileViewer(this);

		m_pRightButton = new MapTilePageRightButton;
		m_pRightButton->initialize(g, i, mapTileViewerNS::RIGHT_BUTTON_ID, this,
			halfWidth + mapTileViewerNS::PAGE_BUTTON_SIZE,
			WINSIZEY - 200,
			mapTileViewerNS::PAGE_BUTTON_SIZE, mapTileViewerNS::PAGE_BUTTON_SIZE,
			mapTileViewerNS::MARGIN);
		m_pRightButton->setMemoryLinkMapTileViewer(this);

	}
	catch (...)
	{
		MessageBox(g_hWndEngine, "MapTileViewer Initialized Failed", "Error", MB_OK);
	}

	return success;
}

void MapTileViewer::update(float frameTime)
{
	SystemUIDialog::update(frameTime);

	if (getMouseOver() == false)
		return;

	if (m_pInput->getMouseLButton())
	{
		int arrCount = 0;
		int pageItemStart = mapTileViewerNS::VIEWER_PAGE_ITEM_MAX * m_nViewPage;
		int pageItemEnd = mapTileViewerNS::VIEWER_PAGE_ITEM_MAX * (m_nViewPage + 1);

		for (auto iter : m_arrObjects)
		{
			if (arrCount >= pageItemStart && arrCount < pageItemEnd)
			{
				if (PtInRect(&iter->getTileDataRECT(), m_pInput->getMousePt()))
				{
					iter->setSelected(true);
					m_pSelectData = iter;
					m_pMapSystem->setMapTileData(m_pSelectData);
					m_pInput->setMouseLButton(false);
				}
				else
					iter->setSelected(false);
			}
			arrCount++;
		}
	}
	
	m_pLeftButton->update(frameTime);
	m_pRightButton->update(frameTime);
}

void MapTileViewer::render()
{
	if (m_bVisible == false)
		return;

	SystemUIDialog::render();
	
	int arrCount = 0;
	int pageItemStart = mapTileViewerNS::VIEWER_PAGE_ITEM_MAX * m_nViewPage;
	int pageItemEnd = mapTileViewerNS::VIEWER_PAGE_ITEM_MAX * (m_nViewPage + 1);
	
	for (auto iter : m_arrObjects)
	{
		if(arrCount >= pageItemStart && arrCount < pageItemEnd)
			iter->draw();
		arrCount++;
	}

	m_pLeftButton->render();
	m_pRightButton->render();
}
