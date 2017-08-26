#include "stdafx.h"
#include "lobby_Scene.h"


CLobby_Scene::CLobby_Scene()
{
}


CLobby_Scene::~CLobby_Scene()
{
	SAFE_DELETE(background_back);
	SAFE_DELETE(background);
	SAFE_DELETE(l_map);
	SAFE_DELETE(l_unit);
	SAFE_DELETE(l_world);
	SAFE_DELETE(l_menu);
}

void CLobby_Scene::initialize(HWND hwnd)
{
	Game::initialize(hwnd);

	background_back = new Image;
	background = new Image;

	l_map = new CLobby_Change_MapTool;
	l_unit = new CLobby_Change_UnitTool;
	l_world = new CLobby_Change_World;
	l_menu = new CLobby_Menu;

	background_back->initialize(this->graphics, 0, 0, 0, IMAGEMANAGER->getTexture("1080p_WHITE"));
	background_back->setColorFilter(SETCOLOR_ARGB(255, 1, 1, 1));

	background->initialize(this->graphics, lobby_sceneNS::BACK_WIDTH, lobby_sceneNS::BACK_HEIGHT, 0, IMAGEMANAGER->getTexture(lobby_sceneNS::BACK_NAME));
	background->setScale(g_fScreenWidth / lobby_sceneNS::BACK_WIDTH);
	background->setX(g_fScreenWidth / 2 - (lobby_sceneNS::BACK_WIDTH / 2) * background->getScale());
	background->setY(-lobby_sceneNS::BACK_MARGIN);

	l_map->initialize(this->graphics, this->input, lobby_sceneNS::MAP_X, lobby_sceneNS::MAP_Y);
	l_unit->initialize(this->graphics, this->input, lobby_sceneNS::UNIT_X, lobby_sceneNS::UNIT_Y);
	l_world->initialize(this->graphics, this->input, g_fScreenWidth / 2 - l_world->getWidth() / 2, lobby_sceneNS::WORLD_Y);
	l_menu->initialize(this->graphics, this->input, lobby_sceneNS::MENU_X, lobby_sceneNS::MENU_Y);
}

void CLobby_Scene::update()
{
	if (SOUNDMANAGER->isPlaySound(lobby_sceneNS::SOUNE_BGM) == false)
		SOUNDMANAGER->play(lobby_sceneNS::SOUNE_BGM, g_fSoundMasterVolume * g_fSoundBGMVolume);

	l_map->update(Game::getTimeDelta());
	l_unit->update(Game::getTimeDelta());
	l_world->update(Game::getTimeDelta());
	l_menu->update(Game::getTimeDelta());
}

void CLobby_Scene::release()
{
	if (SOUNDMANAGER->isPlaySound(lobby_menuNS::SOUNE_BGM) == true)
		SOUNDMANAGER->stop(lobby_menuNS::SOUNE_BGM);

	SAFE_DELETE(background_back);
	SAFE_DELETE(background);
	SAFE_DELETE(l_map);
	SAFE_DELETE(l_unit);
	SAFE_DELETE(l_world);
	SAFE_DELETE(l_menu);
}

void CLobby_Scene::ai()
{
}

void CLobby_Scene::collisions()
{
}

void CLobby_Scene::render()
{
	graphics->spriteBegin();

	background_back->draw();
	background->draw();

	graphics->spriteEnd();
	l_map->render();
	l_unit->render();
	l_world->render();
	l_menu->render();
}

void CLobby_Scene::releaseAll()
{
}

void CLobby_Scene::resetAll()
{
}
