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
	
}

void Scene_Battle::update()
{
	
}

void Scene_Battle::release()
{
}

void Scene_Battle::ai()
{
}

void Scene_Battle::collisions()
{
}

void Scene_Battle::render()
{

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
