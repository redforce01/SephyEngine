#include "stdafx.h"
#include "scene_Test.h"


Scene_Test::Scene_Test() : Game()
{
}


Scene_Test::~Scene_Test()
{
	release();
	releaseAll();
}

void Scene_Test::initialize(HWND hwnd)
{
	Game::initialize(hwnd);

#pragma region ANIMATION TEST
	/* CHARACTER TEST*/
	testTexture = IMAGEMANAGER->getTexture("test");
	testImage.initialize(graphics, 41, 72, 4, testTexture, LAYERMANAGER->getLayer(enLayerList::LAYER_DEFAULT));
	testImage.setX(1280 / 2 - testImage.getWidth() / 2);
	testImage.setY(720 / 2 - testImage.getHeight() / 2);
	testImage.setFrames(0, 3);
	testImage.setCurrentFrame(0);
	testImage.setFrameDelay(0.2f);
#pragma endregion

#pragma region BACKGROUND IMAGE TEST

	/* BACKGROUND TEST */
	testTexture2 = IMAGEMANAGER->getTexture("tile");
	testImage2.initialize(graphics, 0, 0, 0, testTexture2, LAYERMANAGER->getLayer(enLayerList::LAYER_BACKGROUND));
	testImage2.setX(1280 / 2 - testImage.getWidth() / 2);
	testImage2.setY(720 / 2 - testImage.getHeight() / 2);

#pragma endregion


#pragma region UIBUTTON TEST

	/* UIBUTTON TESTING */
	testButton = new UIButton;
	testButton->initialize(	
		g_Graphics, input, LAYERMANAGER->getLayer(enLayerList::LAYER_UI),
		false, graphicsNS::FILTER, "button_test", 300, 300, 49, 16, 1);
	testButton->regiFunction(std::bind(&Scene_Test::testFunction));




	testProgressBar = new UIProgressBar;
	testProgressBar->initialize(
		UIPROGRESSBAR_TYPE::UIPROGRESSBAR_RECT,
		"testBar_red", "testBar_border",
		false, graphicsNS::FILTER,
		100, 100,
		300, 500, 194, 5);

#pragma endregion

#pragma region UITAB TEST

	/* UITAB TESTING */
	tab = new UITab;
	tab->initialize(graphics, input, LAYERMANAGER->getLayer(enLayerList::LAYER_UI),
		false, testNS::UITAB_TEST_KEY, graphicsNS::FILTER, "TabBackTexture", 400, 100, 300, 226);

	tabContent_A* myTab_1 = new tabContent_A;
	myTab_1->initialize(graphics, input, LAYERMANAGER->getLayer(enLayerList::LAYER_UI),
		graphicsNS::FILTER, "tabContentsBack", 0, 0, 100, 155);

	tabContent_A* myTab_2 = new tabContent_A;
	myTab_2->initialize(graphics, input, LAYERMANAGER->getLayer(enLayerList::LAYER_UI),
		graphicsNS::FILTER, "tabContentsBack", 0, 0, 100, 155);

	tabContent_A* myTab_3 = new tabContent_A;
	myTab_3->initialize(graphics, input, LAYERMANAGER->getLayer(enLayerList::LAYER_UI),
		graphicsNS::FILTER, "tabContentsBack", 0, 0, 100, 155);

	tab->addTab("test_1", myTab_1, graphicsNS::FILTER, "tabIcon_0", 10, 10, 147 / 3, 16);
	tab->addTab("test_2", myTab_2, graphicsNS::FILTER, "tabIcon_1", 10, 10, 147 / 3, 16);
	tab->addTab("test_3", myTab_3, graphicsNS::FILTER, "tabIcon_2", 10, 10, 147 / 3, 16);

#pragma endregion
}

void Scene_Test::update()
{
	static float testingTime = 0;
	static float testGauge = 100;
	
	testingTime += frameTime;

	if (testingTime > 1.0f)
	{
		testGauge -= 3;
		testProgressBar->setGauge(testGauge);
		testingTime = 0;
	}

	/*Animation Image Update */
	testImage.update(frameTime);

	/* UIBUTTON TESTING */
	testButton->update(frameTime);

	/* ProgressBar Testing */
	testProgressBar->update(frameTime);

	/* tab testing */
	tab->update(frameTime);


	//Project Exit
	if (input->isKeyDown(testNS::ESCAPE_KEY))
	{
		PostQuitMessage(0);
	}

	//Scene Change Test
	if (input->wasKeyPressed(testNS::SCENE_CHANGE_KEY))
	{
		SCENEMANAGER->changeScene("Main");
	}
}

void Scene_Test::release()
{
}

void Scene_Test::ai()
{
}

void Scene_Test::collisions()
{
}

void Scene_Test::render()
{
	graphics->spriteBegin();
	
	testImage2.draw(graphicsNS::FILTER);		//background test
	testImage.draw(graphicsNS::FILTER);			//character test
	testButton->render();						//uibutton test
	testProgressBar->render();					//progressbar test
	tab->render();								//tab test

												// Scene View Information Render
	static float worldSec;
	worldSec += this->getTimeDelta();
	std::string deltaTime = "deltaTime : " + std::to_string(worldSec);
	std::string worldTime = "worldTime : " + std::to_string(this->getTimeDelta());
	std::string frame = "fps : " + std::to_string(this->fps);

	dxFont.print(deltaTime, 10, 10);
	dxFont.print(worldTime, 10, 30);
	dxFont.print(frame, 10, 70);
	dxFont.print(std::string("TestScene"), 10, 50);

	graphics->spriteEnd();
}

void Scene_Test::releaseAll()
{

	Game::releaseAll();
	return;
}

void Scene_Test::resetAll()
{

	Game::resetAll();
	return;
}

void Scene_Test::testFunction()
{
	printf("test Function!!!!!!!!!!!!!!!!!!!! \n");
}
