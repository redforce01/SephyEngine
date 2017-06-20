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


}

void scene_Main::update()
{
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
