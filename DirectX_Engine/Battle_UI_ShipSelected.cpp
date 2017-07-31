#include "stdafx.h"
#include "Battle_UI_ShipSelected.h"


CBattle_UI_ShipSelected::CBattle_UI_ShipSelected()
{
	m_pGraphics		= nullptr;
	m_nSpriteNum	= 0;
	m_bActive		= false;
}


CBattle_UI_ShipSelected::~CBattle_UI_ShipSelected()
{
}

bool CBattle_UI_ShipSelected::initialize(Graphics * g)
{
	bool success = false;
	try
	{
		m_pGraphics = g;

		if (m_nSpriteNum < 10)
			m_strSelectedKey = battleUIShipSelectedNS::SHIP_SELECTED_FILENAME + "00" + std::to_string(m_nSpriteNum);
		else
			m_strSelectedKey = battleUIShipSelectedNS::SHIP_SELECTED_FILENAME + "0" + std::to_string(m_nSpriteNum);

		success = Image::initialize(m_pGraphics, 0, 0, 0, IMAGEMANAGER->getTexture(m_strSelectedKey));
	}
	catch (...)
	{
		MessageBox(g_hWndEngine, battleUIShipSelectedNS::ERROR_MESSAGE.c_str(), "Error", MB_OK);
	}
	
	return success;
}

void CBattle_UI_ShipSelected::update(float frameTime)
{
	if (m_bActive == false)
		return;

	if (m_nSpriteNum >= battleUIShipSelectedNS::SHIP_SELECTED_MAX_FRAME)
		m_nSpriteNum = 0;

	if (m_nSpriteNum < 10)
		m_strSelectedKey = battleUIShipSelectedNS::SHIP_SELECTED_FILENAME + "00" + std::to_string(m_nSpriteNum);
	else
		m_strSelectedKey = battleUIShipSelectedNS::SHIP_SELECTED_FILENAME + "0" + std::to_string(m_nSpriteNum);

	Image::setTextureManager(IMAGEMANAGER->getTexture(m_strSelectedKey));
	m_nSpriteNum++;
}

void CBattle_UI_ShipSelected::render()
{
	if (m_bActive == false)
		return;

	m_pGraphics->spriteBegin();
	Image::draw();
	m_pGraphics->spriteEnd();
}
