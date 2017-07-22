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

	m_pWorld = new Image;
	m_pWorld->initialize(this->getGraphics(), 4261, 2067, 0, IMAGEMANAGER->getTexture("wmap"));
	m_pWorld->setX(0);
	m_pWorld->setY(0);

	m_pTesting = new testingUI;
	m_pTesting->initialize(this);

	m_pCloud = new Image;
	m_pCloud->initialize(this->getGraphics(), 0, 0, 0, IMAGEMANAGER->getTexture("cld-01"));
	m_pCloud->setX(500);
	m_pCloud->setY(300);
	//m_pCloud->setColorFilter(SETCOLOR_ARGB(192, 255, 255, 255));
	m_pCloudSh = new Image;
	m_pCloudSh->initialize(this->getGraphics(), 0, 0, 0, IMAGEMANAGER->getTexture("cld-01s"));
	m_pCloudSh->setX(500);
	m_pCloudSh->setY(300);
	m_pCloudSh->setColorFilter(SETCOLOR_ARGB(192, 0, 0, 0));
	
	
	//m_pWorld->setLayer(LAYERMANAGER->getLayer(enLayerList::LAYER_BACKGROUND));

	auto file = FILEMANAGER->getDataFile("Ship Information");	
	//auto data = TXTPARSER->getTxtFile("Ship Information", "Unit Type");
	// return std::string

	//// + Unit Type BattleCruiser
	//// data = std::vector<std::string>
	//// "#" 주석문을 제외한 내용

	std::vector<std::string> vData;
	std::string filePath = file->path;
	std::ifstream openFile(filePath.data());
	if (openFile.is_open())
	{
		std::string line;
		while (std::getline(openFile, line))
		{
			vData.emplace_back(line);
		}
		openFile.close();
	}



	m_rc = RectMake(1741 - (162 / 2), 861 - 50, 162, 100);
	m_collision = RectMake(1741 - (150 / 2), 861 - 40, 150, 80);
}

void scene_Main::update()
{
	m_pTesting->update(this->getTimeDelta());
	
	if (m_pTesting->ContainFocus())
	{
		m_flag = true;
	}
	else
		m_flag = false;




	static float worldTime = 0.f;
	worldTime += this->getTimeDelta();

	static int count = 0;
	if (worldTime > 0.1f)
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

	if (input->isKeyDown('A'))
	{
		m_pWorld->moveX(5);
		m_rc.left += 5;
		m_rc.right += 5;
		m_collision.left += 5;
		m_collision.right += 5;
	}
	if (input->isKeyDown('D') || input->isKeyDown(VK_RIGHT))
	{
		m_pWorld->moveX(-5);

		m_rc.left += -5;
		m_rc.right += -5;
		m_collision.left += -5;
		m_collision.right += -5;		
	}
	if (input->isKeyDown('S'))
	{
		m_pWorld->moveY(-5);

		m_rc.top += -5;
		m_rc.bottom += -5;
		m_collision.top += -5;
		m_collision.bottom += -5;
	}
	if (input->isKeyDown('W'))
	{
		m_pWorld->moveY(5);

		m_rc.top += 5;
		m_rc.bottom += 5;
		m_collision.top += 5;
		m_collision.bottom += 5;
	}

	//if (input->getMouseLButton())
	//{
	//	if (PtInRect(&m_rc, input->getMousePt()))
	//	{
	//		m_flag = true;
	//	}
	//	else
	//	{
	//		m_flag = false;
	//	}
	//}
	



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
	
	m_pWorld->draw();
	m_pTestShipTop->draw();	
	m_pTestShipBody->draw();
	m_pTestShipBottom->draw();
	
	m_pCloudSh->draw();
	m_pCloud->draw();

	//char buffer[128];
	//int BUF_SIZE = 32;
	//_snprintf_s(buffer, BUF_SIZE, "SceneName : Scene_Main");
	//dxFont.print(buffer, GAME_WIDTH - 200, GAME_HEIGHT - 60);

	graphics->spriteEnd();

	graphics->drawRect(m_rc, 1.0f, graphicsNS::BLUE);
	
	if(m_flag)
		graphics->drawRect(m_collision, 1.0f, graphicsNS::GREEN);

	m_pTesting->render();
	m_pTestShipBottom->drawRect(graphicsNS::RED);


	for (int i = 0; i < 50; i++)
	{
		graphics->drawCircle(1200, 500, 100, 2.0f, SETCOLOR_ARGB(128, 200, 30, 0));
	}
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
