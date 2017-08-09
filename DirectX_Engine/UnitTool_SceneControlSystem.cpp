#include "stdafx.h"
#include "UnitTool_SceneControlSystem.h"


CUnitTool_SceneControlSystem::CUnitTool_SceneControlSystem()
{
}


CUnitTool_SceneControlSystem::~CUnitTool_SceneControlSystem()
{
}

bool CUnitTool_SceneControlSystem::initialize(Game * gamePtr)
{
	m_pGraphics = gamePtr->getGraphics();
	m_pInput = gamePtr->getInput();

	m_SceneControlViewer.initialize(m_pGraphics, m_pInput);

	return false;
}

void CUnitTool_SceneControlSystem::update(float frameTime)
{
	m_SceneControlViewer.update(frameTime);
}

void CUnitTool_SceneControlSystem::render()
{
	m_SceneControlViewer.render();
}
