#include "stdafx.h"
#include "Battle_UnitSystem.h"
#include "Battle_CameraSystem.h"
#include "Battle_MapSystem.h"
#include "Battle_FleetSystem.h"

#include <iostream>

CBattle_UnitSystem::CBattle_UnitSystem()
{
	m_pBattleCameraSystem		= nullptr;
	m_pBattleMapSystem			= nullptr;
	m_pBattleFleetSystem		= nullptr;
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
	m_bRePlaceShip		= false;
	m_bSetupShip		= false;
	m_bBattleStart		= false;
	m_bWorkableSetup	= false;
	m_bCreateFleet		= false;
	m_bSetUpFlagShip	= false;
	//=======================================
	m_nSelectFlagShip	= -1;
	//=======================================
	m_bClicked			= false;
	m_bSimpleClicked	= false;
	m_fClickStartX		= 0.f;
	m_fClickStartY		= 0.f;
	m_fClickEndX		= 0.f;
	m_fClickEndY		= 0.f;
	//=======================================
	m_nLoad_Player_ShipUniqueID = 0;
	m_nLoad_AI_ShipUniqueID		= 0;
}


CBattle_UnitSystem::~CBattle_UnitSystem()
{
	for (auto iter : m_vPlayerShips)
	{
		SAFE_DELETE(iter);
	}
	m_vPlayerShips.clear();
	for (auto iter : m_vCompterShips)
	{
		SAFE_DELETE(iter);
	}
	m_vCompterShips.clear();
	for (auto iter : m_vBattle_UI_DummyShip)
	{
		SAFE_DELETE(iter);
	}
	m_vBattle_UI_DummyShip.clear();
	
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
		//================================================================================
		m_pBattle_UI_StartButton->setMemoryLinkBattleUnitSystem(this);
		m_pBattle_UI_FleetMakeView->setMemoryLinkBattleUnitSystem(this);
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

	//========================================
	// All Bullet Update 
	//  + Included Enemy Bullet & Player Bullet
	//  + Working InActive Bullet Deleting
	//  + Not Using Auto Iterator -> using std::vector<type>::iterator
	//========================================
	for (auto iter = m_vBullets.begin(); iter != m_vBullets.end(); )
	{
		(*iter)->update(frameTime);
		if ((*iter)->IsActive() == false)
		{
			SAFE_DELETE(*iter);
			m_vBullets.erase(iter);
		}
		else
			iter++;
	}
}

void CBattle_UnitSystem::render()
{
	m_pBattle_UI_Destination->render();

	// Player Ships Render
	for (auto iter : m_vPlayerShips)
	{
		iter->render();
	}
	// AI Ships Render
	for (auto iter : m_vCompterShips)
	{
		iter->render();
	}
	// Dummy Ship Render
	for (auto iter : m_vBattle_UI_DummyShip)
	{
		iter->render();
	}
	// Bullet Render
	for (auto iter : m_vBullets)
	{
		iter->render();
	}
	// Mouse Drag Box Draw
	if (m_bClicked)
	{
		RECT rc = { m_fClickStartX, m_fClickStartY, m_fClickEndX, m_fClickEndY };
		m_pGraphics->drawRect(rc, 1.0f, graphicsNS::GREEN);
	}
	
	m_pBattle_UI_FleetListView->render();
	m_pBattle_UI_FleetMarkView->render();
	m_pBattle_UI_FleetMakeView->render();
	if(m_bBattleStart == false)
		m_pBattle_UI_StartButton->render();
}

void CBattle_UnitSystem::ai()
{
	if (m_bBattleStart == false)
		return;

	for (auto iter : m_vPlayerShips)
	{
		iter->ai();
	}
	for (auto iter : m_vCompterShips)
	{
		iter->ai();
	}
}

void CBattle_UnitSystem::collision()
{
	if (m_bBattleStart == false)
		return;

	for (auto iter : m_vPlayerShips)
	{
		iter->collision();
	}
	for (auto iter : m_vCompterShips)
	{
		iter->collision();
	}
	for (auto iter : m_vBullets)
	{
		for (auto playerIter : m_vPlayerShips)
		{
			iter->collision(playerIter);
		}
		for (auto computerIter : m_vCompterShips)
		{
			iter->collision(computerIter);
		}
	}
}

