#include "stdafx.h"
#include "scene_MapTool.h"


Scene_MapTool::Scene_MapTool() : Game()
{
}


Scene_MapTool::~Scene_MapTool()
{
	SAFE_DELETE(mapSystem);
	SAFE_DELETE(cameraSystem);
	SAFE_DELETE(viewerSystem);
	
	releaseAll();
}

void Scene_MapTool::initialize(HWND hwnd)
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

	// etc initialize settings
	cameraSystem->setCameraPos(100, 100);
}

void Scene_MapTool::update()
{	
	mapSystem->update(frameTime);
	cameraSystem->update(frameTime);
	viewerSystem->update(frameTime);

	if (input->isKeyDown(MapToolNS::ESCAPE_KEY))
	{
		PostQuitMessage(0);
	}
}

void Scene_MapTool::release()
{
}

void Scene_MapTool::ai()
{
}

void Scene_MapTool::collisions()
{
}

void Scene_MapTool::render()
{
	mapSystem->render();
	viewerSystem->render();
}

void Scene_MapTool::releaseAll()
{
	Game::releaseAll();
	return;
}

void Scene_MapTool::resetAll()
{
	Game::resetAll();
	return;
}
