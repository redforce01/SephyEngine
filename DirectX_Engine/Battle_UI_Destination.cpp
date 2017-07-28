#include "stdafx.h"
#include "Battle_UI_Destination.h"

CBattle_UI_Destination::CBattle_UI_Destination()
{
	m_pGraphics				= nullptr;
	m_pDestinationGreen		= nullptr;
	m_pDestinationBlue		= nullptr;
	m_pDestinationYellow	= nullptr;
	m_nCurrentSprite		= 0;
	m_nSpriteMax			= battleUIDestinationNS::DESTINATION_MAX;
	m_fChangeTime			= battleUIDestinationNS::DESTINATION_VIEW_TIME;
	m_fChangeDeltaTime		= 0.f;
	m_bActive				= false;
	m_bInitialized			= false;
	m_enDestinationType		= DESTINATION_TYPE::DESTINATION_GREEN;
}


CBattle_UI_Destination::~CBattle_UI_Destination()
{
	SAFE_DELETE(m_pDestinationGreen);
	SAFE_DELETE(m_pDestinationBlue);
	SAFE_DELETE(m_pDestinationYellow);
}

bool CBattle_UI_Destination::initialize(Graphics * g)
{
	bool success = false;
	m_pGraphics = g;

	try
	{
		if(m_nCurrentSprite < 10)
			m_strGreenKey = battleUIDestinationNS::DESTINATION_GREEN_NAME + "000" + std::to_string(m_nCurrentSprite);
		else
			m_strGreenKey = battleUIDestinationNS::DESTINATION_GREEN_NAME + "00" + std::to_string(m_nCurrentSprite);

		if (m_nCurrentSprite < 10)
			m_strBlueKey = battleUIDestinationNS::DESTINATION_BLUE_NAME + "00" + std::to_string(m_nCurrentSprite);
		else
			m_strBlueKey = battleUIDestinationNS::DESTINATION_BLUE_NAME + "0" + std::to_string(m_nCurrentSprite);

		if (m_nCurrentSprite < 10)
			m_strYellowKey = battleUIDestinationNS::DESTINATION_YELLOW_NAME + "00" + std::to_string(m_nCurrentSprite);
		else
			m_strYellowKey = battleUIDestinationNS::DESTINATION_YELLOW_NAME + "0" + std::to_string(m_nCurrentSprite);

		m_pDestinationGreen = new Image;
		success = m_pDestinationGreen->initialize(g, 0, 0, 0, IMAGEMANAGER->getTexture(m_strGreenKey));		
		m_pDestinationBlue = new Image;
		success = m_pDestinationBlue->initialize(g, 0, 0, 0, IMAGEMANAGER->getTexture(m_strBlueKey));
		m_pDestinationYellow = new Image;
		success = m_pDestinationYellow->initialize(g, 0, 0, 0, IMAGEMANAGER->getTexture(m_strYellowKey));
		m_bInitialized = success;
	}
	catch (...)
	{
		MessageBox(g_hWndEngine, battleUIDestinationNS::ERROR_MESSAGE.c_str(), "Error", MB_OK);
	}

	return success;
}

void CBattle_UI_Destination::update(float frameTime)
{
	if (m_bInitialized == false)
		return;

	if (m_bActive == false)
		return;
	
	updateDestination(frameTime);

	m_pDestinationGreen->update(frameTime);
	m_pDestinationBlue->update(frameTime);
	m_pDestinationYellow->update(frameTime);
}

void CBattle_UI_Destination::render()
{
	if (m_bInitialized == false)
		return;
	
	if (m_bActive == false)
		return;

	m_pGraphics->spriteBegin();
	switch (m_enDestinationType)
	{
	case DESTINATION_TYPE::DESTINATION_GREEN:
		m_pDestinationGreen->draw();
		break;
	case DESTINATION_TYPE::DESTINATION_BLUE:
		m_pDestinationBlue->draw();
		break;
	case DESTINATION_TYPE::DESTINATION_YELLOW:
		m_pDestinationYellow->draw();
		break;
	}
	m_pGraphics->spriteEnd();
}

void CBattle_UI_Destination::updateDestination(float frameTime)
{
	if (m_nCurrentSprite > m_nSpriteMax)
		m_nCurrentSprite = 0;


	if (m_nCurrentSprite < 10)
		m_strGreenKey = battleUIDestinationNS::DESTINATION_GREEN_NAME + "000" + std::to_string(m_nCurrentSprite);
	else
		m_strGreenKey = battleUIDestinationNS::DESTINATION_GREEN_NAME + "00" + std::to_string(m_nCurrentSprite);

	if (m_nCurrentSprite < 10)
		m_strBlueKey = battleUIDestinationNS::DESTINATION_BLUE_NAME + "00" + std::to_string(m_nCurrentSprite);
	else
		m_strBlueKey = battleUIDestinationNS::DESTINATION_BLUE_NAME + "0" + std::to_string(m_nCurrentSprite);

	if (m_nCurrentSprite < 10)
		m_strYellowKey = battleUIDestinationNS::DESTINATION_YELLOW_NAME + "00" + std::to_string(m_nCurrentSprite);
	else
		m_strYellowKey = battleUIDestinationNS::DESTINATION_YELLOW_NAME + "0" + std::to_string(m_nCurrentSprite);

	m_pDestinationGreen->setTextureManager(IMAGEMANAGER->getTexture(m_strGreenKey));
	m_pDestinationBlue->setTextureManager(IMAGEMANAGER->getTexture(m_strBlueKey));
	m_pDestinationYellow->setTextureManager(IMAGEMANAGER->getTexture(m_strYellowKey));

	m_nCurrentSprite++;	

	m_fChangeDeltaTime += frameTime;
	if (m_fChangeDeltaTime > m_fChangeTime)
	{
		m_fChangeDeltaTime = 0.f;
		changeDestination();
	}
}

void CBattle_UI_Destination::changeDestination()
{	
	switch (m_enDestinationType)
	{
	case DESTINATION_TYPE::DESTINATION_GREEN:
		m_enDestinationType = DESTINATION_TYPE::DESTINATION_BLUE;
		break;
	case DESTINATION_TYPE::DESTINATION_BLUE:
		m_enDestinationType = DESTINATION_TYPE::DESTINATION_YELLOW;
		break;
	case DESTINATION_TYPE::DESTINATION_YELLOW:
		m_bActive = false;
		break;
	}
	m_nCurrentSprite = 0;
}

void CBattle_UI_Destination::moveX(float distance)
{
	m_pDestinationGreen->moveX(distance);
	m_pDestinationBlue->moveX(distance);
	m_pDestinationYellow->moveX(distance);
}

void CBattle_UI_Destination::moveY(float distance)
{
	m_pDestinationGreen->moveY(distance);
	m_pDestinationBlue->moveY(distance);
	m_pDestinationYellow->moveY(distance);
}

void CBattle_UI_Destination::setDestinationPos(VECTOR2 v)
{
	float width = m_pDestinationBlue->getWidth();
	float height = m_pDestinationBlue->getHeight();

	float realTargetX = v.x - (width / 2);
	float realTargetY = v.y - (height / 2);

	m_pDestinationGreen->setX(realTargetX);
	m_pDestinationGreen->setY(realTargetY);
	m_pDestinationBlue->setX(realTargetX);
	m_pDestinationBlue->setY(realTargetY);
	m_pDestinationYellow->setX(realTargetX);
	m_pDestinationYellow->setY(realTargetY);
}
