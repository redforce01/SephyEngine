#include "stdafx.h"
#include "viewerSystem.h"


ViewerSystem::ViewerSystem()
{
	bUIMouseOver = false;
	//m_pResTreeViewer = nullptr;
	m_pMapTileViewer = nullptr;
	m_pMinimapViewer = nullptr;
	m_pControlViewer = nullptr;
	m_pStatsViewer = nullptr;
}


ViewerSystem::~ViewerSystem()
{
	//SAFE_DELETE(m_pResTreeViewer);
	SAFE_DELETE(m_pMapTileViewer);
	SAFE_DELETE(m_pMinimapViewer);
	SAFE_DELETE(m_pControlViewer);
	SAFE_DELETE(m_pStatsViewer);
}

bool ViewerSystem::initialize(Game * gamePtr)
{
	bool success = false;

	try
	{
		// Viewer Initialize
		//m_pResTreeViewer = new ResourceTreeViewer;
		//m_pResTreeViewer->initialize(gamePtr->getGraphics(), gamePtr->getInput());
		m_pMapTileViewer = new MapTileViewer;
		m_pMapTileViewer->initialize(gamePtr->getGraphics(), gamePtr->getInput());
		m_pMinimapViewer = new MinimapViewer;
		m_pMinimapViewer->initialize(gamePtr->getGraphics(), gamePtr->getInput());
		m_pMinimapViewer->setMapWidth(128 * 100);
		m_pMinimapViewer->setMapHeight(64 * 100);
		m_pMinimapViewer->setIsoMetric(true);
		m_pControlViewer = new ControlViewer;
		m_pControlViewer->initialize(gamePtr->getGraphics(), gamePtr->getInput());
		m_pStatsViewer = new StatsViewer;
		m_pStatsViewer->initialize(gamePtr->getGraphics(), gamePtr->getInput());
		m_pStatsViewer->setGamePtr(gamePtr);

		// Memory Link Connections
		m_pControlViewer->setMemoryLinkStatsViewer(m_pStatsViewer);
		success = true;
	}
	catch (...)
	{
		MessageBox(g_hWndEngine, "Tool Viewer Initialize Failed", "Error", MB_OK);
	}
	

	return success;
}

void ViewerSystem::update(float frameTime)
{
	//m_pResTreeViewer->update(frameTime);
	m_pMapTileViewer->update(frameTime);
	m_pMinimapViewer->update(frameTime);
	m_pControlViewer->update(frameTime);
	m_pStatsViewer->update(frameTime);

	if (checkMouseOver())
		bUIMouseOver = true;
	else
		bUIMouseOver = false;
}

void ViewerSystem::render()
{
	//m_pResTreeViewer->render();
	m_pMapTileViewer->render();
	m_pMinimapViewer->render();
	m_pControlViewer->render();
	m_pStatsViewer->render();
}

bool ViewerSystem::checkMouseOver()
{
	if (/*m_pResTreeViewer->getMouseOver() && m_pResTreeViewer->getVisible()
		||*/ m_pMapTileViewer->getMouseOver() && m_pMapTileViewer->getVisible()
		|| m_pMinimapViewer->getMouseOver() && m_pMinimapViewer->getVisible()
		|| m_pControlViewer->getMouseOver() && m_pControlViewer->getVisible()
		|| m_pStatsViewer->getMouseOver() && m_pStatsViewer->getVisible())
	{
		return true;
	}
	
	return false;
}
