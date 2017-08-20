#include "stdafx.h"
#include "Battle_Ship.h"
#include "Battle_MapSystem.h"
#include "Battle_UnitSystem.h"
#include "UnitTool_UnitControlSystem.h"


CBattle_Ship::CBattle_Ship()
{
	m_pBattleUnitSystem			= nullptr;
	m_pBattleMapSystem			= nullptr;
	m_pUnitControlSystem		= nullptr;
	m_pUnitMapSystem			= nullptr;
	m_bUnitToolMode				= false;
	//===========================================
	m_pGame						= nullptr;
	m_pGraphics					= nullptr;
	m_pInput					= nullptr;	
	//===========================================
	m_nUnitUniqueID				= -1;
	m_nUnitID					= 0;
	m_nSpriteTopCount			= 0;
	m_nSpriteBodyCount			= 0;
	m_nSpriteBottomCount		= 0;
	//===========================================
	m_nSpriteTopStart			= 0;
	m_nSpriteBodyStart			= 0;
	m_nSpriteBottomStart		= 0;
	m_nSpriteShadowStart		= 0;
	m_nSpriteWaveStart			= 0;
	m_nSpriteSunkenStart		= 0;
	m_nSpriteSunkenShadowStart	= 0;
	//===========================================
	m_nSpriteShipTopNum			= 0;
	m_nSpriteShipBodyNum		= 0;
	m_nSpriteShipBottomNum		= 0;
	m_nSpriteShipShadowNum		= 0;
	m_nSpriteShipWaveNum		= 0;
	m_nSpriteShipWaveRotateNum	= 0;
	m_nSpriteSunkenNum			= 0;
	m_nSpriteSunkenShadowNum	= 0;
	//===========================================
	m_fTargetX					= 0.f;
	m_fTargetY					= 0.f;
	m_fCurrentHealth			= 0.f;
	m_fMaxHealth				= 0.f;
	m_fRepairSpeed				= 0.f;
	m_fRepairSpeedOriginal		= 0.f;
	m_fCurrentAngle				= 0.f;
	m_fTargetAngle				= 0.f;
	m_fRotateSpeed				= 0.f;
	m_fCurrentSpeed				= 0.f;
	m_fMaxSpeed					= 0.f;
	m_fAccelateSpeed			= 0.f;
	m_fRaderRange				= 0.f;
	m_fPerformance				= 0.f;
	m_nSailorCount				= 0;
	m_nTurretCount				= 0;
	m_nAntiAirTurrectCount		= 0.f;
	m_fAntiAirRange				= 0.f;
	m_fAntiAirDamage			= 0.f;
	m_nAirCraftCapacity			= 0;
	m_nCallPhase				= 0;
	m_fMass						= 0.f;
	m_fEvasionRange				= 0.f;
	//===========================================
	m_bIncludedFleet			= false;
	m_nFleetNumber				= -1;
	m_fDistanceFromFleet		= 0.f;
	m_fAngleFromFleet			= 0.f;
	m_pFlagShip					= nullptr;
	m_fFormationX				= 0.f;
	m_fFormationY				= 0.f;
	m_fFleetMaxSpeed			= 0.f;
	//===========================================
	m_bSukenStart				= false;
	m_bSunkenComplete			= false;
	m_fSunkenDeltaTime			= 0.f;
	//===========================================
	m_bPlayerShip				= false;
	m_bInitialized				= false;
	m_bActive					= false;
	m_bDestroy					= false;
	m_bDestroyAnimeComplete		= false;
	m_bChangeSprite				= false;
	m_bSelected					= false;
	m_bArrived					= true;
	m_bFlagShip					= false;
	//===========================================
	m_bFixedEngine				= false;
	m_bAutoGunOnOff				= true;
	m_bAutoAAGunOnOff			= true;
	m_bDetected					= false;
	m_bDetectedSound			= false;
	m_fUnDetectedTime			= 0.f;
	m_bAttacked					= false;
	m_bAttackedSound			= false;
	m_fUnattackedTime			= 0.f;
	//===========================================
	//m_bDebug					= g_bDebugMode;
	m_bDebug					= true;
	m_bDummy					= false;
	//===========================================
	ZeroMemory(&m_stUnitTouch, sizeof(m_stUnitTouch));
	ZeroMemory(&m_stUnitCollision, sizeof(m_stUnitCollision));
	ZeroMemory(&m_stRader, sizeof(m_stRader));
	ZeroMemory(&m_stEvasion, sizeof(m_stEvasion));
	
}


CBattle_Ship::~CBattle_Ship()
{
	for (auto iter : m_vEntity)
	{
		SAFE_DELETE(iter.second);
	}
	m_vEntity.clear();
	for (auto iter : m_vTurret)
	{
		SAFE_DELETE(iter);
	}
	m_vTurret.clear();
}

