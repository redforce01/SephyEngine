#include "stdafx.h"
#include "scene_Battle.h"


Scene_Battle::Scene_Battle() : Game()
{
}


Scene_Battle::~Scene_Battle()
{
	releaseAll();
}

void Scene_Battle::initialize(HWND hwnd)
{
	Game::initialize(hwnd);
	
	m_pBattleMainSystem = new CBattle_MainSystem;
	m_pBattleMainSystem->initialize(this);
}

void Scene_Battle::update()
{
	m_pBattleMainSystem->update(frameTime);

}

void Scene_Battle::release()
{
}

void Scene_Battle::ai()
{
	m_pBattleMainSystem->ai();
}

void Scene_Battle::collisions()
{
	m_pBattleMainSystem->collision();
}

void Scene_Battle::render()
{
	m_pBattleMainSystem->render();
}

void Scene_Battle::releaseAll()
{
	Game::releaseAll();
	return;
}

void Scene_Battle::resetAll()
{
	Game::resetAll();
	return;
}
