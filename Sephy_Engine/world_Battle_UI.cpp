#include "stdafx.h"
#include "world_Battle_UI.h"
#include "world_Player.h"
#include "world_CG.h"
#include "world_Computer.h"


CWorld_Battle_UI::CWorld_Battle_UI()
{
	rt_infor = { 0, };
	rt_start = { 0, };
	rt_retreat = { 0, };
	rt_auto = { 0, };
	rt_total = { 0, };

	visible = false;
	mouse_up = false;
}


CWorld_Battle_UI::~CWorld_Battle_UI()
{
	SAFE_DELETE(infor_ui);
	SAFE_DELETE(battle_infor);
	SAFE_DELETE(battle_start);
	SAFE_DELETE(battle_retreat);
	SAFE_DELETE(auto_battle);

	save.clear();
}

bool CWorld_Battle_UI::initialize(Graphics * g, Input * i, int _x, int _y)
{
	battle_infor = new Image;
	battle_start = new Image;
	battle_retreat = new Image;
	auto_battle = new Image;

	infor_ui = new CWorld_Battle_Infor_UI;

	m_pGraphics = g;
	m_pInput = i;

	battle_infor->initialize(g, worldbattleNS::width, worldbattleNS::height, 0, IMAGEMANAGER->getTexture(worldbattleNS::INFOR));
	battle_start->initialize(g, worldbattleNS::width, worldbattleNS::height, 0, IMAGEMANAGER->getTexture(worldbattleNS::START));
	battle_retreat->initialize(g, worldbattleNS::width, worldbattleNS::height, 0, IMAGEMANAGER->getTexture(worldbattleNS::RETREAT));
	auto_battle->initialize(g, worldbattleNS::width, worldbattleNS::height, 0, IMAGEMANAGER->getTexture(worldbattleNS::AUTO));

	battle_infor->setX(_x - (worldbattleNS::x + worldbattleNS::width));
	battle_infor->setY(_y - (worldbattleNS::y + worldbattleNS::height / 2));
	battle_start->setX(_x - (worldbattleNS::x + worldbattleNS::width));
	battle_start->setY(_y + (worldbattleNS::y + worldbattleNS::height / 2));
	battle_retreat->setX(_x + worldbattleNS::x);
	battle_retreat->setY(_y - (worldbattleNS::y + worldbattleNS::height / 2));
	auto_battle->setX(_x + worldbattleNS::x);
	auto_battle->setY(_y + (worldbattleNS::y + worldbattleNS::height / 2));

	rt_infor = RectMake(
		battle_infor->getX() - worldbattleNS::MARGIN, 
		battle_infor->getY() - worldbattleNS::text_height,
		worldbattleNS::text_width, 
		worldbattleNS::text_height);
	rt_start = RectMake(
		battle_start->getX() - worldbattleNS::MARGIN,
		battle_start->getY() + (worldbattleNS::text_height - worldbattleNS::height / 2),
		worldbattleNS::text_width, 
		worldbattleNS::text_height);
	rt_retreat = RectMake(
		battle_retreat->getX() + worldbattleNS::MARGIN,
		battle_retreat->getY() - worldbattleNS::text_height,
		worldbattleNS::text_width, 
		worldbattleNS::text_height);
	rt_auto = RectMake(
		auto_battle->getX() + worldbattleNS::MARGIN,
		auto_battle->getY() + (worldbattleNS::text_height - worldbattleNS::height / 2),
		worldbattleNS::text_width,
		worldbattleNS::text_height);
	rt_total = RectMake(rt_infor.left, rt_infor.top, rt_auto.right - rt_infor.left, rt_auto.bottom - rt_infor.top);

	m_dxFont.initialize(g, worldbattleNS::FONT_SIZE, true, false, worldbattleNS::FONT);
	m_dxFont.setFontColor(graphicsNS::YELLOW);
	m_test_font.initialize(g, worldbattleNS::FONT_SIZE, true, false, worldbattleNS::FONT);
	m_test_font.setFontColor(graphicsNS::BLACK);

	visible = true;

	return true;
}

bool CWorld_Battle_UI::initialize(Graphics * g, Input * i)
{
	return false;
}

