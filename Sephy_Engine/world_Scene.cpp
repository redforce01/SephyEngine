#include "stdafx.h"
#include "world_Scene.h"
#include "world_Battle_UI.h"
#include "Battle_ResultSystem.h"
#include <iostream>

CWorld_Scene::CWorld_Scene()
{
	m_pWorldMainSystem = nullptr;
}

CWorld_Scene::~CWorld_Scene()
{
	SAFE_DELETE(m_pWorldMainSystem);
	releaseAll();
}

void CWorld_Scene::initialize(HWND hwnd)
{
	Game::initialize(hwnd);
	m_pWorldMainSystem = new CWorld_MainSystem;
	m_pWorldMainSystem->initialize(this);
}

void CWorld_Scene::update()
{
	m_pWorldMainSystem->update(frameTime);
}

void CWorld_Scene::release()
{
	m_pWorldMainSystem->release();

	SAFE_DELETE(m_pWorldMainSystem);
}

void CWorld_Scene::ai()
{
}

void CWorld_Scene::collisions()
{
}

void CWorld_Scene::render()
{
	m_pWorldMainSystem->render();
}

void CWorld_Scene::releaseAll()
{
	Game::releaseAll();
	return;
}

void CWorld_Scene::resetAll()
{
	Game::resetAll();
	return;
}

