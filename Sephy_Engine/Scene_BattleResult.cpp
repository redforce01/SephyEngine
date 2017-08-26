#include "stdafx.h"
#include "Scene_BattleResult.h"


CScene_BattleResult::CScene_BattleResult()
{
	m_pBattleResultMainSystem = nullptr;
}


CScene_BattleResult::~CScene_BattleResult()
{
	SAFE_DELETE(m_pBattleResultMainSystem);
	releaseAll();	
}

void CScene_BattleResult::initialize(HWND hwnd)
{
	Game::initialize(hwnd);
	m_pBattleResultMainSystem = new CBattle_ResultMainSystem;
	m_pBattleResultMainSystem->initialize(this);
}

void CScene_BattleResult::update()
{
	m_pBattleResultMainSystem->update(frameTime);
}

void CScene_BattleResult::release()
{
	SAFE_DELETE(m_pBattleResultMainSystem);
}

void CScene_BattleResult::ai()
{
}

void CScene_BattleResult::collisions()
{
}

void CScene_BattleResult::render()
{
	m_pBattleResultMainSystem->render();
}

void CScene_BattleResult::releaseAll()
{
	Game::releaseAll();
	return;
}

void CScene_BattleResult::resetAll()
{
	Game::resetAll();
	return;
}