bool CBattle_Ship::initialize(Game * gamePtr, std::string shipName)
{
	if (gamePtr == nullptr)
		return false;

	m_pGame = gamePtr;
	m_pInput = gamePtr->getInput();
	m_pGraphics = gamePtr->getGraphics();

	auto vData = m_UnitDataParser.loadShipData(shipName);
	if (vData.size() <= 0)
		return false;

	bool success = false;
	try
	{
		setupShipDataFormat(vData);

#pragma region SHIP_ENTITY_INITIALIZE
		//====================================================================
		// Ship Entity Initialize - Start
		std::vector<std::pair<bool, std::string>> vShipEntityData;
		std::string result;
		for (int i = 0; i < m_nSpriteTopCount; i++)
		{
			m_vSpriteTopKey.emplace_back(m_strTextureKey + "_" + battleShipTextureNS::TEXTURE_KEY_TOP + std::to_string(i) + "_");
			result = m_strTextureKey + "_" + battleShipTextureNS::TEXTURE_KEY_TOP + std::to_string(i) + "_" + "00";
			vShipEntityData.emplace_back(true, result);
		}
		m_nSpriteBodyStart = m_vSpriteTopKey.size();
		for (int i = 0; i < m_nSpriteBodyCount; i++)
		{
			m_vSpriteBodyKey.emplace_back(m_strTextureKey + "_" + battleShipTextureNS::TEXTURE_KEY_BODY + std::to_string(i) + "_");
			result = m_strTextureKey + "_" + battleShipTextureNS::TEXTURE_KEY_BODY + std::to_string(i) + "_" + "00";
			vShipEntityData.emplace_back(true, result);
		}
		m_nSpriteBottomStart = m_nSpriteBodyStart + m_vSpriteBodyKey.size();
		for (int i = 0; i < m_nSpriteBottomCount; i++)
		{
			m_vSpriteBottomKey.emplace_back(m_strTextureKey + "_" + battleShipTextureNS::TEXTURE_KEY_BOTTOM + std::to_string(i) + "_");
			result = m_strTextureKey + "_" + battleShipTextureNS::TEXTURE_KEY_BOTTOM + std::to_string(i) + "_" + "00";
			vShipEntityData.emplace_back(true, result);
		}
		m_nSpriteShadowStart = m_nSpriteBottomStart + m_vSpriteBottomKey.size();
		m_strSpriteShadowKey = m_strTextureKey + "_" + battleShipTextureNS::TEXTURE_KEY_SHADOW;
		result = m_strTextureKey + "_" + battleShipTextureNS::TEXTURE_KEY_SHADOW + "00";
		vShipEntityData.emplace_back(false, result);

		m_nSpriteWaveStart = m_nSpriteShadowStart + battleShipGeneralNS::SHIP_SHADOW_TEXTURE_COUNT;
		m_strSpriteWaveKey = m_strTextureKey + "_" + battleShipTextureNS::TEXTURE_KEY_WAVE;
		result = m_strTextureKey + "_" + battleShipTextureNS::TEXTURE_KEY_WAVE + "00";
		vShipEntityData.emplace_back(false, result);

		m_nSpriteSunkenStart = m_nSpriteWaveStart + battleShipGeneralNS::SHIP_WAVE_TEXTURE_COUNT;
		m_strSpriteSunkenKey = m_strTextureKey + "_" + battleShipTextureNS::TEXTURE_KEY_SUNKEN;
		result = m_strTextureKey + "_" + battleShipTextureNS::TEXTURE_KEY_SUNKEN + "00";
		vShipEntityData.emplace_back(false, result);

		m_nSpriteSunkenShadowStart = m_nSpriteSunkenStart + battleShipGeneralNS::SHIP_SUNKEN_TEXTURE_COUNT;
		m_strSpriteSunkenShadowKey = m_strTextureKey + "_" + battleShipTextureNS::TEXTURE_KEY_SUNKEN_SHADOW;
		result = m_strTextureKey + "_" + battleShipTextureNS::TEXTURE_KEY_SUNKEN_SHADOW + "00";
		vShipEntityData.emplace_back(false, result);
		
		int entityCount = 0;
		entityCount = m_nSpriteTopCount + m_nSpriteBodyCount + m_nSpriteBottomCount + battleShipGeneralNS::SHIP_BASIC_TEXTURE_COUNT;
		for (auto iter : vShipEntityData)
		{
			bool bPhysics = iter.first;
			std::string strTextureName = iter.second;
			success = setupEntity(gamePtr, strTextureName, bPhysics);
			if (success == false)
				throw("Error");
		}
		int realPartsSize = m_vEntity.size() - battleShipGeneralNS::SHIP_BASIC_TEXTURE_COUNT;
		for (int i = 0; i < realPartsSize; i++)
		{
			m_vRealParts.emplace_back(m_vEntity[i]);
		}

		int shadowEntity = m_nSpriteTopCount + m_nSpriteBodyCount + m_nSpriteBottomCount;
		m_vEntity[shadowEntity].second->setColorFilter(battleShipTextureNS::SHIP_SHADOW_COLOR);

		int waveEntity = m_nSpriteTopCount + m_nSpriteBodyCount + m_nSpriteBottomCount + battleShipGeneralNS::SHIP_SHADOW_TEXTURE_COUNT;
		m_vEntity[waveEntity].second->setColorFilter(SETCOLOR_ARGB(192, 128, 128, 128));

		int sunkenShadowEntity = m_vEntity.size() - 1;
		m_vEntity[sunkenShadowEntity].second->setColorFilter(battleShipTextureNS::SHIP_SUNKEN_SHADOW_COLOR);
		// End - Ship Entity Initialize
		//====================================================================
#pragma endregion	


#pragma region SHIP_TURRET_INITIALIZE
		//====================================================================
		// Turret Initialize
		for (int i = 0; i < m_nTurretCount; i++)
		{
			CBattle_Turret* tempTurret = new CBattle_Turret;
			tempTurret->initialize(m_pGraphics, m_strTurretID, this);
			m_vTurret.emplace_back(tempTurret);
		}
		//====================================================================
#pragma endregion

#pragma region SHIP_INTERFACE_INITIALIZE

		m_BattleShipUI_Selected.initialize(m_pGraphics);		
		m_BattleShipUI_FleetMark.initialize(m_pGraphics);
		m_BattleShipUI_FleetMark.setMaster(this);
		m_BattleShipUI_FleetMark.setUIPos();
		m_BattleShipUI_State.initialize(m_pGraphics, this);
		m_BattleShipUI_State.setupProgress(m_fCurrentHealth, m_fMaxHealth);
		m_BattleShipUI_State.setupShipRankMark(m_strShipRankMark);
		m_BattleShipUI_State.setupStateUIPos();
		m_BattleShipUI_Indicator.initialize(m_pGraphics, m_pInput, INDICATOR_TYPE::INDICATOR_BLUE, this);
		m_BattleShipUI_Indicator.setUIPos();
		//====================================================================
#pragma endregion

#pragma region SHIP_TAG_DATA_INITIALIZE
		auto shipCenterX = m_vEntity[0].second->getCenterX();
		auto shipCenterY = m_vEntity[0].second->getCenterY();

		m_stUnitTouch.x = shipCenterX;
		m_stUnitTouch.y = shipCenterY;
		m_stUnitTouch.radius = m_vEntity[0].second->getHeight() / 3;

		m_stUnitCollision.x = shipCenterX;
		m_stUnitCollision.y = shipCenterY;
		m_stUnitCollision.radius = m_vEntity[0].second->getHeight() / 2;

		m_stRader.x = shipCenterX;
		m_stRader.y = shipCenterY;
		m_stRader.radius = m_fRaderRange;

		m_stEvasion.x = shipCenterX;
		m_stEvasion.y = shipCenterY;
		m_stEvasion.radius = m_fEvasionRange;
#pragma endregion

#pragma region SHIP_TAIL_EFFECT_INITIALIZE
		for (int i =0 ; i< battleShipGeneralNS::SHIP_TAIL_EFFECT_SIZE; i++)
		{		
			CBattle_ShipTailEffect tempTail; 
			tempTail.initialize(m_pGraphics, this);
			m_vTailEffect.emplace_back(tempTail);
		}
#pragma endregion

		m_bInitialized = true;
	}
	catch (...)
	{
		std::string strError = battleShipGeneralNS::ERROR_MESSAGE + " : " + shipName;
		MessageBox(g_hWndEngine, strError.c_str(), "Error", MB_OK);
	}
	
	return success;
}

