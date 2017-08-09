#include "stdafx.h"
#include "UnitTool_MainSystem.h"


CUnitTool_MainSystem::CUnitTool_MainSystem()
{
}


CUnitTool_MainSystem::~CUnitTool_MainSystem()
{
	SAFE_DELETE(m_pMapSystem);
	SAFE_DELETE(m_pCameraSystem);
	SAFE_DELETE(m_pUISystem);
	SAFE_DELETE(m_pUnitControlSystem);
	SAFE_DELETE(m_pSceneControlSystem);
}

bool CUnitTool_MainSystem::initialize(Game * gamePtr)
{
	m_pGraphics = gamePtr->getGraphics();
	m_pInput = gamePtr->getInput();

	m_pMapSystem = new CUnitTool_MapSystem;
	m_pMapSystem->initialize(gamePtr);
	m_pCameraSystem = new CUnitTool_CameraSystem;
	m_pCameraSystem->initialize(gamePtr);
	m_pUISystem = new CUnitTool_UISystem;
	m_pUISystem->initialize(gamePtr);
	m_pUnitControlSystem = new CUnitTool_UnitControlSystem;
	m_pUnitControlSystem->initialize(gamePtr);
	m_pSceneControlSystem = new CUnitTool_SceneControlSystem;
	m_pSceneControlSystem->initialize(gamePtr);
	//=========================================================
	// Each System Link Connections
	//=========================================================
	m_pCameraSystem->setMemoryLinkMapSystem(m_pMapSystem);
	m_pCameraSystem->setMemoryLinkUnitControlSystem(m_pUnitControlSystem);
	m_pSceneControlSystem->setMemoryLinkUnitControlSystem(m_pUnitControlSystem);
	m_pUISystem->setMemoryLinkUnitControlSystem(m_pUnitControlSystem);
	auto pRespawnViewer = m_pUISystem->getRespawnListViewer();
	m_pSceneControlSystem->setMemoryLinkRespawnListViewer(pRespawnViewer);


	//=========================================================
	// Camera Min Max Pos Setup
	//=========================================================
	float totalMapWidth = m_pMapSystem->getMapTotalWidth();
	float totalMapHeight = m_pMapSystem->getMapTotalHeight();
	float cellWidth = m_pMapSystem->getCellWidth();
	float cellHeight = m_pMapSystem->getCellHeight();
	m_pCameraSystem->setCameraMinPos(0 + cellWidth, 0 + cellHeight);
	m_pCameraSystem->setCameraMaxPos(
		totalMapWidth - g_fScreenWidth - cellWidth,
		totalMapHeight - g_fScreenHeight - cellHeight * 1.5f);
	m_pCameraSystem->setCameraPos(cellWidth, cellHeight);

	return true;
}

void CUnitTool_MainSystem::update(float frameTime)
{
	m_pMapSystem->update(frameTime);
	m_pCameraSystem->update(frameTime);
	m_pUnitControlSystem->update(frameTime);
	m_pSceneControlSystem->update(frameTime);
	m_pUISystem->update(frameTime);
}

void CUnitTool_MainSystem::render()
{
	m_pMapSystem->render();
	m_pCameraSystem->render();
	m_pUnitControlSystem->render();
	m_pSceneControlSystem->render();
	m_pUISystem->render();
}

void CUnitTool_MainSystem::ai()
{
	m_pUnitControlSystem->ai();
}

void CUnitTool_MainSystem::collision()
{
	m_pUnitControlSystem->collision();
}
