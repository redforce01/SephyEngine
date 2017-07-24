#include "stdafx.h"
#include "Battle_MainSystem.h"


CBattle_MainSystem::CBattle_MainSystem()
{
	m_pBattle_CameraSystem = nullptr;
	m_pBattle_MapSystem = nullptr;
}


CBattle_MainSystem::~CBattle_MainSystem()
{
	SAFE_DELETE(m_pBattle_CameraSystem);
	SAFE_DELETE(m_pBattle_MapSystem);
}

bool CBattle_MainSystem::initialize(Game * gamePtr)
{
	bool success = false;
	try
	{
		m_pBattle_DataParser = new CBattle_DataParser;
		m_pBattle_DataParser->loadBattleData();

		m_pBattle_CameraSystem = new CBattle_CameraSystem;
		success = m_pBattle_CameraSystem->initialize(gamePtr);
		
		m_pBattle_MapSystem = new CBattle_MapSystem;
		success = m_pBattle_MapSystem->initialize(gamePtr);

		//=====================================================================
		// Each System Connect to Other System - Start
		m_pBattle_MapSystem->setMemoryLinkBattleCameraSystem(m_pBattle_CameraSystem);
		m_pBattle_CameraSystem->setMemoryLinkBattleMapSystem(m_pBattle_MapSystem);
		// End - Each System Connect to Other System
		//=====================================================================

		// 
		std::string loadBattleMapName = m_pBattle_DataParser->getBattleMapName();
		m_pBattle_MapSystem->loadBattleMap(loadBattleMapName);
	}
	catch (...)
	{
		MessageBox(g_hWndEngine, battleMainSystemNS::ERROR_MESSAGE.c_str(), "Error", MB_OK);
	}

	return success;
}

void CBattle_MainSystem::update(float frameTime)
{
	m_pBattle_CameraSystem->update(frameTime);
	m_pBattle_MapSystem->update(frameTime);
}

void CBattle_MainSystem::render()
{
	m_pBattle_CameraSystem->render();
	m_pBattle_MapSystem->render();
}
