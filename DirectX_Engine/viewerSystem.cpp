#include "stdafx.h"
#include "viewerSystem.h"
#include "mapSystem.h"

ViewerSystem::ViewerSystem()
{
	m_bUIMouseOver = false;
	m_bUIHasFocus = false;

	//m_pResTreeViewer = nullptr;
	m_pMapTileViewer = nullptr;
	m_pMinimapViewer = nullptr;
	m_pControlViewer = nullptr;
	m_pStatsViewer = nullptr;
	m_pMapSystem = nullptr;
	m_pLogViewer = nullptr;
	m_pObjectControlViewer = nullptr;
	m_pEventViewer = nullptr;
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
	SAFE_DELETE(m_pObjectControlViewer);
	SAFE_DELETE(m_pEventViewer);
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
		m_pControlViewer = new ControlViewer;
		m_pControlViewer->initialize(gamePtr->getGraphics(), gamePtr->getInput());
		m_pStatsViewer = new StatsViewer;
		m_pStatsViewer->initialize(gamePtr->getGraphics(), gamePtr->getInput());
		m_pStatsViewer->setGamePtr(gamePtr);		
		m_pLogViewer = new LogViewer;
		m_pLogViewer->initialize(gamePtr->getGraphics(), gamePtr->getInput());
		m_pObjectControlViewer = new ObjectControlViewer;
		m_pObjectControlViewer->initialize(gamePtr->getGraphics(), gamePtr->getInput());
		m_pEventViewer = new EventViewer;
		m_pEventViewer->initialize(gamePtr->getGraphics(), gamePtr->getInput()); 

		// Memory Link Connections
		m_pControlViewer->setMemoryLinkStatsViewer(m_pStatsViewer);
		m_pControlViewer->setMemoryLinkLogViewer(m_pLogViewer);
		m_pMapTileViewer->setMemoryLinkObjectControlViewer(m_pObjectControlViewer);
		m_pObjectControlViewer->setMemoryLinkMapTileViewer(m_pMapTileViewer);
		m_pObjectControlViewer->setMemoryLinkLogViewer(m_pLogViewer);
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
		m_pMapSystem->addWorkRECT(m_pObjectControlViewer->getDialogRECT());
		m_pMapSystem->addWorkRECT(m_pEventViewer->getDialogRECT());

		m_pEventViewer->addWorkableRECT(m_pStatsViewer->getDialogRECT());
		m_pEventViewer->addWorkableRECT(m_pControlViewer->getDialogRECT());
		m_pEventViewer->addWorkableRECT(m_pMapTileViewer->getDialogRECT());
		m_pEventViewer->addWorkableRECT(m_pMinimapViewer->getDialogRECT());
		m_pEventViewer->addWorkableRECT(m_pLogViewer->getDialogRECT());
		m_pEventViewer->addWorkableRECT(m_pObjectControlViewer->getDialogRECT());
		m_pEventViewer->addWorkableRECT(m_pEventViewer->getDialogRECT());

		m_bMapSystemWorkableSetup = true;
	}
	
	//m_pResTreeViewer->update(frameTime);
	if (m_pEventViewer->getMakeEventModeActive() == false)
	{
		m_pMapTileViewer->update(frameTime);
		m_pMinimapViewer->update(frameTime);
		m_pControlViewer->update(frameTime);
		m_pObjectControlViewer->update(frameTime);
	}

	m_pStatsViewer->update(frameTime);
	m_pLogViewer->update(frameTime);
	m_pEventViewer->update(frameTime);

	if (checkMouseOver())
		m_bUIMouseOver = true;
	else
		m_bUIMouseOver = false;

	if (checkViewerFocus())
		m_bUIHasFocus = true;
	else
		m_bUIHasFocus = false;
}

void ViewerSystem::render()
{
	//m_pResTreeViewer->render();
	m_pMapTileViewer->render();
	m_pMinimapViewer->render();
	m_pControlViewer->render();
	m_pStatsViewer->render();
	m_pLogViewer->render();
	m_pObjectControlViewer->render();
	m_pEventViewer->render();
}

bool ViewerSystem::checkMouseOver()
{
	if (/*m_pResTreeViewer->getMouseOver() && m_pResTreeViewer->getVisible()
		||*/ m_pMapTileViewer->getMouseOver() && m_pMapTileViewer->getVisible()
		|| m_pMinimapViewer->getMouseOver() && m_pMinimapViewer->getVisible()
		|| m_pControlViewer->getMouseOver() && m_pControlViewer->getVisible()
		|| m_pStatsViewer->getMouseOver() && m_pStatsViewer->getVisible()
		|| m_pLogViewer->getMouseOver() && m_pLogViewer->getVisible()
		|| m_pObjectControlViewer->getMouseOver() && m_pObjectControlViewer->getVisible()
		|| m_pEventViewer->getMouseOver() && m_pEventViewer->getVisible())
	{
		return true;
	}
	
	return false;
}

bool ViewerSystem::checkViewerFocus()
{
	if (m_pMapTileViewer->getOnFocus()
		|| m_pMinimapViewer->getOnFocus()
		|| m_pControlViewer->getOnFocus()
		|| m_pStatsViewer->getOnFocus()
		|| m_pLogViewer->getOnFocus()
		|| m_pObjectControlViewer->getOnFocus()
		|| m_pEventViewer->getOnFocus())
	{
		return true;
	}

	return false;
}
