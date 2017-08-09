#include "stdafx.h"
#include "UnitTool_MouseOverShip.h"
#include "UnitTool_UnitControlSystem.h"
#include "UnitTool_RespawnListViewer.h"

CUnitTool_MouseOverShip::CUnitTool_MouseOverShip()
{
	m_pUnitControlSystem = nullptr;
	m_pRespawnListViewer = nullptr;
	m_bOverlabOn = false;
	m_pOverlabShip = nullptr;
}


CUnitTool_MouseOverShip::~CUnitTool_MouseOverShip()
{
}

bool CUnitTool_MouseOverShip::initialize(Graphics * g, Input * i)
{
	m_pGraphics = g;
	m_pInput = i;

	if (m_pGraphics == nullptr)
		return false;

	if (m_pInput == nullptr)
		return false;

	return true;
}

void CUnitTool_MouseOverShip::update(float frameTime)
{
	if (m_bOverlabOn == false)
		return;

	float mouseX = m_pInput->getMouseX();
	float mouseY = m_pInput->getMouseY();

	m_pOverlabShip->setCurrentCenterX(mouseX);
	m_pOverlabShip->setCurrentCenterY(mouseY);

	if (m_pInput->getMouseLButton())
	{
		if (m_pOverlabShip->getIsPlayerShip())
		{
			tagRespawnShipInfo info;
			info.shipName = m_pOverlabShip->getShipName();
			info.shipType = m_pOverlabShip->getShipType();
			info.tagNumber = 0;
			m_pRespawnListViewer->addPlayerShipInfo(info);
			m_pOverlabShip->setUnitToolMode(true);
			m_pOverlabShip->setMemoryLinkUnitControlSystem(m_pUnitControlSystem);
			m_pUnitControlSystem->addPlayerShip(m_pOverlabShip);
		}
		else
		{
			tagRespawnShipInfo info;
			info.shipName = m_pOverlabShip->getShipName();
			info.shipType = m_pOverlabShip->getShipType();
			info.tagNumber = 0;
			m_pRespawnListViewer->addComputerShipInfo(info);
			m_pOverlabShip->setUnitToolMode(true);
			m_pOverlabShip->setMemoryLinkUnitControlSystem(m_pUnitControlSystem);
			m_pUnitControlSystem->addComputerShip(m_pOverlabShip);
		}

		m_bOverlabOn = false;
		m_pInput->setMouseLButton(false);
	}
	m_pOverlabShip->update(frameTime);
}

void CUnitTool_MouseOverShip::render()
{
	if (m_bOverlabOn == false)
		return;

	m_pOverlabShip->render();
}
