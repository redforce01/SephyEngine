#include "stdafx.h"
#include "mapTilePageRightButton.h"
#include "mapTileViewer.h"

MapTilePageRightButton::MapTilePageRightButton()
{
}


MapTilePageRightButton::~MapTilePageRightButton()
{
}

bool MapTilePageRightButton::initialize(Graphics * g, Input * i, int controlID, SystemUIDialog * pDialog, int x, int y, int w, int h, int m)
{
	bool success = false;
	try
	{
		success = SystemUIButton::initButton(g, i, controlID, functionRight, this, pDialog, x, y, w, h, m);

		m_pIcon = new Image;
		m_pIcon->initialize(g, pageRightButtonNS::IMAGE_WIDTH, pageRightButtonNS::IMAGE_HEIGHT, 0, IMAGEMANAGER->getTexture(pageRightButtonNS::FILENAME));
		SetIcon(m_pIcon);
	}
	catch (...)
	{
		MessageBox(g_hWndEngine, "PageRight Button Initialize Failed", "Error", MB_OK);
	}

	return success;
}

void MapTilePageRightButton::update(float frameTime)
{
	SystemUIButton::update(frameTime);
}

void MapTilePageRightButton::render()
{
	SystemUIButton::render();
}

void MapTilePageRightButton::functionRight(void * obj)
{
	MapTilePageRightButton* pThis = (MapTilePageRightButton*)obj;
	pThis->m_pMapTileViewer->increasePage();
	pThis->m_pInput->setMouseLButton(false);
}
