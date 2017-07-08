#include "stdafx.h"
#include "makeObjectButton.h"
#include "objectControlViewer.h"

MakeObjectButton::MakeObjectButton()
{
	m_pObjectControlViewer = nullptr;
}


MakeObjectButton::~MakeObjectButton()
{
}

bool MakeObjectButton::initialize(Graphics * g, Input * i, int controlID, SystemUIDialog * pDialog, int x, int y, int w, int h, int m)
{
	bool success = false;
	try
	{
		success = SystemUIButton::initButton(g, i, controlID, functionMakeObject, this, pDialog, x, y, w, h, m);

		m_pIcon = new Image;
		m_pIcon->initialize(g, makeObjectButtonNS::IMAGE_WIDTH, makeObjectButtonNS::IMAGE_HEIGHT, 0, IMAGEMANAGER->getTexture(makeObjectButtonNS::FILENAME));
		m_dxFont.initialize(g, makeObjectButtonNS::FONT_HEIGHT, false, false, makeObjectButtonNS::FONT);
		m_dxFont.setFontColor(makeObjectButtonNS::FONT_COLOR);
		SetIcon(m_pIcon);
	}
	catch (...)
	{
		MessageBox(g_hWndEngine, "DEBUG Button Initialize Failed", "Error", MB_OK);
	}

	return success;
}

void MakeObjectButton::update(float frameTime)
{
	SystemUIButton::update(frameTime);
}

void MakeObjectButton::render()
{
	SystemUIButton::render();
}

void MakeObjectButton::functionMakeObject(void * obj)
{
	MakeObjectButton* pThis = (MakeObjectButton*)obj;
	pThis->m_pObjectControlViewer;
}
