#include "stdafx.h"
#include "world_Player.h"
#include "world_Island_Data.h"
#include "world_Computer.h"


//**********	new campaign player	**********//
void CWorld_Player::new_player()
{
	//initialize comandcenter
	CBuilding* command_center = new CBuilding;
	CBuilding* basic = new CBuilding;

	command_center->SetLoadLinkUser(this);
	command_center->SetLoadLinkIsland(get_data()->get_Island()[0]);
	command_center->initialize(
		get_data()->get_Building()[0]->getName(),
		get_data()->get_Building()[0]->getID(),
		get_data()->get_Building()[0]->get_turn(),
		get_data()->get_Building()[0]->get_building(),
		get_data()->get_Building()[0]->get_need_resource()[MONEY],
		get_data()->get_Building()[0]->get_need_resource()[IRON],
		get_data()->get_Building()[0]->get_produce_resource()[MONEY],
		get_data()->get_Building()[0]->get_produce_resource()[IRON],
		get_data()->get_Building()[0]->get_produce_resource()[FUEL],
		get_data()->get_Building()[0]->get_produce_resource()[RESEARCH]
	);
	command_center->command_center();

	basic->SetLoadLinkUser(this);
	basic->SetLoadLinkIsland(get_data()->get_Island()[0]);
	basic->initialize(
		get_data()->get_Building()[1]->getName(),
		get_data()->get_Building()[1]->getID(),
		get_data()->get_Building()[1]->get_turn(),
		get_data()->get_Building()[1]->get_building(),
		get_data()->get_Building()[1]->get_need_resource()[MONEY],
		get_data()->get_Building()[1]->get_need_resource()[IRON],
		get_data()->get_Building()[1]->get_produce_resource()[MONEY],
		get_data()->get_Building()[1]->get_produce_resource()[IRON],
		get_data()->get_Building()[1]->get_produce_resource()[FUEL],
		get_data()->get_Building()[1]->get_produce_resource()[RESEARCH]
	);

	for (int i = 0; i < get_data()->get_Building()[1]->get_ship_size(); i++)
		basic->add_Ship(get_data()->get_Building()[1]->get_ship()[i]);
	basic->load(true, true, false, 0);

	add_cur_building(basic->getID());

	get_island()[0]->add_building(0, command_center);
	get_island()[0]->add_building(1, basic);
}

//**********	computer attack player probability	**********//
void CWorld_Player::atk_player()
{
	if (turn <= 5)
		return;

	turn_event();

	int atk_island = RANDOM_MAKER->GetInt(0, computer->get_island().size() - 1);

	for (auto iter : computer->get_island()[atk_island]->get_node())
	{
		int player_island = -1;

		for (auto cIter : island_node)
		{
			if (iter == cIter->getID())
			{
				player_island = iter;
				break;
			}
		}

		if (player_island >= 0)
		{
			int cost = 0;

			for (auto iter : island_data->get_Island()[player_island]->get_ship())
				cost += iter->getCost();
			cost += RANDOM_MAKER->GetInt(-world_playerNS::COST_RANGE, world_playerNS::COST_RANGE);

			if (cost <= 0)
				cost = 1;

			while (cost > 0)
			{
				int rShip = RANDOM_MAKER->GetInt(0, island_data->get_Ship_Size() - 1);

				CProduction_Ship* sObj = island_data->get_Ship()[rShip];

				if (cost - sObj->getCost() >= 0)
				{
					CProduction_Ship* sObj = new CProduction_Ship;

					sObj->initialize(
						island_data->get_Ship()[rShip]->getName(),
						island_data->get_Ship()[rShip]->getID(),
						island_data->get_Ship()[rShip]->getTurn(),
						island_data->get_Ship()[rShip]->get_resource(MONEY),
						island_data->get_Ship()[rShip]->get_resource(IRON),
						island_data->get_Ship()[rShip]->get_resource(FUEL),
						island_data->get_Ship()[rShip]->get_resource(RESEARCH),
						island_data->get_Ship()[rShip]->getCost()
					);

					sObj->SetLoadLinkUser(computer);
					computer->add_cur_ship(sObj);

					cost -= sObj->getCost();
				}
			}

			com_atk_ui->start_event(computer->get_island()[atk_island]->getID(), player_island);
			break;
		}
	}
}

CWorld_Player::CWorld_Player()
{
	event_log = nullptr;
	detail_ui = nullptr;
	select_island = nullptr;
	com_atk_ui = nullptr;

	turn = 1;

	for (int i = 0; i < world_userNS::KIND_RESOURCE; i++)
	{
		increase_resource[i] = 0;
		decrease_resource[i] = 0;
	}

	island_ui = new CWorld_Player_Island_UI;
}


CWorld_Player::~CWorld_Player()
{
	if (island_ui != nullptr)
		island_ui->release();

	if (detail_ui != nullptr)
		SAFE_DELETE(detail_ui);

	if (event_log != nullptr)
		SAFE_DELETE(event_log);

	if (com_atk_ui != nullptr)
		SAFE_DELETE(com_atk_ui);

	img_list.clear();
}

void CWorld_Player::initialize(Graphics * g, Input * i, int _money, int _iron, int _fuel, int _research)
{
	detail_ui = new CWorld_Island_Detail_UI;
	event_log = new CWorld_Event_Log;
	com_atk_ui = new CWorld_Computer_Atk_UI;

	com_atk_ui->initialize(g, i);
	event_log->initialize(g, i);

	m_pGraphics = g;
	m_pInput = i;

	CWorld_User::initialize(g, i, _money, _iron, _fuel, _research);

	com_atk_ui->SetLoadLinkPlayer(this);
	island_ui->SetLoadLinkPlayer(this);
	island_ui->initialize(g, i);
}

