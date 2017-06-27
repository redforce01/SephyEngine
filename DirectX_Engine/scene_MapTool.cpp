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
	cameraSystem->setMemoryLinkMapSystem(mapSystem);
	mapSystem->setMemoryLinkCameraSystem(cameraSystem);
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

	if (viewerSystem->getUIMouseOver() == false)
	{
		std::string str = "isoBasicB";
		if (input->getMouseLButton())
		{
			auto arr = mapSystem->getAllTiles();
			for (auto iter : arr)
			{
				if (PtInRect(&iter->getTileRect(), PointMake(input->getMouseX(), input->getMouseY())))
				{
					iter->changeTile(IMAGEMANAGER->getTexture(str));
					break;
				}
			}
		}
	}

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


	graphics->spriteBegin();

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
