#include "stdafx.h"
#include "Battle_UnitSystem.h"
#include "Battle_CameraSystem.h"
#include "Battle_MapSystem.h"

CBattle_UnitSystem::CBattle_UnitSystem()
{
	m_pBattleCameraSystem		= nullptr;
	m_pBattleMapSystem			= nullptr;
	//=======================================
	m_pBattleUnitParser			= nullptr;
	m_pBattle_UI_Destination	= nullptr;
	m_pBattle_UI_FleetListView	= nullptr;
	m_pBattle_UI_StartButton	= nullptr;
	//=======================================
	m_nCurrentBattlePhase	= 3;
	m_nSetupShipIndex		= -1;
	m_nSelectUnitNum		= -1;
	//=======================================
	m_bSelectedUnit		= false;
	m_bReSetupShip		= false;
	m_bSetupShip		= false;
	m_bBattleStart		= false;
	m_bWorkableSetup	= false;
	//=======================================
	m_bClicked			= false;
	m_bSimpleClicked	= false;
	m_fClickStartX = 0.f;
	m_fClickStartY = 0.f;
	m_fClickEndX = 0.f;
	m_fClickEndY = 0.f;
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
	SAFE_DELETE(m_pBattle_UI_FleetListView);
	SAFE_DELETE(m_pBattle_UI_FleetMarkView);
	SAFE_DELETE(m_pBattle_UI_FleetMakeView);
	SAFE_DELETE(m_pBattle_UI_StartButton);
}

bool CBattle_UnitSystem::initialize(Game * gamePtr)
{
	bool success = false;
	if (gamePtr == nullptr)
		return false;

	try
	{
		m_pGamePtr = gamePtr;
		m_pGraphics = m_pGamePtr->getGraphics();
		m_pInput = m_pGamePtr->getInput();
		//================================================================================
		m_pBattle_UI_Destination = new CBattle_UI_Destination;
		success = m_pBattle_UI_Destination->initialize(m_pGraphics);
		//================================================================================
		m_pBattle_UI_FleetListView = new CBattle_UI_FleetListView;
		success = m_pBattle_UI_FleetListView->initialize(m_pGraphics, m_pInput);
		m_pBattle_UI_FleetListView->setMemoryLinkBattleUnitSystem(this);
		m_pBattle_UI_FleetMarkView = new CBattle_UI_FleetMarkViewer;
		success = m_pBattle_UI_FleetMarkView->initialize(m_pGraphics, m_pInput);
		m_pBattle_UI_FleetMakeView = new CBattle_UI_FleetMakeViewer;
		success = m_pBattle_UI_FleetMakeView->initialize(m_pGraphics, m_pInput);
		//================================================================================
		m_pBattle_UI_StartButton = new CBattle_UI_StartButton;
		success = m_pBattle_UI_StartButton->initialize(m_pGraphics, m_pInput);
		m_pBattle_UI_StartButton->setMemoryLinkBattleUnitSystem(this);
		//================================================================================
		m_vWorkableRect.emplace_back(m_pBattle_UI_FleetListView->getDialogRECT());
		m_vWorkableRect.emplace_back(m_pBattle_UI_FleetMarkView->getDialogRECT());
	}
	catch (...)
	{
		MessageBox(g_hWndEngine, battleUnitSystemNS::ERROR_MESSAGE.c_str(), "Error", MB_OK);
	}
	
	return success;
}

