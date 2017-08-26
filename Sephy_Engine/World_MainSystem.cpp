#include "stdafx.h"
#include "World_MainSystem.h"
#include "Battle_ResultSystem.h"


CWorld_MainSystem::CWorld_MainSystem()
{
	worldSpeed = world_systemNS::speed;
	my_turn = true;
}


CWorld_MainSystem::~CWorld_MainSystem()
{
	SAFE_DELETE(worldImage);

	for (auto iter : w_cg)
		SAFE_DELETE(iter);
	w_cg.clear();
	save.clear();

	for (auto iter : bgm_list)
	{
		if (SOUNDMANAGER->isPlaySound(iter) == true)
		{
			SOUNDMANAGER->stop(iter);

			break;
		}
	}
	bgm_list.clear();

	if (player != nullptr)
		SAFE_DELETE(player);

	if (computer != nullptr)
		SAFE_DELETE(computer);

	if (data_island != nullptr)
		SAFE_DELETE(data_island);

	if (w_scene_ui != nullptr)
		SAFE_DELETE(w_scene_ui);
}

//**********	world camera move	***********//
void CWorld_MainSystem::worldMove()
{
	if (m_pInput->isKeyDown('W'))
	{
		if (worldImage->getY() < 0 - world_systemNS::margin)	//limit up
		{
			worldImage->moveY(worldSpeed);
			player->w_move_ud(worldSpeed);
			computer->w_move_ud(worldSpeed);
			for (auto iter : w_cg)
				iter->w_move_ud(worldSpeed);
		}
	}
	if (m_pInput->isKeyDown('S'))
	{
		if (worldImage->getY() > g_fScreenHeight - worldImage->getHeight() + world_systemNS::margin)	//limit down
		{
			worldImage->moveY(-worldSpeed);
			player->w_move_ud(-worldSpeed);
			computer->w_move_ud(-worldSpeed);
			for (auto iter : w_cg)
				iter->w_move_ud(-worldSpeed);
		}
	}
	if (m_pInput->isKeyDown('A'))
	{
		if (worldImage->getX() < 0 - world_systemNS::margin)	//limit left
		{
			worldImage->moveX(worldSpeed);
			player->w_move_rl(worldSpeed);
			computer->w_move_rl(worldSpeed);
			for (auto iter : w_cg)
				iter->w_move_lr(worldSpeed);
		}
	}
	if (m_pInput->isKeyDown('D'))
	{
		if (worldImage->getX() > g_fScreenWidth - worldImage->getWidth() + world_systemNS::margin)	//limit right
		{
			worldImage->moveX(-worldSpeed);
			player->w_move_rl(-worldSpeed);
			computer->w_move_rl(-worldSpeed);
			for (auto iter : w_cg)
				iter->w_move_lr(-worldSpeed);
		}
	}
}

//**********	image initialize	***********//
void CWorld_MainSystem::init_position()
{
	worldImage->moveY(-world_systemNS::margin);

	for (auto iter : w_cg)
		iter->w_move_ud(-world_systemNS::margin);

	worldImage->moveX(-world_systemNS::margin);

	for (auto iter : w_cg)
		iter->w_move_lr(-world_systemNS::margin);
}

