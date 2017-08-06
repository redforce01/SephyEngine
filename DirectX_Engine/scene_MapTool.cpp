#include "stdafx.h"
#include "Scene_MapTool.h"


CScene_MapTool::CScene_MapTool() : Game()
{
}


CScene_MapTool::~CScene_MapTool()
{
	SAFE_DELETE(mapSystem);
	SAFE_DELETE(cameraSystem);
	SAFE_DELETE(viewerSystem);
	
	releaseAll();
}

void CScene_MapTool::initialize(HWND hwnd)
{
	Game::initialize(hwnd);

	// object new & initialize + Setup link
	mapSystem = new MapSystem;
	mapSystem->initialize(this);
	cameraSystem = new CameraSystem;
	cameraSystem->initialize(this);	
	viewerSystem = new ViewerSystem;
	viewerSystem->initialize(this);

	// Each System Memory Link Connect
	mapSystem->setMemoryLinkCameraSystem(cameraSystem);
	mapSystem->setMemoryLinkLogViewer(viewerSystem->getLogViewer());
	cameraSystem->setMemoryLinkMapSystem(mapSystem);
	cameraSystem->setMemoryLinkMinimap(viewerSystem->getMinimapViewer());
	viewerSystem->setMemoryLinkCameraSystem(cameraSystem);
	viewerSystem->setMemoryLinkMapSystem(mapSystem);

	// Start Camera Pos Setting
	cameraSystem->setCameraPos(100, 100);

	// Minimap InGame Size Setting
	int tileSizeX = mapSystemNS::MAP_SIZE_X;
	int tileSizeY = mapSystemNS::MAP_SIZE_Y;
	int tileWidth = mapSystemNS::TILE_BASIC_WIDTH;
	int tileHeight = mapSystemNS::TILE_BASIC_HEIGHT;
	viewerSystem->getMinimapViewer()->setMapWidth(tileWidth * tileSizeX);
	viewerSystem->getMinimapViewer()->setMapHeight(tileHeight * tileSizeY);
	viewerSystem->getMinimapViewer()->setIsoMetric(true);
}

void CScene_MapTool::update()
{	
	mapSystem->update(frameTime);

	if(viewerSystem->getUIHasFocus() == false)
		cameraSystem->update(frameTime);

	viewerSystem->update(frameTime);


	if (input->isKeyDown(MapToolNS::ESCAPE_KEY))
	{
		PostQuitMessage(0);
	}
}

void CScene_MapTool::release()
{
}

void CScene_MapTool::ai()
{
}

void CScene_MapTool::collisions()
{
}

void CScene_MapTool::render()
{
	mapSystem->render();
	viewerSystem->render();
}

void CScene_MapTool::releaseAll()
{
	Game::releaseAll();
	return;
}

void CScene_MapTool::resetAll()
{
	Game::resetAll();
	return;
}
