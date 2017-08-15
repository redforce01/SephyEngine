#include "stdafx.h"
#include "Intro_AnimeSystem.h"


CIntro_AnimeSystem::CIntro_AnimeSystem()
{
	m_strOpeningPlaneKey = introAnimeSystemNS::OPENING_PLANE_KEY_NAME;
	m_strOpeningPlaneShadowKey = introAnimeSystemNS::OPENING_PLANE_SH_KEY_NAME;
	m_nCurrentFrame = 0;
	m_animeTime = 0.f;
	m_startX = (g_fScreenWidth / 2) - (introAnimeSystemNS::OPENING_PLANE_WIDTH / 2);
	m_startY = 0;
	m_bAnimeComplete = false;
}


CIntro_AnimeSystem::~CIntro_AnimeSystem()
{
	SAFE_DELETE(m_pOpeningPlane);
	SAFE_DELETE(m_pOpeningPlaneShadow);
	SAFE_DELETE(m_pBlackMasking);
	SAFE_DELETE(m_pPanel);
	SAFE_DELETE(m_pPanelShadow);
	SAFE_DELETE(m_pPanelShip);
	SAFE_DELETE(m_pPanelShipShadow);
	SAFE_DELETE(m_pBackground);
}

bool CIntro_AnimeSystem::initialize(Game * gamePtr)
{
	bool success = false;
	try
	{
		m_pGraphics = gamePtr->getGraphics();
		m_pInput = gamePtr->getInput();
		//==========================================================================================
		std::string planeKey = m_strOpeningPlaneKey;
		std::string planeShadowKey = m_strOpeningPlaneShadowKey;
		if (m_nCurrentFrame < 10)
		{
			planeKey += "000" + std::to_string(m_nCurrentFrame);
			planeShadowKey += "000" + std::to_string(m_nCurrentFrame);
		}
		else if (m_nCurrentFrame < 100)
		{
			planeKey += "00" + std::to_string(m_nCurrentFrame);
			planeShadowKey += "00" + std::to_string(m_nCurrentFrame);
		}
		else
		{
			planeKey += "0" + std::to_string(m_nCurrentFrame);
			planeShadowKey += "0" + std::to_string(m_nCurrentFrame);
		}

		m_pOpeningPlane = new Image;
		success = m_pOpeningPlane->initialize(m_pGraphics, 0, 0, 0, IMAGEMANAGER->getTexture(planeKey));
		m_pOpeningPlane->setX(m_startX);
		m_pOpeningPlane->setY(m_startY);
		m_pOpeningPlaneShadow = new Image;
		success = m_pOpeningPlaneShadow->initialize(m_pGraphics, 0, 0, 0, IMAGEMANAGER->getTexture(planeShadowKey));
		m_pOpeningPlaneShadow->setX(m_startX);
		m_pOpeningPlaneShadow->setY(m_startY);
		m_pOpeningPlaneShadow->setColorFilter(introAnimeSystemNS::OPENING_PLANE_SHADOW_COLOR_FILTER);
		//==========================================================================================
		m_pBlackMasking = new Image;
		m_pBlackMasking->initialize(m_pGraphics, 0, 0, 0, IMAGEMANAGER->getTexture(introAnimeSystemNS::BLACK_MASKING_FILENAME));
		m_pBlackMasking->setColorFilter(introAnimeSystemNS::BLACK_MASKING_COLOR_FILTER);
		m_pBlackMasking->setX(0);
		m_pBlackMasking->setY(0);
		//==========================================================================================
		m_pPanel			= new Image;
		m_pPanel->initialize(m_pGraphics, 0, 0, 0, IMAGEMANAGER->getTexture(introAnimeSystemNS::PANEL_FRONT_FILENAME));
		m_pPanel->setX((g_fScreenWidth / 2) - (m_pPanel->getWidth() / 2));
		m_pPanel->setY((g_fScreenHeight / 2) - (m_pPanel->getHeight() / 2));
		m_pPanelShadow		= new Image;
		m_pPanelShadow->initialize(m_pGraphics, 0, 0, 0, IMAGEMANAGER->getTexture(introAnimeSystemNS::PANEL_SHADOW_FILENAME));
		m_pPanelShadow->setX((g_fScreenWidth / 2) - (m_pPanelShadow->getWidth() / 2));
		m_pPanelShadow->setY((g_fScreenHeight / 2) - (m_pPanelShadow->getHeight() / 2));
		m_pPanelShadow->setColorFilter(introAnimeSystemNS::PANEL_SHADOW_COLOR_FILTER);
		//==========================================================================================
		m_pPanelShip		= new Image;
		m_pPanelShip->initialize(m_pGraphics, 0, 0, 0, IMAGEMANAGER->getTexture(introAnimeSystemNS::PANEL_SHIP_FILENAME));
		m_pPanelShip->setX((g_fScreenWidth / 2) - (m_pPanelShip->getWidth() / 2) + introAnimeSystemNS::PANEL_SHIP_RELATE_X);
		m_pPanelShip->setY((g_fScreenHeight / 2) - (m_pPanelShip->getHeight() / 2) + introAnimeSystemNS::PANEL_SHIP_RELATE_Y);
		m_pPanelShipShadow	= new Image;
		m_pPanelShipShadow->initialize(m_pGraphics, 0, 0, 0, IMAGEMANAGER->getTexture(introAnimeSystemNS::PANEL_SHIP_SHADOW_FILENAME));
		m_pPanelShipShadow->setX((g_fScreenWidth / 2) - (m_pPanelShipShadow->getWidth() / 2) + introAnimeSystemNS::PANEL_SHIP_RELATE_X);
		m_pPanelShipShadow->setY((g_fScreenHeight / 2) - (m_pPanelShipShadow->getHeight() / 2) + introAnimeSystemNS::PANEL_SHIP_RELATE_Y);
		m_pPanelShipShadow->setColorFilter(introAnimeSystemNS::PANEL_SHADOW_COLOR_FILTER);
		//==========================================================================================
		m_pBackground = new Image;
		m_pBackground->initialize(m_pGraphics, 0, 0, 0, IMAGEMANAGER->getTexture(introAnimeSystemNS::BACKGROUND_FILENAME));
		m_pBackground->setX((g_fScreenWidth / 2) - (m_pBackground->getWidth() / 2));
		m_pBackground->setY((g_fScreenHeight / 2) - (m_pBackground->getHeight() / 2));
	}
	catch (...)
	{
		MessageBox(g_hWndEngine, introAnimeSystemNS::ERROR_MESSAGE.c_str(), "Error", MB_OK);
	}

	return success;
}

