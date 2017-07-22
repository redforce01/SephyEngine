#include "stdafx.h"
#include "scene_Battle.h"


Scene_Battle::Scene_Battle() : Game()
{
}


Scene_Battle::~Scene_Battle()
{
	releaseAll();
}

void Scene_Battle::initialize(HWND hwnd)
{
	Game::initialize(hwnd);
	
	m_pTop = new Image;
	m_pTop->initialize(this->getGraphics(), 0, 0, 0, IMAGEMANAGER->getTexture("Z1_Top00"));
	m_pBody = new Image;
	m_pBody->initialize(this->getGraphics(), 0, 0, 0, IMAGEMANAGER->getTexture("Z1_Body00"));
	m_pBottom = new Image;
	m_pBottom->initialize(this->getGraphics(), 0, 0, 0, IMAGEMANAGER->getTexture("Z1_Bottom00"));

	m_pShadow = new Image;
	m_pShadow->initialize(this->getGraphics(), 0, 0, 0, IMAGEMANAGER->getTexture("Z1_Shadow00"));
	m_pShadow->setColorFilter(SETCOLOR_ARGB(128, 255, 255, 255));

	m_pWave = new Image;
	m_pWave->initialize(this->getGraphics(), 0, 0, 0, IMAGEMANAGER->getTexture("Z1_Wave00"));

	m_pSunken = new Image;
	m_pSunken->initialize(this->getGraphics(), 0, 0, 0, IMAGEMANAGER->getTexture("Z1_Sunken00"));
	m_pSunkenSh = new Image;
	m_pSunkenSh->initialize(this->getGraphics(), 0, 0, 0, IMAGEMANAGER->getTexture("Z1_Sunkenshadow00"));

	m_Back = new Image;
	m_Back->initialize(this->getGraphics(), 0, 0, 0, IMAGEMANAGER->getTexture("wmap"));
	m_Back->moveX(-1000);
	m_Back->moveY(-700);


	m_pWave->setX(500);
	m_pWave->setY(300);
	m_pWave->setScale(0.5);
	m_pShadow->setX(500);
	m_pShadow->setY(300);
	m_pShadow->setScale(0.5);
	m_pTop->setX(500);
	m_pTop->setY(300);
	m_pTop->setScale(0.5);
	m_pBody->setX(500);
	m_pBody->setY(300);
	m_pBody->setScale(0.5);
	m_pBottom->setX(500);
	m_pBottom->setY(300);
	m_pBottom->setScale(0.5);
}

void Scene_Battle::update()
{
	static float worldTime = 0.f;
	worldTime += this->getTimeDelta();

	static int count = 0;
	if (worldTime > 0.1f)
	{
		count++;
		worldTime = 0.f;
		if (count > 9)
			count = 0;
	}

	std::string shipName = "Z1";
	std::string shipWave = "_Wave";
	std::string aniCount = "0";
	aniCount += std::to_string(count);

	std::string resultWave = shipName + shipWave + aniCount;
	m_pWave->setTextureManager(IMAGEMANAGER->getTexture(resultWave));

}

void Scene_Battle::release()
{
}

void Scene_Battle::ai()
{
}

void Scene_Battle::collisions()
{
}

void Scene_Battle::render()
{
	graphics->spriteBegin();
	m_Back->draw();
	m_pWave->draw(SETCOLOR_ARGB(128, 128, 128 + 64, 128 + 64));
	m_pShadow->draw(SETCOLOR_ARGB(128, 0, 0, 0));
	m_pTop->draw();
	m_pBody->draw();
	m_pBottom->draw();
	graphics->spriteEnd();
}

void Scene_Battle::releaseAll()
{
	Game::releaseAll();
	return;
}

void Scene_Battle::resetAll()
{
	Game::resetAll();
	return;
}
