#include "stdafx.h"
#include "world_Scene.h"
#include "world_Battle_UI.h"
#include <iostream>

void CWorld_Scene::worldMove()
{
	if (input->isKeyDown('W'))
	{
		if (worldImage->getY() < 0 - worldmapNS::margin)	//limit up
		{
			worldImage->moveY(worldSpeed);
			//w_action_ship->worldMoveud(worldSpeed);
			player->w_move_ud(worldSpeed);
			computer->w_move_ud(worldSpeed);
			//w_battle_ui->w_move_ud(worldSpeed);
			for (auto iter : w_cg)
				iter->w_move_ud(worldSpeed);
		}
	}
	if (input->isKeyDown('S'))
	{
		if (worldImage->getY() > g_fScreenHeight - worldImage->getHeight() + worldmapNS::margin)	//limit down
		{
			worldImage->moveY(-worldSpeed);
			//w_action_ship->worldMoveud(-worldSpeed);
			player->w_move_ud(-worldSpeed);
			computer->w_move_ud(-worldSpeed);
			//w_battle_ui->w_move_ud(-worldSpeed);
			for (auto iter : w_cg)
				iter->w_move_ud(-worldSpeed);
		}
	}
	if (input->isKeyDown('A'))
	{
		if (worldImage->getX() < 0 - worldmapNS::margin)	//limit left
		{
			worldImage->moveX(worldSpeed);
			//w_action_ship->worldMoverl(worldSpeed);
			player->w_move_rl(worldSpeed);
			computer->w_move_rl(worldSpeed);
			//w_battle_ui->w_move_rl(worldSpeed);
			for (auto iter : w_cg)
				iter->w_move_lr(worldSpeed);
		}
	}
	if (input->isKeyDown('D'))
	{
		if (worldImage->getX() > g_fScreenWidth - worldImage->getWidth() + worldmapNS::margin)	//limit right
		{
			worldImage->moveX(-worldSpeed);
			//w_action_ship->worldMoverl(-worldSpeed);
			player->w_move_rl(-worldSpeed);
			computer->w_move_rl(-worldSpeed);
			//w_battle_ui->w_move_rl(-worldSpeed);
			for (auto iter : w_cg)
				iter->w_move_lr(-worldSpeed);
		}
	}

	//worldmap move speed
	//if (input->isKeyDown('['))
	//{
	//	if (getSpeed() > 10.0f)
	//		setSpeed(getSpeed() - 0.1f);
	//}
	//if (input->isKeyDown(']'))
	//{
	//	if (getSpeed() < 30.0f)
	//		setSpeed(getSpeed() + 0.1f);
	//}

	//else if (input->isKeyDown(ESC_KEY))
	//	PostQuitMessage(0);
}

void CWorld_Scene::init_position()
{
	worldImage->moveY(-worldmapNS::margin);
	//w_action_ship->worldMoveud(worldSpeed);
	//player->w_move_ud(-worldmapNS::margin);
	for (auto iter : w_cg)
		iter->w_move_ud(-worldmapNS::margin);

	worldImage->moveX(-worldmapNS::margin);
	//w_action_ship->worldMoverl(worldSpeed);
	//player->w_move_rl(-worldmapNS::margin);
	for (auto iter : w_cg)
		iter->w_move_lr(-worldmapNS::margin);
}