void CBattle_Ship::update(float frameTime)
{
	if (m_bInitialized == false)
		return;

	if (m_bActive == false)
		return;

	if (m_bDestroy == true)
	{
		// When Ship Destroyed
		int updatePos = m_vEntity.size()
			- battleShipGeneralNS::SHIP_SUNKEN_TEXTURE_COUNT
			- battleShipGeneralNS::SHIP_SUNKEN_SHADOW_TEXTURE_COUNT;
		for ( ; updatePos < m_vEntity.size(); updatePos++)
		{
			m_vEntity[updatePos].second->update(frameTime);
		}
		m_bChangeSprite = updateRotate(frameTime);
		updateSprite(frameTime);
		return;
	}
	else
	{
		// When Ship Alive
		int updateSize = m_vEntity.size() 
			- battleShipGeneralNS::SHIP_SUNKEN_TEXTURE_COUNT
			- battleShipGeneralNS::SHIP_SUNKEN_SHADOW_TEXTURE_COUNT;
		for (int i = 0; i < updateSize; i++)
		{
			m_vEntity[i].second->update(frameTime);
		}
	}

	//======================================
	// Ship Destroy Event Check
	//======================================
	if (m_fCurrentHealth <= 0)
	{
		m_bDestroy = true;
		m_bChangeSprite = updateRotate(frameTime);
		updateSprite(frameTime);
		if (m_bSukenStart == false)
		{
			m_bSukenStart = true;
			SOUNDMANAGER->play(m_strSukenSoundName, g_fSoundMasterVolume * g_fSoundEffectVolume);
		}
		return;
	}
	
	//======================================
	// When Ship is Included Fleet Update
	//======================================
	if (m_bIncludedFleet)
	{
		m_BattleShipUI_FleetMark.update(frameTime);

		if (m_bFlagShip)
		{
			//=============================================
			// Flag Ship Target Arrived Event 
			//  + Warning!!!! 
			//  + This Code Scope Not Working...
			//=============================================

			//if (m_bArrived)
			//{
			//	m_fTargetX = m_vEntity[0].second->getCenterX() + ((float)cos(m_fCurrentAngle) * m_fCurrentSpeed / 2);
			//	m_fTargetY = m_vEntity[0].second->getCenterY() + (-(float)sin(m_fCurrentAngle) * m_fCurrentSpeed / 2);
			//}
		}
		else
		{
			m_fTargetX = m_fFormationX = cos(m_fAngleFromFleet) * m_fDistanceFromFleet + m_pFlagShip->getCurrentCenterX();
			m_fTargetY = m_fFormationY = -sin(m_fAngleFromFleet) * m_fDistanceFromFleet + m_pFlagShip->getCurrentCenterY();
		}
	}
	else
	{
		// if Arrived TargetPos(x,y) Then, Set TargetPos(_currentX + (angle * speed), _currentY + (angle * speed))
		if (m_bArrived)
		{
			m_fTargetX = m_vEntity[0].second->getCenterX() + ((float)cos(m_fCurrentAngle) * m_fCurrentSpeed / 2);
			m_fTargetY = m_vEntity[0].second->getCenterY() + (-(float)sin(m_fCurrentAngle) * m_fCurrentSpeed / 2);
		}
	}
	
	if (m_bDummy)
		return;

	//======================================================
	// Ship Tail Update
	//  + Update Only Active Tail Effect
	//======================================================
	for (auto iter : m_vTailEffect)
	{
		iter.update(frameTime);
	}
	//======================================================
	// Not Using This Indicator - Selecting UI
	//======================================================
	//m_BattleShipUI_Selected.update(frameTime);
	
	//======================================================
	// Ship UI Update
	//======================================================
	m_BattleShipUI_State.update(frameTime);
	m_BattleShipUI_FleetMark.update(frameTime);
	m_BattleShipUI_Indicator.update(frameTime);

	//======================================================
	// Update All Tag Data
	//  + Rader Data
	//  + Touch Data
	//  + Collision Data
	//  + Evasion Data
	//======================================================
	auto shipCenterX = m_vEntity[0].second->getCenterX();
	auto shipCenterY = m_vEntity[0].second->getCenterY();
	updateTagDataPos(shipCenterX, shipCenterY);

	//======================================================
	// Ship Rotate Update
	//  + Calculate Angle & Each Rotation - Sprite Number
	//======================================================
	m_bChangeSprite = updateRotate(frameTime);

	//======================================================
	// Update Current Sprite Texture
	//======================================================
	updateSprite(frameTime);

	//======================================================
	// Update Repairing
	//  + Current Health += Repair Speed
	//======================================================
	updateRepair(frameTime);

	//======================================================
	// Ship Engine Update
	//======================================================
	updateEngine(frameTime);

	//======================================================
	// Ship Movement Update
	//======================================================
	updateMovement(frameTime);

	//======================================================
	// Ship Turret Update
	//  + Targetting Update
	//  + Firing Order
	//======================================================
	updateTurret(frameTime);

	//======================================================
	// Each Sound Update
	//  + UnDetected Sound
	//  + Attack Sound
	//======================================================
	updateUndetectedSound(frameTime);
	updateAttackedSound(frameTime);
}

void CBattle_Ship::render()
{
	if (m_bInitialized == false)
		return;

	if (m_bSunkenComplete)
		return;

	float currentX = m_vEntity[0].second->getCenter()->x;
	float currentY = m_vEntity[0].second->getCenter()->y;
	float objWidth = m_vEntity[0].second->getWidth();
	float objHeight = m_vEntity[0].second->getHeight();
	if (MyUtil::getObjInScreen(currentX, currentY, objWidth, objHeight, g_fScreenWidth, g_fScreenHeight) == false)
		return;

	// Draw Dummy Ship For Dummy Ship UI
	if (m_bDummy)
	{
		m_pGraphics->spriteBegin();

		if (m_bPlayerShip)
		{
			int updateSize = m_vEntity.size()
				- battleShipGeneralNS::SHIP_SUNKEN_TEXTURE_COUNT
				- battleShipGeneralNS::SHIP_SUNKEN_SHADOW_TEXTURE_COUNT;
			for (int i = 0; i < updateSize; i++)
			{
				//======================================================
				// WAVE RENDERING CONTINUE -------------- WARNING
				// WAVE RENDERING CONTINUE -------------- WARNING
				// WAVE RENDERING CONTINUE -------------- WARNING
				//======================================================
				if (i == m_nSpriteWaveStart)
					continue;

				m_vEntity[i].second->draw();
			}
			m_pGraphics->spriteEnd();
			return;
		}
	}

	if (m_bActive == false)
		return;
	
	//======================================================
	// ShipUI Rendering - Under Ship Entity
	//======================================================
	if (m_bDestroy == false)
	{
		if (m_bSelected)
		{
			// Not Using This Indicator - Selecting UI
			//m_BattleShipUI_Selected.render();
			m_BattleShipUI_Indicator.render();
		}

		if(m_bDetected)
			m_BattleShipUI_State.render();
	}

	//======================================================
	// Ship Tail Effect Rendering
	//======================================================
	for (auto iter : m_vTailEffect)
	{
		iter.render();
	}

	//======================================================
	// General Entity Rendering
	//======================================================	
	m_pGraphics->spriteBegin();
	if (m_bDestroy == true)
	{
		// When Ship Destroyed
		int renderPos = m_vEntity.size()
			- battleShipGeneralNS::SHIP_SUNKEN_TEXTURE_COUNT
			- battleShipGeneralNS::SHIP_SUNKEN_SHADOW_TEXTURE_COUNT;
		for (; renderPos < m_vEntity.size(); renderPos++)
		{
			m_vEntity[renderPos].second->draw();
		}
		return;
	}
	else
	{
		if (m_bPlayerShip)
		{
			// When Ship Alive
			int updateSize = m_vEntity.size()
				- battleShipGeneralNS::SHIP_SUNKEN_TEXTURE_COUNT
				- battleShipGeneralNS::SHIP_SUNKEN_SHADOW_TEXTURE_COUNT;
			for (int i = 0; i < updateSize; i++)
			{
				//======================================================
				// WAVE RENDERING CONTINUE -------------- WARNING
				// WAVE RENDERING CONTINUE -------------- WARNING
				// WAVE RENDERING CONTINUE -------------- WARNING
				//======================================================
				if (i == m_nSpriteWaveStart)
					continue;

				m_vEntity[i].second->draw();
			}
		}
		else
		{
			if (m_bDetected)
			{
				// When Ship Alive
				int updateSize = m_vEntity.size()
					- battleShipGeneralNS::SHIP_SUNKEN_TEXTURE_COUNT
					- battleShipGeneralNS::SHIP_SUNKEN_SHADOW_TEXTURE_COUNT;
				for (int i = 0; i < updateSize; i++)
				{
					//======================================================
					// WAVE RENDERING CONTINUE -------------- WARNING
					// WAVE RENDERING CONTINUE -------------- WARNING
					// WAVE RENDERING CONTINUE -------------- WARNING
					//======================================================
					if (i == m_nSpriteWaveStart)
						continue;

					m_vEntity[i].second->draw();
				}
			}
		}
	}

	//======================================================
	// ShipUI Rendering - Above Ship Entity
	//======================================================
	if (m_bIncludedFleet)
	{
		m_BattleShipUI_FleetMark.draw();
	}
	m_pGraphics->spriteEnd();

	//======================================================
	// ShipUI Debug Mode Rendering
	//======================================================
	if (m_bDebug)
	{
		// Draw Fleet Line To FlagShip
		if (m_bIncludedFleet)
			m_pGraphics->drawLine(currentX, currentY, m_pFlagShip->getCurrentCenterX(), m_pFlagShip->getCurrentCenterY());

		// Draw Touch Data Circle	-- BROWN COLOR
		m_pGraphics->drawCircle(m_stUnitTouch.x, m_stUnitTouch.y, m_stUnitTouch.radius, 1.0f, graphicsNS::BROWN);

		// Draw Collision Circle	-- GREEN COLOR
		m_pGraphics->drawCircle(m_stUnitCollision.x, m_stUnitCollision.y, m_stUnitCollision.radius, 1.0f, graphicsNS::GREEN);

		// Draw Rader Range Circle	-- BLUE COLOR
		m_pGraphics->drawCircle(m_stRader.x, m_stRader.y, m_stRader.radius, 1.0f, graphicsNS::BLUE);

		// Draw Evasion Circle		-- RED COLOR
		m_pGraphics->drawCircle(m_stEvasion.x, m_stEvasion.y, m_stEvasion.radius, 1.0f, graphicsNS::RED);

		// Draw Line Current(x,y) To Target(x,y)
		m_pGraphics->drawLine(currentX, currentY, m_fTargetX, m_fTargetY, 1.0f, graphicsNS::RED);
	}
}