//**********	player & computer data load		**********//
bool CWorld_MainSystem::data_load()
{
	std::vector<std::string> data = loadObjectData(world_systemNS::IS_STATE_NAME);

	if (data[0].compare("New") == false)
	{
		player->initialize(m_pGraphics, m_pInput, 200, 200, 200, 200);
		player->new_player();

		CBattle_DataParser battleParser;

		std::string worldIndex;
		std::string battleMap;
		std::vector<std::string> p_shipList;
		std::vector<std::string> c_shipList;

		battleParser.saveBattleData(worldIndex, battleMap, p_shipList, c_shipList);

		save_data();

		return false;
	}

	data.clear();

	data = loadObjectData(world_systemNS::LOAD_NAME);

	bool is_begin = false;
	int index = -1;	//player = 0 , computer = 1
	int kind = -1;	//island = 0 , child = 1 , building = 2 , ship = 3
	int stack_end = 0;
	int cur_island = 0;

	bool is_player = true;

	for (auto iter = data.begin(); iter != data.end(); iter++)
	{
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

				player->initialize(m_pGraphics, m_pInput, _money, _iron, _fuel, _research);
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

							player->add_increase_resource(MONEY, dIter->get_child()[MONEY]->get_resource());
							player->add_increase_resource(IRON, dIter->get_child()[IRON]->get_resource());
							player->add_increase_resource(FUEL, dIter->get_child()[FUEL]->get_resource());

							computer->remove_island(cur_island);
						}

						break;
					}
				}

				continue;
			}

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
							player->add_increase_resource(MONEY, bIter->get_produce_resource()[MONEY]);
							player->add_increase_resource(IRON, bIter->get_produce_resource()[IRON]);
							player->add_increase_resource(FUEL, bIter->get_produce_resource()[FUEL]);
							player->add_increase_resource(RESEARCH, bIter->get_produce_resource()[RESEARCH]);

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

										for (auto aIter : sIter->get_building())
											sObj->add_building(aIter);

										bObj->add_action(a_count++, sObj);
										iter++;
										sObj->set_turn(std::stoi((*iter)));
										break;
									}
								}
								iter++;
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
						sObj->set_is_create(true);
						sObj->set_is_complete(true);
						sObj->set_turn(0);

						player->add_decrease_resource(FUEL, sObj->getCost());

						break;
					}
				}

				continue;
			}
		}
	}
	return true;
}

//**********	computer ship data load	**********//
void CWorld_MainSystem::computer_data(CWorld_Island* _island)
{
	std::vector<std::string> data = loadObjectData(world_systemNS::COMPUTER_NAME);

	for (auto iter = data.begin(); iter != data.end();)
	{
		if ((*iter++).compare(_island->getName()) == false)
		{
			while ((*iter).compare(world_systemNS::FILE_FINISH))
			{
				CProduction_Ship* obj = nullptr;

				for (auto sIter : player->get_data()->get_Ship())
				{
					if ((*iter).compare(sIter->getName()) == false)
					{
						obj = sIter;

						break;
					}
				}

				iter++;

				if (obj == nullptr)
					continue;

				int temp = std::stoi(*iter);

				for (int i = 0; i < temp; i++)
				{
					CProduction_Ship* _ship = new CProduction_Ship;

					_ship->initialize(
						obj->getName(),
						obj->getID(),
						obj->getTurn(),
						obj->get_resource(MONEY),
						obj->get_resource(IRON),
						obj->get_resource(FUEL),
						obj->get_resource(RESEARCH),
						obj->getCost()
					);

					_ship->SetLoadLinkUser(computer);

					for (auto aIter : obj->get_building())
						_ship->add_building(aIter);

					_ship->load(true, true);
					_ship->set_is_create(true);
					_ship->set_is_complete(true);
					_ship->set_turn(0);

					_island->add_ship(_ship);
				}
			}
		}
	}
}

//**********	battle area data load 	***********//
void CWorld_MainSystem::battle_result_load()
{
	CBattle_ResultSystem parser;

	parser.loadBattleResult();

	std::string worldIndex = parser.getResultWorldIndex();
	auto vPlayerShips = parser.getResultPlayerShips();
	auto vComputerShips = parser.getResultComputerShips();

	CWorld_Island* _island = nullptr;

	for (auto iter : player->get_data()->get_Island())	//Check island ID
	{
		if (iter->getName().compare(worldIndex) == false)
		{
			_island = iter;

			break;
		}
	}

	if (_island == nullptr)
		return;

	for (int i = 0; i < _island->get_Ship_Size(); i++)
		_island->remove_ship(0);

	if (vPlayerShips.size() > vComputerShips.size())
	{
		bool _exist = false;
		for (auto iter : player->get_island())
		{
			if (iter->getName().compare(_island->getName()) == false)
			{
				_exist = true;
				break;
			}
		}

		if (_exist == false)
		{
			player->add_island(_island);
			computer->remove_island(_island->getID());
			_island->SetLoadLinkUser(player);
		}

		for (auto iter : vPlayerShips)
		{
			for (auto sIter : player->get_data()->get_Ship())
			{
				if (iter.compare(sIter->getName()) == false)
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

					sObj->SetLoadLinkUser(player);

					for (auto aIter : sIter->get_building())
						sObj->add_building(aIter);

					sObj->load(true, true);
					sObj->set_is_create(true);
					sObj->set_is_complete(true);
					sObj->set_turn(0);

					_island->add_ship(sObj);

					player->add_decrease_resource(FUEL, sObj->getCost());
				}
			}
		}
	}
	else
	{
		for (auto iter : vComputerShips)
		{
			for (auto sIter : player->get_data()->get_Ship())
			{
				if (iter.compare(sIter->getName()) == false)
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

					sObj->SetLoadLinkUser(computer);

					for (auto aIter : sIter->get_building())
						sObj->add_building(aIter);

					_island->add_ship(sObj);
				}
			}
		}
	}
}

