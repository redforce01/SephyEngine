#include "stdafx.h"
#include "mapTilePageLeftButton.h"
#include "mapTileViewer.h"

MapTilePageLeftButton::MapTilePageLeftButton()
{
}


MapTilePageLeftButton::~MapTilePageLeftButton()
{
}

bool MapTilePageLeftButton::initialize(Graphics * g, Input * i, int controlID, SystemUIDialog * pDialog, int x, int y, int w, int h, int m)
{
	bool success = false;
	try
	{
		success = SystemUIButton::initButton(g, i, controlID, functionLeft, this, pDialog, x, y, w, h, m);

		m_pIcon = new Image;
		m_pIcon->initialize(g, pageLeftButtonNS::IMAGE_WIDTH, pageLeftButtonNS::IMAGE_HEIGHT, 0, IMAGEMANAGER->getTexture(pageLeftButtonNS::FILENAME));
		SetIcon(m_pIcon);
	}
	catch (...)
	{
		MessageBox(g_hWndEngine, "PageLeft Button Initialize Failed", "Error", MB_OK);
	}

	return success;
}

void MapTilePageLeftButton::update(float frameTime)
{
	SystemUIButton::update(frameTime);
}

void MapTilePageLeftButton::render()
{
	SystemUIButton::render();
}

void MapTilePageLeftButton::functionLeft(void * obj)
{
	MapTilePageLeftButton* pThis = (MapTilePageLeftButton*)obj;
	pThis->m_pMapTileViewer->decreasePage();
	pThis->m_pInput->setMouseLButton(false);
}