void CBattle_Ship::ai()
{
}

void CBattle_Ship::collision()
{
	if (m_bActive == false)
		return;

	if (m_bDestroy)
		return;

	if (m_bUnitToolMode)
	{
#pragma region UNIT Tool Mode - Ship vs Ship Enemy Targetting Detection Function
		//====================================================
		// Ship Rader Collision Check
		//  + Enemy Ship Detection
		//  + Aim At Fire
		//====================================================
		auto enemyShips = m_pUnitControlSystem->getComputerShips();
		if (m_bPlayerShip == false)
			enemyShips = m_pUnitControlSystem->getPlayerShips();

		for (auto iter : enemyShips)
		{
			if (iter->getShipActive() == false)
				continue;

			if (iter->getShipDestroy())
				continue;

			auto enemyShipX = iter->getShipCollision().x;
			auto enemyShipY = iter->getShipCollision().y;
			auto enemyShipRad = iter->getShipCollision().radius;
			auto raderX = this->getShipRaderCollision().x;
			auto raderY = this->getShipRaderCollision().y;
			auto raderRad = this->getShipRaderCollision().radius;

			if (MyUtil::circleIncircle(raderX, raderY, raderRad, enemyShipX, enemyShipY, enemyShipRad))
			{
				auto targetEvasionX = iter->getShipEvasionCollision().x;
				auto targetEvasionY = iter->getShipEvasionCollision().y;
				auto targetEvasionRad = iter->getShipEvasionCollision().radius;

				POINT target = RANDOM_MAKER->GetPtInCircle(targetEvasionX, targetEvasionY, targetEvasionRad);

				for (auto turretIter : m_vTurret)
				{
					if (turretIter->IsReloading())
						continue;

					turretIter->FireInUnitTool(target.x, target.y);
				}
				break;
			}
		}
#pragma endregion
		return;
	}
	
	// Collision Vector2
	VECTOR2 collisionVector;

	//====================================================
	// Ship vs Island or Objects Collision Check
	//====================================================
#pragma region Ship vs Island or Object Collision Detect
	auto collisionBoxes = m_pBattleMapSystem->getCollisionAreas();
	auto centerX = m_stUnitCollision.x;
	auto centerY = m_stUnitCollision.y;
	auto radius = m_stUnitCollision.radius;
	
	for (auto iter : collisionBoxes)
	{
		auto boxX = iter->getCenterX();
		auto boxY = iter->getCenterY();
		auto boxRad = iter->getCollisionWidth() / 2;
				
		if (MyUtil::circleIncircle(centerX, centerY, radius, boxX, boxY, boxRad) == false)
			continue;

		//====================================================
		// Check Count = 
		//  + Unit[Ship] Texture Top Count
		//  + Unit[Ship] Texture Body Count
		//  + Unit[Ship] Texture Bottom Count
		//====================================================
		int checkCount = m_nSpriteTopCount + m_nSpriteBodyCount + m_nSpriteBottomCount;

		for (int i = 0; i < checkCount; i++)
		{
			m_bIntersect = iter->collidesWith(*m_vEntity[i].second, collisionVector);

			if (m_bIntersect)
			{
				m_fCurrentSpeed = m_fCurrentSpeed * (95 / 100);
				break;
			}
			
		}
	}
#pragma endregion
#pragma region Ship_vs_Ship Collision Check
	//====================================================
	// Ship vs Ship Collision Check
	//  + Not Implemented...
	//====================================================

	//auto playerShips = m_pBattleUnitSystem->getPlayerShips();
	//for (auto iter : playerShips)
	//{
	//	auto shipParts = iter->getShipEntity();
	//	for (auto partsIter : shipParts)
	//	{
	//	}
	//}
#pragma endregion

#pragma region EnemyShip Detection & Fire
	//====================================================
	// Ship Rader Collision Check
	//  + Enemy Ship Detection (-- This Function Moved To UnitSystem --)
	//  + Aim At Fire
	//====================================================
	auto enemyShips = m_pBattleUnitSystem->getComputerShips();
	if (m_bPlayerShip == false)
		enemyShips = m_pBattleUnitSystem->getPlayerShips();
	
	//====================================================
	// Automatic Turret Aiming
	//====================================================
	for (auto iter : enemyShips)
	{
		if (iter->getShipActive() == false)
			continue;
		
		if (iter->getShipDestroy())
			continue;

		if (iter->getDummyShip())
			continue;

		auto enemyShipX = iter->getShipCollision().x;
		auto enemyShipY = iter->getShipCollision().y;
		auto enemyShipRad = iter->getShipCollision().radius;
		auto raderX = this->getShipRaderCollision().x;
		auto raderY = this->getShipRaderCollision().y;
		auto raderRad = this->getShipRaderCollision().radius;
				
		if (MyUtil::circleIncircle(raderX, raderY, raderRad, enemyShipX, enemyShipY, enemyShipRad))
		{
			auto targetEvasionX = iter->getShipEvasionCollision().x;
			auto targetEvasionY = iter->getShipEvasionCollision().y;
			auto targetEvasionRad = iter->getShipEvasionCollision().radius;

			POINT target = RANDOM_MAKER->GetPtInCircle(targetEvasionX, targetEvasionY, targetEvasionRad);

			if (m_bAutoGunOnOff)
			{
				for (auto turretIter : m_vTurret)
				{
					if (turretIter->IsReloading())
						continue;

					turretIter->Fire(target.x, target.y);
				}
			}

			break;
		}
	}
#pragma endregion
}

