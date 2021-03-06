#include "stdafx.h"
#include "Battle_UnitSystem.h"
#include "Battle_CameraSystem.h"
#include "Battle_MapSystem.h"
#include "Battle_FleetSystem.h"
#include "Battle_FogSystem.h"
#include "Battle_ResultSystem.h"

CBattle_UnitSystem::CBattle_UnitSystem()
{
	m_pBattleCameraSystem		= nullptr;
	m_pBattleMapSystem			= nullptr;
	m_pBattleFleetSystem		= nullptr;
	m_pBattleFogSystem			= nullptr;
	m_pBattleResultSystem		= nullptr;
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
	m_fPlayerDamageScore	= 0.f;
	m_fComputerDamageScore	= 0.f;
	//=======================================
	m_bSelectedUnit		= false;
	m_bRePlaceShip		= false;
	m_bSetupShip		= false;
	m_bBattleStart		= false;
	m_bBattleFinish		= false;
	m_bPlayerWin		= false;
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
	m_bPhaseTwoUp		= false;
	m_bPhaseThreeUp		= false;
	//=======================================
	m_nLoad_Player_ShipUniqueID = 0;
	m_nLoad_AI_ShipUniqueID		= 0;
	//=======================================
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
	for (auto iter : m_vDigit)
	{
		SAFE_DELETE(iter);
	}
	m_vDigit.clear();
	for (auto iter : m_vOperator)
	{
		SAFE_DELETE(iter);
	}
	m_vOperator.clear();
	
	SAFE_DELETE(m_pBattleUnitParser);
	SAFE_DELETE(m_pBattle_UI_Destination);
	SAFE_DELETE(m_pBattle_UI_FleetListView);
	SAFE_DELETE(m_pBattle_UI_FleetMarkView);
	SAFE_DELETE(m_pBattle_UI_FleetMakeView);
	SAFE_DELETE(m_pBattle_UI_StartButton);
	SAFE_DELETE(m_pBattle_UI_ControlView);
	SAFE_DELETE(m_pBattle_UI_PhaseAlert);
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
		m_pBattle_UI_ControlView = new CBattle_UI_UnitControlViewer;
		success = m_pBattle_UI_ControlView->initialize(m_pGraphics, m_pInput);
		m_pBattle_UI_PhaseAlert = new CBattle_UI_PhaseAlert;
		success = m_pBattle_UI_PhaseAlert->initialize(m_pGraphics);
		//================================================================================
		m_pBattle_UI_StartButton = new CBattle_UI_StartButton;
		success = m_pBattle_UI_StartButton->initialize(m_pGraphics, m_pInput);
		//================================================================================
		m_pBattle_UI_StartButton->setMemoryLinkBattleUnitSystem(this);
		m_pBattle_UI_FleetMakeView->setMemoryLinkBattleUnitSystem(this);
		//================================================================================
		m_vWorkableRect.emplace_back(m_pBattle_UI_FleetListView->getDialogRECT());
		m_vWorkableRect.emplace_back(m_pBattle_UI_FleetMarkView->getDialogRECT());
		m_vWorkableRect.emplace_back(m_pBattle_UI_ControlView->getDialogRECT());
	}
	catch (...)
	{
		MessageBox(g_hWndEngine, battleUnitSystemNS::ERROR_MESSAGE.c_str(), "Error", MB_OK);
	}
	
	return success;
}