void CWorld_Scene::data_load()
{
	std::vector<std::string> data = loadObjectData(worldmapNS::IS_STATE_NAME);

	if (data[0].compare("New") == false)
	{
		player->initialize(this->graphics, this->input, 200, 200, 200, 200);
		player->new_player();

		save_data();

		return;
	}

	data.clear();

	data = loadObjectData(worldmapNS::LOAD_NAME);

	bool is_begin = false;
	int index = -1;	//player = 0 , computer = 1
	int kind = -1;	//island = 0 , child = 1 , building = 2 , ship = 3
	int stack_end = 0;

	bool is_player = true;

	for (auto iter = data.begin(); iter != data.end(); iter++)
	{
		UINT cur_island = 0;

		CWorld_User* _user = nullptr;
		if ((*iter).compare(" ") == false)
			continue;

		if ((*iter).compare("BEGIN") == false)
		{
			stack_end++;
			continue;
		}

		if ((*iter).compare("END") == false)
		{
			stack_end--;

			if (stack_end == 0)
				cur_island = 0;

			continue;
		}

		if (stack_end > 0)
		{
			if ((*iter).compare("Base") == false)
			{
				iter++;
				
				int _money = std::stoi((*iter++));
				int _iron = std::stoi((*iter++));
				int _fuel = std::stoi((*iter++));
				int _research = std::stoi((*iter++));
				int _turn = std::stoi((*iter++));

				player->initialize(this->graphics, this->input, _money, _iron, _fuel, _research);
				player->setTurn(_turn);

				continue;
			}
			if ((*iter).compare("LOG") == false)
			{
				iter++;

				std::string str = "";
				int stack_count = 1;

				while (stack_count != 0)	// (*iter).compare("END")
				{
					if ((*iter).compare("BEGIN") == false)
					{
						iter++;
						stack_count++;
						continue;
					}
					if ((*iter).compare("END") == false)
					{
						player->print_world_log(str);
						str = "";
						iter++;
						stack_count--;
						continue;
					}

					str += (*iter++) + " ";
					//player->print_world_log((*iter++));
				}
			}
			if ((*iter).compare("Player") == false)
			{
				_user = player;
				is_player = true;
				continue;
			}
			if ((*iter).compare("Computer") == false)
			{
				_user = computer;
				is_player = false;
				continue;
			}

			if (is_player == false)
				continue;

			if ((*iter).compare("Island") == false)
			{
				iter++;

				for (auto dIter : player->get_data()->get_Island())
				{
					if (dIter->getName().compare((*iter)) == false)
					{
						iter++;
						dIter->setTurn(std::stoi((*iter)));
						cur_island = dIter->getID();

						if (is_player == true && cur_island != 0)
						{
							dIter->SetLoadLinkUser(player);

							bool is_island = false;
							for (auto pIter : player->get_island())
							{
								if (pIter->getID() == dIter->getID())
								{
									is_island = true;

									break;
								}
							}
							if (is_island == false)
								player->add_island(dIter);
							
							computer->remove_island(cur_island);
						}

						break;
					}
				}

				continue;
			}

			//if ((*iter).compare("Child") == false);	//no need

			if ((*iter).compare("Building") == false)
			{
				iter++;

				if (is_player)// && (*iter).compare(player->get_data()->get_Building()[0]->getName()))
				{
					for (auto bIter : player->get_data()->get_Building())
					{
						if (bIter->getName().compare((*iter)) == false)
						{
							CBuilding* bObj = new CBuilding;

							bObj->initialize(
								bIter->getName(),
								bIter->getID(),
								bIter->get_turn(),
								bIter->get_building(),
								bIter->get_need_resource()[MONEY],
								bIter->get_need_resource()[IRON],
								bIter->get_produce_resource()[MONEY],
								bIter->get_produce_resource()[IRON],
								bIter->get_produce_resource()[FUEL],
								bIter->get_produce_resource()[RESEARCH]
							);
							
							for (int i = 0; i < bIter->get_ship_size(); i++)
								bObj->add_Ship(bIter->get_ship()[i]);
							
							bObj->SetLoadLinkUser(player);
							bObj->SetLoadLinkIsland(player->get_data()->get_Island()[cur_island]);

							player->add_cur_building(bObj->getID());

							int b_size = 0;
							while (player->get_data()->get_Island()[cur_island]->get_Building(b_size) != nullptr)
								b_size++;

							player->get_data()->get_Island()[cur_island]->add_building(b_size, bObj);

							iter++;

							int _turn = std::stoi((*iter++));
							bool _building = std::stoi((*iter++));
							bool _complete = std::stoi((*iter++));
							bool _destroy = std::stoi((*iter++));

							bObj->load(_building, _complete, _destroy, _turn);

							int a_count = 0;

							while ((*iter).compare("END"))
							{
								for (auto sIter : player->get_data()->get_Ship())
								{
									if ((*iter).compare(sIter->getName()) == false)
									{
										CProduction_Ship* sObj = new CProduction_Ship;

										sObj->initialize(
											sIter->getName(),
											sIter->getID(),
											sIter->getTurn(),
											sIter->get_resource(MONEY),
											sIter->get_resource(IRON),
											sIter->get_resource(FUEL),
											sIter->get_resource(RESEARCH),
											sIter->getCost()
										);

										//sObj->SetLoadLinkUser(bObj->get_user());
										
										for (auto aIter : sIter->get_building())
											sObj->add_building(aIter);

										bObj->add_action(a_count++, sObj);
										iter++;
										sObj->set_turn(std::stoi((*iter++)));
										break;
									}
								}
							}

							break;
						}
					}
				}

				continue;
			}

			if ((*iter).compare("Ship") == false)
			{
				iter++;

				for (auto sIter : player->get_data()->get_Ship())
				{
					if ((*iter).compare(sIter->getName()) == false)
					{
						CProduction_Ship* sObj = new CProduction_Ship;

						sObj->initialize(
							sIter->getName(),
							sIter->getID(),
							sIter->getTurn(),
							sIter->get_resource(MONEY),
							sIter->get_resource(IRON),
							sIter->get_resource(FUEL),
							sIter->get_resource(RESEARCH),
							sIter->getCost()
						);

						//sObj->SetLoadLinkUser(bObj->get_user());

						for (auto aIter : sIter->get_building())
							sObj->add_building(aIter);

						iter++;

						//player->get_data()->get_Island()[cur_island]->add_ship(sObj);
						player->add_ship(sObj, player->get_data()->get_Island()[cur_island]);

						bool _move = std::stoi((*iter++));
						bool _fuel = std::stoi((*iter++));

						sObj->load(_move, _fuel);

						player->add_decrease_resource(FUEL, sObj->getCost());

						break;
					}
				}

				continue;
			}
		}
	}
}