void CBattle_Ship::updateSprite(float frameTime)
{
	if (m_bChangeSprite == false)
		return;
	
	updateShipSprite();
	updateWaveSprite();

	if(m_bDestroy)
		updateSunkenSprite(frameTime);

	//===================================================================
	// Ship Sprite Number Recognize & Setup Sprite Keys - Start
	// Ship Sprite Top Key
	//===================================================================
#pragma region SETUP_SPRITE_TEXTURE_KEY
	for (int i = 0; i < m_nSpriteTopCount; i++)
	{
		if (m_nSpriteShipTopNum < 10)
			m_vSpriteTopKey[i] = m_strTextureKey + "_" + battleShipTextureNS::TEXTURE_KEY_TOP + std::to_string(i) + "_" + "0" + std::to_string(m_nSpriteShipTopNum);
		else
			m_vSpriteTopKey[i] = m_strTextureKey + "_" + battleShipTextureNS::TEXTURE_KEY_TOP + std::to_string(i) + "_" + std::to_string(m_nSpriteShipTopNum);
	}
	// Ship Sprite Body Key
	for (int i = 0; i < m_nSpriteBodyCount; i++)
	{
		if (m_nSpriteShipBodyNum < 10)
			m_vSpriteBodyKey[i] = m_strTextureKey + "_" + battleShipTextureNS::TEXTURE_KEY_BODY + std::to_string(i) + "_" + "0" + std::to_string(m_nSpriteShipBodyNum);
		else
			m_vSpriteBodyKey[i] = m_strTextureKey + "_" + battleShipTextureNS::TEXTURE_KEY_BODY + std::to_string(i) + "_" + std::to_string(m_nSpriteShipBodyNum);
	}
	// Ship Sprite Bottom Key
	for (int i = 0; i < m_nSpriteBottomCount; i++)
	{
		if (m_nSpriteShipBottomNum < 10)
			m_vSpriteBottomKey[i] = m_strTextureKey + "_" + battleShipTextureNS::TEXTURE_KEY_BOTTOM + std::to_string(i) + "_" + "0" + std::to_string(m_nSpriteShipBottomNum);
		else
			m_vSpriteBottomKey[i] = m_strTextureKey + "_" + battleShipTextureNS::TEXTURE_KEY_BOTTOM + std::to_string(i) + "_" + std::to_string(m_nSpriteShipBottomNum);
	}
	// Ship Sprite Shadow Key
	if (m_nSpriteShipShadowNum < 10)
		m_strSpriteShadowKey = m_strTextureKey + "_" + battleShipTextureNS::TEXTURE_KEY_SHADOW + "0" + std::to_string(m_nSpriteShipShadowNum);
	else
		m_strSpriteShadowKey = m_strTextureKey + "_" + battleShipTextureNS::TEXTURE_KEY_SHADOW + std::to_string(m_nSpriteShipShadowNum);
	// Ship Sprite Wave Key
	if(m_nSpriteShipWaveNum < 10)
		m_strSpriteWaveKey = m_strSpriteWaveKey = m_strTextureKey + "_" + battleShipTextureNS::TEXTURE_KEY_WAVE + "0" + std::to_string(m_nSpriteShipWaveNum);
	else
		m_strSpriteWaveKey = m_strSpriteWaveKey = m_strTextureKey + "_" + battleShipTextureNS::TEXTURE_KEY_WAVE + std::to_string(m_nSpriteShipWaveNum);
	// Ship Sprite Sunken Key
	if(m_nSpriteSunkenNum < 10)
		m_strSpriteSunkenKey = m_strTextureKey + "_" + battleShipTextureNS::TEXTURE_KEY_SUNKEN + "0" + std::to_string(m_nSpriteSunkenNum);
	else
		m_strSpriteSunkenKey = m_strTextureKey + "_" + battleShipTextureNS::TEXTURE_KEY_SUNKEN + std::to_string(m_nSpriteSunkenNum);
	// Ship Sprite Sunken Shadow Key
	if(m_nSpriteSunkenShadowNum < 10)
		m_strSpriteSunkenShadowKey = m_strTextureKey + "_" + battleShipTextureNS::TEXTURE_KEY_SUNKEN_SHADOW + "0" + std::to_string(m_nSpriteSunkenShadowNum);
	else
		m_strSpriteSunkenShadowKey = m_strTextureKey + "_" + battleShipTextureNS::TEXTURE_KEY_SUNKEN_SHADOW + std::to_string(m_nSpriteSunkenShadowNum);
#pragma endregion

	//===================================================================
	// std::string Keys Setup to Result std::vector<std::string>
	//===================================================================
#pragma region EMPLACE TEXTURE KEY
	std::vector<std::string> totalResult;
	for (auto iter : m_vSpriteTopKey)
	{
		totalResult.emplace_back(iter);
	}
	for (auto iter : m_vSpriteBodyKey)
	{
		totalResult.emplace_back(iter);
	}
	for (auto iter : m_vSpriteBottomKey)
	{
		totalResult.emplace_back(iter);
	}
	totalResult.emplace_back(m_strSpriteShadowKey);
	totalResult.emplace_back(m_strSpriteWaveKey);
	totalResult.emplace_back(m_strSpriteSunkenKey);
	totalResult.emplace_back(m_strSpriteSunkenShadowKey);
#pragma endregion

	// Entity TextureManager Change Texture [Update: Sprite] - Start
	// Each Frame Updated Sprite Texture
	for (int i = 0; i < m_vEntity.size(); i++)
	{
		m_vEntity[i].second->setTextureManager(IMAGEMANAGER->getTexture(totalResult[i]));
	}
	// End - Entity TextureManager Change Texture
}