void CBattle_UnitSystem::update(float frameTime)
{
	if (m_bBattleFinish)
	{
		return;
	}
	
	m_pBattle_UI_FleetListView->update(frameTime);
	m_pBattle_UI_FleetMarkView->update(frameTime);
	m_pBattle_UI_FleetMakeView->update(frameTime);
	m_pBattle_UI_ControlView->update(frameTime);
	m_pBattle_UI_PhaseAlert->update(frameTime);

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

	//========================================
	// All Damage Digit Update
	//  + Included Enemy & Player Damage Digit
	//  + if The Digit Animation Complete -> erase
	//========================================
	for (auto iter = m_vDigit.begin(); iter != m_vDigit.end(); )
	{
		(*iter)->update(frameTime);
		if ((*iter)->IsAnimeComplete() == true)
		{
			SAFE_DELETE(*iter);
			m_vDigit.erase(iter);
		}
		else
			iter++;
	}

	//========================================
	// Operator Update
	//  + It's only Update First Operator
	//  + if First Operator Complete -> erase
	//  + and Update Next Operator
	//========================================
	if (m_vOperator.size() > 0)
	{
		auto iter = m_vOperator.begin();
		(*iter)->update(frameTime);

		if ((*iter)->IsOperatorComplete())
		{
			SAFE_DELETE(*iter);
			m_vOperator.erase(iter);
		}
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
	// Damage Digit Render
	for (auto iter : m_vDigit)
	{
		iter->render();
	}

	if (m_vOperator.size() > 0)
	{
		auto iter = m_vOperator.begin();
		(*iter)->render();
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
	m_pBattle_UI_ControlView->render();
	m_pBattle_UI_PhaseAlert->render();

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

	// 
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

	//==================================================
	// Collision Check Player Ships Rader - Detect EnemyShip 
	//  + Each Ship Checked EnemyShip Entity
	//==================================================
	for (auto aiShipIter : m_vCompterShips)
	{
		auto aiShipCollision = aiShipIter->getShipCollision();

		auto aiShipX = aiShipCollision.x;
		auto aiShipY = aiShipCollision.y;
		auto aiShipRadius = aiShipCollision.radius;

		for (auto playerIter : m_vPlayerShips)
		{
			if (playerIter->getShipActive() == false)
				continue;

			if (playerIter->getDummyShip())
				continue;

			if (playerIter->getShipDestroy())
				continue;

			auto playerShipX = playerIter->getCurrentCenterX();
			auto playerShipY = playerIter->getCurrentCenterY();
			auto playerRaderRange = playerIter->getRaderRange();

			if (MyUtil::circleIncircle(playerShipX, playerShipY, playerRaderRange, aiShipX, aiShipY, aiShipRadius) == false)
			{
				aiShipIter->setDetected(false);
				continue;
			}
			else
			{
				if (m_bPhaseTwoUp == false)
				{
					m_bPhaseTwoUp = true;
					m_nCurrentBattlePhase = 2;
					m_pBattle_UI_PhaseAlert->setAlert(true);
					CBattle_Operator* phaseOperator = new CBattle_Operator;
					phaseOperator->initialize(m_pGraphics, m_pInput);
					phaseOperator->setupEventPosition(m_pBattleCameraSystem->getCameraX(), m_pBattleCameraSystem->getCameraY());
					phaseOperator->setupOperator(OPERATOR_TYPE::OPERATOR_TYPE_CAPTAIN, OPERATOR_SITUATION_TYPE::OPERATOR_SITUATION_N, "Phase 2 Active");
					m_vOperator.emplace_back(phaseOperator);
				}

				if (aiShipIter->getDetectedSound() == false)
				{
					aiShipIter->setDetectedSound(true);
					playSoundEnemyShipInSight();
				}
			
				aiShipIter->setDetected(true);
				break;
			}
		}
	}

	//==================================================
	// Collision Check All Ship Is On/Off Repair Area 
	//==================================================
	auto vRepairArea = m_pBattleMapSystem->getRepairArea();
	for (auto iter : vRepairArea)
	{
		float areaCenterX = iter->getAreaCenterX();
		float areaCenterY = iter->getAreaCenterY();
		float areaRadius = iter->getAreaRadius();
		float areaCaptureRadius = iter->getAreaCaptureRadius();

		bool bPlayerArea = iter->isPlayerArea();
		//===============================================
		// Check Player Ship - Repair Area - Repairing
		//===============================================
		for (auto shipIter : m_vPlayerShips)
		{
			if (shipIter->getShipActive() == false)
				continue;

			if (shipIter->getDummyShip() == true)
				continue;

			if (shipIter->getShipDestroy())
				continue;

			auto shipCollisionCircle = shipIter->getShipCollision();

			float shipCenterX = shipCollisionCircle.x;
			float shipCenterY = shipCollisionCircle.y;
			float shipRadius = shipCollisionCircle.radius;

			if (MyUtil::circleIncircle(areaCenterX, areaCenterY, areaRadius, shipCenterX, shipCenterY, shipRadius) == false)
			{
				shipIter->takeRepairBuf(false);
				continue;
			}

			if (bPlayerArea)
			{
				shipIter->takeRepairBuf(true, iter->getRepairSpeed());
			}
		}
		//===============================================
		// Check Player Ship - Repair Area - Capturing
		//===============================================
		for (auto shipIter : m_vPlayerShips)
		{
			if (shipIter->getShipActive() == false)
				continue;

			if (shipIter->getDummyShip() == true)
				continue;

			if (shipIter->getShipDestroy())
				continue;

			auto shipCollisionCircle = shipIter->getShipCollision();

			float shipCenterX = shipCollisionCircle.x;
			float shipCenterY = shipCollisionCircle.y;
			float shipRadius = shipCollisionCircle.radius;

			if (MyUtil::circleIncircle(areaCenterX, areaCenterY, areaCaptureRadius, shipCenterX, shipCenterY, shipRadius) == false)
			{
				iter->capturing(false);
				continue;
			}

			if (bPlayerArea == false)
			{
				iter->capturing(true);
				break;
			}
		}
	}

	//==================================================
	// Collision Check All Ship Is On/Off Observer Area 
	//==================================================
	auto vObserverArea = m_pBattleMapSystem->getObserverArea();
	for (auto iter : vObserverArea)
	{
		float areaCenterX = iter->getAreaCenterX();
		float areaCenterY = iter->getAreaCenterY();
		float areaCaptureRadius = iter->getAreaCaptureRadius();

		bool bPlayerArea = iter->isPlayerArea();
		//===============================================
		// Check Player Ship - Observer Area - Capturing
		//===============================================
		for (auto shipIter : m_vPlayerShips)
		{
			if (shipIter->getShipActive() == false)
				continue;

			if (shipIter->getDummyShip() == true)
				continue;

			if (shipIter->getShipDestroy())
				continue;

			auto shipCollisionCircle = shipIter->getShipCollision();

			float shipCenterX = shipCollisionCircle.x;
			float shipCenterY = shipCollisionCircle.y;
			float shipRadius = shipCollisionCircle.radius;

			if (MyUtil::circleIncircle(areaCenterX, areaCenterY, areaCaptureRadius, shipCenterX, shipCenterY, shipRadius) == false)
			{
				iter->capturing(false);
				continue;
			}

			if (bPlayerArea == false)
			{
				iter->capturing(true);
				break;
			}
		}
	}

	//==================================================
	// Collision Check All Ship - Enemy Starting Area
	//==================================================
	auto vStartingArea = m_pBattleMapSystem->getStartingArea();
	for (auto iter : vStartingArea)
	{
		if (iter->isPlayerArea())
			continue;

		float areaCenterX = iter->getCenterX();
		float areaCenterY = iter->getCenterY();
		float areaCaptureRadius = iter->getRadius();
		for (auto shipIter : m_vPlayerShips)
		{
			if (shipIter->getShipActive() == false)
				continue;

			if (shipIter->getDummyShip() == true)
				continue;

			if (shipIter->getShipDestroy())
				continue;

			auto shipCollisionCircle = shipIter->getShipCollision();

			float shipCenterX = shipCollisionCircle.x;
			float shipCenterY = shipCollisionCircle.y;
			float shipRadius = shipCollisionCircle.radius;

			if (MyUtil::circleIncircle(areaCenterX, areaCenterY, areaCaptureRadius, shipCenterX, shipCenterY, shipRadius) == false)
			{
				iter->capturing(false);
				continue;
			}

			iter->capturing(true);
			break;
		}
	}
	
	//==================================================
	// Observer Area - Enemy Ship Detect Collision Check
	//==================================================
	for (auto iter : vObserverArea)
	{
		if (iter->isPlayerArea() == false)
			continue;

		float areaCenterX = iter->getAreaCenterX();
		float areaCenterY = iter->getAreaCenterY();
		float areaRadius = iter->getAreaSightRadius();

		for (auto aiShipIter : m_vCompterShips)
		{
			if (aiShipIter->getShipActive() == false)
				continue;

			auto aiShipCollision = aiShipIter->getShipCollision();

			float shipCenterX = aiShipCollision.x;
			float shipCenterY = aiShipCollision.y;
			float shipRadius = aiShipCollision.radius;
			
			if (MyUtil::circleIncircle(areaCenterX, areaCenterY, areaRadius, shipCenterX, shipCenterY, shipRadius) == false)
				continue;

			aiShipIter->setDetected(true);
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
		newShip->setPlayerShip(true);
		newShip->initialize(m_pGamePtr, shipName);
		newShip->setShipUniqueID(m_nLoad_Player_ShipUniqueID);
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
		ship->setDetected(true);
	}

	if (m_bRePlaceShip)
	{
		m_vPlayerShips[m_nSelectUnitNum]->setCurrentX(m_pInput->getMouseX() - (m_vPlayerShips[m_nSelectUnitNum]->getShipHeight() / 2));
		m_vPlayerShips[m_nSelectUnitNum]->setCurrentY(m_pInput->getMouseY() - (m_vPlayerShips[m_nSelectUnitNum]->getShipHeight() / 2));
	}
	
	if (m_pInput->getMouseLButton())
	{
		//=============================================
		// Setup Flag Ship - Fleet Make Event
		//=============================================
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
		//=============================================
		// Select Ship - Fleet Make Event
		//=============================================
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
		//=============================================
		// Setup Ship - From Ship List
		//=============================================
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
				ship->setDetected(true);
				m_bSetupShip = false;
				m_pInput->setMouseLButton(false);
			}
		}
		//=============================================
		// Replace Ship Position Setup Event
		//=============================================
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
			//=============================================
			// Replace Ship Change to True - Check. Clicked Ship?
			//=============================================
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
	//============================================
	// Before Update - Setup Ship Cancel placement
	//============================================
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
	//  + Update Only When Before Start
	//============================================
	m_pBattle_UI_StartButton->update(frameTime);
}

void CBattle_UnitSystem::updateFuncAfterStart(float frameTime)
{
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
			dummyShip->setDummyShip(true);
			dummyShip->setDetected(true);
			m_nSetupShipIndex = -1;
			m_bSetupShip = false;
			m_vBattle_UI_DummyShip.emplace_back(dummyShip);
			m_pInput->setMouseLButton(false);
		}
	}
	else
	{
		//===========================================
		// Simple Select Unit Event
		//===========================================
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
						m_pBattle_UI_ControlView->setupShip(iter);
						break;
					}
					else
					{
						m_vPlayerShips[unitCount]->setUnitSelected(false);
						m_pBattle_UI_ControlView->setupNone(true);
					}
				}				
				unitCount++;
			}
			m_bSimpleClicked = false;
		}

		//===========================================
		// Drag Box End Event - Select All Unit In Box
		//===========================================
		if (m_bClicked == true)
		{
			m_bClicked = false;
			m_fClickEndX = m_pInput->getMouseX();
			m_fClickEndY = m_pInput->getMouseY();

			float tempX = 0.f;
			float tempY = 0.f;
			if (m_fClickEndX < m_fClickStartX)
			{
				tempX = m_fClickStartX;
				m_fClickStartX = m_fClickEndX;
				m_fClickEndX = tempX;
			}
			if (m_fClickEndY < m_fClickStartY)
			{
				tempY = m_fClickStartY;
				m_fClickStartY = m_fClickEndY;
				m_fClickEndY = tempY;
			}

			RECT rcDragBox = RectMake(m_fClickStartX, m_fClickStartY, m_fClickEndX - m_fClickStartX, m_fClickEndY - m_fClickStartY);
			for (auto iter : m_vPlayerShips)
			{
				if (MyUtil::circleInRect(iter->getShipTouchData().x, iter->getShipTouchData().y, iter->getShipTouchData().radius, &rcDragBox))
				{
					iter->setUnitSelected(true);
					m_bSelectedUnit = true;
					m_pBattle_UI_ControlView->setupShip(iter);
				}
				else
				{
					iter->setUnitSelected(false);
					m_pBattle_UI_ControlView->setupNone(false);
				}
			}
		}
	}

	if (m_pInput->getMouseRButton())
	{
		//===========================================
		// Destination UI Create
		//===========================================
		if (m_bFleetClicked)
		{
			float targetX = m_pInput->getMousePt().x;
			float targetY = m_pInput->getMousePt().y;

			m_pBattleFleetSystem->getFleet(m_nClickedFleetNumber)->flagShip->setTargetX(targetX);
			m_pBattleFleetSystem->getFleet(m_nClickedFleetNumber)->flagShip->setTargetY(targetY);
			m_pBattle_UI_Destination->setActive(true);
			m_pBattle_UI_Destination->setDestinationPos(VECTOR2(targetX, targetY));
			if(SOUNDMANAGER->isPlaySound(battleUnitSystemNS::FLEET_MOVE_ORDER_SOUND_NAME) == false)
			{
				SOUNDMANAGER->play(battleUnitSystemNS::FLEET_MOVE_ORDER_SOUND_NAME, g_fSoundMasterVolume * g_fSoundEffectVolume);
			}
			m_pInput->setMouseRButton(false);
		}
		//===========================================
		// Set Ship Move To - Target Pos Event
		//===========================================
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
			
			bool bSelectManyShips = false;
			int selectUnitCount = 0;
			for (auto iter : m_vPlayerShips)
			{
				if(iter->getShipSelected())
					selectUnitCount++;

				if (selectUnitCount > 1)
				{
					bSelectManyShips = true;
					break;
				}
			}

			if (bSelectManyShips)
			{
				if (SOUNDMANAGER->isPlaySound(battleUnitSystemNS::FLEET_MOVE_ORDER_SOUND_NAME) == false)
				{
					SOUNDMANAGER->play(battleUnitSystemNS::FLEET_MOVE_ORDER_SOUND_NAME, g_fSoundMasterVolume * g_fSoundEffectVolume);
				}
			}
			else
			{
				if (SOUNDMANAGER->isPlaySound(battleUnitSystemNS::SHIP_MOVE_ORDER_SOUND_NAME) == false)
				{
					SOUNDMANAGER->play(battleUnitSystemNS::SHIP_MOVE_ORDER_SOUND_NAME, g_fSoundMasterVolume * g_fSoundEffectVolume);
				}
			}

			m_pBattle_UI_Destination->setActive(true);
			m_pBattle_UI_Destination->setDestinationPos(VECTOR2(targetX, targetY));
			m_pInput->setMouseRButton(false);
		}

		//===========================================
		// Dummy Ship Delete Event - Before Placement
		//  + This Is Mouse R Button Event Function
		//===========================================
		auto mouseX = m_pInput->getMouseX();
		auto mouseY = m_pInput->getMouseY();
		for (auto iter = m_vBattle_UI_DummyShip.begin(); iter != m_vBattle_UI_DummyShip.end();)
		{
			if (MyUtil::ptInCircle((*iter)->getShipTouchData().x, (*iter)->getShipTouchData().y, (*iter)->getShipTouchData().radius, mouseX, mouseY))
			{
				if ((*iter)->getShipActive() == false)
				{
					iter++;
					continue;
				}

				(*iter)->setShipActive(false);
				(*iter)->setDummyShip(false);
				(*iter)->resetShipFleetData();
				m_pBattle_UI_FleetListView->addShipToFleetList((*iter)->getShipType(), (*iter)->getShipName(), (*iter)->getCallPhase());
				SAFE_DELETE(*iter);
				m_vBattle_UI_DummyShip.erase(iter);
				m_pInput->setMouseRButton(false);
				break;
			}
			else
			{
				iter++;
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
	// Check Player Ship Destroy - Sunken Complete
	//  + if Sunken Complete ? true -> erase from ShipArray
	//============================================
	for (auto iter = m_vPlayerShips.begin(); iter != m_vPlayerShips.end(); )
	{
		if ((*iter)->getShipActive() == false)
		{
			iter++;
			continue;
		}

		if ((*iter)->getShipDestroy() == false)
		{
			iter++;
			continue;
		}

		if ((*iter)->getSunkenComplete())
		{
			m_vPlayerShips.erase(iter);
		}
		else
		{
			iter++;
		}
	}
	//============================================
	// Check Computer Ship Destroy - Sunken Complete
	//  + if Sunken Complete ? true -> erase from ShipArray
	//============================================
	for (auto iter = m_vCompterShips.begin(); iter != m_vCompterShips.end(); )
	{
		if ((*iter)->getShipActive() == false)
		{
			iter++;
			continue;
		}

		if ((*iter)->getShipDestroy() == false)
		{
			iter++;
			continue;
		}

		if ((*iter)->getSunkenComplete())
		{
			m_vCompterShips.erase(iter);
		}
		else
		{
			iter++;
		}
	}

	//============================================
	// Update Dummy Ship - if Complete Setup Time
	//  + Spawn Ship to Respawn Area
	//  + And Erase Dummy Ship UI
	//============================================
	for (auto iter = m_vBattle_UI_DummyShip.begin(); iter != m_vBattle_UI_DummyShip.end();)
	{
		if ((*iter)->getSetup() == false)
		{
			(*iter)->update(frameTime);
			iter++;
			continue;
		}
		else
		{
			auto activeShipName = (*iter)->getShipName();
			for (auto iterPlayerShip : m_vPlayerShips)
			{
				if (iterPlayerShip->getShipActive() == true)
					continue;

				if (iterPlayerShip->getShipName().compare(activeShipName) == false)
				{
					iterPlayerShip->setShipActive(true);
					iterPlayerShip->setCurrentCenterX(m_pBattleMapSystem->getPlayerRespawnArea()->getRespawnAreaCenterX());
					iterPlayerShip->setCurrentCenterY(m_pBattleMapSystem->getPlayerRespawnArea()->getRespawnAreaCenterY());
					iterPlayerShip->setTargetX((*iter)->getCurrentCenterX());
					iterPlayerShip->setTargetY((*iter)->getCurrentCenterY());
					iterPlayerShip->setShipArrived(false);
					iterPlayerShip->setDummyShip(false);
					iterPlayerShip->setDetected(true);

					std::string message = iterPlayerShip->getShipName() + battleOperatorMessageNS::SHIP_RESPAWN_COMPLETE;
					CBattle_Operator* cptOperator = new CBattle_Operator;
					cptOperator->initialize(m_pGraphics, m_pInput);
					cptOperator->setupOperator(OPERATOR_TYPE::OPERATOR_TYPE_CAPTAIN,
						OPERATOR_SITUATION_TYPE::OPERATOR_SITUATION_N,
						message);
					cptOperator->setupEventPosition(iterPlayerShip->getCurrentCenterX(), iterPlayerShip->getCurrentCenterY());
					addOperator(cptOperator);			
					break;
				}
			}
			SAFE_DELETE(*iter);
			m_vBattle_UI_DummyShip.erase(iter);
		}
	}

	//============================================
	// Destination UI Update 
	//  + This UI is Only one Object
	//============================================
	m_pBattle_UI_Destination->update(frameTime);


	//============================================
	// Check Battle Phase - To Phase 3
	//  + Check Repair Area - is Player? -> Phase 3 Active
	//  + Check Observer Area - is Player? -> Phase 3 Active
	//============================================
	auto vRepairArea = m_pBattleMapSystem->getRepairArea();
	if (m_bPhaseThreeUp == false)
	{
		for (auto iter : vRepairArea)
		{
			if (iter->isPlayerArea() == false)
				continue;

			m_bPhaseTwoUp = true;
			m_bPhaseThreeUp = true;
			m_nCurrentBattlePhase = 3;
			CBattle_Operator* phaseOperator = new CBattle_Operator;
			phaseOperator->initialize(m_pGraphics, m_pInput);
			phaseOperator->setupEventPosition(m_pBattleCameraSystem->getCameraX(), m_pBattleCameraSystem->getCameraY());
			phaseOperator->setupOperator(OPERATOR_TYPE::OPERATOR_TYPE_CAPTAIN, OPERATOR_SITUATION_TYPE::OPERATOR_SITUATION_P, "Phase 3 Active");
			m_vOperator.emplace_back(phaseOperator);
			break;
		}
	}
	auto vObserverArea = m_pBattleMapSystem->getObserverArea();
	if (m_bPhaseThreeUp == false)
	{
		for (auto iter : vObserverArea)
		{
			if (iter->isPlayerArea() == false)
				continue;

			m_bPhaseTwoUp = true;
			m_bPhaseThreeUp = true;
			m_nCurrentBattlePhase = 3;
			CBattle_Operator* phaseOperator = new CBattle_Operator;
			phaseOperator->initialize(m_pGraphics, m_pInput);
			phaseOperator->setupEventPosition(m_pBattleCameraSystem->getCameraX(), m_pBattleCameraSystem->getCameraY());
			phaseOperator->setupOperator(OPERATOR_TYPE::OPERATOR_TYPE_CAPTAIN, OPERATOR_SITUATION_TYPE::OPERATOR_SITUATION_P, "Phase 3 Active");
			m_vOperator.emplace_back(phaseOperator);
			break;
		}
	}

	//========================================
	// Battle Finish Check
	//  + Player Has Starting Area Count >= 2 ? -> Finish
	//  + Enemy Ships Size <= 0 ? -> Finish
	//========================================
	if (m_bBattleFinish == false)
	{
		auto vStartingArea = m_pBattleMapSystem->getStartingArea();
		int playerStartingAreaCount = 0;
		for (auto iter : vStartingArea)
		{
			if (iter->isPlayerArea() == false)
				continue;

			playerStartingAreaCount++;
		}
		if (playerStartingAreaCount >= 2)
		{
			m_bBattleFinish = true;
			m_bPlayerWin = true;
			m_pBattleResultSystem->saveBattleResult();
			SOUNDMANAGER->stop(battleUnitSystemNS::BATTLE_START_BGM_PHASE_1_NAME);
		}

		if (m_vCompterShips.size() <= 0)
		{
			m_bBattleFinish = true;
			m_bPlayerWin = true;
			m_pBattleResultSystem->saveBattleResult();
			SOUNDMANAGER->stop(battleUnitSystemNS::BATTLE_START_BGM_PHASE_1_NAME);
		}
		else
		{
			bool bFinish = false;
			for (auto iter : m_vCompterShips)
			{
				if (iter->getShipActive() == false)
				{
					bFinish = false;
					break;
				}

				if (iter->getShipDestroy() == false)
				{
					bFinish = false;
					break;
				}

				bFinish = true;
			}

			if (bFinish)
			{
				m_bBattleFinish = true;
				m_bPlayerWin = true;
				m_pBattleResultSystem->saveBattleResult();
				SOUNDMANAGER->stop(battleUnitSystemNS::BATTLE_START_BGM_PHASE_1_NAME);
			}
		}
		
		if (m_vPlayerShips.size() <= 0)
		{
			m_bBattleFinish = true;
			m_bPlayerWin = false;
			m_pBattleResultSystem->saveBattleResult();
			SOUNDMANAGER->stop(battleUnitSystemNS::BATTLE_START_BGM_PHASE_1_NAME);
		}
		else
		{
			bool bFinish = false;
			for (auto iter : m_vPlayerShips)
			{
				if (iter->getShipActive() == false)
				{
					bFinish = false;
					break;
				}

				if (iter->getShipDestroy() == false)
				{
					bFinish = false;
					break;
				}

				bFinish = true;
			}

			if (bFinish)
			{
				m_bBattleFinish = true;
				m_bPlayerWin = false;
				m_pBattleResultSystem->saveBattleResult();
				SOUNDMANAGER->stop(battleUnitSystemNS::BATTLE_START_BGM_PHASE_1_NAME);
			}
		}
	}
}

void CBattle_UnitSystem::setupEnemyShips()
{
	for (auto iter : m_vCompterShips)
	{
		int randX = RANDOM_MAKER->GetInt(-200, 200);
		int randY = RANDOM_MAKER->GetInt(-200, 200);
		iter->setCurrentCenterX(m_pBattleMapSystem->getEnemyStartingArea()->getCenterX() + randX);
		iter->setCurrentCenterY(m_pBattleMapSystem->getEnemyStartingArea()->getCenterY() + randY);
		iter->setShipActive(true);
		iter->setPlayerShip(false);
		iter->setDetected(false);
	}
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
	for (auto iter : m_vDigit)
	{
		iter->moveX(fDistance);
	}
	for (auto iter : m_vOperator)
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
	for (auto iter : m_vDigit)
	{
		iter->moveY(fDistance);
	}
	for (auto iter : m_vOperator)
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
		if (iter->getShipActive() == false)
			continue;

		if (iter->getCallPhase() > m_nCurrentBattlePhase)
		{
			iter->setCurrentCenterX(-99999);
			iter->setCurrentCenterY(-99999);
			iter->setShipActive(false);
			m_pBattle_UI_FleetListView->addShipToFleetList(iter->getShipType(), iter->getShipName(), iter->getCallPhase());
		}
	}
	SOUNDMANAGER->play(battleUnitSystemNS::BATTLE_START_BGM_PHASE_1_NAME, g_fSoundMasterVolume * g_fSoundBGMVolume);
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
	m_vFleetMakeShips[0]->setShipActive(false);

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
		iter->setShipActive(false);

		shipCount++;
	}

	m_bCreateFleet = false;
}

void CBattle_UnitSystem::playSoundEnemyShipInSight()
{
	if (SOUNDMANAGER->isPlaySound(battleUnitSystemNS::ENEMY_SHIP_INSIGHT_SOUND_NAME) == false)
	{
		SOUNDMANAGER->play(battleUnitSystemNS::ENEMY_SHIP_INSIGHT_SOUND_NAME, g_fSoundMasterVolume * g_fSoundEffectVolume);
	}
}
