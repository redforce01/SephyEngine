#include "stdafx.h"
#include "tileViewButton.h"
#include "mapTileViewer.h"

TileViewButton::TileViewButton()
{
	m_pMapTileViewer = nullptr;
}


TileViewButton::~TileViewButton()
{
}

bool TileViewButton::initialize(Graphics * g, Input * i, int controlID, SystemUIDialog * pDialog, int x, int y, int w, int h, int m)
{
	bool success = false;
	try
	{
		success = SystemUIButton::initButton(g, i, controlID, functionTileView, this, pDialog, x, y, w, h, m);

		m_pIcon = new Image;
		m_pIcon->initialize(g, tileViewButtonNS::IMAGE_WIDTH, objectViewButtonNS::IMAGE_HEIGHT, 0, IMAGEMANAGER->getTexture(tileViewButtonNS::FILENAME));
		m_dxFont.initialize(g, tileViewButtonNS::FONT_HEIGHT, false, false, tileViewButtonNS::FONT);
		m_dxFont.setFontColor(tileViewButtonNS::FONT_COLOR);
		SetIcon(m_pIcon);
		SetMessage(tileViewButtonNS::NAME);
	}
	catch (...)
	{
		MessageBox(g_hWndEngine, "DEBUG Button Initialize Failed", "Error", MB_OK);
	}

	return success;
}

void TileViewButton::update(float frameTime)
{
	SystemUIButton::update(frameTime);
}

void TileViewButton::render()
{
	SystemUIButton::render();
}

void TileViewButton::functionTileView(void * obj)
{
	TileViewButton* pThis = (TileViewButton*)obj;
	pThis->m_pMapTileViewer->setViewType(MAPTILEVIEWER_VIEW_TYPE::VIEW_MAP_TILE);
	pThis->m_pInput->setMouseLButton(false);
}
