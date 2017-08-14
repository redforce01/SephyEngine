#include "stdafx.h"
#include "world_Player.h"
#include "world_Island_Data.h"

CWorld_Player::CWorld_Player()
{
	island_ui = new CWorld_Player_Island_UI;

	select_island = nullptr;
	//show_ui = false;
	turn = 1;

	for (int i = 0; i < world_userNS::KIND_RESOURCE; i++)
	{
		increase_resource[i] = 0;
		decrease_resource[i] = 0;
	}
}


CWorld_Player::~CWorld_Player()
{
}

void CWorld_Player::initialize(Graphics * g, Input * i, int _money, int _iron, int _fuel, int _research)
{
	CWorld_User::initialize(g, i, _money, _iron, _fuel, _research);

	island_ui->SetLoadLinkPlayer(this);
	island_ui->initialize(g, i);

	//initialize comandcenter
	CBuilding* command_center = new CBuilding;

	command_center->SetLoadLinkUser(this);
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

	get_island()[0]->add_building(0, command_center);
}

void CWorld_Player::update(float frameTime)
{
	if (is_update == false)
		return;

	island_ui->update(frameTime);

	//Project quit
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
		return;

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
	}

	m_pGraphics->spriteBegin();

	for (auto iter : img_list)
		iter->draw();

	m_pGraphics->spriteEnd();
	
	island_ui->render();
}

void CWorld_Player::click_island()
{
	//if (show_ui == true)
	//	return;
	//if (select_island != nullptr)
	//	return select_island;

	for (auto iter : island_node)
	{
		if (PtInRect(&iter->getRect(), m_pInput->getMousePt()) && m_pInput->getMouseLButton())
		{
			select_island = iter;
			island_ui->show_UI(iter->getPt(), iter->getWidth(), iter->getHeight());
			//show_ui = true;
			//return iter;
			return;
		}
	}
	select_island = nullptr;
	
	//return nullptr;
}

void CWorld_Player::turn_end()
{
	for (int i = 0; i < world_userNS::KIND_RESOURCE; i++)
	{
		increase_resource[i] = 0;
		decrease_resource[i] = 0;
	}

	turn++;

	for (auto iter : island_node)	//all island
		iter->turn_end();

	for (auto iter : current_ship)	//all ship
		iter->turn_end();
}


void CWorld_Player::cancel_ui()
{
	//if (show_ui == false)
	//	return;
	if (select_island == nullptr)
		return;

	//if (m_pInput->getMouseLButton())	//섬 크기로 변경할것
	//{
	//	if (!PtInRect(&select_island->getCancelRect(), m_pInput->getMousePt()))
	//	{
	//		island_ui->hide_UI();
	//		select_island = nullptr;

	//		return;
	//	}
	//}

	if (!PtInRect(&select_island->getCancelRect(), m_pInput->getMousePt()) && m_pInput->getMouseLButton() || m_pInput->isKeyDown(ESC_KEY))	//섬 크기로 변경할것
	{
		island_ui->hide_UI();
		select_island = nullptr;

		return;
	}

	//for (auto iter : island_node)
	//{
	//	if (!PtInRect(&iter->getRect(), m_pInput->getMousePt()) && m_pInput->getMouseLButton())	//섬 크기로 변경할것
	//	{
	//		island_ui->hide_UI();
	//		//show_ui = false;

	//		return;
	//	}
	//}
}

void CWorld_Player::w_move_ud(float _speed)
{
	island_ui->w_move_ud(_speed);

	for (auto iter : island_node)
		iter->w_move_ud(_speed);
	
	for (auto iter : img_list)
		iter->moveY(_speed);
}

void CWorld_Player::w_move_rl(float _speed)
{
	island_ui->w_move_rl(_speed);

	for (auto iter : island_node)
		iter->w_move_rl(_speed);

	for (auto iter : img_list)
		iter->moveX(_speed);
}