void CWorld_Player::update(float frameTime)
{
	if (m_pInput->isKeyDown(ESC_KEY))
	{
		SCENEMANAGER->changeScene("Lobby");
		return;
	}

	if (com_atk_ui->get_is_show() == true)
	{
		com_atk_ui->SetLoadLinkPlayer(this);
		com_atk_ui->update(frameTime);
	}

	if (is_update == false)
		return;

	island_ui->update(frameTime);
	event_log->update(frameTime);

	if (island_ui->get_show() == true)
		cancel_ui();

	if (select_island == nullptr)
		click_island();

	for (auto iter : island_node)
		iter->update(frameTime);
}

void CWorld_Player::render()
{
	if (is_update == false)
	{
		com_atk_ui->render();
		return;
	}

	for (auto iter : img_list)
		SAFE_DELETE(iter);
	img_list.clear();

	for (auto iter : island_node)
	{
		Image* img = new Image;
		img->initialize(m_pGraphics, world_playerNS::FLAG_WIDTH, world_playerNS::FLAG_HEIGHT, 0, IMAGEMANAGER->getTexture(world_playerNS::FLAG_NAME));
		img->setX(iter->getX() - world_playerNS::FLAG_WIDTH / 2);
		img->setY(iter->getY() - world_playerNS::FLAG_HEIGHT / 2);

		img_list.emplace_back(img);

		iter->render();

		if (island_ui->get_show() == false)
		{
			for (auto iter : island_node)
			{
				if (PtInRect(&iter->getRect(), m_pInput->getMousePt()))
				{
					if (detail_ui->get_is_show() == false)
					{
						detail_ui->initialize(m_pGraphics, m_pInput, iter);
						detail_ui->render();
					}
					else
						detail_ui->render();

					break;
				}
				else 
					detail_ui->set_is_show(false);
			}
		}
	}

	m_pGraphics->spriteBegin();

	for (auto iter : img_list)
		iter->draw();

	m_pGraphics->spriteEnd();
	
	island_ui->render();
	event_log->render();

	if (com_atk_ui->get_is_show() == true)
		com_atk_ui->render();
}

void CWorld_Player::release()
{
	CWorld_User::release();

	if (island_ui != nullptr)
		island_ui->release();

	if (detail_ui != nullptr)
	{
		detail_ui->release();
		SAFE_DELETE(detail_ui);
	}

	if (event_log != nullptr)
	{
		event_log->release();
		SAFE_DELETE(event_log);
	}

	if (com_atk_ui != nullptr)
	{
		com_atk_ui->release();
		SAFE_DELETE(com_atk_ui);
	}

	img_list.clear();
}

//**********	select island	**********//
void CWorld_Player::click_island()
{
	for (auto iter : island_node)
	{
		if (PtInRect(&iter->getRect(), m_pInput->getMousePt()) && m_pInput->getMouseLButton())
		{
			SOUNDMANAGER->play(world_playerNS::SOUND_ISLAND, g_fSoundMasterVolume * g_fSoundEffectVolume);

			select_island = iter;
			island_ui->show_UI(iter->getPt(), iter->getWidth(), iter->getHeight());

			return;
		}
	}
	select_island = nullptr;
}

//**********	player turn end	**********//
void CWorld_Player::turn_end()
{
	std::string _message = "======== " + std::to_string(turn) + " Turn End ========";

	print_world_log(_message);

	for (int i = 0; i < world_userNS::KIND_RESOURCE; i++)
	{
		increase_resource[i] = 0;
		decrease_resource[i] = 0;
	}

	turn++;

	for (auto iter : island_node)	//all island
		iter->turn_end();

	for (auto iter : current_ship)	//all ship
	{
		iter->SetLoadLinkUser(this);
		iter->turn_end();
	}

	_message = "======== Start " + std::to_string(turn) + " Turn ========";

	print_world_log(_message);

	active_event();
	world_event();
	atk_player();
}


//**********	cancel island	**********//
void CWorld_Player::cancel_ui()
{
	if (select_island == nullptr)
		return;

	if (!PtInRect(&select_island->getCancelRect(), m_pInput->getMousePt()) && m_pInput->getMouseLButton() || m_pInput->isKeyDown(ESC_KEY))	//섬 크기로 변경할것
	{
		island_ui->hide_UI();
		select_island = nullptr;

		return;
	}
}

void CWorld_Player::w_move_ud(float _speed)
{
	island_ui->w_move_ud(_speed);

	for (auto iter : island_node)
		iter->w_move_ud(_speed);
	
	for (auto iter : img_list)
		iter->moveY(_speed);

	if (detail_ui->get_is_show())
		detail_ui->w_move_ud(_speed);

	if (com_atk_ui->get_is_show())
		com_atk_ui->w_move_ud(_speed);
}

void CWorld_Player::w_move_rl(float _speed)
{
	island_ui->w_move_rl(_speed);

	for (auto iter : island_node)
		iter->w_move_rl(_speed);

	for (auto iter : img_list)
		iter->moveX(_speed);

	if (detail_ui->get_is_show())
		detail_ui->w_move_rl(_speed);

	if (com_atk_ui->get_is_show())
		com_atk_ui->w_move_rl(_speed);
}
