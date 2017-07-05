#include "stdafx.h"
#include "statsViewer.h"


StatsViewer::StatsViewer()
{
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

	return SystemDebugStats::initialize(g, i);
}

void StatsViewer::update(float frameTime)
{
	SystemDebugStats::update(frameTime);
		
	static float worldSec;
	worldSec += frameTime;
	std::string deltaTime = "deltaTime : " + std::to_string(worldSec);
	std::string worldTime = "worldTime : " + std::to_string(frameTime);
	std::string fps = "fps : " + std::to_string(pGame->getFPS());

	int mouseX = pGame->getInput()->getMouseX();
	int mouseY = pGame->getInput()->getMouseY();
	std::string mouse = "mouseX : " + std::to_string(mouseX)  + " mouseY : " + std::to_string(mouseY);
	
	setMessage(statsViewerNS::KEY_WORLD, worldTime);
	setMessage(statsViewerNS::KEY_DELTA, deltaTime);
	setMessage(statsViewerNS::KEY_FPS, fps);
	setMessage(statsViewerNS::KEY_MOUSE, mouse);
}

void StatsViewer::render()
{
	if (m_bVisible == false)
		return;

	SystemDebugStats::render();
}