void CWorld_Scene::save_data()
{
	save.clear();

	save.emplace_back(worldbattleNS::FILE_START);
	save.emplace_back("Base ");
	save.emplace_back(std::to_string(player->get_resource(MONEY)));
	save.emplace_back(" ");
	save.emplace_back(std::to_string(player->get_resource(IRON)));
	save.emplace_back(" ");
	save.emplace_back(std::to_string(player->get_resource(FUEL)));
	save.emplace_back(" ");
	save.emplace_back(std::to_string(player->get_resource(RESEARCH)));
	save.emplace_back(" ");
	save.emplace_back(std::to_string(player->get_turn()));
	save.emplace_back(worldbattleNS::FILE_FINISH);

	save.emplace_back(worldbattleNS::FILE_START);
	save.emplace_back("LOG\n");
	for (auto iter : player->get_log_message())
	{
		save.emplace_back(iter);
		save.emplace_back("\n");
	}
	save.emplace_back(worldbattleNS::FILE_FINISH);

	save.emplace_back(worldbattleNS::FILE_START);
	save.emplace_back("Player\n");

	for (auto iter : player->get_island())
	{
		save.emplace_back("\t");
		save.emplace_back(worldbattleNS::FILE_START);
		save.emplace_back("Island");
		save.emplace_back(" ");
		save.emplace_back(iter->getName());
		save.emplace_back(" ");
		save.emplace_back(std::to_string(iter->getTurn()));
		save.emplace_back("\n");

		//for (auto cIter : iter->get_child())
		//{
		//	save.emplace_back("\t\t");
		//	save.emplace_back(worldbattleNS::FILE_START);
		//	save.emplace_back("Child");
		//	save.emplace_back(" ");
		//	save.emplace_back(std::to_string(cIter->get_type()));
		//	save.emplace_back(" ");
		//	save.emplace_back(std::to_string(cIter->get_resource()));
		//	save.emplace_back(worldbattleNS::FILE_FINISH);
		//}

		for (int i = 0; i < iter->get_Building_Size(); i++)
		{
			if (iter->get_Building(i) == nullptr)
				continue;

			save.emplace_back("\t\t");
			save.emplace_back(worldbattleNS::FILE_START);
			save.emplace_back("Building");
			save.emplace_back(" ");
			save.emplace_back(iter->get_Building(i)->getName());
			save.emplace_back(" ");
			save.emplace_back(std::to_string(iter->get_Building(i)->get_turn()));
			save.emplace_back(" ");
			if (iter->get_Building(i)->get_is_building() == true)
				save.emplace_back(std::to_string(1));
			else save.emplace_back(std::to_string(0));
			//save.emplace_back(std::to_string(iter->get_Building(i)->get_is_building()));
			save.emplace_back(" ");
			if (iter->get_Building(i)->get_is_complete() == true)
				save.emplace_back(std::to_string(1));
			else save.emplace_back(std::to_string(0));
			//save.emplace_back(std::to_string(iter->get_Building(i)->get_is_complete()));
			save.emplace_back(" ");
			if (iter->get_Building(i)->get_is_destroy() == true)
				save.emplace_back(std::to_string(1));
			else save.emplace_back(std::to_string(0));
			//save.emplace_back(std::to_string(iter->get_Building(i)->get_is_destroy()));

			for (int j = 0; j < worldbattleNS::ACTION_SIZE; j++)
			{
				if (iter->get_Building(i)->get_action(j) == nullptr)
					break;

				save.emplace_back(" ");
				save.emplace_back(iter->get_Building(i)->get_action(j)->getName());
				save.emplace_back(" ");
				save.emplace_back(std::to_string(iter->get_Building(i)->get_action(j)->getTurn()));
			}

			save.emplace_back(worldbattleNS::FILE_FINISH);
		}

		for (auto sIter : iter->get_ship())
		{
			save.emplace_back("\t\t");
			save.emplace_back(worldbattleNS::FILE_START);
			save.emplace_back("Ship");
			save.emplace_back(" ");
			save.emplace_back(sIter->getName());
			save.emplace_back(" ");
			if (sIter->get_is_move() == true)
				save.emplace_back(std::to_string(1));
			else save.emplace_back(std::to_string(0));
			//save.emplace_back(std::to_string(sIter->get_is_move()));
			save.emplace_back(" ");
			if (sIter->get_is_fuel() == true)
				save.emplace_back(std::to_string(1));
			else save.emplace_back(std::to_string(0));
			//save.emplace_back(std::to_string(sIter->get_is_fuel()));
			save.emplace_back(worldbattleNS::FILE_FINISH);
		}

		save.emplace_back(worldbattleNS::FILE_FINISH);
	}

	save.emplace_back(worldbattleNS::FILE_FINISH);

	//////////////////////////////////////////////////
	save.emplace_back("\n");

	save.emplace_back(worldbattleNS::FILE_START);
	save.emplace_back("Computer\n");

	for (auto iter : player->get_data()->get_Island())
	{
		bool exist = false;

		for (auto pIter : player->get_island())
		{
			if (iter->getID() == pIter->getID())
			{
				exist = true;
				break;
			}
		}

		if (exist == true)
			continue;

		save.emplace_back("\t");
		save.emplace_back(worldbattleNS::FILE_START);
		save.emplace_back("Island");
		save.emplace_back(" ");
		save.emplace_back(iter->getName());
		save.emplace_back(" ");
		save.emplace_back(std::to_string(iter->getTurn()));
		save.emplace_back("\n");

		//for (auto cIter : iter->get_child())
		//{
		//	save.emplace_back("\t\t");
		//	save.emplace_back(worldbattleNS::FILE_START);
		//	save.emplace_back("Child");
		//	save.emplace_back(" ");
		//	save.emplace_back(std::to_string(cIter->get_type()));
		//	save.emplace_back(" ");
		//	save.emplace_back(std::to_string(cIter->get_resource()));
		//	save.emplace_back(worldbattleNS::FILE_FINISH);
		//}

		for (int i = 0; i < iter->get_Building_Size(); i++)
		{
			if (iter->get_Building(i) == nullptr)
				continue;

			save.emplace_back("\t\t");
			save.emplace_back(worldbattleNS::FILE_START);
			save.emplace_back("Building");
			save.emplace_back(" ");
			save.emplace_back(iter->get_Building(i)->getName());
			save.emplace_back(" ");
			save.emplace_back(std::to_string(iter->get_Building(i)->get_turn()));
			save.emplace_back(" ");
			if (iter->get_Building(i)->get_is_building() == true)
				save.emplace_back(std::to_string(1));
			else save.emplace_back(std::to_string(0));
			//save.emplace_back(std::to_string(iter->get_Building(i)->get_is_building()));
			save.emplace_back(" ");
			if (iter->get_Building(i)->get_is_complete() == true)
				save.emplace_back(std::to_string(1));
			else save.emplace_back(std::to_string(0));
			//save.emplace_back(std::to_string(iter->get_Building(i)->get_is_complete()));
			save.emplace_back(" ");
			if (iter->get_Building(i)->get_is_destroy() == true)
				save.emplace_back(std::to_string(1));
			else save.emplace_back(std::to_string(0));
			//save.emplace_back(std::to_string(iter->get_Building(i)->get_is_destroy()));

			for (int j = 0; j < worldbattleNS::ACTION_SIZE; j++)
			{
				if (iter->get_Building(i)->get_action(j) == nullptr)
					break;

				save.emplace_back(" ");
				save.emplace_back(iter->get_Building(i)->get_action(j)->getName());
				save.emplace_back(" ");
				save.emplace_back(std::to_string(iter->get_Building(i)->get_action(j)->getTurn()));
			}

			save.emplace_back(worldbattleNS::FILE_FINISH);
		}

		for (auto sIter : iter->get_ship())
		{
			save.emplace_back("\t\t");
			save.emplace_back(worldbattleNS::FILE_START);
			save.emplace_back("Ship");
			save.emplace_back(" ");
			save.emplace_back(sIter->getName());
			save.emplace_back(" ");
			if (sIter->get_is_move() == true)
				save.emplace_back(std::to_string(1));
			else save.emplace_back(std::to_string(0));
			//save.emplace_back(std::to_string(sIter->get_is_move()));
			save.emplace_back(" ");
			if (sIter->get_is_fuel() == true)
				save.emplace_back(std::to_string(1));
			else save.emplace_back(std::to_string(0));
			//save.emplace_back(std::to_string(sIter->get_is_fuel()));
			save.emplace_back(worldbattleNS::FILE_FINISH);
		}

		save.emplace_back(worldbattleNS::FILE_FINISH);
	}

	save.emplace_back(worldbattleNS::FILE_FINISH);

	TXTDATA_PARSER->saveDataFromArray(worldbattleNS::FILE_PATH, save);
}

