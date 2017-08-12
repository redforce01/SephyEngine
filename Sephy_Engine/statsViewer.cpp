#include "stdafx.h"
#include "statsViewer.h"
#include "CameraSystem.h"

StatsViewer::StatsViewer()
{
	m_pGame = nullptr;
	m_pCameraSystem = nullptr;
}


StatsViewer::~StatsViewer()
{
}

bool StatsViewer::initialize(Graphics * g, Input * i)
{
	addMessage(statsViewerNS::KEY_SCENE, "Scene : MapTool");
	addMessage(statsViewerNS::KEY_WORLD, "");
	addMessage(statsViewerNS::KEY_DELTA, "");
	addMessage(statsViewerNS::KEY_FPS, "");
	addMessage(statsViewerNS::KEY_CPU, "CPU : None");
	addMessage(statsViewerNS::KEY_MOUSE, "");
	addMessage(statsViewerNS::KEY_CAMERA, "");

	return SystemDebugStats::initialize(g, i);
}

void StatsViewer::update(float frameTime)
{
	SystemDebugStats::update(frameTime);
		
	static float worldSec;
	worldSec += frameTime;
	std::string deltaTime = "deltaTime : " + std::to_string(frameTime);
	std::string worldTime = "worldTime : " + std::to_string(worldSec);
	std::string fps = "fps : " + std::to_string(m_pGame->getFPS());

	int mouseX = m_pGame->getInput()->getMouseX();
	int mouseY = m_pGame->getInput()->getMouseY();
	std::string mouse = "mouseX : " + std::to_string(mouseX)  + " mouseY : " + std::to_string(mouseY);
	
	int cameraX = m_pCameraSystem->getCameraX();
	int cameraY = m_pCameraSystem->getCameraY();
	std::string strCameraX = "camera X : " + std::to_string(cameraX);
	std::string strCameraY = " camera Y : " + std::to_string(cameraY);

	setMessage(statsViewerNS::KEY_WORLD, worldTime);
	setMessage(statsViewerNS::KEY_DELTA, deltaTime);
	setMessage(statsViewerNS::KEY_FPS, fps);
	setMessage(statsViewerNS::KEY_MOUSE, mouse);
	setMessage(statsViewerNS::KEY_CAMERA, strCameraX + strCameraY);
}

void StatsViewer::render()
{
	if (m_bVisible == false)
		return;

	SystemDebugStats::render();
}