void CBattle_UnitSystem::loadPlayerShipData(std::vector<std::string> vArray)
{	
	for (auto iter : vArray)
	{		
		auto vData = functionTokenize(iter);
		std::string shipName = vData[battleUnitSystemNS::UNIT_NAME_POS];
		CBattle_Ship* newShip = new CBattle_Ship;
		newShip->initialize(m_pGamePtr, shipName);
		newShip->setShipUniqueID(m_nLoad_Player_ShipUniqueID);
		newShip->setPlayerShip(true);
		newShip->setMemoryLinkBattleMapSystem(m_pBattleMapSystem);
		newShip->setMemoryLinkBattleUnitSystem(this);

		m_vPlayerShips.emplace_back(newShip);
		//=========================================================
		std::string resultShipType = newShip->getShipType();
		std::string resultShipName = newShip->getShipName();
		int resultShipPhase = newShip->getCallPhase();
		m_pBattle_UI_FleetListView->addShipToFleetList(resultShipType, resultShipName, resultShipPhase);
		m_nLoad_Player_ShipUniqueID++;
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
		newShip->setShipUniqueID(m_nLoad_AI_ShipUniqueID);
		newShip->setMemoryLinkBattleMapSystem(m_pBattleMapSystem);
		newShip->setMemoryLinkBattleUnitSystem(this);
		m_vCompterShips.emplace_back(newShip);
		//=========================================================
		m_nLoad_AI_ShipUniqueID++;
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

	if (m_bRePlaceShip)
	{
		m_vPlayerShips[m_nSelectUnitNum]->setCurrentX(m_pInput->getMouseX() - (m_vPlayerShips[m_nSelectUnitNum]->getShipHeight() / 2));
		m_vPlayerShips[m_nSelectUnitNum]->setCurrentY(m_pInput->getMouseY() - (m_vPlayerShips[m_nSelectUnitNum]->getShipHeight() / 2));
	}
	
	if (m_pInput->getMouseLButton())
	{
		if (m_bSetUpFlagShip)
		{
			int nSelectShipNum = 0;
			for (auto iter : m_vPlayerShips)
			{
				if (iter->getShipActive() == false)
				{
					nSelectShipNum++;
					continue;
				}

				if (iter->getFlagShip())
				{
					nSelectShipNum++;
					continue;
				}

				auto mouseX = m_pInput->getMouseX();
				auto mouseY = m_pInput->getMouseY();
				if (MyUtil::ptInCircle(iter->getCurrentCenterX(), iter->getCurrentCenterY(), (iter->getShipHeight() / 2), mouseX, mouseY))
				{
					if (m_vFleetMakeShips.size() > 0)
					{
						m_vFleetMakeShips.clear();
					}

					// Save Select Ship Number For FlagShip Number
					m_nSelectFlagShip = nSelectShipNum;
					
					m_vFleetMakeShips.emplace_back(iter);

					// FleetMakeViewer - Set FlagShip Messages ( shipType , shipName )
					m_pBattle_UI_FleetMakeView->setFlagShipMessage(iter->getShipType(), iter->getShipName());
					m_bSetUpFlagShip = false;
					m_bCreateFleet = true;
					break;
				}

				nSelectShipNum++;
			}
			m_pInput->setMouseLButton(false);
		}
		else if (m_bCreateFleet)
		{			
			for (auto iter : m_vPlayerShips)
			{
				if (iter->getShipActive() == false)
					continue;

				if (iter->getFlagShip())
					continue;

				bool bContinue = false;
				for (auto fleetIter : m_vFleetMakeShips)
				{
					if (fleetIter->getShipUniqueID() == iter->getShipUniqueID())
						bContinue = true;
				}
				if (bContinue)
					continue;

				auto mouseX = m_pInput->getMouseX();
				auto mouseY = m_pInput->getMouseY();
				if (MyUtil::ptInCircle(iter->getCurrentCenterX(), iter->getCurrentCenterY(), (iter->getShipHeight() / 2), mouseX, mouseY))
				{
					m_vFleetMakeShips.emplace_back(iter);
					break;
				}
			}
			m_pInput->setMouseLButton(false);
		}
		else if (m_bSetupShip)
		{
			auto ship = m_vPlayerShips[m_nSetupShipIndex];
			auto areaCenterX = m_pBattleMapSystem->getPlayerStartingArea()->getCenterX();
			auto areaCenterY = m_pBattleMapSystem->getPlayerStartingArea()->getCenterY();
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
		else if (m_bRePlaceShip)
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
				m_bRePlaceShip = false;
				m_pInput->setMouseLButton(false);
			}
		}
		else
		{
			if (m_bRePlaceShip)
				m_bRePlaceShip = false;

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
					m_bRePlaceShip = true;
					m_nSelectUnitNum = count;
					m_pInput->setMouseLButton(false);
					break;
				}
				count++;
			}
			m_pBattle_UI_FleetMakeView->setFlagShipMessage("N/A", "N/A");
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

				m_nSetupShipIndex = -1;
				m_bSetupShip = false;
				iter->setShipActive(false);
				iter->resetShipFleetData();
				m_pBattle_UI_FleetListView->addShipToFleetList(iter->getShipType(), iter->getShipName(), iter->getCallPhase());
				break;
			}
		}
	}
	
	//============================================
	// Player & AI Ship Update
	//  + It would be updating Only Active Ships
	//============================================
	for (auto iter : m_vPlayerShips)
	{
		iter->update(frameTime);
	}
	for (auto iter : m_vCompterShips)
	{
		iter->update(frameTime);
	}
	
	//============================================
	// Batte Start Button Update
	//============================================
	m_pBattle_UI_StartButton->update(frameTime);
}