void CBattle_Ship::updateShipSprite()
{
	float degreeAngle = abs(D3DXToDegree(m_fCurrentAngle));
	
	// Ship Top-Body-Bottom-Shadow Sprite Update
	if (degreeAngle >= 0 && degreeAngle <= 90)
	{
		m_nSpriteShipTopNum = (int)(degreeAngle / 10.f) - 9;
		m_nSpriteShipBodyNum = (int)(degreeAngle / 10.f) - 9;
		m_nSpriteShipBottomNum = (int)(degreeAngle / 10.f) - 9;
		m_nSpriteShipShadowNum = (int)(degreeAngle / 10.f) - 9;
		if (m_nSpriteShipBodyNum < 0)
		{
			m_nSpriteShipTopNum += 35;
			m_nSpriteShipBodyNum += 35;
			m_nSpriteShipBottomNum += 35;
			m_nSpriteShipShadowNum += 35;
		}
	}
	else
	{
		m_nSpriteShipTopNum = (int)(degreeAngle - D3DXToDegree(D3DX_PI / 2)) / 10;
		m_nSpriteShipBodyNum = (int)(degreeAngle - D3DXToDegree(D3DX_PI / 2)) / 10;
		m_nSpriteShipBottomNum = (int)(degreeAngle - D3DXToDegree(D3DX_PI / 2)) / 10;
		m_nSpriteShipShadowNum = (int)(degreeAngle - D3DXToDegree(D3DX_PI / 2)) / 10;
		if (m_nSpriteShipBodyNum > 35)
		{
			m_nSpriteShipTopNum -= 36;
			m_nSpriteShipBodyNum -= 36;
			m_nSpriteShipBottomNum -= 36;
			m_nSpriteShipShadowNum -= 36;
		}
	}
}

void CBattle_Ship::updateWaveSprite()
{
	float degreeAngle = abs(D3DXToDegree(m_fCurrentAngle));

	// Ship - Wave Sprite Update
	if (degreeAngle >= 0 && degreeAngle <= 90)
	{
		m_nSpriteShipWaveRotateNum = (int)(degreeAngle / 10.f) - 9;
		if (m_nSpriteShipWaveRotateNum < 0)
		{
			m_nSpriteShipWaveRotateNum += 35;
		}
	}
	else
	{
		m_nSpriteShipWaveRotateNum = (int)(degreeAngle - D3DXToDegree(D3DX_PI / 2)) / 10;
	}

	if (m_nSpriteShipWaveNum >= 10)
		m_nSpriteShipWaveNum = 0;
	m_nSpriteShipWaveNum++;
}

void CBattle_Ship::updateSunkenSprite(float frameTime)
{
	if (m_bSunkenComplete)
		return;
	
	if (m_nSpriteSunkenNum % 10 < 4)
	{
		if (m_fSunkenDeltaTime >= battleShipGeneralNS::SHIP_SUNKEN_SPRITE_CHANGE_TIME_EARLY)
		{
			m_fSunkenDeltaTime = 0.f;
			m_nSpriteSunkenNum++;
			m_nSpriteSunkenShadowNum++;
		}
		else
		{
			m_fSunkenDeltaTime += frameTime;
		}
	}
	else
	{
		if (m_fSunkenDeltaTime >= battleShipGeneralNS::SHIP_SUNKEN_SPRITE_CHANGE_TIME_LATE)
		{
			m_fSunkenDeltaTime = 0.f;
			m_nSpriteSunkenNum++;
			m_nSpriteSunkenShadowNum++;
			if (m_nSpriteSunkenNum >= ((m_nSpriteSunkenNum / 10) + 1) * battleShipTextureNS::SHIP_SUNKEN_MAX_FRAME - 1)
				m_bSunkenComplete = true;
		}
		else
		{
			m_fSunkenDeltaTime += frameTime;
		}
	}

	
}

void CBattle_Ship::updateTurret(float frameTime)
{
	if (m_bActive == false)
		return;

	if (m_bDestroy)
		return;

	for (auto iter : m_vTurret)
	{
		iter->update(frameTime);
	}
}

void CBattle_Ship::updateUndetectedSound(float frameTime)
{
	if (m_bDetectedSound)
	{
		if (m_bDetected == false)
		{
			m_fUnDetectedTime += frameTime;

			if (m_fUnDetectedTime > battleShipGeneralNS::UNDETECTED_SOUND_TIME)
			{
				m_fUnDetectedTime = 0.f;
				m_bDetectedSound = false;
			}
		}
	}
}

void CBattle_Ship::updateAttackedSound(float frameTime)
{
	if (m_bAttackedSound)
	{
		m_fUnattackedTime += frameTime;
		if (m_fUnattackedTime > battleShipGeneralNS::UNATTACKED_SOUND_TIME)
		{
			m_fUnattackedTime = 0.f;
			m_bAttackedSound = false;
		}
	}
}

void CBattle_Ship::playSoundDamagedOperator()
{
	if (SOUNDMANAGER->isPlaySound("ship_damaged") == false)
	{
		SOUNDMANAGER->play("ship_damaged", g_fSoundMasterVolume * g_fSoundEffectVolume);
	}
}

void CBattle_Ship::moveX(float fDistance)
{
	for (auto iter : m_vEntity)
	{
		iter.second->Image::moveX(fDistance);
	}

	for (auto iter : m_vTailEffect)
	{
		iter.moveX(fDistance);
	}

	m_fTargetX += fDistance;

	auto shipCenterX = m_vEntity[0].second->getCenterX();
	auto shipCenterY = m_vEntity[0].second->getCenterY();
	updateTagDataPos(shipCenterX, shipCenterY);

	m_BattleShipUI_Selected.moveX(fDistance);
	m_BattleShipUI_FleetMark.moveX(fDistance);
	m_BattleShipUI_State.moveX(fDistance);
	m_BattleShipUI_Indicator.moveX(fDistance);
}

void CBattle_Ship::moveY(float fDistance)
{
	for (auto iter : m_vEntity)
	{
		iter.second->Image::moveY(fDistance);
	}

	for (auto iter : m_vTailEffect)
	{
		iter.moveY(fDistance);
	}

	m_fTargetY += fDistance;

	auto shipCenterX = m_vEntity[0].second->getCenterX();
	auto shipCenterY = m_vEntity[0].second->getCenterY();
	updateTagDataPos(shipCenterX, shipCenterY);

	m_BattleShipUI_Selected.moveY(fDistance);
	m_BattleShipUI_FleetMark.moveY(fDistance);
	m_BattleShipUI_State.moveY(fDistance);
	m_BattleShipUI_Indicator.moveY(fDistance);
}

void CBattle_Ship::HitDamage(float damage)
{
	m_fCurrentHealth -= damage;
	m_BattleShipUI_State.setupProgress(m_fCurrentHealth, m_fMaxHealth);

	if (m_bUnitToolMode == false)
	{
		CBattle_DamageDigit* pDigit = new CBattle_DamageDigit;
		DIGIT_TYPE digitType;
		if (damage < 300)
		{
			digitType = DIGIT_TYPE::DIGIT_TYPE_BLUE;
		}
		else if (damage < 500)
		{
			digitType = DIGIT_TYPE::DIGIT_TYPE_WHITE;
		}
		else
		{
			digitType = DIGIT_TYPE::DIGIT_TYPE_RED;
		}
		float centerX = m_vEntity[0].second->getCenterX();
		float centerY = m_vEntity[0].second->getCenterY();
		pDigit->initialize(m_pGraphics, damage, digitType, centerX, centerY);
		m_pBattleUnitSystem->addDamageDigit(pDigit);

		if (m_bPlayerShip)
		{
			m_pBattleUnitSystem->addDamageScoreToComputer(damage);
		}
		else
		{
			m_pBattleUnitSystem->addDamageScoreToPlayer(damage);
		}
	}
		
	m_bAttacked = true;
	if (m_bAttackedSound == false)
	{
		m_bAttackedSound = true;

		if (m_bSelected)
		{
			playSoundDamagedOperator();
		}
	}
}

