#include "stdafx.h"
#include "Scene_UnitTool.h"


CScene_UnitTool::CScene_UnitTool() : Game()
{
}


CScene_UnitTool::~CScene_UnitTool()
{
	releaseAll();
	SAFE_DELETE(m_pUnitToolMainSystem);
}

void CScene_UnitTool::initialize(HWND hwnd)
{
	Game::initialize(hwnd);
	m_pUnitToolMainSystem = new CUnitTool_MainSystem;
	m_pUnitToolMainSystem->initialize(this);
}

void CScene_UnitTool::update()
{
	m_pUnitToolMainSystem->update(frameTime);
}

void CScene_UnitTool::release()
{
}

void CScene_UnitTool::ai()
{
	m_pUnitToolMainSystem->ai();
}

void CScene_UnitTool::collisions()
{
	m_pUnitToolMainSystem->collision();
}

void CScene_UnitTool::render()
{
	m_pUnitToolMainSystem->render();
}

void CScene_UnitTool::releaseAll()
{
	Game::releaseAll();
	return;
}

void CScene_UnitTool::resetAll()
{
	Game::resetAll();
	return;
}
