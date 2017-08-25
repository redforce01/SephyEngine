#include "stdafx.h"
#include "world_Atk_List_UI.h"
#include "world_Player.h"
#include "world_Computer.h"
#include "world_Computer_Atk_UI.h"

CWorld_Atk_List_UI::CWorld_Atk_List_UI()
{
	mouse_up = false;

	scroll_mount_island = 0;
	scroll_mount_current = 0;
}

CWorld_Atk_List_UI::~CWorld_Atk_List_UI()
{
	rt_island.clear();
	rt_current.clear();

	SAFE_DELETE(background);
}

void CWorld_Atk_List_UI::rt_make_list()
{
	rt_island.clear();
	rt_current.clear();

	m_dxFont.print(world_atk_list_uiNS::TITLE_MSG, rt_title, DT_CENTER | DT_VCENTER);
	m_dxFont.print(world_atk_list_uiNS::BATTLE_MSG, rt_battle, DT_CENTER | DT_VCENTER);
	m_dxFont.print(world_atk_list_uiNS::AUTO_MSG, rt_auto, DT_CENTER | DT_VCENTER);
	m_dxFont.print(world_atk_list_uiNS::ATK_MSG, rt_island_title, DT_CENTER | DT_VCENTER);
	m_dxFont.print(world_atk_list_uiNS::DEF_MSG, rt_current_title, DT_CENTER | DT_VCENTER);

	int line = world_atk_list_uiNS::LINE;

	int count_scroll = 0;
	int count_line = 0;

	std::map<std::string, int> _ship;

	for (auto iter : player->get_computer()->get_cur_ship())
	{
		player->add_cur_ship(iter);
		iter->SetLoadLinkUser(player);
	}
	player->get_computer()->clear_cur_ship();

	for (auto iter : player->get_cur_ship())
	{
		bool is_ship = false;

		auto mIter = _ship.find(iter->getName());

		if (mIter != _ship.end())
		{
			mIter->second++;
			is_ship = true;
		}

		if (is_ship == false)
			_ship.emplace(iter->getName(), 1);
	}

	for (auto iter : _ship)
	{
		if (count_scroll++ < scroll_mount_island)
			continue;

		if (line < count_line++)
			break;

		RECT rt = RectMake(
			rt_ship_island.left + world_atk_list_uiNS::MARGIN,
			rt_ship_island.top + world_atk_list_uiNS::LIST_HEIGHT * (count_line - 1),	//count_line++ 로 인하여 -1
			world_atk_list_uiNS::LIST_WIDTH, world_atk_list_uiNS::LIST_HEIGHT
		);

		m_dxFont.print(iter.first, rt, DT_LEFT | DT_VCENTER);
		m_dxFont.print(std::to_string(iter.second), rt, DT_RIGHT | DT_VCENTER);

		rt_island.emplace_back(rt);
	}
	_ship.clear();

	count_scroll = 0;
	count_line = 0;

	for (auto iter : player->get_data()->get_Island()[battle_island]->get_ship())
	{
		bool is_ship = false;

		auto mIter = _ship.find(iter->getName());

		if (mIter != _ship.end())
		{
			mIter->second++;
			is_ship = true;
		}

		if (is_ship == false)
			_ship.emplace(iter->getName(), 1);
	}

	for (auto iter : _ship)
	{
		if (count_scroll++ < scroll_mount_current)
			continue;

		if (line < count_line++)
			break;

		RECT rt = RectMake(
			rt_ship_battle.left + world_atk_list_uiNS::MARGIN,
			rt_ship_battle.top + world_atk_list_uiNS::LIST_HEIGHT * (count_line - 1),	//count_line++ 로 인하여 -1
			world_atk_list_uiNS::LIST_WIDTH, world_atk_list_uiNS::LIST_HEIGHT
		);

		m_dxFont.print(iter.first, rt, DT_LEFT + DT_VCENTER);
		m_dxFont.print(std::to_string(iter.second), rt, DT_RIGHT + DT_VCENTER);

		rt_current.emplace_back(rt);
	}
}