void CBattle_Ship::takeRepairBuf(bool bTakeOnOff, float bufSpeed)
{
	if (bTakeOnOff)
	{
		m_fRepairSpeed = m_fRepairSpeedOriginal + bufSpeed;
	}
	else
		m_fRepairSpeed = m_fRepairSpeedOriginal;
}

void CBattle_Ship::updateMovement(float frameTime)
{
	if (m_bDestroy)
		return;

	for (auto iter : m_vTailEffect)
	{
		if (iter.getActive() == true)
			continue;

		iter.setActive();
		break;
	}

	VECTOR2 CurrentPos = *m_vEntity[0].second->getCenter();
	float interRadius = m_vEntity[0].second->getHeight() / 2;
	float calDistance = MyUtil::getDistance(CurrentPos.x, CurrentPos.y, m_fTargetX, m_fTargetY);
	float sumDistance = interRadius + m_stUnitTouch.radius;
	if (calDistance < sumDistance)
		m_bArrived = true;
	else
		m_bArrived = false;

	for (auto iter : m_vEntity)
	{
		iter.second->Image::moveX((float)cos(m_fCurrentAngle) * m_fCurrentSpeed * frameTime);
		iter.second->Image::moveY(-(float)sin(m_fCurrentAngle) * m_fCurrentSpeed * frameTime);
	}
	m_BattleShipUI_Selected.moveX((float)cos(m_fCurrentAngle) * m_fCurrentSpeed * frameTime);
	m_BattleShipUI_Selected.moveY(-(float)sin(m_fCurrentAngle) * m_fCurrentSpeed * frameTime);


	if (m_bUnitToolMode == false)
	{
		if (CurrentPos.x <= m_pBattleMapSystem->getMapBorderLeft())
		{
			this->setTargetX(CurrentPos.x += battleShipGeneralNS::BATTLEMAP_OUTLINE_REVERSING_DISTANCE);
		}
		else if (CurrentPos.x > m_pBattleMapSystem->getMapBorderRight())
		{
			this->setTargetX(CurrentPos.x -= battleShipGeneralNS::BATTLEMAP_OUTLINE_REVERSING_DISTANCE);
		}
	
		if (CurrentPos.y <= m_pBattleMapSystem->getMapBorderTop())
		{
			this->setTargetX(CurrentPos.y += battleShipGeneralNS::BATTLEMAP_OUTLINE_REVERSING_DISTANCE);
		}
		else if (CurrentPos.y > m_pBattleMapSystem->getMapBorderBottom())
		{
			this->setTargetX(CurrentPos.y -= battleShipGeneralNS::BATTLEMAP_OUTLINE_REVERSING_DISTANCE);
		}
	}
}

void CBattle_Ship::updateEngine(float frameTime)
{
	if (m_bIntersect)
	{
		if (m_fCurrentSpeed > 0)
		{
			m_fCurrentSpeed -= m_fAccelateSpeed * frameTime;
		}
	}

	if (m_bArrived)
	{
		if (m_bFixedEngine)
		{
			m_fCurrentSpeed += m_fAccelateSpeed * frameTime;
		}
		else
		{
			if (m_fCurrentSpeed > 0.f)
				m_fCurrentSpeed -= m_fAccelateSpeed * frameTime;
		}
	}
	else
	{
		m_fCurrentSpeed += m_fAccelateSpeed * frameTime;
	}
	
	if (m_fCurrentSpeed < 0.f)
		m_fCurrentSpeed = 0.f;

	if (m_fCurrentSpeed > m_fMaxSpeed)
		m_fCurrentSpeed = m_fMaxSpeed;
}

