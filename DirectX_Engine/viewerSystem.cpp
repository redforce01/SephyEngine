#include "stdafx.h"
#include "viewerSystem.h"


ViewerSystem::ViewerSystem()
{
	bUIMouseOver = false;
}


ViewerSystem::~ViewerSystem()
{
	SAFE_DELETE(pResTreeViewer);
	SAFE_DELETE(pMapTileViewer);
	SAFE_DELETE(pMinimapViewer);
	SAFE_DELETE(pControlViewer);

}

bool ViewerSystem::initialize(Game * gamePtr)
{
	bool success = false;

	try
	{
		pResTreeViewer = new ResourceTreeViewer;
		pResTreeViewer->initialize(gamePtr->getGraphics(), gamePtr->getInput());
		pMapTileViewer = new MapTileViewer;
		pMapTileViewer->initialize(gamePtr->getGraphics(), gamePtr->getInput());
		pMinimapViewer = new MinimapViewer;
		pMinimapViewer->initialize(gamePtr->getGraphics(), gamePtr->getInput());
		pMinimapViewer->setMapWidth(128 * 100);
		pMinimapViewer->setMapHeight(64 * 100);
		pMinimapViewer->setIsoMetric(true);
		pControlViewer = new ControlViewer;
		pControlViewer->initialize(gamePtr->getGraphics(), gamePtr->getInput());
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
	pResTreeViewer->update(frameTime);
	pMapTileViewer->update(frameTime);
	pMinimapViewer->update(frameTime);
	pControlViewer->update(frameTime);

	if (pResTreeViewer->getMouseOver() || pMapTileViewer->getMouseOver()
		|| pMinimapViewer->getMouseOver())
	{
		bUIMouseOver = true;
	}
	else
		bUIMouseOver = false;
}

void ViewerSystem::render()
{
	pResTreeViewer->render();
	pMapTileViewer->render();
	pMinimapViewer->render();
	pControlViewer->render();
}