//**********	save world's (player & computer) data	***********//
void CWorld_MainSystem::save_data()
{
	std::vector<std::string> temp;

	TXTDATA_PARSER->saveDataFromArray(world_systemNS::FILE_PATH, temp);
	temp.emplace_back(worldbattleNS::STATE_PLAY);
	TXTDATA_PARSER->saveDataFromArray(worldbattleNS::FILE_STATE_PATH, temp);

	save.clear();

	save.emplace_back(
		worldbattleNS::FILE_START + "Base " +
		std::to_string(player->get_resource(MONEY)) + " " +
		std::to_string(player->get_resource(IRON)) + " " +
		std::to_string(player->get_resource(FUEL)) + " " +
		std::to_string(player->get_resource(RESEARCH)) + " " +
		std::to_string(player->get_turn()) + " " +
		worldbattleNS::FILE_FINISH
	);

	save.emplace_back(worldbattleNS::FILE_START + "LOG");

	std::deque<std::string> reverse;

	for (auto iter : player->get_log_message())
		reverse.emplace_front("\t" + iter);

	for (auto iter : reverse)
		save.emplace_back(worldbattleNS::FILE_START + iter + " " + worldbattleNS::FILE_FINISH);

	save.emplace_back(worldbattleNS::FILE_FINISH);

	save.emplace_back(worldbattleNS::FILE_START + "Player");

	for (auto iter : player->get_island())
	{
		save.emplace_back("\t" + worldbattleNS::FILE_START + "Island " + iter->getName() + " " + std::to_string(iter->getTurn()));

		for (int i = 0; i < iter->get_Building_Size(); i++)
		{
			if (iter->get_Building(i) == nullptr)
				continue;

			std::vector<std::string> build_info;

			if (iter->get_Building(i)->get_is_building() == true)
				build_info.emplace_back(std::to_string(1));
			else build_info.emplace_back(std::to_string(0));
			if (iter->get_Building(i)->get_is_complete() == true)
				build_info.emplace_back(std::to_string(1));
			else build_info.emplace_back(std::to_string(0));
			if (iter->get_Building(i)->get_is_destroy() == true)
				build_info.emplace_back(std::to_string(1));
			else build_info.emplace_back(std::to_string(0));

			save.emplace_back(
				"\t\t" + worldbattleNS::FILE_START + "Building " +
				iter->get_Building(i)->getName() + " " +
				std::to_string(iter->get_Building(i)->get_turn()) + " " +
				build_info[0] + " " + build_info[1] + " " + build_info[2]
			);

			for (int j = 0; j < worldbattleNS::ACTION_SIZE; j++)
			{
				if (iter->get_Building(i)->get_action(j) == nullptr)
					break;

				save.emplace_back(
					" " + iter->get_Building(i)->get_action(j)->getName() +
					" " + std::to_string(iter->get_Building(i)->get_action(j)->getTurn())
				);
			}

			save.emplace_back("\t\t" + worldbattleNS::FILE_FINISH);
		}

		for (auto sIter : iter->get_ship())
		{
			std::vector<std::string> ship_info;

			if (sIter->get_is_move() == true)
				ship_info.emplace_back(std::to_string(1));
			else ship_info.emplace_back(std::to_string(0));
			if (sIter->get_is_fuel() == true)
				ship_info.emplace_back(std::to_string(1));
			else ship_info.emplace_back(std::to_string(0));

			save.emplace_back(
				"\t\t" + worldbattleNS::FILE_START + "Ship " +
				sIter->getName() + " " + ship_info[0] + " " +
				ship_info[1] + " " + worldbattleNS::FILE_FINISH
			);
		}

		save.emplace_back("\t" + worldbattleNS::FILE_FINISH);
	}

	save.emplace_back(worldbattleNS::FILE_FINISH);

	save.emplace_back(worldbattleNS::FILE_START + "Computer");

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

		save.emplace_back("\t" + worldbattleNS::FILE_START + "Island " + iter->getName() + " " + std::to_string(iter->getTurn()));

		for (int i = 0; i < iter->get_Building_Size(); i++)
		{
			if (iter->get_Building(i) == nullptr)
				continue;

			std::vector<std::string> build_info;

			if (iter->get_Building(i)->get_is_building() == true)
				build_info.emplace_back(std::to_string(1));
			else build_info.emplace_back(std::to_string(0));
			if (iter->get_Building(i)->get_is_complete() == true)
				build_info.emplace_back(std::to_string(1));
			else build_info.emplace_back(std::to_string(0));
			if (iter->get_Building(i)->get_is_destroy() == true)
				build_info.emplace_back(std::to_string(1));
			else build_info.emplace_back(std::to_string(0));

			save.emplace_back(
				"\t\t" + worldbattleNS::FILE_START + "Building " +
				iter->get_Building(i)->getName() + " " +
				std::to_string(iter->get_Building(i)->get_turn()) + " " +
				build_info[0] + " " + build_info[1] + " " + build_info[2]
			);

			for (int j = 0; j < worldbattleNS::ACTION_SIZE; j++)
			{
				if (iter->get_Building(i)->get_action(j) == nullptr)
					break;

				save.emplace_back(
					" " + iter->get_Building(i)->get_action(j)->getName() +
					" " + std::to_string(iter->get_Building(i)->get_action(j)->getTurn())
				);
			}

			save.emplace_back(worldbattleNS::FILE_FINISH);
		}

		for (auto sIter : iter->get_ship())
		{
			std::vector<std::string> ship_info;

			if (sIter->get_is_move() == true)
				ship_info.emplace_back(std::to_string(1));
			else ship_info.emplace_back(std::to_string(0));
			//save.emplace_back(std::to_string(sIter->get_is_move()));
			if (sIter->get_is_fuel() == true)
				ship_info.emplace_back(std::to_string(1));
			else ship_info.emplace_back(std::to_string(0));

			save.emplace_back(
				"\t\t" + worldbattleNS::FILE_START + "Ship " +
				sIter->getName() + " " + ship_info[0] + " " +
				ship_info[1] + " " + worldbattleNS::FILE_FINISH
			);
		}

		save.emplace_back(worldbattleNS::FILE_FINISH);
	}

	save.emplace_back(worldbattleNS::FILE_FINISH);

	TXTDATA_PARSER->saveDataFromArray(worldbattleNS::FILE_PATH, save);
}