void CIntro_AnimeSystem::update(float frameTime)
{
	if (SOUNDMANAGER->isPlaySound(introAnimeSystemNS::BACKGROUND_MUSIC_FILENAME) == false)
	{
		SOUNDMANAGER->play(introAnimeSystemNS::BACKGROUND_MUSIC_FILENAME, g_fSoundBGMVolume * g_fSoundMasterVolume);
	}


	if (m_nCurrentFrame < introAnimeSystemNS::OPENING_PLANE_MAX_FRAME)
	{
		m_animeTime += frameTime;
		if (m_animeTime > introAnimeSystemNS::OPENING_PLANE_ANIMETIME)
		{
			std::string planeKey = m_strOpeningPlaneKey;
			std::string planeShadowKey = m_strOpeningPlaneShadowKey;
			if (m_nCurrentFrame < 10)
			{
				planeKey += "000" + std::to_string(m_nCurrentFrame);
				planeShadowKey += "000" + std::to_string(m_nCurrentFrame);
			}
			else if (m_nCurrentFrame < 100)
			{
				planeKey += "00" + std::to_string(m_nCurrentFrame);
				planeShadowKey += "00" + std::to_string(m_nCurrentFrame);
			}
			else
			{
				planeKey += "0" + std::to_string(m_nCurrentFrame);
				planeShadowKey += "0" + std::to_string(m_nCurrentFrame);
			}
			m_pOpeningPlane->setTextureManager(IMAGEMANAGER->getTexture(planeKey));
			m_pOpeningPlaneShadow->setTextureManager(IMAGEMANAGER->getTexture(planeShadowKey));
			m_nCurrentFrame++;
			m_animeTime = 0.f;
		}
	}
	else
		m_bAnimeComplete = true;
}

void CIntro_AnimeSystem::render()
{
	m_pGraphics->spriteBegin();
	m_pBlackMasking->draw();
	m_pBackground->draw();
	m_pPanelShipShadow->draw();
	m_pPanelShadow->draw();
	m_pPanelShip->draw();
	m_pPanel->draw();
	if (m_bAnimeComplete == false)
	{
		m_pOpeningPlane->draw();
		m_pOpeningPlaneShadow->draw();
	}
	m_pGraphics->spriteEnd();
}