//**********	calculater auto battle		**********//
void CWorld_Battle_UI::auto_battle_cacul()
{
	int distance;
	int p_n = 0;
	int c_n = 0;

	for (auto iter : player->get_cur_ship())
		p_n += iter->getCost();

	for (auto iter : player->get_data()->get_Island()[battle_island]->get_ship())
		c_n += iter->getCost();

	distance = p_n - c_n;

	if (distance < 0)
	{
		int remain = c_n + distance;

		while (remain - player->get_data()->get_Island()[battle_island]->get_ship()[0]->getCost() >= 0)
		{
			remain -= player->get_data()->get_Island()[battle_island]->get_ship()[0]->getCost();

			SAFE_DELETE(player->get_data()->get_Island()[battle_island]->get_ship()[0]);
			player->get_data()->get_Island()[battle_island]->remove_ship(0);
		}

		for (auto iter : player->get_cur_ship())
			SAFE_DELETE(iter);
		player->clear_cur_ship();
	}
	else if (distance == 0)
	{
		int remain = c_n / 2;

		while (remain - player->get_data()->get_Island()[battle_island]->get_ship()[0]->getCost() >= 0)
		{
			remain -= player->get_data()->get_Island()[battle_island]->get_ship()[0]->getCost();

			SAFE_DELETE(player->get_data()->get_Island()[battle_island]->get_ship()[0]);
			player->get_data()->get_Island()[battle_island]->remove_ship(0);
		}

		remain = p_n / 2;

		while (remain - player->get_cur_ship()[0]->getCost() >= 0)
		{
			remain -= player->get_cur_ship()[0]->getCost();

			SAFE_DELETE(player->get_cur_ship()[0]);
			player->remove_cur_ship(0);
		}

		cg->create_move_ship_cg(
			player->get_data()->get_Island()[battle_island]->getPt(),
			player->get_data()->get_Island()[player->get_select_island()->getID()]->getPt(),
			player->get_select_island()->getID()	//player->get_cur_ship()[0]->getIsland()
		);

		cg->set_is_complete(false);
	}
	else 
	{
		int remain = p_n - distance;

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

		player->get_data()->get_Island()[battle_island]->SetLoadLinkUser(player);
		player->add_island(player->get_data()->get_Island()[battle_island]);
		player->get_computer()->remove_island(battle_island);
	}
	player->get_data()->get_Island()[battle_island]->remove_ship_img();
}

void CWorld_Battle_UI::save_data()
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

	//////////////////////////////////////////////////

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

void CWorld_Battle_UI::update(float frameTime)
{
	if (visible == false)
		return;

	infor_ui->update(frameTime);
	
	if (infor_ui->get_is_show() == true)
		return;

	if (m_pInput->getMouseLButton())
		mouse_up = true;
	else
	{
		if (mouse_up == true)
		{
			if (PtInRect(&rt_start, m_pInput->getMousePt()))	//Exit
			{
				save_data();
				CBattle_DataParser battleParser;
				
				auto worldIndex = player->get_data()->get_Island()[battle_island]->getName();	//island Name (+ _Battle_map)
				auto battleMap = player->get_data()->get_Island()[battle_island]->getName() + "_Battle_Map";
				std::vector<std::string> p_shipList;
				std::vector<std::string> c_shipList;

				for (auto iter : player->get_cur_ship())	//all ship -> seleted ship -> moved ship
					p_shipList.emplace_back(iter->getName());

				for (auto iter : player->get_data()->get_Island()[battle_island]->get_ship())	//computer
					c_shipList.emplace_back(iter->getName());

				battleParser.saveBattleData(worldIndex, battleMap, p_shipList, c_shipList);

				SCENEMANAGER->changeScene("Battle");
				//SCENEMANAGER->changeSceneWithLoading("Battle", "BattleLoading");
			}

			if (PtInRect(&rt_retreat, m_pInput->getMousePt()))	//Retreat
			{
				cg->create_move_ship_cg(
					player->get_data()->get_Island()[battle_island]->getPt(),
					player->get_data()->get_Island()[player->get_select_island()->getID()]->getPt(),
					player->get_select_island()->getID()	//player->get_cur_ship()[0]->getIsland()
				);

				visible = false;
			}

			if (PtInRect(&rt_infor, m_pInput->getMousePt()))	//Infor
			{
				SOUNDMANAGER->play(worldbattleNS::SOUND_OPEN, g_fSoundMasterVolume * g_fSoundEffectVolume);

				infor_ui->SetLoadLinkPlayer(player);
				infor_ui->set_battle_island(battle_island);
				infor_ui->initialize(m_pGraphics, m_pInput);
				infor_ui->set_is_show(true);
			}

			if (PtInRect(&rt_auto, m_pInput->getMousePt()))
			{
				cg->set_is_complete(true);
				auto_battle_cacul();

				visible = false;
			}
		}

		mouse_up = false;
	}
}

