#include "stdafx.h"
#include "Intro_MainSystem.h"


CIntro_MainSystem::CIntro_MainSystem()
{
	m_pJoinButton = nullptr;
	m_pCancelButton = nullptr;
}


CIntro_MainSystem::~CIntro_MainSystem()
{
	SAFE_DELETE(m_pJoinButton);
	SAFE_DELETE(m_pCancelButton);
}

bool CIntro_MainSystem::initialize(Game * gamePtr)
{
	bool success = false;

	try
	{
		m_pGraphics = gamePtr->getGraphics();
		m_pInput = gamePtr->getInput();

		success = m_AnimeSystem.initialize(gamePtr);
		m_pJoinButton = new SystemButton;
		m_pJoinButton->initialize(m_pGraphics, m_pInput,
			(g_fScreenWidth / 2) - (m_pJoinButton->getWidth() / 2) + introMainSystemNS::JOIN_BUTTON_RELATE_X,
			(g_fScreenHeight / 2) - (m_pJoinButton->getHeight() / 2) + introMainSystemNS::JOIN_BUTTON_RELATE_Y, introMainSystemNS::INTRO_BUTTON_JOIN, true);
		m_pJoinButton->setRegistFunction(std::bind(&CIntro_MainSystem::functionJoinButton));
		m_pCancelButton = new SystemButton;
		m_pCancelButton->initialize(m_pGraphics, m_pInput,
			(g_fScreenWidth / 2) - (m_pCancelButton->getWidth() / 2) + introMainSystemNS::CANCEL_BUTTON_RELATE_X,
			(g_fScreenHeight / 2) - (m_pCancelButton->getHeight() / 2) + introMainSystemNS::CANCEL_BUTTON_RELATE_Y, introMainSystemNS::INTRO_BUTTON_CANCEL, true);
		m_pCancelButton->setRegistFunction(std::bind(&CIntro_MainSystem::functionCancelButton));		

		m_dxFont.initialize(m_pGraphics, introMainSystemNS::FONT_HEIGHT, false, false, introMainSystemNS::FONT);
	}
	catch (...)
	{
		MessageBox(g_hWndEngine, introMainSystemNS::ERROR_MESSAGE.c_str(), "Error", MB_OK);
	}

	return success;
}

void CIntro_MainSystem::update(float frameTime)
{
	m_AnimeSystem.update(frameTime);
	m_pJoinButton->update(frameTime);
	m_pCancelButton->update(frameTime);
}

void CIntro_MainSystem::render()
{
	m_AnimeSystem.render();
	m_pJoinButton->render();
	m_pCancelButton->render();
	m_pGraphics->spriteBegin();
	RECT rc = RectMake(
		(g_fScreenWidth / 2) + introMainSystemNS::INTRO_PANEL_RELATE_X,
		(g_fScreenHeight / 2) + introMainSystemNS::INTRO_PANEL_RELATE_Y,
		introMainSystemNS::INTRO_PANEL_WIDTH,
		20);
	m_dxFont.print(introMainSystemNS::INTRO_COMMENT_00, rc, DT_LEFT);
	rc.top += 20;
	rc.bottom += 20;
	m_dxFont.print(introMainSystemNS::INTRO_COMMENT_01, rc, DT_LEFT);
	m_pGraphics->spriteEnd();
}

void CIntro_MainSystem::functionJoinButton()
{
	SOUNDMANAGER->stop(introMainSystemNS::BACKGROUND_MUSIC_FILENAME);
	SCENEMANAGER->changeScene("Lobby");
}

void CIntro_MainSystem::functionCancelButton()
{
	SOUNDMANAGER->stop(introMainSystemNS::BACKGROUND_MUSIC_FILENAME);
	PostQuitMessage(0);
}
