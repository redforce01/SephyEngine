#include "stdafx.h"
#include "Battle_UI_FleetMark.h"
#include "Battle_UI_FleetMarkViewer.h"

CBattle_UI_FleetMark::CBattle_UI_FleetMark()
{
	m_pFleetMark	= nullptr;
	m_pFleetText	= nullptr;
	m_nIndex		= 0;
	m_x				= battleFleetMarkNS::FLEET_MARK_X;
	m_y				= battleFleetMarkNS::FLEET_MARK_Y;
	m_width			= 0.f;
	m_height		= 0.f;
	m_bActive		= false;
}


CBattle_UI_FleetMark::~CBattle_UI_FleetMark()
{
	SAFE_DELETE(m_pFleetMark);
	SAFE_DELETE(m_pFleetText);
}

bool CBattle_UI_FleetMark::initialize(Graphics * g, Input * i, int index)
{
	bool success = false;
	try
	{
		m_pGraphics = g;
		m_pInput = i;
		m_nIndex = index;

		if (index >= battleFleetMarkNS::FLEET_MARK_MAX_COUNT)
			return false;

		m_strFleetMarkKey = battleFleetMarkNS::FLEET_MARK_FILENAME + std::to_string(m_nIndex);
		m_strFleetTextKey = battleFleetMarkNS::FLEET_TEXT_FILENAME + std::to_string(m_nIndex);

		m_pFleetMark = new Image;
		success = m_pFleetMark->initialize(m_pGraphics, 0, 0, 0, IMAGEMANAGER->getTexture(m_strFleetMarkKey));
		m_pFleetText = new Image;
		success = m_pFleetText->initialize(m_pGraphics, 0, 0, 0, IMAGEMANAGER->getTexture(m_strFleetTextKey));
		
		if (index > 0)
		{
			m_y = battleFleetMarkNS::FLEET_MARK_Y + (battleFleetMarkNS::FLEET_MARK_TOTAL_HEIGHT * index);
		}
		m_width = m_pFleetMark->getWidth() + m_pFleetText->getWidth();
		m_height = m_pFleetText->getHeight();
		
		m_rcFleetMark = RectMake(m_x, m_y, m_width, m_height);
		m_pFleetMark->setX(m_x);
		m_pFleetMark->setY(m_y);
		m_pFleetText->setX(m_x + m_pFleetMark->getWidth() + battleFleetMarkNS::FLEET_MARK_MARGIN);
		m_pFleetText->setY(m_y - abs(m_pFleetMark->getHeight() - m_pFleetText->getHeight()) / 2);
	}
	catch (...)
	{
		std::string message = battleFleetMarkNS::ERROR_MESSAGE + ": Index = " + std::to_string(index);
		MessageBox(g_hWndEngine, message.c_str(), "Error", MB_OK);
	}

	return success;
}

void CBattle_UI_FleetMark::update(float frameTime)
{
	if (m_pInput->getMouseLButton())
	{
		if (PtInRect(&m_rcFleetMark, m_pInput->getMousePt()))
		{
			m_pBattleUIFleetMarkViewer->setArrowAtMark(m_nIndex);
		}
	}
}

void CBattle_UI_FleetMark::render()
{
	m_pGraphics->spriteBegin();
	m_pFleetMark->draw();
	m_pFleetText->draw();
	m_pGraphics->spriteEnd();
}

void CBattle_UI_FleetMark::moveFleetMarkX(float distance)
{
	m_x += distance;
	m_pFleetMark->moveX(distance);
	m_pFleetText->moveX(distance);
	updateFleetMarkRect();
}

void CBattle_UI_FleetMark::moveFleetMarkY(float distance)
{
	m_y += distance;
	m_pFleetMark->moveY(distance);
	m_pFleetText->moveY(distance);
	updateFleetMarkRect();
}
