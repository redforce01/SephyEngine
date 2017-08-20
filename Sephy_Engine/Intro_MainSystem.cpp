#include "stdafx.h"
#include "Intro_MainSystem.h"


CIntro_MainSystem::CIntro_MainSystem()
{
	m_pJoinButton = nullptr;
}


CIntro_MainSystem::~CIntro_MainSystem()
{
	SAFE_DELETE(m_pJoinButton);
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
			(g_fScreenWidth / 2) - (m_pJoinButton->getWidth() / 2),
			(g_fScreenHeight / 2) - (m_pJoinButton->getHeight() / 2), "Join", true);
		m_pJoinButton->setRegistFunction(std::bind(&CIntro_MainSystem::functionJoinButton));
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
}

void CIntro_MainSystem::render()
{
	m_AnimeSystem.render();
	m_pJoinButton->render();
}

void CIntro_MainSystem::functionJoinButton()
{
	SCENEMANAGER->changeScene("Lobby");
	SOUNDMANAGER->stop(introMainSystemNS::BACKGROUND_MUSIC_FILENAME);
}
