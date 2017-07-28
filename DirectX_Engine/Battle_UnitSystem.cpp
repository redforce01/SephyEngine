#include "stdafx.h"
#include "Battle_UnitSystem.h"
#include "Battle_CameraSystem.h"

CBattle_UnitSystem::CBattle_UnitSystem()
{
	m_pBattleCameraSystem		= nullptr;
	//=======================================
	m_pBattleUnitParser			= nullptr;
	m_pBattle_UI_Destination	= nullptr;
	m_pBattle_UI_FleetCategory	= nullptr;
	//=======================================
	m_bSelectedUnit = false;
}


CBattle_UnitSystem::~CBattle_UnitSystem()
{
	for (auto iter : m_vPlayerShips)
	{
		SAFE_DELETE(iter);
	}
	for (auto iter : m_vCompterShips)
	{
		SAFE_DELETE(iter);
	}
	
	SAFE_DELETE(m_pBattleUnitParser);
	SAFE_DELETE(m_pBattle_UI_Destination);
	SAFE_DELETE(m_pBattle_UI_FleetCategory);
}

bool CBattle_UnitSystem::initialize(Game * gamePtr)
{
	m_pGamePtr = gamePtr;
	m_pGraphics = m_pGamePtr->getGraphics();
	m_pInput = m_pGamePtr->getInput();

	m_pBattle_UI_Destination = new CBattle_UI_Destination;
	m_pBattle_UI_Destination->initialize(m_pGraphics);

	m_pBattle_UI_FleetCategory = new CBattle_UI_FleetCategory;
	m_pBattle_UI_FleetCategory->initialize(m_pGraphics, m_pInput);

	return true;
}

void CBattle_UnitSystem::update(float frameTime)
{	
	if (m_pInput->getMouseLButton())
	{
		int unitCount = 0;
		for (auto iter : m_vPlayerShips)
		{			
			float unitX = iter->getShipTouchData().x;
			float unitY = iter->getShipTouchData().y;
			float unitRadius = iter->getShipTouchData().radius;

			float mouseX = m_pInput->getMouseX();
			float mouseY = m_pInput->getMouseY();
			float mouseClickRadius = 10.f;

			float distance = MyUtil::getDistance(unitX, unitY, mouseX, mouseY);
			float sumRadius = unitRadius + mouseClickRadius;
			
			if (distance < sumRadius)
			{
				m_vPlayerShips[unitCount]->setUnitSelected(true);
				m_bSelectedUnit = true;
				break;
			}
			else
			{
				m_vPlayerShips[unitCount]->setUnitSelected(false);
				m_bSelectedUnit = false;
			}
			unitCount++;
		}
	}

	if (m_pInput->getMouseRButton())
	{
		if (m_bSelectedUnit)
		{
			float targetX = m_pInput->getMousePt().x;
			float targetY = m_pInput->getMousePt().y;
			for (auto iter : m_vPlayerShips)
			{
				if (iter->getUnitSelected())
				{
					iter->setTargetPos(VECTOR2(targetX, targetY));
				}
			}
			m_pBattle_UI_Destination->setActive(true);
			m_pBattle_UI_Destination->setDestinationPos(VECTOR2(targetX, targetY));
			m_pInput->setMouseRButton(false);
		}
	}



	for (auto iter : m_vPlayerShips)
	{
		iter->update(frameTime);
	}

	for (auto iter : m_vCompterShips)
	{
		iter->update(frameTime);
	}

	m_pBattle_UI_Destination->update(frameTime);
	m_pBattle_UI_FleetCategory->update(frameTime);
}

void CBattle_UnitSystem::render()
{
	for (auto iter : m_vPlayerShips)
	{
		iter->render();
	}

	for (auto iter : m_vCompterShips)
	{
		iter->render();
	}

	m_pBattle_UI_Destination->render();
	m_pBattle_UI_FleetCategory->render();
}

void CBattle_UnitSystem::ai()
{
}

void CBattle_UnitSystem::collision()
{
}

void CBattle_UnitSystem::loadPlayerShipData(std::vector<std::string> vArray)
{
	for (auto iter : vArray)
	{		
		auto vData = functionTokenize(iter);
		std::string shipName = vData[battleUnitSystemNS::UNIT_NAME_POS];
		CBattle_Ship* newShip = new CBattle_Ship;
		newShip->initialize(m_pGamePtr, shipName);
		m_vPlayerShips.emplace_back(newShip);
	}
}

void CBattle_UnitSystem::loadAIShipData(std::vector<std::string> vArray)
{
	for (auto iter : vArray)
	{
		auto vData = functionTokenize(iter);
		std::string shipName = vData[battleUnitSystemNS::UNIT_NAME_POS];

		CBattle_Ship* newShip = new CBattle_Ship;
		newShip->initialize(m_pGamePtr, shipName);
		m_vCompterShips.emplace_back(newShip);
	}
}

std::vector<std::string> CBattle_UnitSystem::functionTokenize(std::string strData)
{
	std::vector<std::string> vResult;
	
	std::istringstream is(strData);
	std::string part;
	while (getline(is, part, ' '))
	{
		vResult.emplace_back(part);
	}

	return vResult;
}

void CBattle_UnitSystem::moveX(float fDistance)
{
	for (auto iter : m_vPlayerShips)
	{
		iter->moveX(fDistance);
	}

	for (auto iter : m_vCompterShips)
	{
		iter->moveX(fDistance);
	}

	m_pBattle_UI_Destination->moveX(fDistance);
}

void CBattle_UnitSystem::moveY(float fDistance)
{
	for (auto iter : m_vPlayerShips)
	{
		iter->moveY(fDistance);
	}

	for (auto iter : m_vCompterShips)
	{
		iter->moveY(fDistance);
	}

	m_pBattle_UI_Destination->moveY(fDistance);
}