//**********	txt file load	***********//
std::vector<std::string> CWorld_MainSystem::loadObjectData(std::string name)
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

//**********	camera location move	***********//
void CWorld_MainSystem::jump_camera(float _x, float _y)
{
	int distance_x = g_fScreenWidth / 2 - _x;
	int distance_y = g_fScreenHeight / 2 - _y;

	if (worldImage->getX() + distance_x >= 0 - world_systemNS::margin)
		distance_x = 0 - world_systemNS::margin - worldImage->getX();
	if (worldImage->getX() + distance_x <= g_fScreenWidth - worldImage->getWidth() + world_systemNS::margin)
		distance_x = g_fScreenWidth - worldImage->getWidth() + world_systemNS::margin - worldImage->getX();
	if (worldImage->getY() + distance_y >= 0 - world_systemNS::margin)
		distance_y = 0 - world_systemNS::margin - worldImage->getY();
	if (worldImage->getY() + distance_y <= g_fScreenHeight - worldImage->getHeight() + world_systemNS::margin)
		distance_y = g_fScreenHeight - worldImage->getHeight() + world_systemNS::margin - worldImage->getY();

	worldImage->moveX(distance_x);
	player->w_move_rl(distance_x);
	computer->w_move_rl(distance_x);
	for (auto iter : w_cg)
		iter->w_move_lr(distance_x);

	worldImage->moveY(distance_y);
	player->w_move_ud(distance_y);
	computer->w_move_ud(distance_y);
	for (auto iter : w_cg)
		iter->w_move_ud(distance_y);
}

//**********	load file character replace the other character		***********//
void CWorld_MainSystem::ReplaceStringInPlace(std::string & subject, const std::string & search, const std::string & replace)
{
	size_t pos = 0;
	while ((pos = subject.find(search, pos)) != std::string::npos)
	{
		subject.replace(pos, search.length(), replace);
		pos += replace.length();
	}
}

