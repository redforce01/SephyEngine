#include "stdafx.h"
#include "systemUITitlebar.h"


SystemUITitlebar::SystemUITitlebar()
{
	m_pGraphics = nullptr;
	m_pInput = nullptr;
	m_pFrameIcon = nullptr;
	m_pMinMaxButton = nullptr;
	m_pCloseButton = nullptr;
	m_x = m_y = 0;
	m_width = m_height = 0;
	m_rcBoundingBox = { 0, };
	m_rcTitle = { 0, };
	m_rcMinimizeButton = { 0, };
	m_rcCloseButton = { 0, };
	m_bMinimize = false;
	m_bVisible = true;
}


SystemUITitlebar::~SystemUITitlebar()
{
	SAFE_DELETE(m_pFrameIcon);
	SAFE_DELETE(m_pMinMaxButton);
	SAFE_DELETE(m_pCloseButton);
}

bool SystemUITitlebar::initializeTitlebar(Graphics * g, Input * i, SystemUIDialog * pDialog, std::string title)
{
	bool success = false;
	try
	{
		m_pGraphics = g;
		m_pInput = i;
		m_pDialog = pDialog;
		m_strTitleName = title;
		m_x = m_pDialog->getDialogX();
		m_y = m_pDialog->getDialogY() - systemUITitleBarNS::BASIC_TITLEBAR_HEIGHT;
		m_width = m_pDialog->getDialogWidth();
		m_height = systemUITitleBarNS::BASIC_TITLEBAR_HEIGHT;

		m_rcBoundingBox = RectMake(m_x, m_y, m_width, m_height);
		m_rcTitle = RectMake(m_x + systemUITitleBarNS::TITLE_UI_WIDTH, m_y, m_width - systemUITitleBarNS::TITLE_UI_WIDTH, m_height);
		m_rcMinimizeButton = RectMake(m_x + m_width - (systemUITitleBarNS::BAISC_TITLEBAR_BUTTON_WIDTH * 2), m_y,
			systemUITitleBarNS::BAISC_TITLEBAR_BUTTON_WIDTH, systemUITitleBarNS::BASIC_TITLEBAR_HEIGHT);
		m_rcCloseButton = RectMake(m_x + m_width - systemUITitleBarNS::BAISC_TITLEBAR_BUTTON_WIDTH, m_y,
			systemUITitleBarNS::BAISC_TITLEBAR_BUTTON_WIDTH, systemUITitleBarNS::BASIC_TITLEBAR_HEIGHT);
		
		//m_pFrameIcon = new Image;
		//if (m_pFrameIcon->initialize(g, systemUITitleBarNS::TITLE_UI_WIDTH, systemUITitleBarNS::TITLE_UI_HEIGHT, 0,
		//	IMAGEMANAGER->getTexture(systemUITitleBarNS::UI_IMAGE_NAME)) == false)
		//	throw(engineErrorNS::ENGINE_INTERFACE_ERROR);

		m_pMinMaxButton = new Image;
		if (m_pMinMaxButton->initialize(g, systemUITitleBarNS::MINIMIZE_WIDTH, systemUITitleBarNS::MINIMIZE_HEIGHT, 0,
			IMAGEMANAGER->getTexture(systemUITitleBarNS::MINIMIZE_IMAGE_NAME)) == false)
			throw(engineErrorNS::ENGINE_INTERFACE_ERROR);
		m_pMinMaxButton->setX(m_rcMinimizeButton.left);
		m_pMinMaxButton->setY(m_rcMinimizeButton.top);

		m_pCloseButton = new Image;
		if(m_pCloseButton->initialize(g, systemUITitleBarNS::CLOSE_WIDTH, systemUITitleBarNS::CLOSE_HEIGHT, 0,
			IMAGEMANAGER->getTexture(systemUITitleBarNS::CLOSE_IMAGE_NAME)) == false)
			throw(engineErrorNS::ENGINE_INTERFACE_ERROR);
		m_pCloseButton->setX(m_rcCloseButton.left);
		m_pCloseButton->setY(m_rcCloseButton.top);

		success = true;
	}
	catch (...)
	{
		MessageBox(g_hWndEngine, "systemUITitleBar Initialized Failed", "Error", MB_OK);
	}

	return success;
}

void SystemUITitlebar::update(float frameTime)
{
	if (m_pInput->getMouseLButton())
	{
		if (PtInRect(&m_rcMinimizeButton, m_pInput->getMousePt()))
		{
			m_pDialog->setShowHide();
		}

		if (PtInRect(&m_rcCloseButton, m_pInput->getMousePt()))
		{
			//m_pDialog->setVisible(false);
		}
	}
}

void SystemUITitlebar::render()
{
	m_pGraphics->spriteBegin();

	m_pMinMaxButton->draw();
	m_pCloseButton->draw();

	m_pGraphics->spriteEnd();
}

void SystemUITitlebar::setMinimize()
{
	m_bMinimize = m_bMinimize;
	if (m_bMinimize)
	{
		
	}
}
