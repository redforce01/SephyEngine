#include "stdafx.h"
#include "Battle_Ship.h"
#include "Battle_MapSystem.h"
#include "Battle_UnitSystem.h"

CBattle_Ship::CBattle_Ship()
{
	m_pBattleUnitSystem = nullptr;
	m_pBattleMapSystem = nullptr;
	//===========================================
	m_pGraphics = nullptr;
	m_pInput = nullptr;	
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
	m_bInitialized				= false;
	m_bActive					= false;
	m_bDestroy					= false;
	m_bDestroyAnimeComplete		= false;
	m_bChangeSprite				= false;
	m_bSelected					= false;
	m_bArrived					= true;
	m_bFixedEngine				= false;
	m_bFlagShip					= false;
	//===========================================	
	m_bDebug					= true;
	m_bDummy					= false;
	//===========================================
	ZeroMemory(&m_stUnitTouch, sizeof(m_stUnitTouch));
}


CBattle_Ship::~CBattle_Ship()
{
	for (auto iter : m_vEntity)
	{
		SAFE_DELETE(iter.second);
		SAFE_DELETE(iter);
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

		int shadowEntity = m_nSpriteTopCount + m_nSpriteBodyCount + m_nSpriteBottomCount;
		m_vEntity[shadowEntity].second->setColorFilter(SETCOLOR_ARGB(128, 19, 19, 19));

		int waveEntity = m_nSpriteTopCount + m_nSpriteBodyCount + m_nSpriteBottomCount + battleShipGeneralNS::SHIP_SHADOW_TEXTURE_COUNT;
		m_vEntity[waveEntity].second->setColorFilter(SETCOLOR_ARGB(192, 128, 128, 128));
		// End - Ship Entity Initialize
		//====================================================================
#pragma endregion	


		//====================================================================
		CBattle_Turret* tempTurret = new CBattle_Turret;


		m_vTurret.emplace_back(tempTurret);
		//====================================================================
		m_BattleUIShipSelected.initialize(m_pGraphics);
		m_BattleShipUI_FleetMark.initialize(m_pGraphics);
		m_BattleShipUI_FleetMark.setMaster(this);


		// WARNING - NOT USING YET!
		// WARNING - NOT USING YET!
		// WARNING - NOT USING YET!
		// WARNING - NOT USING YET!
		// WARNING - NOT USING YET!
		m_BattleUIShipIndicator.initialize(m_pGraphics, m_pInput, INDICATOR_TYPE::INDICATOR_BLUE);
		//====================================================================

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

	if (m_bSelected)
	{
		m_BattleUIShipSelected.update(frameTime);
	}

	updateRepair(frameTime);
	updateTouchData();
	updateCollisionData();

	m_bChangeSprite = updateRotate(frameTime);
	updateSprite();
	updateEngine(frameTime);
	updateMovement(frameTime);
}

void CBattle_Ship::render()
{
	if (m_bInitialized == false)
		return;

	// Draw Dummy Ship For Dummy Ship UI
	if (m_bDummy)
	{
		m_pGraphics->spriteBegin();
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

	if (m_bActive == false)
		return;

	if (m_bSelected)
	{
		m_BattleUIShipSelected.render();
	}

	float currentX = m_vEntity[0].second->getCenter()->x;
	float currentY = m_vEntity[0].second->getCenter()->y;
	float objWidth = m_vEntity[0].second->getWidth();
	float objHeight = m_vEntity[0].second->getHeight();
	if (MyUtil::getObjInScreen(currentX, currentY, objWidth, objHeight, g_fScreenWidth, g_fScreenHeight) == false)
		return;

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
	}
	else
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

	if (m_bIncludedFleet)
	{
		m_BattleShipUI_FleetMark.draw();
	}

	m_pGraphics->spriteEnd();

	if (m_bDebug)
	{
		// Draw Rader Range Circle
		if (m_bSelected)
			m_pGraphics->drawCircle(currentX, currentY, m_fRaderRange, 1.0f, graphicsNS::BLUE);

		// Draw Fleet Line To FlagShip
		if (m_bIncludedFleet)
			m_pGraphics->drawLine(currentX, currentY, m_pFlagShip->getCurrentCenterX(), m_pFlagShip->getCurrentCenterY());

		// Draw Touch Data Circle
		m_pGraphics->drawCircle(currentX, currentY, m_vEntity[0].second->getHeight() / 2, 1.0f, graphicsNS::BROWN);

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

	VECTOR2 collisionVector;

	//====================================================
	// Ship vs Island or Objects Collision Check
	//====================================================

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

	//====================================================
	// Ship vs Ship Collision Check
	//====================================================
#pragma region Ship_vs_Ship Collision Check
	//auto playerShips = m_pBattleUnitSystem->getPlayerShips();
	//for (auto iter : playerShips)
	//{
	//	auto shipParts = iter->getShipEntity();
	//	for (auto partsIter : shipParts)
	//	{
	//	}
	//}
#pragma endregion


	//====================================================
	// Ship Rader Collision Check
	//====================================================
	m_fRaderRange;


}

void CBattle_Ship::updateSprite()
{	
	if (m_bChangeSprite == false)
		return;

	updateShipSprite();
	updateWaveSprite();
	updateSunkenSprite();

	//===================================================================
	// Ship Sprite Number Recognize & Setup Sprite Keys - Start
	// Ship Sprite Top Key
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
	// End - Ship Sprite Number Recognize & Setup Sprite Keys
	//===================================================================
	// std::string Keys Setup to Result std::vector<std::string> - Start
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
	// End - std::string Keys Setup to Result std::vector<std::string>
	//===================================================================
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

	if (m_nSpriteShipWaveNum > 9)
		m_nSpriteShipWaveNum = 0;
	m_nSpriteShipWaveNum++;
}

void CBattle_Ship::updateSunkenSprite()
{

}

void CBattle_Ship::moveX(float fDistance)
{
	for (auto iter : m_vEntity)
	{
		iter.second->Image::moveX(fDistance);
	}

	m_fTargetX += fDistance;
	m_BattleUIShipSelected.moveX(fDistance);
	m_BattleShipUI_FleetMark.moveX(fDistance);
}

void CBattle_Ship::moveY(float fDistance)
{
	for (auto iter : m_vEntity)
	{
		iter.second->Image::moveY(fDistance);
	}

	m_fTargetY += fDistance;
	m_BattleUIShipSelected.moveY(fDistance);
	m_BattleShipUI_FleetMark.moveY(fDistance);
}

void CBattle_Ship::updateTouchData()
{
	m_stUnitTouch.x = m_vEntity[0].second->getCenterX();
	m_stUnitTouch.y = m_vEntity[0].second->getCenterY();
	m_stUnitTouch.radius = m_vEntity[0].second->getHeight() / 2;
}

void CBattle_Ship::updateCollisionData()
{
	m_stUnitCollision.x = m_vEntity[0].second->getCenterX();
	m_stUnitCollision.y = m_vEntity[0].second->getCenterY();
	m_stUnitCollision.radius = m_vEntity[0].second->getHeight() / 2;	
}

void CBattle_Ship::updateMovement(float frameTime)
{
	if (m_bDestroy)
		return;

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
	m_BattleUIShipSelected.moveX((float)cos(m_fCurrentAngle) * m_fCurrentSpeed * frameTime);
	m_BattleUIShipSelected.moveY(-(float)sin(m_fCurrentAngle) * m_fCurrentSpeed * frameTime);


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
	if (m_bDestroy)
		return false;
	
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
		m_fCurrentHealth += m_fRepairSpeed * frameTime;
}

void CBattle_Ship::setupShipDataFormat(std::vector<std::string> vArray)
{
	if (vArray.size() < 0)
		return;

	int dataNumber = 0;
	
	m_nUnitID				= std::stoi(vArray[dataNumber]);
	m_strTextureKey			= vArray[++dataNumber];
	m_nSpriteTopCount		= std::stoi(vArray[++dataNumber]);
	m_nSpriteBodyCount		= std::stoi(vArray[++dataNumber]);
	m_nSpriteBottomCount	= std::stoi(vArray[++dataNumber]);
	m_strName				= vArray[++dataNumber];
	m_strShipType			= vArray[++dataNumber];
	m_fMaxHealth			= std::stof(vArray[++dataNumber]);
	m_fRepairSpeed			= std::stof(vArray[++dataNumber]);
	m_fRotateSpeed			= std::stof(vArray[++dataNumber]);
	m_fAccelateSpeed		= std::stof(vArray[++dataNumber]);
	m_fMaxSpeed				= std::stof(vArray[++dataNumber]);
	m_fRaderRange			= std::stof(vArray[++dataNumber]);
	m_nTurretCount			= std::stoi(vArray[++dataNumber]);
	m_strTurretID			= vArray[++dataNumber];
	m_nAirCraftCapacity		= std::stoi(vArray[++dataNumber]);
	m_fPerformance			= std::stof(vArray[++dataNumber]);
	m_nSailorCount			= std::stoi(vArray[++dataNumber]);
	m_nAntiAirTurrectCount	= std::stoi(vArray[++dataNumber]);
	m_fAntiAirRange			= std::stof(vArray[++dataNumber]);
	m_fAntiAirDamage		= std::stof(vArray[++dataNumber]);
	m_nCallPhase			= std::stoi(vArray[++dataNumber]);
	m_fMass					= std::stof(vArray[++dataNumber]);
}

bool CBattle_Ship::setupEntity(Game * gamePtr, std::string strImageName, bool bPhysics)
{
	bool success = false;
	Entity* shipParts = new Entity;
	success = shipParts->initialize(gamePtr, 0, 0, 0, IMAGEMANAGER->getTexture(strImageName));
	shipParts->setCollisionType(entityNS::PIXEL_PERFECT);
	shipParts->setScale(battleShipGeneralNS::SHIP_ENTITY_TEXTURE_SCALE);

	m_vEntity.emplace_back(bPhysics, shipParts);
	return success;
}
