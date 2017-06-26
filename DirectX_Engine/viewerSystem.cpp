#include "stdafx.h"
#include "viewerSystem.h"


ViewerSystem::ViewerSystem()
{
	bUIMouseOver = false;
}


ViewerSystem::~ViewerSystem()
{
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
		pMinimapViewer->setMapWidth(128 * 64);
		pMinimapViewer->setMapHeight(64 * 64);
		
		pMinimapViewer->setIsoMetric(true);
		success = true;
	}
	catch (...)
	{

	}
	

	return success;
}

void ViewerSystem::update(float frameTime)
{
	pResTreeViewer->update(frameTime);
	pMapTileViewer->update(frameTime);
	pMinimapViewer->update(frameTime);

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
}
