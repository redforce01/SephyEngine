#include "stdafx.h"
#include "scene_TestScene.h"


Scene_TestScene::Scene_TestScene()
{
}


Scene_TestScene::~Scene_TestScene()
{
}

void Scene_TestScene::initialize(HWND hwnd)
{
	Game::initialize(hwnd);

	m_pTestImage = new Image;
	m_pTestImage->initialize(this->getGraphics(), 41, 72, 4, IMAGEMANAGER->getTexture("test"));
	m_pTestImage->setX(400);
	m_pTestImage->setY(200);
	m_pTestImage->setFrames(0, 3);
	m_pTestImage->setCurrentFrame(0);
	m_pTestImage->setFrameDelay(0.2f);

	m_pTestShipTop = new Image;
	m_pTestShipTop->initialize(this->getGraphics(), 0, 0, 0, IMAGEMANAGER->getTexture("SN_BC_Stalingrad_sdtop0000"));
	m_pTestShipTop->setScale(0.5);
	m_pTestShipTop->setX(600);
	m_pTestShipMiddle = new Image;
	m_pTestShipMiddle->initialize(this->getGraphics(), 0, 0, 0, IMAGEMANAGER->getTexture("SN_BC_Stalingrad_sdmiddle0000"));
	m_pTestShipMiddle->setScale(0.5);
	m_pTestShipMiddle->setX(600);
	m_pTestShipBottom = new Image;
	m_pTestShipBottom->initialize(this->getGraphics(), 0, 0, 0, IMAGEMANAGER->getTexture("SN_BC_Stalingrad_sdbody0000"));
	m_pTestShipBottom->setScale(0.5);
	m_pTestShipBottom->setX(600);

}

void Scene_TestScene::update()
{
	//if (input->getMouseLButton())
	//{
	//	m_bClicked = true;
	//}
	//else
	//	m_bClicked = false;
	//if (PtInRect(&rcBoundingBox, input->getMousePt()))
	//{
	//	m_bClicked = true;
	//}
	//else
	//	m_bClicked = false;
	//if (input->isKeyDown('T'))
	//{
	//	m_bClicked = true;
	//}
	//else
	//	m_bClicked = false;

	static float aniTime = 1.0f;
	static float worldTime = 0.0f;
	worldTime += this->getTimeDelta();

	static int count = 0;
	if (worldTime > aniTime)
	{
		count++;
		if (count > 35)
			count = 0;
		worldTime = 0;
	}

	std::string strTop = "SN_BC_Stalingrad_sdtop";
	std::string strMiddle = "SN_BC_Stalingrad_sdmiddle";
	std::string strBottom = "SN_BC_Stalingrad_sdbody";

	strTop += "00";
	strMiddle += "00";
	strBottom += "00";
	
	if (count < 10)
	{
		strTop += "0";
		strMiddle += "0";
		strBottom += "0";
	}

	strTop += std::to_string(count);
	strMiddle += std::to_string(count);
	strBottom += std::to_string(count);

	m_pTestShipTop->setTextureManager(IMAGEMANAGER->getTexture(strTop));
	m_pTestShipMiddle->setTextureManager(IMAGEMANAGER->getTexture(strMiddle));
	m_pTestShipBottom->setTextureManager(IMAGEMANAGER->getTexture(strBottom));

	m_pTestImage->update(this->getTimeDelta());
}

void Scene_TestScene::release()
{
}

void Scene_TestScene::ai()
{
}

void Scene_TestScene::collisions()
{
}

void Scene_TestScene::render()
{
	RECT rc = RectMake(100, 100, 100, 100);
	graphics->drawRect(rcBoundingBox);

	graphics->spriteBegin();

	if (m_bClicked)
		dxFont.print("test mouse clicked!!!!!!!!", rc, DT_LEFT);
	
	m_pTestImage->draw();

	m_pTestShipBottom->draw();
	m_pTestShipMiddle->draw();
	m_pTestShipTop->draw();
	
	graphics->spriteEnd();
}

void Scene_TestScene::releaseAll()
{	
	// Todo..

	Game::releaseAll();
}

void Scene_TestScene::resetAll()
{
	// Todo..

	Game::resetAll();
}
