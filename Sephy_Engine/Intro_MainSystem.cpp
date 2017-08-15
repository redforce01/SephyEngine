#include "stdafx.h"
#include "Intro_MainSystem.h"


CIntro_MainSystem::CIntro_MainSystem()
{
}


CIntro_MainSystem::~CIntro_MainSystem()
{
}

bool CIntro_MainSystem::initialize(Game * gamePtr)
{
	bool success = false;

	try
	{
		m_pGraphics = gamePtr->getGraphics();
		m_pInput = gamePtr->getInput();

		success = m_AnimeSystem.initialize(gamePtr);
	}
	catch (...)
	{
		MessageBox(g_hWndEngine, "Intro MainSystem Initialize Failed", "Error", MB_OK);
	}

	return success;
}

void CIntro_MainSystem::update(float frameTime)
{
	m_AnimeSystem.update(frameTime);
}

void CIntro_MainSystem::render()
{
	m_AnimeSystem.render();
}
