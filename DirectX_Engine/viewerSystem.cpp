#include "stdafx.h"
#include "viewerSystem.h"
#include "mapSystem.h"

ViewerSystem::ViewerSystem()
{
	bUIMouseOver = false;
	//m_pResTreeViewer = nullptr;
	m_pMapTileViewer = nullptr;
	m_pMinimapViewer = nullptr;
	m_pControlViewer = nullptr;
	m_pStatsViewer = nullptr;
	m_pMapSystem = nullptr;
	m_pLogViewer = nullptr;
	m_bMapSystemWorkableSetup = false;
}


ViewerSystem::~ViewerSystem()
{
	//SAFE_DELETE(m_pResTreeViewer);
	SAFE_DELETE(m_pMapTileViewer);
	SAFE_DELETE(m_pMinimapViewer);
	SAFE_DELETE(m_pControlViewer);
	SAFE_DELETE(m_pStatsViewer);
	SAFE_DELETE(m_pLogViewer);
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
		m_pLogViewer = new LogViewer;
		m_pLogViewer->initialize(gamePtr->getGraphics(), gamePtr->getInput());

		// Memory Link Connections
		m_pControlViewer->setMemoryLinkStatsViewer(m_pStatsViewer);
		m_pControlViewer->setMemoryLinkLogViewer(m_pLogViewer);
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
	if (m_bMapSystemWorkableSetup == false)
	{
		m_pMapSystem->addWorkRECT(m_pStatsViewer->getDialogRECT());
		m_pMapSystem->addWorkRECT(m_pControlViewer->getDialogRECT());
		m_pMapSystem->addWorkRECT(m_pMapTileViewer->getDialogRECT());
		m_pMapSystem->addWorkRECT(m_pMinimapViewer->getDialogRECT());
		m_pMapSystem->addWorkRECT(m_pLogViewer->getDialogRECT());
		m_bMapSystemWorkableSetup = true;
	}
	
	//m_pResTreeViewer->update(frameTime);
	m_pMapTileViewer->update(frameTime);
	m_pMinimapViewer->update(frameTime);
	m_pControlViewer->update(frameTime);
	m_pStatsViewer->update(frameTime);
	m_pLogViewer->update(frameTime);

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
	m_pLogViewer->render();
}

bool ViewerSystem::checkMouseOver()
{
	if (/*m_pResTreeViewer->getMouseOver() && m_pResTreeViewer->getVisible()
		||*/ m_pMapTileViewer->getMouseOver() && m_pMapTileViewer->getVisible()
		|| m_pMinimapViewer->getMouseOver() && m_pMinimapViewer->getVisible()
		|| m_pControlViewer->getMouseOver() && m_pControlViewer->getVisible()
		|| m_pStatsViewer->getMouseOver() && m_pStatsViewer->getVisible()
		|| m_pLogViewer->getMouseOver() && m_pLogViewer->getVisible())
	{
		return true;
	}
	
	return false;
}
