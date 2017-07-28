#include "stdafx.h"
#include "Battle_Ship.h"

CBattle_Ship::CBattle_Ship()
{
	//===========================================
	m_pGraphics = nullptr;
	m_pInput = nullptr;
	//===========================================
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
	//===========================================
	m_bInitialized			= false;
	m_bActive				= false;
	m_bDestroy				= false;
	m_bDestroyAnimeComplete = false;
	m_bChangeSprite			= false;
	m_bSelected				= false;
	m_bOnEngine				= false;
	//===========================================
	ZeroMemory(&m_stUnitTouch, sizeof(m_stUnitTouch));
}


CBattle_Ship::~CBattle_Ship()
{
	for (auto iter : m_vEntity)
	{
		SAFE_DELETE(iter.second);
	}
	m_vEntity.clear();
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

	updateRepair(frameTime);
	updateTouchData();

	m_bChangeSprite = updateRotate(frameTime);
	updateSprite();
	updateEngine(frameTime);
	updateMovement(frameTime);
}

void CBattle_Ship::render()
{
	if (m_bInitialized == false)
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
			if (i == m_nSpriteWaveStart)
				continue;

			m_vEntity[i].second->draw();
		}
	}
		
	m_pGraphics->spriteEnd();

	float currentX = m_vEntity[0].second->getCenter()->x;
	float currentY = m_vEntity[0].second->getCenter()->y;
	m_pGraphics->drawLine(currentX, currentY, m_fTargetX, m_fTargetY, 2.0f, graphicsNS::RED);
}

void CBattle_Ship::ai()
{
}

void CBattle_Ship::collision()
{
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
}

void CBattle_Ship::moveY(float fDistance)
{
	for (auto iter : m_vEntity)
	{
		iter.second->Image::moveY(fDistance);
	}

	m_fTargetY += fDistance;
}

void CBattle_Ship::updateTouchData()
{
	m_stUnitTouch.x = m_vEntity[0].second->getCenterX();
	m_stUnitTouch.y = m_vEntity[0].second->getCenterY();
	m_stUnitTouch.radius = m_vEntity[0].second->getWidth() / 2;
}

void CBattle_Ship::updateMovement(float frameTime)
{
	if (m_bDestroy)
		return;

	VECTOR2 CurrentPos = *m_vEntity[0].second->getCenter();
	float interRadius = 5.f;
	float calDistance = MyUtil::getDistance(CurrentPos.x, CurrentPos.y, m_fTargetX, m_fTargetY);
	float sumDistance = interRadius + m_stUnitTouch.radius;
	if (calDistance < sumDistance)
		m_bOnEngine = false;
	else
		m_bOnEngine = true;

	for (auto iter : m_vEntity)
	{
		iter.second->Image::moveX((float)cos(m_fCurrentAngle) * m_fCurrentSpeed * frameTime);
		iter.second->Image::moveY(-(float)sin(m_fCurrentAngle) * m_fCurrentSpeed * frameTime);
	}
}

void CBattle_Ship::updateEngine(float frameTime)
{
	if (m_bOnEngine)
	{
		m_fCurrentSpeed += m_fAccelateSpeed * frameTime;
	}
	else
	{
		if(m_fCurrentSpeed > 0.f)
			m_fCurrentSpeed -= m_fAccelateSpeed * frameTime;
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
}

bool CBattle_Ship::setupEntity(Game * gamePtr, std::string strImageName, bool bPhysics)
{
	bool success = false;
	Entity* shipParts = new Entity;
	success = shipParts->initialize(gamePtr, 0, 0, 0, IMAGEMANAGER->getTexture(strImageName));
	shipParts->setCollisionType(entityNS::PIXEL_PERFECT);
	shipParts->setScale(0.75);


	m_vEntity.emplace_back(bPhysics, shipParts);
	return success;
}
