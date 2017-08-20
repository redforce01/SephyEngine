#include "stdafx.h"
#include "Scene_BattleResult.h"


CScene_BattleResult::CScene_BattleResult()
{
	m_pBlackBack = nullptr;
	m_pResultBackground = nullptr;
	m_pResultSystem = nullptr;
}


CScene_BattleResult::~CScene_BattleResult()
{
	SAFE_DELETE(m_pBlackBack);
	SAFE_DELETE(m_pResultBackground);
	releaseAll();	
}

void CScene_BattleResult::initialize(HWND hwnd)
{
	Game::initialize(hwnd);
	m_pResultSystem = new CBattle_ResultSystem;

	m_pBlackBack = new Image;
	m_pBlackBack->initialize(graphics, 0, 0, 0, IMAGEMANAGER->getTexture(scenebattleResultNS::LOADING_BLACK_BACKGROUND));
	m_pBlackBack->setColorFilter(scenebattleResultNS::LOADING_BLACK_BACK_COLOR_FILTER);

	m_pResultBackground = new Image;
	m_pResultBackground->initialize(graphics, 0, 0, 0, IMAGEMANAGER->getTexture(scenebattleResultNS::BATTLE_RESULT_BACKGROUND));
	m_pResultBackground->setX((g_fScreenWidth / 2) - (m_pResultBackground->getWidth() / 2));
	m_pResultBackground->setY((g_fScreenHeight / 2) - (m_pResultBackground->getHeight() / 2));


	m_pResultSystem->loadBattleResult();
}

void CScene_BattleResult::update()
{
}

void CScene_BattleResult::release()
{
}

void CScene_BattleResult::ai()
{
}

void CScene_BattleResult::collisions()
{
}

void CScene_BattleResult::render()
{
	graphics->spriteBegin();
	m_pBlackBack->draw();
	m_pResultBackground->draw();
	graphics->spriteEnd();
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
