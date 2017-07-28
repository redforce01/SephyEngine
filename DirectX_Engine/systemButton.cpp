#include "stdafx.h"
#include "systemButton.h"


SystemButton::SystemButton()
{
	m_pGraphics			= nullptr;
	m_pInput			= nullptr;
	m_x					= 0.f;
	m_y					= 0.f;
	m_width				= 0.f;
	m_height			= 0.f;
	m_rcButton			= { 0, };
	m_bUseKey			= false;
	m_bInitialized		= false;
	m_bActive			= false;
	m_enButtonState		= SYSTEM_UI_BUTTON::BUTTON_STATE_DEACTIVE;
}


SystemButton::~SystemButton()
{
}

bool SystemButton::initialize(Graphics * g, Input * i, std::string imageName, bool bUseKey)
{
	bool success = false;
	try
	{		
		m_pGraphics = g;
		m_pInput = i;
		m_strButtonKey = imageName;
		m_bUseKey = bUseKey;

		if (m_bUseKey)
		{
			m_strButtonUpKey = m_strButtonKey + systemButtonNS::FRAME_UP_KEY;
			m_strButtonDownKey = m_strButtonKey + systemButtonNS::FRAME_DOWN_KEY;
			m_strButtonOverKey = m_strButtonKey + systemButtonNS::FRAME_OVERLAB_KEY;
			m_strButtonDeactiveKey = m_strButtonKey + systemButtonNS::FRAME_DEACTIVE_KEY;
			success = Image::initialize(g, 0, 0, 0, IMAGEMANAGER->getTexture(m_strButtonUpKey));
		}
		else
			success = Image::initialize(g, 0, 0, 0, IMAGEMANAGER->getTexture(m_strButtonKey));
		
		m_width = Image::getWidth();
		m_height = Image::getHeight();
		setupButtonRect();
		m_bInitialized = m_bActive = success;
	}
	catch (...)
	{
		std::string error = systemButtonNS::ERROR_MESSAGE + " : " + imageName;
		MessageBox(g_hWndEngine, error.c_str(), "Error", MB_OK);
	}

	return success;
}

bool SystemButton::initialize(Graphics * g, Input * i, float x, float y, std::string imageName, bool bUseKey)
{
	bool success = false;
	try
	{
		m_pGraphics = g;
		m_pInput = i;
		m_strButtonKey = imageName;
		m_bUseKey = bUseKey;

		if (m_bUseKey)
		{
			m_strButtonUpKey = m_strButtonKey + systemButtonNS::FRAME_UP_KEY;
			m_strButtonDownKey = m_strButtonKey + systemButtonNS::FRAME_DOWN_KEY;
			m_strButtonOverKey = m_strButtonKey + systemButtonNS::FRAME_OVERLAB_KEY;
			m_strButtonDeactiveKey = m_strButtonKey + systemButtonNS::FRAME_DEACTIVE_KEY;
			success = Image::initialize(g, 0, 0, 0, IMAGEMANAGER->getTexture(m_strButtonUpKey));
		}
		else
			success = Image::initialize(g, 0, 0, 0, IMAGEMANAGER->getTexture(m_strButtonKey));

		m_x = x;
		m_y = y;
		m_width = Image::getWidth();
		m_height = Image::getHeight();
		setupButtonRect();
		m_bInitialized = m_bActive = success;
	}
	catch (...)
	{
		std::string error = systemButtonNS::ERROR_MESSAGE + " : " + imageName;
		MessageBox(g_hWndEngine, error.c_str(), "Error", MB_OK);
	}

	return success;
}

void SystemButton::update(float frameTime)
{
	if (m_bInitialized == false)
		return;

	if (m_bActive == false)
	{
		m_enButtonState = SYSTEM_UI_BUTTON::BUTTON_STATE_DEACTIVE;
		if(m_bUseKey)
			Image::setTextureManager(IMAGEMANAGER->getTexture(m_strButtonDeactiveKey));
		return;
	}

	if (PtInRect(&m_rcButton, m_pInput->getMousePt()))
	{
		if (m_bUseKey)
			Image::setTextureManager(IMAGEMANAGER->getTexture(m_strButtonOverKey));
		m_enButtonState = SYSTEM_UI_BUTTON::BUTTON_STATE_OVERLAB;
	}
	else
	{
		if (m_bUseKey)
			Image::setTextureManager(IMAGEMANAGER->getTexture(m_strButtonUpKey));
		m_enButtonState = SYSTEM_UI_BUTTON::BUTTON_STATE_UP;
	}

	if (m_pInput->getMouseLButton())
	{
		if (PtInRect(&m_rcButton, m_pInput->getMousePt()))
		{
			if (m_bUseKey)
				Image::setTextureManager(IMAGEMANAGER->getTexture(m_strButtonDownKey));
			m_enButtonState = SYSTEM_UI_BUTTON::BUTTON_STATE_DOWN;

			if(m_function != nullptr)
				m_function();

			m_pInput->setMouseLButton(false);
		}
	}
	else
	{
		if (m_bUseKey)
			Image::setTextureManager(IMAGEMANAGER->getTexture(m_strButtonUpKey));
		else
			m_enButtonState = SYSTEM_UI_BUTTON::BUTTON_STATE_UP;
	}
}

void SystemButton::render()
{
	if (m_bInitialized == false)
		return;

	if (m_bActive == false)
		return;

	m_pGraphics->spriteBegin();
	Image::draw();
	m_pGraphics->spriteEnd();
}
