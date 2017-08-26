#include "stdafx.h"
#include "Scene_Battle.h"


CScene_Battle::CScene_Battle() : Game()
{
}


CScene_Battle::~CScene_Battle()
{
	releaseAll();
	SAFE_DELETE(m_pBattleMainSystem);
}

void CScene_Battle::initialize(HWND hwnd)
{
	Game::initialize(hwnd);
	
	m_pBattleMainSystem = new CBattle_MainSystem;
	m_pBattleMainSystem->initialize(this);
}

void CScene_Battle::update()
{
	m_pBattleMainSystem->update(frameTime);
}

void CScene_Battle::release()
{
	SAFE_DELETE(m_pBattleMainSystem);
}

void CScene_Battle::ai()
{
	m_pBattleMainSystem->ai();
}

void CScene_Battle::collisions()
{
	m_pBattleMainSystem->collision();
}

void CScene_Battle::render()
{
	m_pBattleMainSystem->render();
}

void CScene_Battle::releaseAll()
{
	Game::releaseAll();
	return;
}

void CScene_Battle::resetAll()
{
	Game::resetAll();
	return;
}
