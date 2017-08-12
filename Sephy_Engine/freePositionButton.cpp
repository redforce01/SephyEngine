#include "stdafx.h"
#include "freePositionButton.h"
#include "objectControlViewer.h"

FreePositionButton::FreePositionButton()
{
	m_pObjectControlViewer = nullptr;
}


FreePositionButton::~FreePositionButton()
{
}

bool FreePositionButton::initialize(Graphics * g, Input * i, int controlID, SystemUIDialog * pDialog, int x, int y, int w, int h, int m)
{
	bool success = false;
	try
	{
		success = SystemUIButton::initButton(g, i, controlID, functionFreePosition, this, pDialog, x, y, w, h, m);

		m_pIcon = new Image;
		m_pIcon->initialize(g, freePositionButtonNS::OFF_IMAGE_WIDTH, freePositionButtonNS::OFF_IMAGE_HEIGHT, 0, IMAGEMANAGER->getTexture(freePositionButtonNS::FILENAME_OFF));
		m_dxFont.initialize(g, freePositionButtonNS::FONT_HEIGHT, false, false, freePositionButtonNS::FONT);
		m_dxFont.setFontColor(freePositionButtonNS::FONT_COLOR);
		SetIcon(m_pIcon);
		m_pIcon->setScale(0.75);
	}
	catch (...)
	{
		MessageBox(g_hWndEngine, "DEBUG Button Initialize Failed", "Error", MB_OK);
	}

	return success;
}

void FreePositionButton::update(float frameTime)
{
	SystemUIButton::update(frameTime);
}

void FreePositionButton::render()
{
	SystemUIButton::render();
}

void FreePositionButton::functionFreePosition(void * obj)
{
	FreePositionButton* pThis = (FreePositionButton*)obj;

	bool flag = pThis->m_pObjectControlViewer->getFreePoisitionMode();
	pThis->m_pObjectControlViewer->setFreePositionMode(!flag);

	if (flag)
	{
		pThis->m_pIcon->setTextureManager(IMAGEMANAGER->getTexture(freePositionButtonNS::FILENAME_ON));
		pThis->m_pIcon->setWidth(freePositionButtonNS::ON_IMAGE_WIDTH);
		pThis->m_pIcon->setHeight(freePositionButtonNS::ON_IMAGE_HEIGHT);
	}
	else
	{
		pThis->m_pIcon->setTextureManager(IMAGEMANAGER->getTexture(freePositionButtonNS::FILENAME_OFF));
		pThis->m_pIcon->setWidth(freePositionButtonNS::OFF_IMAGE_WIDTH);
		pThis->m_pIcon->setHeight(freePositionButtonNS::OFF_IMAGE_HEIGHT);
	}

	pThis->m_pInput->setMouseLButton(false);
}
