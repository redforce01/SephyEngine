#include "stdafx.h"
#include "scene_Main.h"


scene_Main::scene_Main() : Game()
{
}

scene_Main::~scene_Main()
{
	releaseAll();
}

void scene_Main::initialize(HWND hwnd)
{
	Game::initialize(hwnd);


	m_pTestShipTop = new Image;
	m_pTestShipTop->initialize(this->getGraphics(), 0, 0, 0, IMAGEMANAGER->getTexture("SN_BC_Stalingrad_sdbody0000"));
	m_pTestShipBody = new Image;
	m_pTestShipBody->initialize(this->getGraphics(), 0, 0, 0, IMAGEMANAGER->getTexture("SN_BC_Stalingrad_sdmiddle0000"));
	m_pTestShipBottom = new Image;
	m_pTestShipBottom->initialize(this->getGraphics(), 0, 0, 0, IMAGEMANAGER->getTexture("SN_BC_Stalingrad_sdtop0000"));
	m_pTestShipTop->setScale(0.75);
	m_pTestShipBody->setScale(0.75);
	m_pTestShipBottom->setScale(0.75);
}

void scene_Main::update()
{
	static float worldTime = 0.f;
	worldTime += this->getTimeDelta();

	static int count = 0;
	if (worldTime > 1.0f)
	{
		count++;
		worldTime = 0.f;
		if (count > 35)
			count = 0;
	}

	std::string shipName = "SN_BC_Stalingrad_";
	std::string shipTop = "sdbody";
	std::string shipBody = "sdmiddle";
	std::string shipBottom = "sdtop";

	std::string aniCount = "00";
	if (count < 10)
		aniCount += "0";

	aniCount += std::to_string(count);

	std::string resultTop = shipName + shipTop + aniCount;
	std::string resultBody = shipName + shipBody + aniCount;
	std::string resultBottom = shipName + shipBottom + aniCount;
	m_pTestShipTop->setTextureManager(IMAGEMANAGER->getTexture(resultTop));
	m_pTestShipBody->setTextureManager(IMAGEMANAGER->getTexture(resultBody));
	m_pTestShipBottom->setTextureManager(IMAGEMANAGER->getTexture(resultBottom));




	auto iter = gameObjMgr.beginIteration();
	while (iter)
	{
		iter->update(frameTime);
		iter = gameObjMgr.nextIteration();
	}

	//Scene Change Test
	if (input->isKeyDown(mainNS::SCENE_CHANGE_KEY))
	{
		SCENEMANAGER->changeScene("Test");
	}

	//Project Exit
	if (input->isKeyDown(mainNS::ESCAPE_KEY))
	{
		PostQuitMessage(0);
	}
}

void scene_Main::release()
{
}

void scene_Main::ai()
{
}

void scene_Main::collisions()
{
}

void scene_Main::render()
{	
	graphics->spriteBegin();

	m_pTestShipTop->draw();
	m_pTestShipBody->draw();
	m_pTestShipBottom->draw();


	char buffer[128];
	int BUF_SIZE = 32;
	_snprintf_s(buffer, BUF_SIZE, "SceneName : Scene_Main");
	dxFont.print(buffer, GAME_WIDTH - 200, GAME_HEIGHT - 60);

	graphics->spriteEnd();
}

void scene_Main::releaseAll()
{

	Game::releaseAll();
	return;
}

void scene_Main::resetAll()
{
	Game::resetAll();
	return;
}
