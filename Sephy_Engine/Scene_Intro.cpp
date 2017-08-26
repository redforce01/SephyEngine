#include "stdafx.h"
#include "Scene_Intro.h"


CScene_Intro::CScene_Intro() : Game()
{
	m_pIntroMainSystem = nullptr;
}


CScene_Intro::~CScene_Intro()
{
	releaseAll();
}

void CScene_Intro::initialize(HWND hwnd)
{
	Game::initialize(hwnd);

	m_pIntroMainSystem = new CIntro_MainSystem;
	m_pIntroMainSystem->initialize(this);
}

void CScene_Intro::update()
{
	m_pIntroMainSystem->update(frameTime);
}

void CScene_Intro::release()
{	
	SAFE_DELETE(m_pIntroMainSystem);
}

void CScene_Intro::ai()
{
}

void CScene_Intro::collisions()
{
}

void CScene_Intro::render()
{
	m_pIntroMainSystem->render();
}

void CScene_Intro::releaseAll()
{
	Game::releaseAll();
	return;
}

void CScene_Intro::resetAll()
{
	Game::resetAll();
	return;
}
