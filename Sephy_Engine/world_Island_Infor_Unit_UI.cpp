#include "stdafx.h"
#include "world_Island_Infor_Unit_UI.h"
#include "world_Player.h"
#include "World_Island_Data.h"
#include "World_Island_Infor_UI.h"


void CWorld_Island_Infor_Unit_UI::rect_initialize(RECT _rtM, RECT _rtR)
{
	for (int i = 0; i < world_island_infor_unitNS::MAX_UNIT; i++)
	{
		rt_unit[i] = RectMake(
			_rtM.left + world_island_infor_unitNS::MARGIN + (world_island_infor_unitNS::BUILDING_MARGIN + world_island_infor_unitNS::MARGIN) * i,
			_rtM.top + world_island_infor_unitNS::MARGIN, world_island_infor_unitNS::UNIT_WIDTH, world_island_infor_unitNS::UNIT_HEIGHT
		);

		rt_turn[i] = RectMake(
			rt_unit[i].left, rt_unit[i].bottom + world_island_infor_unitNS::MARGIN,
			world_island_infor_unitNS::TURN_WIDTH, world_island_infor_unitNS::TURN_HEIGHT
		);
	}
	
	int next_line = -1;

	for (int i = 0; i < world_island_infor_unitNS::MAX_BOX; i++)
	{
		if (i % 5 == 0)
			next_line++;

		if (next_line > 0)
		{
			rt_box[i] = rt_box[i - world_island_infor_buildNS::MAX_BOX / 3];
			rt_box[i].top = rt_box[i].bottom + world_island_infor_buildNS::MARGIN / 2;
			rt_box[i].bottom = rt_box[i].top + world_island_infor_buildNS::BOX_HEIGHT;

			continue;
		}

		rt_box[i] = RectMake(
			_rtR.left + world_island_infor_unitNS::MARGIN + (world_island_infor_unitNS::BOX_WIDTH + world_island_infor_unitNS::MARGIN) * i,
			_rtR.top + world_island_infor_unitNS::MARGIN / 2, world_island_infor_unitNS::BOX_WIDTH, world_island_infor_unitNS::BOX_HEIGHT
		);
	}
}

//**********	destroy ship (red square img)	**********//
void CWorld_Island_Infor_Unit_UI::destroy_button_render(int _index)
{
	Image* img = new Image;
	img->initialize(
		m_pGraphics, world_island_infor_unitNS::DESTROY_WIDTH
		, world_island_infor_unitNS::DESTROY_HEIGHT, 0,
		IMAGEMANAGER->getTexture(world_island_infor_unitNS::DESTROY_IMG)
	);
	img->setX(rt_unit[_index].left);
	img->setY(rt_unit[_index].top);
	img->setColorFilter(world_island_infor_unitNS::DESTROY_COLOR);

	m_pGraphics->spriteBegin();
	img->draw();
	m_pGraphics->spriteEnd();

	img_list.emplace_back(img);
}

//**********	check player's building	**********//
bool CWorld_Island_Infor_Unit_UI::is_build(CProduction_Ship * _ship)
{
	for (int i = 0; i < _ship->get_building_size(); i++)
	{
		if (player->get_cur_building(_ship->get_building()[i]) <= 0)
			return false;
	}
	
	return true;
}


CWorld_Island_Infor_Unit_UI::CWorld_Island_Infor_Unit_UI()
{
	for (int i = 0; i < world_island_infor_unitNS::MAX_UNIT; i++)
	{
		rt_unit[i] = { 0, };
		rt_turn[i] = { 0, };

		ship[i] = nullptr;
	}

	for (int i = 0; i < world_island_infor_unitNS::MAX_BOX; i++)
		rt_box[i] = { 0, };

	current_action = 0;

	mouse_up = false;
}


CWorld_Island_Infor_Unit_UI::~CWorld_Island_Infor_Unit_UI()
{
	for (auto iter : img_list)
		SAFE_DELETE(iter);
	img_list.clear();
}

void CWorld_Island_Infor_Unit_UI::initialize(Graphics * g, Input * i, int _index, RECT _rtM, RECT _rtR)
{
	ship_infor = new CWorld_Ship_Buy_Infor;

	m_pGraphics = g;
	m_pInput = i;
	index = _index;

	rect_initialize(_rtM, _rtR);

	m_dxFont.initialize(g, world_island_infor_buildNS::FONT_SIZE, true, false, world_island_infor_buildNS::FONT);

	for (int a = 0; a < world_island_infor_unitNS::MAX_UNIT; a++)
	{
		if (player->get_select_island()->get_Building(_index) != nullptr)
			ship[a] = player->get_select_island()->get_Building(_index)->get_action(a);
	}

	ship_infor->SetLoadLinkPlayer(player);
	ship_infor->initialize(g, i);
}

