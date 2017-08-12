#include "stdafx.h"
#include "Scene_Intro.h"


CScene_Intro::CScene_Intro() : Game()
{
}


CScene_Intro::~CScene_Intro()
{
	releaseAll();
}

void CScene_Intro::initialize(HWND hwnd)
{
	Game::initialize(hwnd);

	m_IntroMainSystem.initialize(this);
}

void CScene_Intro::update()
{
	m_IntroMainSystem.update(frameTime);
}

void CScene_Intro::release()
{	
}

void CScene_Intro::ai()
{
}

void CScene_Intro::collisions()
{
}

void CScene_Intro::render()
{
	m_IntroMainSystem.render();
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
