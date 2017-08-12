#include "stdafx.h"
#include "UnitTool_ShipDataSetter.h"
#include "UnitTool_UIViewer.h"

CUnitTool_ShipDataSetter::CUnitTool_ShipDataSetter()
{
	m_pUnitToolUIViewer = nullptr;
}


CUnitTool_ShipDataSetter::~CUnitTool_ShipDataSetter()
{
	SAFE_DELETE(m_pSettingShip);
}

bool CUnitTool_ShipDataSetter::initialize(Game * gamePtr)
{
	m_pGame = gamePtr;

	return false;
}

void CUnitTool_ShipDataSetter::setupShipData(std::string shipName)
{
	if (m_pSettingShip)
	{
		SAFE_DELETE(m_pSettingShip);
	}
	m_pSettingShip = new CBattle_Ship;

	bool loadSuccess = false;
	loadSuccess = m_pSettingShip->initialize(m_pGame, shipName);
	if (loadSuccess == false)
		return;

	m_pUnitToolUIViewer->setID(m_pSettingShip->getShipID());										 // 01. Ship ID				1
	m_pUnitToolUIViewer->setTextureKey(m_pSettingShip->getTextureKey());							 // 02. TextureKey			1
	m_pUnitToolUIViewer->setTopCount(m_pSettingShip->getTopSpriteCount());							 // 03. TopCount			1
	m_pUnitToolUIViewer->setBodyCount(m_pSettingShip->getBodySpriteCount());						 // 04. BodyCount			1
	m_pUnitToolUIViewer->setBottomCount(m_pSettingShip->getBottomSpriteCount());					 // 05. BottomCount			1
	m_pUnitToolUIViewer->setName(m_pSettingShip->getShipName());									 // 06. ShipName			1
	m_pUnitToolUIViewer->setShipType(m_pSettingShip->getShipType());								 // 07. ShipType			1
																									 // 08. UnitType			
	m_pUnitToolUIViewer->setMaxDP(m_pSettingShip->getMaxHealth());									 // 09. MaxDP				1
	m_pUnitToolUIViewer->setCurrentDP(m_pSettingShip->getCurrentHealth());							 // 10. CurrentDP			1
	m_pUnitToolUIViewer->setRepairSpeed(m_pSettingShip->getRepairSpeed());							 // 11. RepairSpeed			1
	m_pUnitToolUIViewer->setRotateSpeed(m_pSettingShip->getRotateSpeed());							 // 12. RotateSpeed			1
	m_pUnitToolUIViewer->setAccelerateSpeed(m_pSettingShip->getAccelateSpeed());					 // 13. AccelerateSpeed		1
	m_pUnitToolUIViewer->setMaxSpeed(m_pSettingShip->getMaxSpeed());								 // 14. MaxSpeed			1
	m_pUnitToolUIViewer->setCurrentSpeed(m_pSettingShip->getCurrentSpeed());						 // 15. CurrentSpeed		1
	m_pUnitToolUIViewer->setRaderRange(m_pSettingShip->getRaderRange());							 // 16. RaderRange			1
	m_pUnitToolUIViewer->setTurretCapacity(m_pSettingShip->getTurretCount());						 // 17. Turret Capacity		1
	m_pUnitToolUIViewer->setTurretName(m_pSettingShip->getTurretID());								 // 18. Turret Name			1
	m_pUnitToolUIViewer->setAircraftCapacity(m_pSettingShip->getAirCraftCapacity());				 // 19. Aircraft Capacity	1
	m_pUnitToolUIViewer->setPerformance(m_pSettingShip->getPerformance());							 // 20. Performance			1
	m_pUnitToolUIViewer->setSailor(m_pSettingShip->getSailorCount());								 // 21. Sailor				1
	m_pUnitToolUIViewer->setAntiAirCapacity(m_pSettingShip->getAntiAirTurretCount());				 // 22. Antiair Capacity	1
	m_pUnitToolUIViewer->setAntiAirRange(m_pSettingShip->getAntiAirRange());						 // 23. Antiair Range		1
	m_pUnitToolUIViewer->setAntiAirDamage(m_pSettingShip->getAntiAirDamage());						 // 24. Antiair Damage		1
	m_pUnitToolUIViewer->setPhase(m_pSettingShip->getCallPhase());									 // 25. Phase				1
	m_pUnitToolUIViewer->setMass(m_pSettingShip->getShipMass());									 // 26. Mass				1
	m_pUnitToolUIViewer->setEvasionRadius(m_pSettingShip->getEvasion());							 // 27. Evasion Radius		1
																									 // 28. Skill

	m_pUnitToolUIViewer->setBeSetup(true);
}