void CWorld_Island_Infor_Unit_UI::update(float frameTime)
{
	if (player->get_select_island()->get_Building(index)->get_is_destroy() == true)
		return;

	//지어진 건물에 배가 있는지 확인 후 배가 있다면 그 배를 추가
	if (m_pInput->getMouseLButton())
		mouse_up = true;
	else
	{
		if (mouse_up == true)
		{
			for (int i = 0; i < player->get_select_island()->get_Building(index)->get_ship_size(); i++)
			{
				if (PtInRect(&rt_box[i], m_pInput->getMousePt()))
				{
					for (auto iter : player->get_data()->get_Ship())	//해당 배 확인
					{
						if (iter->getID() == player->get_select_island()->get_Building(index)->get_ship()[i] && is_build(iter) == true)	//배 테크 확인
						{
							set_action(iter);

							break;
						}
					}
				}
			}

			for (int i = 0; i < world_island_infor_unitNS::MAX_UNIT; i++)
			{
				if (PtInRect(&rt_unit[i], m_pInput->getMousePt()))
				{
					if (ship[i] != nullptr)
					{
						if (ship[i]->get_is_create() == false)
						{
							player->add_resource(MONEY, ship[i]->get_resource(MONEY));
							player->add_resource(IRON, ship[i]->get_resource(IRON));
							player->add_resource(FUEL, ship[i]->get_resource(FUEL));
							player->add_resource(RESEARCH, ship[i]->get_resource(RESEARCH));

							SOUNDMANAGER->play(world_island_infor_unitNS::SOUND_CANCEL, g_fSoundMasterVolume * g_fSoundEffectVolume);

							SAFE_DELETE(ship[i]);
							current_action = 0;
						}
					}
				}
			}

			for (int i = 0; i < world_island_infor_unitNS::MAX_UNIT; i++)
			{
				if (PtInRect(&rt_unit[i], m_pInput->getMousePt()))
				{
					if (ship[i] != nullptr)
					{
						if (ship[i]->get_is_destroy() == false)
						{
							SOUNDMANAGER->play(world_island_infor_unitNS::SOUND_SELECT, g_fSoundMasterVolume * g_fSoundEffectVolume);
							ship[i]->set_is_destroy(true);
						}
						else
						{
							SOUNDMANAGER->play(world_island_infor_unitNS::SOUND_CANCEL, g_fSoundMasterVolume * g_fSoundEffectVolume);
							ship[i]->set_is_destroy(false);
						}
					}
				}
			}
		}
		mouse_up = false;
	}

	bool flag = false;
	for (int i = 0; i < player->get_select_island()->get_Building(index)->get_ship_size(); i++)
	{
		if (PtInRect(&rt_box[i], m_pInput->getMousePt()))
		{
			for (auto iter : player->get_data()->get_Ship())	//해당 배 확인
			{
				if (player->get_select_island()->get_Building(index)->get_ship_size() > 0)
				{
					if (iter->getID() == player->get_select_island()->get_Building(index)->get_ship()[i] && is_build(iter) == true)	//배 테크 확인
					{
						ship_infor->set_ship(iter);
						flag = true;
						break;
					}
				}
			}
		}

		if (flag == true)
			break;
		else ship_infor->set_ship(nullptr);
	}
	ship_infor->update(frameTime);
}