void CWorld_Atk_List_UI::scroll()
{
	if (PtInRect(&rt_ship_island, m_pInput->getMousePt()))
	{
		if (m_pInput->isMouseWheelUp())
		{
			if (scroll_mount_island == 0)
				scroll_mount_island = 0;
			else scroll_mount_island--;

			m_pInput->mouseWheelIn(0);
		}
		if (m_pInput->isMouseWheelDown())
		{
			if (scroll_mount_island < player->get_data()->get_Island()[battle_island]->get_Ship_Size() - world_atk_list_uiNS::LINE)
				scroll_mount_island++;

			m_pInput->mouseWheelIn(0);
		}
	}

	if (PtInRect(&rt_ship_battle, m_pInput->getMousePt()))
	{
		if (m_pInput->isMouseWheelUp())
		{
			if (scroll_mount_current == 0)
				scroll_mount_current = 0;
			else scroll_mount_current--;

			m_pInput->mouseWheelIn(0);
		}
		if (m_pInput->isMouseWheelDown())
		{
			if (scroll_mount_current < player->get_cur_ship().size() - world_atk_list_uiNS::LINE)
				scroll_mount_current++;

			m_pInput->mouseWheelIn(0);
		}
	}
}

void CWorld_Atk_List_UI::auto_battle_cacul()
{
	int distance;
	int p_n = 0;
	int c_n = 0;

	for (auto iter : player->get_cur_ship())
		c_n += iter->getCost();

	for (auto iter : player->get_data()->get_Island()[battle_island]->get_ship())
		p_n += iter->getCost();

	distance = p_n - c_n;

	if (distance < 0)
	{
		int remain = c_n + distance;

		while (player->get_data()->get_Island()[battle_island]->get_Ship_Size() > 0)
		{
			SAFE_DELETE(player->get_data()->get_Island()[battle_island]->get_ship()[0]);
			player->get_data()->get_Island()[battle_island]->remove_ship(0);
		}
		player->get_data()->get_Island()[battle_island]->clear_ship();

		while (remain - player->get_cur_ship()[0]->getCost() >= 0)
		{
			remain -= player->get_cur_ship()[0]->getCost();

			SAFE_DELETE(player->get_cur_ship()[0]);
			player->remove_cur_ship(0);
		}

		for (auto iter : player->get_cur_ship())
			player->get_data()->get_Island()[battle_island]->add_ship(iter);

		player->clear_cur_ship();

		player->remove_island(battle_island);
		player->get_computer()->add_island(player->get_data()->get_Island()[battle_island]);
	}
	else if (distance == 0)
	{
		int remain = p_n / 2;

		while (remain - player->get_data()->get_Island()[battle_island]->get_ship()[0]->getCost() >= 0)
		{
			remain -= player->get_data()->get_Island()[battle_island]->get_ship()[0]->getCost();

			SAFE_DELETE(player->get_data()->get_Island()[battle_island]->get_ship()[0]);
			player->get_data()->get_Island()[battle_island]->remove_ship(0);
		}

		while (player->get_cur_ship().size() > 0)
		{
			SAFE_DELETE(player->get_cur_ship()[0]);
			player->remove_cur_ship(0);
		}
		player->clear_cur_ship();
	}
	else
	{
		int remain = p_n - distance;

		while (remain - player->get_data()->get_Island()[battle_island]->get_ship()[0]->getCost() >= 0)
		{
			remain -= player->get_data()->get_Island()[battle_island]->get_ship()[0]->getCost();

			SAFE_DELETE(player->get_data()->get_Island()[battle_island]->get_ship()[0]);
			player->get_data()->get_Island()[battle_island]->remove_ship(0);
		}

		while (player->get_cur_ship().size() > 0)
		{
			SAFE_DELETE(player->get_cur_ship()[0]);
			player->remove_cur_ship(0);
		}
		player->clear_cur_ship();
	}
	player->get_data()->get_Island()[battle_island]->remove_ship_img();
}