void CBattle_UnitSystem::update(float frameTime)
{
	m_pBattle_UI_FleetListView->update(frameTime);
	m_pBattle_UI_FleetMarkView->update(frameTime);
	m_pBattle_UI_FleetMakeView->update(frameTime);

	if (m_bBattleStart == false)
	{
		updateFuncBeforeStart(frameTime);
	}
	else
	{
		updateFuncAfterStart(frameTime);
	}
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

	if (m_bClicked)
	{
		RECT rc = { m_fClickStartX, m_fClickStartY, m_fClickEndX, m_fClickEndY };
		m_pGraphics->drawRect(rc, 1.0f, graphicsNS::GREEN);
	}
	
	m_pBattle_UI_Destination->render();
	m_pBattle_UI_FleetListView->render();
	m_pBattle_UI_FleetMarkView->render();
	m_pBattle_UI_FleetMakeView->render();
	if(m_bBattleStart == false)
		m_pBattle_UI_StartButton->render();
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

		std::string resultShipType = newShip->getShipType();
		std::string resultShipName = newShip->getShipName();
		int resultShipPhase = newShip->getCallPhase();
		m_pBattle_UI_FleetListView->addShipToFleetList(resultShipType, resultShipName, resultShipPhase);

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

void CBattle_UnitSystem::updateFuncBeforeStart(float frameTime)
{
	//=======================================
	// Update Before - Battle Start 
	//=======================================

	if (m_bSetupShip)
	{
		auto ship = m_vPlayerShips[m_nSetupShipIndex];

		ship->setCurrentX(m_pInput->getMouseX() - (ship->getShipWidth() / 2));
		ship->setCurrentY(m_pInput->getMouseY() - (ship->getShipHeight() / 2));
		ship->setShipActive(true);
	}

	if (m_bReSetupShip)
	{
		m_vPlayerShips[m_nSelectUnitNum]->setCurrentX(m_pInput->getMouseX() - (m_vPlayerShips[m_nSelectUnitNum]->getShipHeight() / 2));
		m_vPlayerShips[m_nSelectUnitNum]->setCurrentY(m_pInput->getMouseY() - (m_vPlayerShips[m_nSelectUnitNum]->getShipHeight() / 2));
		if (m_pInput->getMouseLButton())
		{
			auto areaCenterX = m_pBattleMapSystem->getPlayerStartingArea()->getCenterX() + m_pBattleCameraSystem->getCameraX();
			auto areaCenterY = m_pBattleMapSystem->getPlayerStartingArea()->getCenterY() + m_pBattleCameraSystem->getCameraY();
			auto areaRadius = m_pBattleMapSystem->getPlayerStartingArea()->getRadius();
			auto mouseX = m_pInput->getMouseX();
			auto mouseY = m_pInput->getMouseY();
			auto distance = MyUtil::getDistance(mouseX, mouseY, areaCenterX, areaCenterY);

			//=======================================
			// Checking MouseOverlab Unit Position
			// true : unit In AreaCircle
			// false : unit Out AreaCircle
			//=======================================
			if (distance < areaRadius)
			{
				m_vPlayerShips[m_nSelectUnitNum]->setCurrentX(m_pInput->getMouseX() - (m_vPlayerShips[m_nSelectUnitNum]->getShipHeight() / 2));
				m_vPlayerShips[m_nSelectUnitNum]->setCurrentY(m_pInput->getMouseY() - (m_vPlayerShips[m_nSelectUnitNum]->getShipHeight() / 2));
				m_bReSetupShip = false;
				m_pInput->setMouseLButton(false);
			}
		}
	}

	if (m_pInput->getMouseLButton())
	{
		if (m_bSetupShip)
		{
			auto ship = m_vPlayerShips[m_nSetupShipIndex];
			auto areaCenterX = m_pBattleMapSystem->getPlayerStartingArea()->getCenterX() + m_pBattleCameraSystem->getCameraX();
			auto areaCenterY = m_pBattleMapSystem->getPlayerStartingArea()->getCenterY() + m_pBattleCameraSystem->getCameraY();
			auto areaRadius = m_pBattleMapSystem->getPlayerStartingArea()->getRadius();
			auto mouseX = m_pInput->getMouseX();
			auto mouseY = m_pInput->getMouseY();
			auto distance = MyUtil::getDistance(mouseX, mouseY, areaCenterX, areaCenterY);

			//=======================================
			// Checking MouseOverlab Unit Position
			// true : unit In AreaCircle
			// false : unit Out AreaCircle
			//=======================================
			if (distance < areaRadius)
			{
				ship->setCurrentX(m_pInput->getMouseX() - (ship->getShipHeight() / 2));
				ship->setCurrentY(m_pInput->getMouseY() - (ship->getShipHeight() / 2));
				ship->setShipActive(true);
				m_bSetupShip = false;
				m_pInput->setMouseLButton(false);
			}
		}
		else
		{
			if (m_bReSetupShip)
				m_bReSetupShip = false;

			int count = 0;
			for (auto iter : m_vPlayerShips)
			{
				if (iter->getShipActive() == false)
				{
					count++;
					continue;
				}

				auto mouseX = m_pInput->getMouseX();
				auto mouseY = m_pInput->getMouseY();
				if (MyUtil::ptInCircle(iter->getCurrentCenterX(), iter->getCurrentCenterY(), (iter->getShipHeight() / 2), mouseX, mouseY))
				{
					m_bReSetupShip = true;
					m_nSelectUnitNum = count;
					m_pInput->setMouseLButton(false);
					break;
				}
				count++;
			}
		}
	}

	if (m_pInput->getMouseRButton())
	{
		auto mouseX = m_pInput->getMouseX();
		auto mouseY = m_pInput->getMouseY();
		for (auto iter : m_vPlayerShips)
		{
			if (MyUtil::ptInCircle(iter->getCurrentCenterX(), iter->getCurrentCenterY(), (iter->getShipHeight() / 2), mouseX, mouseY))
			{
				if (iter->getShipActive() == false)
					continue;

				iter->setShipActive(false);
				m_pBattle_UI_FleetListView->addShipToFleetList(iter->getShipType(), iter->getShipName(), iter->getCallPhase());
			}
		}
	}


	m_pBattle_UI_StartButton->update(frameTime);
}

void CBattle_UnitSystem::updateFuncAfterStart(float frameTime)
{
	//=======================================
	// Update After - Battle Start 
	//=======================================

	if (m_pInput->getMouseLButton())
	{
		if (m_bClicked == false)
		{
			m_bClicked = true;
			m_fClickStartX = m_pInput->getMouseX();
			m_fClickStartY = m_pInput->getMouseY();
			m_fClickEndX = m_pInput->getMouseX();
			m_fClickEndY = m_pInput->getMouseY();
		}

		if (m_bSelectedUnit)
			m_bSelectedUnit = false;

		m_bSimpleClicked = true;
	}
	else
	{
		if (m_bSimpleClicked)
		{
			int unitCount = 0;
			for (auto iter : m_vPlayerShips)
			{
				float unitX = iter->getShipTouchData().x;
				float unitY = iter->getShipTouchData().y;
				float unitRadius = iter->getShipTouchData().radius;

				float mouseX = m_pInput->getMouseX();
				float mouseY = m_pInput->getMouseY();
				float mouseClickRadius = 1.f;

				float distance = MyUtil::getDistance(unitX, unitY, mouseX, mouseY);
				float sumRadius = unitRadius + mouseClickRadius;

				if (distance < sumRadius)
				{
					m_vPlayerShips[unitCount]->setUnitSelected(true);
					m_bSelectedUnit = true;
				}
				else
				{
					m_vPlayerShips[unitCount]->setUnitSelected(false);
				}
				unitCount++;
			}
			m_bSimpleClicked = false;
		}

		if (m_bClicked == true)
		{
			m_bClicked = false;
			m_fClickEndX = m_pInput->getMouseX();
			m_fClickEndY = m_pInput->getMouseY();

			RECT rcDragBox = RectMake(m_fClickStartX, m_fClickStartY, m_fClickEndX - m_fClickStartX, m_fClickEndY - m_fClickStartY);
			for (auto iter : m_vPlayerShips)
			{
				if (MyUtil::circleInRect(iter->getShipTouchData().x, iter->getShipTouchData().y, iter->getShipTouchData().radius, &rcDragBox))
				{
					iter->setUnitSelected(true);
					m_bSelectedUnit = true;
				}
				else
					iter->setUnitSelected(false);
			}
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
				if (iter->getShipSelected())
				{
					iter->setTargetPos(VECTOR2(targetX, targetY));
				}
			}
			m_pBattle_UI_Destination->setActive(true);
			m_pBattle_UI_Destination->setDestinationPos(VECTOR2(targetX, targetY));
			m_pInput->setMouseRButton(false);
		}
	}

	if (m_bClicked)
	{
		m_fClickEndX = m_pInput->getMouseX();
		m_fClickEndY = m_pInput->getMouseY();
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

void CBattle_UnitSystem::clearActiveShip()
{
	if (m_bBattleStart == false)
	{
		for (auto iter : m_vPlayerShips)
		{
			if (iter->getShipActive())
			{
				iter->setShipActive(false);
				m_pBattle_UI_FleetListView->addShipToFleetList(iter->getShipType(), iter->getShipName(), iter->getCallPhase());
			}
		}
	}
}

void CBattle_UnitSystem::setupShip(std::string shipName)
{
	int count = 0;
	for (auto iter : m_vPlayerShips)
	{
		if (iter->getShipName().compare(shipName) == false)
		{
			if (iter->getShipActive() == false)
			{
				m_bSetupShip = true;
				m_nSetupShipIndex = count;
				break;
			}
		}
		count++;
	}
}

void CBattle_UnitSystem::setupActiveForStart()
{
	for (auto iter : m_vPlayerShips)
	{
		if (iter->getCallPhase() > m_nCurrentBattlePhase)
		{
			iter->setShipActive(false);
		}
	}
}