bool CWorld_MainSystem::initialize(Game * gamePtr)
{
	bool success = false;
	try
	{
		m_pGraphics = gamePtr->getGraphics();
		m_pInput = gamePtr->getInput();

		w_scene_ui = new CWorld_Scene_UI;
		data_island = new CWorld_Island_Data;
		player = new CWorld_Player;
		computer = new CWorld_Computer;
		worldImage = new Image;
		
		w_scene_ui->SetLoadLinkPlayer(player);
		w_scene_ui->initialize(m_pGraphics, m_pInput);
		player->SetLoadLinkUI(w_scene_ui);
		player->SetLoadLinkScene(this);

		data_island->SetLoadLinkPlayer(player);	//player & computer -> data_island
		data_island->SetLoadLinkComputer(computer);

		data_island->initialize(m_pGraphics, m_pInput);	//데이터 전체
																//w_action_ship->initialize(this->graphics, this->input);

		player->SetLoadLinkData(data_island);	//data_island -> player & computer
		player->SetLoadLinkComputer(computer);

		worldImage->initialize(m_pGraphics, world_systemNS::width, world_systemNS::height, 0, IMAGEMANAGER->getTexture(world_systemNS::img_name));
		worldImage->setX(0);	//margin value
		worldImage->setY(0);

		computer->initialize(m_pGraphics, m_pInput, 0, 0, 0, 0);
		computer->SetLoadLinkScene(this);

		init_position();

		if (data_load() == true)
			battle_result_load();

		for (auto iter : computer->get_island())
			computer_data(iter);

		if (SOUNDMANAGER->isPlaySound(world_systemNS::SOUND_BGM + std::to_string(0)) == false)
			SOUNDMANAGER->play(world_systemNS::SOUND_BGM + std::to_string(0), g_fSoundMasterVolume * g_fSoundBGMVolume);


		for (int i = 0; i < world_systemNS::SOUND_LIST; i++)
			bgm_list.emplace_back(world_systemNS::SOUND_BGM + std::to_string(i));

		// ======== add ship computer ==========
	}
	catch (...)
	{
		MessageBox(g_hWndEngine, "World MainSystem Initialize Failed", "Error", MB_OK);
	}	
	return success;
}

void CWorld_MainSystem::update(float frameTime)
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
		SOUNDMANAGER->play(world_systemNS::SOUND_BGM + std::to_string(RANDOM_MAKER->GetInt(0, 4)), g_fSoundMasterVolume * g_fSoundBGMVolume);

	worldMove();
	player->set_is_update(true);
	w_scene_ui->set_is_update(true);

	for (auto iter = w_cg.begin(); iter != w_cg.end();)
	{
		player->set_is_update(false);
		w_scene_ui->set_is_update(false);
		(*iter)->update(frameTime);

		if ((*iter)->get_is_complete() == true)
		{
			SAFE_DELETE(*iter);
			w_cg.erase(iter);
		}
		else iter++;
	}

	player->update(frameTime);
	computer->update(frameTime);
	w_scene_ui->update(frameTime);
}

void CWorld_MainSystem::render()
{
	m_pGraphics->spriteBegin();
	worldImage->draw();
	m_pGraphics->spriteEnd();
	computer->render();
	for (auto iter : w_cg)
		iter->render();
	player->render();
	w_scene_ui->render();
}

void CWorld_MainSystem::release()
{
	SAFE_DELETE(worldImage);

	for (auto iter : w_cg)
	{
		iter->release();
		SAFE_DELETE(iter);
	}
	w_cg.clear();
	save.clear();

	for (auto iter : bgm_list)
	{
		if (SOUNDMANAGER->isPlaySound(iter) == true)
		{
			SOUNDMANAGER->stop(iter);

			break;
		}
	}
	bgm_list.clear();

	if (player != nullptr)
	{
		player->release();
		SAFE_DELETE(player);
	}

	if (computer != nullptr)
	{
		computer->release();
		SAFE_DELETE(computer);
	}

	if (data_island != nullptr)
	{
		data_island->release();
		SAFE_DELETE(data_island);
	}

	if (w_scene_ui != nullptr)
	{
		w_scene_ui->release();
		SAFE_DELETE(w_scene_ui);
	}
}