void CBattle_UnitSystem::updateFuncAfterStart(float frameTime)
{
	//static bool debugAI = false;
	//if (debugAI == false)
	//{
	//	debugAI = true;
	//	m_vCompterShips[0]->setCurrentCenterX(1900);
	//	m_vCompterShips[0]->setCurrentCenterY(500);
	//	m_vCompterShips[0]->setShipActive(true);
	//	m_vCompterShips[0]->setTargetX(600);
	//	m_vCompterShips[0]->setTargetY(900);
	//}


	//=======================================
	// Update After - Battle Start 
	//=======================================
	
	if (m_bFleetClicked)
	{
		for (auto iter : m_vPlayerShips)
		{
			if (iter->getShipActive() == false)
				continue;

			if (iter->getFleetIncluded() == false)
				continue;

			if (iter->getShipDestroy() == true)
				continue;

			if (iter->getFleetNumber() == m_nClickedFleetNumber)
			{
				iter->setUnitSelected(true);
			}
			else
				iter->setUnitSelected(false);
		}
	}

	// When Drag Boxing Update ClickEnd(x, y)
	if (m_bClicked)
	{
		m_fClickEndX = m_pInput->getMouseX();
		m_fClickEndY = m_pInput->getMouseY();
	}

	if (m_bSetupShip)
	{
		auto ship = m_vPlayerShips[m_nSetupShipIndex];

		ship->setCurrentX(m_pInput->getMouseX() - (ship->getShipWidth() / 2));
		ship->setCurrentY(m_pInput->getMouseY() - (ship->getShipHeight() / 2));
		ship->setShipActive(true);
	}

	if (m_pInput->getMouseLButton())
	{
		// Mouse Drag Event
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

		if (m_bSetupShip)
		{			
			auto ship = m_vPlayerShips[m_nSetupShipIndex];
			ship->setShipActive(false);
			CBattle_UI_DummyShip* dummyShip;
			dummyShip = new CBattle_UI_DummyShip;
			dummyShip->initialize(m_pGamePtr, ship->getTextureKey(), m_nSetupShipIndex);
			dummyShip->setCurrentX(m_pInput->getMouseX() - (dummyShip->getShipHeight() / 2));
			dummyShip->setCurrentY(m_pInput->getMouseY() - (dummyShip->getShipHeight() / 2));
			dummyShip->setShipActive(true);
			m_nSetupShipIndex = -1;
			m_bSetupShip = false;
			m_vBattle_UI_DummyShip.emplace_back(dummyShip);
			m_pInput->setMouseLButton(false);
		}
	}
	else
	{
		if (m_bSimpleClicked)
		{
			float mouseX = m_pInput->getMouseX();
			float mouseY = m_pInput->getMouseY();
			float mouseClickRadius = 1.f;
			int unitCount = 0;
			for (auto iter : m_vPlayerShips)
			{
				if (iter->getShipActive() == false)
					continue;
				
				if (iter->getShipDestroy() == true)
					continue;

				if (iter->getFleetIncluded() == true)
				{
					if (m_bFleetClicked)
					{
						m_bFleetClicked = false;
						m_bSelectedUnit = false;
						break;
					}

					float unitX = iter->getShipTouchData().x;
					float unitY = iter->getShipTouchData().y;
					float unitRadius = iter->getShipTouchData().radius;
					if (MyUtil::ptInCircle(unitX, unitY, unitRadius, mouseX, mouseY))
					{
						m_bFleetClicked = true;
						m_nClickedFleetNumber = iter->getFleetNumber();
						m_bSelectedUnit = true;
						break;
					}
				}
				else
				{
					float unitX = iter->getShipTouchData().x;
					float unitY = iter->getShipTouchData().y;
					float unitRadius = iter->getShipTouchData().radius;
					if (MyUtil::ptInCircle(unitX, unitY, unitRadius, mouseX, mouseY))
					{
						m_vPlayerShips[unitCount]->setUnitSelected(true);
						m_bSelectedUnit = true;
					}
					else
					{
						m_vPlayerShips[unitCount]->setUnitSelected(false);
					}
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
		if (m_bFleetClicked)
		{
			float targetX = m_pInput->getMousePt().x;
			float targetY = m_pInput->getMousePt().y;

			m_pBattleFleetSystem->getFleet(m_nClickedFleetNumber)->flagShip->setTargetX(targetX);
			m_pBattleFleetSystem->getFleet(m_nClickedFleetNumber)->flagShip->setTargetY(targetY);
			m_pBattle_UI_Destination->setActive(true);
			m_pBattle_UI_Destination->setDestinationPos(VECTOR2(targetX, targetY));
			m_pInput->setMouseRButton(false);
		}
		else if (m_bSelectedUnit)
		{
			float targetX = m_pInput->getMousePt().x;
			float targetY = m_pInput->getMousePt().y;
			for (auto iter : m_vPlayerShips)
			{
				if (iter->getShipActive() == false)
					continue;

				if (iter->getShipDestroy() == true)
					continue;

				if (iter->getShipSelected())
				{
					iter->setTargetPos(VECTOR2(targetX, targetY));
				}
			}
			m_pBattle_UI_Destination->setActive(true);
			m_pBattle_UI_Destination->setDestinationPos(VECTOR2(targetX, targetY));
			m_pInput->setMouseRButton(false);
		}

		//===========================================
		// Dummy Ship Delete Event
		//===========================================
		auto mouseX = m_pInput->getMouseX();
		auto mouseY = m_pInput->getMouseY();
		int dummyShipCount = 0;
		for (auto iter : m_vBattle_UI_DummyShip)
		{
			if (MyUtil::ptInCircle(iter->getShipTouchData().x, iter->getShipTouchData().y, iter->getShipTouchData().radius, mouseX, mouseY))
			{
				if (iter->getShipActive() == false)
				{
					dummyShipCount++;
					continue;
				}
				
				m_nSetupShipIndex = -1;
				m_bSetupShip = false;
				iter->setShipActive(false);
				iter->setDummyShip(false);
				iter->resetShipFleetData();
				m_pBattle_UI_FleetListView->addShipToFleetList(iter->getShipType(), iter->getShipName(), iter->getCallPhase());
				m_vBattle_UI_DummyShip.erase(m_vBattle_UI_DummyShip.begin() + dummyShipCount);
				SAFE_DELETE(iter);
				break;
			}
			dummyShipCount++;
		}
	}

	//============================================
	// Player & AI Ship Update
	//  + It would be updating Only Active Ships
	//============================================
	for (auto iter : m_vPlayerShips)
	{
		iter->update(frameTime);
	}
	for (auto iter : m_vCompterShips)
	{
		iter->update(frameTime);
	}

	//============================================
	// Update Dummy Ship - if Complete Setup Time
	//  + Spawn Ship to Respawn Area
	//  + And Erase Dummy Ship UI
	//============================================
	int dummyShipCount = 0;
	for (auto iter : m_vBattle_UI_DummyShip)
	{
		if (iter->getSetup() == false)
		{
			iter->update(frameTime);
			dummyShipCount++;
			continue;
		}

		auto activeShipName = iter->getShipName();
		for (auto iterPlayerShip : m_vPlayerShips)
		{
			if (iterPlayerShip->getShipActive() == true)
				continue;

			if (iterPlayerShip->getShipDestroy() == true)
				continue;

			if (iterPlayerShip->getShipName().compare(activeShipName) == false)
			{
				iterPlayerShip->setShipActive(true);
				iterPlayerShip->setCurrentCenterX(m_pBattleMapSystem->getPlayerRespawnArea()->getRespawnAreaCenterX());
				iterPlayerShip->setCurrentCenterY(m_pBattleMapSystem->getPlayerRespawnArea()->getRespawnAreaCenterY());
				iterPlayerShip->setTargetX(iter->getCurrentCenterX());
				iterPlayerShip->setTargetY(iter->getCurrentCenterY());
				iterPlayerShip->setShipArrived(false);

				auto iterator = m_vBattle_UI_DummyShip.begin() + dummyShipCount;
				m_vBattle_UI_DummyShip.erase(iterator);
				SAFE_DELETE(iter);
				break;
			}
		}
		dummyShipCount++;
	}

	//============================================
	// Destination UI Update 
	//  + This UI is Only one Object
	//============================================
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
	for (auto iter : m_vBattle_UI_DummyShip)
	{
		iter->moveX(fDistance);
	}
	for (auto iter : m_vBullets)
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
	for (auto iter : m_vBattle_UI_DummyShip)
	{
		iter->moveY(fDistance);
	}
	for (auto iter : m_vBullets)
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

void CBattle_UnitSystem::setupFleetToFleetSystem()
{
	if (m_bCreateFleet == false)
		return;

	if (m_vFleetMakeShips.size() <= 0)
		return;

	int nFleetNumber = m_pBattle_UI_FleetMarkView->getSelectedFleet();	

	auto selectFleetData = m_pBattleFleetSystem->getFleet(nFleetNumber);
	if (selectFleetData->bActiveFleet)
	{
		nFleetNumber++;
	}
	
	// Selected Ship Setup - Flag Ship (true)
	m_vFleetMakeShips[0]->setFlagShip(true);
	m_vFleetMakeShips[0]->setFleetConnectFlagShip(m_vFleetMakeShips[0]);
	m_vFleetMakeShips[0]->setFleetIncluded(true);
	m_vFleetMakeShips[0]->setFleetNumber(nFleetNumber);

	// Fleet System->SetFlagShip Throw Parameter(Ship, Selected Fleet Number)
	m_pBattleFleetSystem->setFlagShip(m_vFleetMakeShips[0], nFleetNumber);

	// Fleet System->SetFleetShips Throw Parameter(Ships, Select Fleet Number)
	m_pBattleFleetSystem->setFleetShips(m_vFleetMakeShips, nFleetNumber);

	int shipCount = 0;
	for (auto iter : m_vFleetMakeShips)
	{
		if (shipCount == 0)
		{
			shipCount++;
			continue;
		}
			
		iter->setFlagShip(false);
		iter->setFleetConnectFlagShip(m_vFleetMakeShips[0]);
		iter->setFleetIncluded(true);
		iter->setFleetNumber(nFleetNumber);

		shipCount++;
	}

	m_bCreateFleet = false;
}