CWorld_Scene::CWorld_Scene()
{
	//w_resource_ui = new CWorld_Resource_UI;
	//w_turn_ui = new CWorld_Turn_UI;
	//w_log_ui = new CWorld_Log_UI;
	//w_minimap_ui = new CWorld_Minimap_UI;
	w_scene_ui = new CWorld_Scene_UI;

	//w_battle_ui = new CWorld_Battle_UI;

	data_island = new CWorld_Island_Data;
	//w_action_ship = new CWorld_Action_Ship;

	player = new CWorld_Player;
	computer = new CWorld_Computer;

	worldImage = new Image;
	worldSpeed = worldmapNS::speed;

	my_turn = true;
}

CWorld_Scene::~CWorld_Scene()
{
	//SAFE_DELETE(); 필수 필수
}

std::vector<std::string> CWorld_Scene::loadObjectData(std::string name)
{
	std::vector<std::string> vData = TXTDATA_PARSER->loadDataToArray(name);


	std::vector<std::string> vRecogData;
	for (auto iter : vData)
	{
		ReplaceStringInPlace(iter, "\t", " ");

		std::istringstream iss(iter);
		std::string token;
		while (std::getline(iss, token, ' '))
		{
			vRecogData.emplace_back(token);
		}
	}

	return vRecogData;
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

void CWorld_Scene::ReplaceStringInPlace(std::string & subject, const std::string & search, const std::string & replace)
{
	size_t pos = 0;
	while ((pos = subject.find(search, pos)) != std::string::npos)
	{
		subject.replace(pos, search.length(), replace);
		pos += replace.length();
	}
}

void CWorld_Scene::initialize(HWND hwnd)
{
	Game::initialize(hwnd);

	//w_turn_ui->SetLoadLinkPlayer(player);

	//w_resource_ui->initialize(this->graphics, this->input);
	//w_turn_ui->initialize(this->graphics, this->input);
	//w_log_ui->initialize(this->graphics, this->input);
	////w_minimap_ui->initialze(this->graphics, this->input);
	w_scene_ui->SetLoadLinkPlayer(player);
	w_scene_ui->initialize(this->graphics, this->input);
	player->SetLoadLinkUI(w_scene_ui);
	player->SetLoadLinkScene(this);
	computer->SetLoadLinkScene(this);
	
	//w_battle_ui->initialize(this->graphics, this->input, 1865, 1497);
	
	data_island->SetLoadLinkPlayer(player);	//player & computer -> data_island
	data_island->SetLoadLinkComputer(computer);
	
	data_island->initialize(this->graphics, this->input);	//데이터 전체
	//w_action_ship->initialize(this->graphics, this->input);

	player->SetLoadLinkData(data_island);	//data_island -> player & computer

	worldImage->initialize(this->graphics, worldmapNS::width, worldmapNS::height, 0, IMAGEMANAGER->getTexture(worldmapNS::img_name));
	//worldImage->setX(-worldmapNS::margin);	//margin value
	//worldImage->setY(-worldmapNS::margin);
	worldImage->setX(0);	//margin value
	worldImage->setY(0);
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

	//================= cg test ======================

	//CWorld_CG* obj = new CWorld_CG;
	//obj->initialize(this->graphics, this->input);
	//obj->SetLoadLinkUser(player);
	//obj->create_battle_cg(1000, 1000);
	//obj->create_move_ship_cg(player->get_island()[0]->getPt(), player->get_island()[1]->getPt());
	//obj->create_move_ship_cg(player->get_island()[1]->getPt(), player->get_island()[0]->getPt());
	//obj->create_move_ship_cg(player->get_island()[1]->getPt(), player->get_island()[3]->getPt());
	//obj->create_move_ship_cg(player->get_island()[3]->getPt(), player->get_island()[1]->getPt());
	//w_cg.emplace_back(obj);
	//================================================
	//player->initialize(this->graphics, this->input, 200, 200, 200, 200);
	computer->initialize(this->graphics, this->input, 0, 0, 0, 0);
	///////////////////////////////////////////////////

	init_position();

	data_load();

	if (SOUNDMANAGER->isPlaySound(worldmapNS::SOUND_BGM) == false)
		SOUNDMANAGER->play(worldmapNS::SOUND_BGM, g_fSoundMasterVolume * g_fSoundBGMVolume);

	bgm_list.emplace_back(worldmapNS::SOUND_BGM);

	for (int i = 0; i < worldmapNS::SOUND_LIST; i++)
		bgm_list.emplace_back(worldmapNS::SOUND_BGM + std::to_string(i));
}

void CWorld_Scene::update()
{
	bool is_bgm = false;

	for (auto iter : bgm_list)
	{
		if (SOUNDMANAGER->isPlaySound(iter) == false)
		{
			is_bgm = true;

			break;
		}
	}

	if (is_bgm == false)
		SOUNDMANAGER->play(worldmapNS::SOUND_BGM + std::to_string(rand() % 5), g_fSoundMasterVolume * g_fSoundBGMVolume);

	worldMove();

	//world UI
	//w_resource_ui->update(Game::getTimeDelta());
	//w_turn_ui->update(Game::getTimeDelta());
	//w_log_ui->update(Game::getTimeDelta());
	player->set_is_update(true);
	w_scene_ui->set_is_update(true);

	for (auto iter = w_cg.begin(); iter != w_cg.end();)
	{
		player->set_is_update(false);
		w_scene_ui->set_is_update(false);
		(*iter)->update(Game::getTimeDelta());

		if ((*iter)->get_is_complete() == true)
		{
			SAFE_DELETE(*iter);
			w_cg.erase(iter);
		}
		else iter++;
	}

	//if (w_cg.size() > 0)
	//	w_scene_ui->set_is_update(false);
	//else w_scene_ui->set_is_update(true);

	//w_action_ship->update(Game::getTimeDelta());
	

	//for (auto iter : w_cg)
	//{
	//	iter->update(Game::getTimeDelta());

	//	if (iter->get_is_complete() == true)
	//		SAFE_DELETE(iter);
	//}

	player->update(Game::getTimeDelta());
	computer->update(Game::getTimeDelta());

	w_scene_ui->update(Game::getTimeDelta());
	//if (input->wasKeyPressed('Q'))
	//	player->add_ship(data_island->get_Ship()[1], player->get_island()[0]);

	//w_battle_ui->update(Game::getTimeDelta());
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

	computer->render();
	//w_action_ship->render();
	for (auto iter : w_cg)
		iter->render();

	//world UI
	//w_resource_ui->render();
	//w_turn_ui->render();
	//w_log_ui->render();
	
	//w_battle_ui->render();
	player->render();

	w_scene_ui->render();
}

void CWorld_Scene::releaseAll()
{
}

void CWorld_Scene::resetAll()
{
}

