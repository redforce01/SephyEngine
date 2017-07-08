#include "stdafx.h"
#include "objectViewButton.h"
#include "mapTileViewer.h"

ObjectViewButton::ObjectViewButton()
{
	m_pMapTileViewer = nullptr;
}


ObjectViewButton::~ObjectViewButton()
{
}

bool ObjectViewButton::initialize(Graphics * g, Input * i, int controlID, SystemUIDialog * pDialog, int x, int y, int w, int h, int m)
{
	bool success = false;
	try
	{
		success = SystemUIButton::initButton(g, i, controlID, functionObjectView, this, pDialog, x, y, w, h, m);

		m_pIcon = new Image;
		m_pIcon->initialize(g, objectViewButtonNS::IMAGE_WIDTH, objectViewButtonNS::IMAGE_HEIGHT, 0, IMAGEMANAGER->getTexture(objectViewButtonNS::FILENAME));
		m_dxFont.initialize(g, objectViewButtonNS::FONT_HEIGHT, false, false, objectViewButtonNS::FONT);
		m_dxFont.setFontColor(objectViewButtonNS::FONT_COLOR);
		SetIcon(m_pIcon);
		SetMessage(objectViewButtonNS::NAME);
	}
	catch (...)
	{
		MessageBox(g_hWndEngine, "DEBUG Button Initialize Failed", "Error", MB_OK);
	}

	return success;
}

void ObjectViewButton::update(float frameTime)
{
	SystemUIButton::update(frameTime);
}

void ObjectViewButton::render()
{
	SystemUIButton::render();
}

void ObjectViewButton::functionObjectView(void * obj)
{
	ObjectViewButton* pThis = (ObjectViewButton*)obj;
	pThis->m_pMapTileViewer->setViewType(MAPTILEVIEWER_VIEW_TYPE::VIEW_MAP_OBJECT);
	pThis->m_pInput->setMouseLButton(false);
}
