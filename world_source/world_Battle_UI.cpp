#include "stdafx.h"
#include "world_Battle_UI.h"
#include "world_Player.h"
#include "world_CG.h"


CWorld_Battle_UI::CWorld_Battle_UI()
{
	battle_infor = new Image;
	battle_start = new Image;
	battle_retreat = new Image;
	auto_battle = new Image;

	infor_ui = new CWorld_Battle_Infor_UI;

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
}

bool CWorld_Battle_UI::initialize(Graphics * g, Input * i, int _x, int _y)
{
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

	//battle_infor->setX(_x - worldbattleNS::x + worldbattleNS::width / 2);
	//battle_infor->setY(_y - worldbattleNS::y + worldbattleNS::height / 2);
	//battle_start->setX(_x - worldbattleNS::x + worldbattleNS::width / 2);
	//battle_start->setY(_y + worldbattleNS::y + worldbattleNS::height / 2);
	//battle_retreat->setX(_x + worldbattleNS::x + worldbattleNS::width / 2);
	//battle_retreat->setY(_y - worldbattleNS::y + worldbattleNS::height / 2);
	//auto_battle->setX(_x + worldbattleNS::x + worldbattleNS::width / 2);
	//auto_battle->setY(_y + worldbattleNS::y + worldbattleNS::height / 2);

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

void CWorld_Battle_UI::save_data()
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

	std::deque<std::string> reverse;

	for (auto iter : player->get_log_message())
		reverse.emplace_front(iter);

	for (auto iter : reverse)
	{
		save.emplace_back(worldbattleNS::FILE_START);
		save.emplace_back(iter);
		save.emplace_back(worldbattleNS::FILE_FINISH);
	}
	save.emplace_back(worldbattleNS::FILE_FINISH);

	save.emplace_back(worldbattleNS::FILE_START);
	save.emplace_back("Player\n");

	for (auto iter : player->get_island())
	{
		if (battle_island == iter->getID())
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

		if (battle_island == iter->getID())
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

void CWorld_Battle_UI::back_island()
{

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
			if (PtInRect(&rt_start, m_pInput->getMousePt()))
			{
				save_data();

				PostQuitMessage(0);
			}

			if (PtInRect(&rt_retreat, m_pInput->getMousePt()))
			{
				cg->create_move_ship_cg(
					player->get_data()->get_Island()[battle_island]->getPt(),
					player->get_data()->get_Island()[player->get_cur_ship()[0]->getIsland()]->getPt(), 
					player->get_cur_ship()[0]->getIsland()
				);

				visible = false;
			}

			if (PtInRect(&rt_infor, m_pInput->getMousePt()))
			{
				SOUNDMANAGER->play(worldbattleNS::SOUND_OPEN, g_fSoundMasterVolume + g_fSoundEffectVolume);

				infor_ui->SetLoadLinkPlayer(player);
				infor_ui->set_battle_island(battle_island);
				infor_ui->initialize(m_pGraphics, m_pInput);
				infor_ui->set_is_show(true);
			}

			//if (PtInRect(&rt_total, m_pInput->getMousePt()))
			//{
			//	visible = false;

			//	//전투 하기
			//	//데이터 세이브 및 전투씬 전환
			//	//player->get_cur_ship();
			//	//cur_ship->move->true

			//	//전투 정보
			//	//현재 함대 출력

			//	//후퇴하기
			//	//다시 이전섬으로 이동

			//	//자동전투
			//	//미구현
			//}
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

	m_test_font.print("전투 정보", shadow_infor, DT_RIGHT);
	m_test_font.print("전투 돌입", shadow_start, DT_RIGHT);
	m_test_font.print("전투 후퇴", shadow_retreat, DT_LEFT);
	m_test_font.print("자동 전투", shadow_battle, DT_LEFT);

	m_dxFont.print("전투 정보", rt_infor, DT_RIGHT);
	m_dxFont.print("전투 돌입", rt_start, DT_RIGHT);
	m_dxFont.print("전투 후퇴", rt_retreat, DT_LEFT);
	m_dxFont.print("자동 전투", rt_auto, DT_LEFT);

	m_pGraphics->spriteEnd();

	infor_ui->render();

	//m_pGraphics->drawRect(rt_total);
	//m_pGraphics->drawRect(rt_infor);
	//m_pGraphics->drawRect(rt_start);
	//m_pGraphics->drawRect(rt_retreat);
	//m_pGraphics->drawRect(rt_auto);
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