void CWorld_Atk_List_UI::save_data()
{
	std::vector<std::string> temp;
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
		if (battle_island == iter->getID())
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

	save.emplace_back(worldbattleNS::FILE_START + "computer");

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

		if (battle_island == iter->getID())
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

bool CWorld_Atk_List_UI::initialize(Graphics * g, Input * i)
{
	background = new Image;

	m_pGraphics = g;
	m_pInput = i;

	background->initialize(
		g, world_atk_list_uiNS::WIDTH,
		world_atk_list_uiNS::HEIGHT, 0,
		IMAGEMANAGER->getTexture(world_atk_list_uiNS::BACK_NAME)
	);
	background->setX(g_fScreenWidth / 2 - world_atk_list_uiNS::WIDTH / 2);
	background->setY(g_fScreenHeight / 2 - world_atk_list_uiNS::HEIGHT / 2);

	rt_ship_island = RectMake(
		background->getX() + world_atk_list_uiNS::X,
		background->getY() + world_atk_list_uiNS::Y,
		world_atk_list_uiNS::RT_WIDTH,
		world_atk_list_uiNS::RT_HEIGHT
	);
	rt_ship_battle = RectMake(
		rt_ship_island.right + world_atk_list_uiNS::MID_MARGIN,
		rt_ship_island.top,
		world_atk_list_uiNS::RT_WIDTH,
		world_atk_list_uiNS::RT_HEIGHT
	);
	rt_title = RectMake(
		background->getX() + background->getWidth() / 2 - world_atk_list_uiNS::TITLE_WIDTH / 2,
		background->getY() + world_atk_list_uiNS::MARGIN,
		world_atk_list_uiNS::TITLE_WIDTH, world_atk_list_uiNS::TITLE_HEIGHT
	);

	rt_battle = RectMake(
		background->getX() + background->getWidth() / 2 - world_atk_list_uiNS::BUTTON_WIDTH - world_atk_list_uiNS::MARGIN * 3,
		background->getY() + background->getHeight() - world_atk_list_uiNS::MARGIN - world_atk_list_uiNS::BUTTON_HEIGHT,
		world_atk_list_uiNS::BUTTON_WIDTH, world_atk_list_uiNS::BUTTON_HEIGHT
	);

	rt_auto = RectMake(
		background->getX() + background->getWidth() / 2 + world_atk_list_uiNS::MARGIN * 3,
		background->getY() + background->getHeight() - world_atk_list_uiNS::MARGIN - world_atk_list_uiNS::BUTTON_HEIGHT,
		world_atk_list_uiNS::BUTTON_WIDTH, world_atk_list_uiNS::BUTTON_HEIGHT
	);
	rt_island_title = RectMake(
		rt_ship_island.left,
		rt_ship_island.top - world_atk_list_uiNS::TITLE_HEIGHT,
		world_atk_list_uiNS::RT_WIDTH,
		world_atk_list_uiNS::TITLE_HEIGHT
	);
	rt_current_title = RectMake(
		rt_ship_battle.left,
		rt_ship_battle.top - world_atk_list_uiNS::TITLE_HEIGHT,
		world_atk_list_uiNS::RT_WIDTH,
		world_atk_list_uiNS::TITLE_HEIGHT
	);

	m_dxFont.initialize(g, world_atk_list_uiNS::FONT_SIZE, true, false, world_atk_list_uiNS::FONT);

	return true;
}

void CWorld_Atk_List_UI::update(float frameTime)
{
	player->set_is_update(false);

	if (m_pInput->getMouseLButton())
		mouse_up = true;
	else
	{
		if (mouse_up == true)
		{
			if (PtInRect(&rt_battle, m_pInput->getMousePt()))
			{
				save_data();
				CBattle_DataParser battleParser;

				auto worldIndex = player->get_data()->get_Island()[battle_island]->getName();	//island Name (+ _Battle_map)
				auto battleMap = player->get_data()->get_Island()[battle_island]->getName() + "_Battle_Map";
				std::vector<std::string> p_shipList;
				std::vector<std::string> c_shipList;

				for (auto iter : player->get_cur_ship())	//all ship -> seleted ship -> moved ship
					c_shipList.emplace_back(iter->getName());

				for (auto iter : player->get_data()->get_Island()[battle_island]->get_ship())	//computer
					p_shipList.emplace_back(iter->getName());

				battleParser.saveBattleData(worldIndex, battleMap, p_shipList, c_shipList);

				SCENEMANAGER->changeScene("Battle");
			}
			if (PtInRect(&rt_auto, m_pInput->getMousePt()))
			{
				auto_battle_cacul();
				w_atk_ui->set_is_show(false);
				player->set_is_update(true);
			}
		}

		mouse_up = false;
	}

	scroll();
}

void CWorld_Atk_List_UI::render()
{
	m_pGraphics->spriteBegin();

	background->draw();

	rt_make_list();

	m_pGraphics->spriteEnd();

	m_pGraphics->drawRect(rt_battle);
	m_pGraphics->drawRect(rt_auto);
}

void CWorld_Atk_List_UI::release()
{
	rt_island.clear();
	rt_current.clear();

	SAFE_DELETE(background);
}
