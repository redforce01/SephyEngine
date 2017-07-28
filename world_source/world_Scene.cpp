#include "stdafx.h"
#include "world_Scene.h"
#include <iostream>

void CWorld_Scene::worldMove()
{
	if (input->isKeyDown('W'))
	{
		if (worldImage->getY() < 0 - worldmapNS::margin)	//limit up
		{
			worldImage->moveY(worldSpeed);
			//w_action_ship->worldMoveud(worldSpeed);
		}
	}
	if (input->isKeyDown('S'))
	{
		if (worldImage->getY() > WINSIZEY - worldImage->getHeight() + worldmapNS::margin)	//limit down
		{
			worldImage->moveY(-worldSpeed);
			//w_action_ship->worldMoveud(-worldSpeed);
		}
	}
	if (input->isKeyDown('A'))
	{
		if (worldImage->getX() < 0 - worldmapNS::margin)	//limit left
		{
			worldImage->moveX(worldSpeed);
			//w_action_ship->worldMoverl(worldSpeed);
		}
	}
	if (input->isKeyDown('D'))
	{
		if (worldImage->getX() > WINSIZEX - worldImage->getWidth() + worldmapNS::margin)	//limit right
		{
			worldImage->moveX(-worldSpeed);
			//w_action_ship->worldMoverl(-worldSpeed);
		}
	}

	//worldmap move speed
	if (input->isKeyDown('['))
	{
		if (getSpeed() > 10.0f)
			setSpeed(getSpeed() - 0.1f);
	}
	if (input->isKeyDown(']'))
	{
		if (getSpeed() < 30.0f)
			setSpeed(getSpeed() + 0.1f);
	}

	//Project quit
	if (input->isKeyDown(ESC_KEY))
	{
		PostQuitMessage(0);
	}
}

CWorld_Scene::CWorld_Scene()
{
	w_resource_ui = new CWorld_Resource_UI;
	w_turn_ui = new CWorld_Turn_UI;
	w_log_ui = new CWorld_Log_UI;
	w_minimap_ui = new CWorld_Minimap_UI;

	w_battle_ui = new CWorld_Battle_UI;

	data_island = new CWorld_Island_Data;
	//w_action_ship = new CWorld_Action_Ship;

	player = new CWorld_Player;
	computer = new CWorld_Computer;

	worldImage = new Image;
	worldSpeed = 10.0f;

	my_turn = true;
}

CWorld_Scene::~CWorld_Scene()
{
	//SAFE_DELETE(); 필수 필수
}

void CWorld_Scene::setSpeed(float speed)
{
	worldSpeed = speed;
}

float CWorld_Scene::getSpeed()
{
	return worldSpeed;
}

void CWorld_Scene::turn_end()
{
	//for (auto iter : w_current_island)
	//	iter->turn_end();

	//Player & Computer turn_end(); -> island -> building & child & ship
}

void CWorld_Scene::initialize(HWND hwnd)
{
	Game::initialize(hwnd);

	w_resource_ui->initialize(this->graphics, this->input);
	w_turn_ui->initialize(this->graphics, this->input);
	w_log_ui->initialize(this->graphics, this->input);
	//w_minimap_ui->initialze(this->graphics, this->input);
	
	w_battle_ui->initialize(this->graphics, this->input, 500, 500);

	data_island->SetLoadLinkPlayer(player);
	data_island->SetLoadLinkComputer(computer);
	
	data_island->initialize(this->graphics, this->input);	//데이터 전체
	//w_action_ship->initialize(this->graphics, this->input);

	worldImage->initialize(this->graphics, 4261, 2067, 0, IMAGEMANAGER->getTexture(worldmapNS::img_name));
	worldImage->setX(-worldmapNS::margin);	//margin value
	worldImage->setY(-worldmapNS::margin);
	//test_start
	//POINT temp = { 1300, 900 };
	//w_action_ship->add_ship("SN_BC_Stalingrad_sd", 300, 300, 60);
	//w_action_ship->get_current_ship()[0]->add_move_point(temp);
	//temp = { 600, 200 };
	//w_action_ship->get_current_ship()[0]->add_move_point(temp);
	//w_action_ship->get_current_ship()[0]->turn_end();
	//test_end
	//============= ship movement test ====================
	//POINT temp = { 1300, 900 };
	//player->initialize(this->graphics, this->input, 0, 0, 0, 0);
	//CProduction_Ship* test_obj = new CProduction_Ship;
	//test_obj->initialize("SN_BC_Stalingrad_sd", 1, 100, 100, 100, 100, 100);
	//test_obj->setX(300);
	//test_obj->setY(300);
	//player->add_ship(test_obj);
	//=====================================================
	//for (auto iter : player->get_island())
	//{
	//	std::cout << "---------------- Player ------------------" << std::endl;
	//	std::cout << "ID : " << iter->getID() << "\t Name : " << iter->getName() << std::endl;
	//}

	//for (auto iter : computer->get_island())
	//{
	//	std::cout << "---------------- Computer ------------------" << std::endl;
	//	std::cout << "ID : " << iter->getID() << "\t Name : " << iter->getName() << std::endl;
	//}
}

void CWorld_Scene::update()
{
	worldMove();

	//world UI
	w_resource_ui->update(Game::getTimeDelta());
	w_turn_ui->update(Game::getTimeDelta());
	w_log_ui->update(Game::getTimeDelta());

	//w_action_ship->update(Game::getTimeDelta());
}

void CWorld_Scene::release()
{
}

void CWorld_Scene::ai()
{
}

void CWorld_Scene::collisions()
{
}

void CWorld_Scene::render()
{
	graphics->spriteBegin();

	worldImage->draw();

	graphics->spriteEnd();

	//w_action_ship->render();

	//world UI
	w_resource_ui->render();
	w_turn_ui->render();
	w_log_ui->render();
	
	w_battle_ui->render();
}

void CWorld_Scene::releaseAll()
{
}

void CWorld_Scene::resetAll()
{
}