void CWorld_Island_Infor_Unit_UI::render()
{
	for (auto iter : img_list)
		SAFE_DELETE(iter);
	img_list.clear();

	m_pGraphics->spriteBegin();

	for (int i = 0; i < player->get_select_island()->get_Building(index)->get_ship_size(); i++)
	{
		for (auto iter : player->get_data()->get_Ship())
		{
			if (iter->getID() == player->get_select_island()->get_Building(index)->get_ship()[i] && is_build(iter) == true)
			{
				Image* img = new Image;

				img->initialize(
					m_pGraphics, world_island_infor_unitNS::BOX_WIDTH,
					world_island_infor_unitNS::BOX_HEIGHT, 0,
					IMAGEMANAGER->getTexture(iter->getName() + world_island_infor_unitNS::BOX_NAME)
				);
				img->setX(rt_box[i].left);
				img->setY(rt_box[i].top);

				img->draw();
				img_list.emplace_back(img);

				m_dxFont.print(iter->getName(), rt_box[i], DT_CENTER + DT_BOTTOM);

				break;
			}
		}
	}

	for (int i = 0; i < world_island_infor_unitNS::MAX_UNIT; i++)	//지어질 or 지어진 건물
	{
		if (ship[i] != nullptr)
		{
			Image* img = new Image;

			img->initialize(
				m_pGraphics, world_island_infor_unitNS::UNIT_WIDTH,
				world_island_infor_unitNS::UNIT_HEIGHT, 0,
				IMAGEMANAGER->getTexture(ship[i]->getName() + world_island_infor_unitNS::UNIT_NAME)
			);
			img->setX(rt_unit[i].left);
			img->setY(rt_unit[i].top);

			img->draw();
			img_list.emplace_back(img);

			m_dxFont.print(ship[i]->getName(), rt_unit[i], DT_CENTER + DT_BOTTOM);

			if (ship[i]->get_is_create() == true)
			{
				std::string temp = "D - ";
				temp += std::to_string(ship[i]->getTurn());
				temp += " turn";

				m_dxFont.print(temp, rt_turn[i], DT_CENTER + DT_VCENTER);
			}
			else
			{
				std::string temp = "D - ";
				temp += std::to_string(ship[i]->getTurn());
				temp += " turn";

				m_dxFont.print(temp, rt_turn[i], DT_CENTER + DT_VCENTER);
			}
		}
	}

	m_pGraphics->spriteEnd();

	for (int i = 0; i < world_island_infor_unitNS::MAX_UNIT; i++)
	{
		m_pGraphics->drawRect(rt_unit[i], 0.1f);
		m_pGraphics->drawRect(rt_turn[i], 0.1f);

		if (ship[i] != nullptr)
		{
			if (ship[i]->get_is_destroy() == true && player->get_select_island()->get_Building(index)->get_is_destroy() == false)
				destroy_button_render(i);
		}
	}

	for (int i = 0; i < world_island_infor_unitNS::MAX_BOX; i++)
	{
		m_pGraphics->drawRect(rt_box[i], 0.1f);
	}

	//build_destroy_render();
	ship_infor->render();
}

//**********	set create ship		**********//
void CWorld_Island_Infor_Unit_UI::set_action(CProduction_Ship * _ship)
{
	for (int i = current_action; i < world_island_infor_unitNS::MAX_UNIT; i++)
	{
		if (ship[i] != nullptr)
			current_action++;
		else break;
	}

	if (current_action >= world_island_infor_unitNS::MAX_UNIT)
		return ;

	if (player->spend_resource(MONEY, _ship->get_resource(MONEY)) == false)
	{
		player->print_world_log("Not Create Ship : Short supply money");
		return;	//imposible build;
	}
	if (player->spend_resource(IRON, _ship->get_resource(IRON)) == false)
	{
		player->add_resource(IRON, _ship->get_resource(IRON));
		player->print_world_log("Not Create Ship : Short supply IRON");

		return;
	}
	if (player->spend_resource(FUEL, _ship->get_resource(FUEL)) == false)
	{
		player->add_resource(IRON, _ship->get_resource(IRON));
		player->add_resource(FUEL, _ship->get_resource(FUEL));
		player->print_world_log("Not Create Ship : Short supply fuel");
		return;
	}
	if (player->spend_resource(RESEARCH, _ship->get_resource(RESEARCH)) == false)
	{
		player->add_resource(IRON, _ship->get_resource(IRON));
		player->add_resource(FUEL, _ship->get_resource(FUEL));
		player->add_resource(RESEARCH, _ship->get_resource(RESEARCH));
		player->print_world_log("Not Create Ship : Short supply research");
		return;
	}

	SOUNDMANAGER->play(world_island_infor_unitNS::SOUND_SELECT, g_fSoundMasterVolume * g_fSoundEffectVolume);

	CProduction_Ship* obj = new CProduction_Ship;

	obj->initialize(
		_ship->getName(),
		_ship->getID(),
		_ship->getTurn(),
		_ship->get_resource(MONEY),
		_ship->get_resource(IRON),
		_ship->get_resource(FUEL),
		_ship->get_resource(RESEARCH),
		_ship->getCost()
	);

	if (player->get_buf_type() == 2)
		obj->set_turn(obj->getTurn() - 1);

	obj->SetLoadLinkUser(player);

	for (auto iter : obj->get_building())
		obj->add_building(iter);

	ship[current_action] = obj;
}

void CWorld_Island_Infor_Unit_UI::w_move_rl(float _speed)
{
	for (int i = 0; i < world_island_infor_unitNS::MAX_UNIT; i++)
	{
		rt_unit[i].left += _speed;
		rt_unit[i].right += _speed;
		rt_turn[i].left += _speed;
		rt_turn[i].right += _speed;
	}

	for (int i = 0; i < world_island_infor_unitNS::MAX_BOX; i++)
	{
		rt_box[i].left += _speed;
		rt_box[i].right += _speed;
	}

	for (auto iter : img_list)
		iter->moveX(_speed);

	ship_infor->w_move_rl(_speed);
}