void CWorld_Battle_UI::render()
{
	if (visible == false)
		return;

	m_pGraphics->spriteBegin();

	battle_infor->draw();
	battle_start->draw();
	battle_retreat->draw();
	auto_battle->draw();
	
	RECT shadow_infor = rt_infor;
	RECT shadow_start = rt_start;
	RECT shadow_retreat = rt_retreat;
	RECT shadow_battle = rt_auto;

	shadow_infor.left = rt_infor.left + 2;
	shadow_start.left = rt_start.left + 2;
	shadow_retreat.left = rt_retreat.left + 2;
	shadow_battle.left = rt_auto.left + 2;

	shadow_infor.right = rt_infor.right + 2;
	shadow_start.right = rt_start.right + 2;
	shadow_retreat.right = rt_retreat.right + 2;
	shadow_battle.right = rt_auto.right + 2;

	shadow_infor.top = rt_infor.top + 2;
	shadow_start.top = rt_start.top + 2;
	shadow_retreat.top = rt_retreat.top + 2;
	shadow_battle.top = rt_auto.top + 2;

	shadow_infor.bottom = rt_infor.bottom + 2;
	shadow_start.bottom = rt_start.bottom + 2;
	shadow_retreat.bottom = rt_retreat.bottom + 2;
	shadow_battle.bottom = rt_auto.bottom + 2;

	m_test_font.print(worldbattleNS::INFOR_MSG, shadow_infor, DT_RIGHT | DT_VCENTER);
	m_test_font.print(worldbattleNS::START_MSG, shadow_start, DT_RIGHT | DT_VCENTER);
	m_test_font.print(worldbattleNS::RETREAT_MSG, shadow_retreat, DT_LEFT | DT_VCENTER);
	m_test_font.print(worldbattleNS::AUTO_MSG, shadow_battle, DT_LEFT | DT_VCENTER);

	m_dxFont.print(worldbattleNS::INFOR_MSG, rt_infor, DT_RIGHT | DT_VCENTER);
	m_dxFont.print(worldbattleNS::START_MSG, rt_start, DT_RIGHT | DT_VCENTER);
	m_dxFont.print(worldbattleNS::RETREAT_MSG, rt_retreat, DT_LEFT | DT_VCENTER);
	m_dxFont.print(worldbattleNS::AUTO_MSG, rt_auto, DT_LEFT | DT_VCENTER);

	m_pGraphics->spriteEnd();

	infor_ui->render();
}

void CWorld_Battle_UI::release()
{
	infor_ui->release();

	SAFE_DELETE(infor_ui);
	SAFE_DELETE(battle_infor);
	SAFE_DELETE(battle_start);
	SAFE_DELETE(battle_retreat);
	SAFE_DELETE(auto_battle);

	save.clear();
}

void CWorld_Battle_UI::w_move_ud(float _speed)
{
	battle_infor->moveY(_speed);
	battle_start->moveY(_speed);
	battle_retreat->moveY(_speed);
	auto_battle->moveY(_speed);

	rt_infor.top += _speed;
	rt_infor.bottom += _speed;
	rt_start.top += _speed;
	rt_start.bottom += _speed;
	rt_retreat.top += _speed;
	rt_retreat.bottom += _speed;
	rt_auto.top += _speed;
	rt_auto.bottom += _speed;
	rt_total.top += _speed;
	rt_total.bottom += _speed;
}

void CWorld_Battle_UI::w_move_rl(float _speed)
{
	battle_infor->moveX(_speed);
	battle_start->moveX(_speed);
	battle_retreat->moveX(_speed);
	auto_battle->moveX(_speed);

	rt_infor.left += _speed;
	rt_infor.right += _speed;
	rt_start.left += _speed;
	rt_start.right += _speed;
	rt_retreat.left += _speed;
	rt_retreat.right += _speed;
	rt_auto.left += _speed;
	rt_auto.right += _speed;
	rt_total.left += _speed;
	rt_total.right += _speed;
}
