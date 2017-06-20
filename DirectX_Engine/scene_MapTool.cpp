#include "stdafx.h"
#include "scene_MapTool.h"


Scene_MapTool::Scene_MapTool() : Game()
{
}


Scene_MapTool::~Scene_MapTool()
{
	safeDelete(mapSystem);
	safeDelete(cameraSystem);

	releaseAll();
}

void Scene_MapTool::initialize(HWND hwnd)
{
	Game::initialize(hwnd);

	mapSystem = new MapSystem;
	mapSystem->initialize(this);
	cameraSystem = new CameraSystem;
	cameraSystem->initialize();
	resourceTreeViewer = new ResourceTreeViewer;
	resourceTreeViewer->initialize(this->graphics, this->input);
	
	cameraSystem->setMemoryLinkMapSystem(mapSystem);
	mapSystem->setMemoryLinkCameraSystem(cameraSystem);
}

void Scene_MapTool::update()
{	
	mapSystem->update(frameTime);
	cameraSystem->update(this->getInput());
	resourceTreeViewer->update(frameTime);

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
	graphics->spriteBegin();

	mapSystem->render();
	resourceTreeViewer->render();
	


	// Scene View Information Render
	static float worldSec;
	worldSec += this->getTimeDelta();
	std::string deltaTime = "deltaTime : " + std::to_string(worldSec);
	std::string worldTime = "worldTime : " + std::to_string(this->getTimeDelta());
	std::string frame = "fps : " + std::to_string(this->fps);

	dxFont.print(deltaTime, 10, 10);
	dxFont.print(worldTime, 10, 30);
	dxFont.print(frame, 10, 70);
	dxFont.print(std::string("SceneView"), 10, 50);

	graphics->spriteEnd();
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