bool CBattle_Ship::updateRotate(float frameTime)
{
	if (m_bDestroy == false)
	{
		float degreeAngle = abs(D3DXToDegree(m_fCurrentAngle));
		if (degreeAngle >= 0 && degreeAngle < 40)
		{
			m_nSpriteSunkenNum = 70;
			m_nSpriteSunkenShadowNum = 70;
		}
		else if (degreeAngle >= 40 && degreeAngle < 80)
		{
			m_nSpriteSunkenNum = 80;
			m_nSpriteSunkenShadowNum = 80;
		}
		else if (degreeAngle >= 80 && degreeAngle < 120)
		{
			m_nSpriteSunkenNum = 0;
			m_nSpriteSunkenShadowNum = 0;
		}
		else if (degreeAngle >= 120 && degreeAngle < 160)
		{
			m_nSpriteSunkenNum = 10;
			m_nSpriteSunkenShadowNum = 10;
		}
		else if (degreeAngle >= 160 && degreeAngle < 200)
		{
			m_nSpriteSunkenNum = 20;
			m_nSpriteSunkenShadowNum = 20;
		}
		else if (degreeAngle >= 200 && degreeAngle < 240)
		{
			m_nSpriteSunkenNum = 30;
			m_nSpriteSunkenShadowNum = 30;
		}
		else if (degreeAngle >= 240 && degreeAngle < 280)
		{
			m_nSpriteSunkenNum = 40;
			m_nSpriteSunkenShadowNum = 40;
		}
		else if (degreeAngle >= 280 && degreeAngle < 320)
		{
			m_nSpriteSunkenNum = 50;
			m_nSpriteSunkenShadowNum = 50;
		}
		else if (degreeAngle >= 320 && degreeAngle < 360)
		{
			m_nSpriteSunkenNum = 60;
			m_nSpriteSunkenShadowNum = 60;
		}
	}

	if (m_bDestroy)
		return true;
	
	VECTOR2 CurrentPos = *m_vEntity[0].second->getCenter();
	m_fTargetAngle = MyUtil::getAngle(CurrentPos.x, CurrentPos.y, m_fTargetX, m_fTargetY);

	if (fabsf(m_fCurrentAngle) > fabsf(D3DX_PI * 2))
		m_fCurrentAngle = 0;
	
	if (m_fCurrentAngle < 0)
		m_fCurrentAngle += D3DX_PI * 2;

	float fChanging = fabsf(m_fCurrentAngle - m_fTargetAngle);
	if (fChanging < m_fRotateSpeed * frameTime)
		return false;

	switch ((int)(m_fCurrentAngle / (D3DX_PI / 2)))
	{
	case (int)QUDRANT_TYPE::QUDRANT_RIGHT_TOP : // m_fCurrentAngle : _QUDRANT_RIGHT_TOP
		switch ((int)(m_fTargetAngle / (D3DX_PI / 2)))
		{
		case (int)QUDRANT_TYPE::QUDRANT_RIGHT_TOP:
		case (int)QUDRANT_TYPE::QUDRANT_LEFT_TOP:
			if (m_fCurrentAngle > m_fTargetAngle)
				m_fCurrentAngle -= m_fRotateSpeed * frameTime;
			else
				m_fCurrentAngle += m_fRotateSpeed * frameTime;
			break;
		case (int)QUDRANT_TYPE::QUDRANT_LEFT_BOTTOM:
			if((m_fTargetAngle - m_fCurrentAngle) >= (D3DX_PI))
				m_fCurrentAngle -= m_fRotateSpeed * frameTime;
			else
				m_fCurrentAngle += m_fRotateSpeed * frameTime;
			break;
		case (int)QUDRANT_TYPE::QUDRANT_RIGHT_BOTTOM:
			m_fCurrentAngle -= m_fRotateSpeed * frameTime;
			break;
		}
		break;
	case (int)QUDRANT_TYPE::QUDRANT_LEFT_TOP:
		switch ((int)(m_fTargetAngle / (D3DX_PI / 2)))
		{
		case (int)QUDRANT_TYPE::QUDRANT_RIGHT_TOP:
		case (int)QUDRANT_TYPE::QUDRANT_LEFT_TOP:
		case (int)QUDRANT_TYPE::QUDRANT_LEFT_BOTTOM:
			if (m_fCurrentAngle > m_fTargetAngle)
				m_fCurrentAngle -= m_fRotateSpeed * frameTime;
			else
				m_fCurrentAngle += m_fRotateSpeed * frameTime;
			break;
		case (int)QUDRANT_TYPE::QUDRANT_RIGHT_BOTTOM:
			if (m_fTargetAngle - m_fCurrentAngle >= (D3DX_PI))
				m_fCurrentAngle -= m_fRotateSpeed * frameTime;
			else
				m_fCurrentAngle += m_fRotateSpeed * frameTime;
			break;
		}
		break;
	case (int)QUDRANT_TYPE::QUDRANT_LEFT_BOTTOM:
		switch ((int)(m_fTargetAngle / (D3DX_PI / 2)))
		{
		case (int)QUDRANT_TYPE::QUDRANT_RIGHT_TOP:
			if (m_fCurrentAngle - m_fTargetAngle >= (D3DX_PI))
				m_fCurrentAngle += m_fRotateSpeed * frameTime;
			else
				m_fCurrentAngle -= m_fRotateSpeed * frameTime;
			break;
		case (int)QUDRANT_TYPE::QUDRANT_LEFT_TOP:
		case (int)QUDRANT_TYPE::QUDRANT_LEFT_BOTTOM:
		case (int)QUDRANT_TYPE::QUDRANT_RIGHT_BOTTOM:
			if (m_fCurrentAngle > m_fTargetAngle)
				m_fCurrentAngle -= m_fRotateSpeed * frameTime;
			else
				m_fCurrentAngle += m_fRotateSpeed * frameTime;
			break;
		}
		break;
	case (int)QUDRANT_TYPE::QUDRANT_RIGHT_BOTTOM:
		switch ((int)(m_fTargetAngle / (D3DX_PI / 2)))
		{
		case (int)QUDRANT_TYPE::QUDRANT_RIGHT_TOP:
			m_fCurrentAngle += m_fRotateSpeed * frameTime;
			break;
		case (int)QUDRANT_TYPE::QUDRANT_LEFT_TOP:
			if (m_fCurrentAngle - m_fTargetAngle >= (D3DX_PI))
				m_fCurrentAngle += m_fRotateSpeed * frameTime;
			else
				m_fCurrentAngle -= m_fRotateSpeed * frameTime;
			break;
		case (int)QUDRANT_TYPE::QUDRANT_LEFT_BOTTOM:
		case (int)QUDRANT_TYPE::QUDRANT_RIGHT_BOTTOM:
			if(m_fCurrentAngle > m_fTargetAngle)
				m_fCurrentAngle -= m_fRotateSpeed * frameTime;
			else
				m_fCurrentAngle += m_fRotateSpeed * frameTime;
			break;
		}
		break;
	}

	return true;
}

void CBattle_Ship::updateRepair(float frameTime)
{
	if (m_fCurrentHealth < m_fMaxHealth)
	{
		m_fCurrentHealth += m_fRepairSpeed * frameTime;
		m_BattleShipUI_State.setupProgress(m_fCurrentHealth, m_fMaxHealth);
	}
}

void CBattle_Ship::setupShipDataFormat(std::vector<std::string> vArray)
{
	if (vArray.size() < 0)
		return;

	int dataNumber = 0;
	
	m_nUnitID								= std::stoi(vArray[dataNumber]);
	m_strTextureKey							= vArray[++dataNumber];
	m_nSpriteTopCount						= std::stoi(vArray[++dataNumber]);
	m_nSpriteBodyCount						= std::stoi(vArray[++dataNumber]);
	m_nSpriteBottomCount					= std::stoi(vArray[++dataNumber]);
	m_strName								= vArray[++dataNumber];
	m_strShipType							= vArray[++dataNumber];
	m_fCurrentHealth = m_fMaxHealth			= std::stof(vArray[++dataNumber]);
	m_fRepairSpeedOriginal = m_fRepairSpeed	= std::stof(vArray[++dataNumber]);
	m_fRotateSpeed							= std::stof(vArray[++dataNumber]);
	m_fAccelateSpeed						= std::stof(vArray[++dataNumber]);
	m_fMaxSpeed								= std::stof(vArray[++dataNumber]);
	m_fRaderRange							= std::stof(vArray[++dataNumber]);
	m_nTurretCount							= std::stoi(vArray[++dataNumber]);
	m_strTurretID							= vArray[++dataNumber];
	m_nAirCraftCapacity						= std::stoi(vArray[++dataNumber]);
	m_fPerformance							= std::stof(vArray[++dataNumber]);
	m_nSailorCount							= std::stoi(vArray[++dataNumber]);
	m_nAntiAirTurrectCount					= std::stoi(vArray[++dataNumber]);
	m_fAntiAirRange							= std::stof(vArray[++dataNumber]);
	m_fAntiAirDamage						= std::stof(vArray[++dataNumber]);
	m_nCallPhase							= std::stoi(vArray[++dataNumber]);
	m_fMass									= std::stof(vArray[++dataNumber]);
	m_fEvasionRange							= std::stof(vArray[++dataNumber]);
	m_strShipRankMark						= vArray[++dataNumber];
	m_strSukenSoundName						= vArray[++dataNumber];
}

bool CBattle_Ship::setupEntity(Game * gamePtr, std::string strImageName, bool bPhysics)
{
	bool success = false;
	Entity* shipParts = new Entity;
	success = shipParts->initialize(gamePtr, 0, 0, 0, IMAGEMANAGER->getTexture(strImageName));
	shipParts->setCollisionType(entityNS::PIXEL_PERFECT);
	shipParts->setScale(battleShipGeneralNS::SHIP_ENTITY_TEXTURE_SCALE);
	if (m_bPlayerShip)
	{
		shipParts->setX(-99999);
		shipParts->setY(-99999);
	}
	else
	{
		shipParts->setX(100000);
		shipParts->setY(100000);
	}
	m_vEntity.emplace_back(bPhysics, shipParts);

	return success;
}
