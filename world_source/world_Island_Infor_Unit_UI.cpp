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
			_rtM.left + world_island_infor_unitNS::MARGIN + (world_island_infor_unitNS::UNIT_WIDTH + world_island_infor_unitNS::MARGIN / 2) * i,
			_rtM.top + world_island_infor_unitNS::MARGIN, world_island_infor_unitNS::UNIT_WIDTH, world_island_infor_unitNS::UNIT_HEIGHT
		);

		rt_turn[i] = RectMake(
			rt_unit[i].left, rt_unit[i].bottom + world_island_infor_unitNS::MARGIN / 2,
			world_island_infor_unitNS::TURN_WIDTH, world_island_infor_unitNS::TURN_HEIGHT
		);
	}

	for (int i = 0; i < world_island_infor_unitNS::MAX_BOX; i++)
	{
		if (i >= world_island_infor_unitNS::MAX_BOX / 2)
		{
			//rt_box[i][j].left = rt_box[i][j - world_island_inforNS::MAX_BOX].left;
			//rt_box[i][j].right = rt_box[i][j - world_island_inforNS::MAX_BOX].right;
			rt_box[i] = rt_box[i - world_island_infor_unitNS::MAX_BOX / 2];
			rt_box[i].top = rt_box[i - world_island_infor_unitNS::MAX_BOX / 2].top + world_island_infor_unitNS::BOX_HEIGHT + world_island_infor_unitNS::MARGIN / 2;
			rt_box[i].bottom = rt_box[i - world_island_infor_unitNS::MAX_BOX / 2].bottom + world_island_infor_unitNS::BOX_HEIGHT + world_island_infor_unitNS::MARGIN / 2;

			continue;
		}

		rt_box[i] = RectMake(
			_rtR.left + world_island_infor_unitNS::MARGIN / 2 + (world_island_infor_unitNS::BOX_WIDTH + world_island_infor_unitNS::MARGIN / 2) * i,
			_rtR.top + world_island_infor_unitNS::MARGIN, world_island_infor_unitNS::BOX_WIDTH, world_island_infor_unitNS::BOX_HEIGHT
		);
	}
}

void CWorld_Island_Infor_Unit_UI::build_destroy_render()
{
	if (player->get_select_island()->get_Building(index)->get_is_destroy() == true)	//show destroy
	{
		m_pGraphics->drawLine(
			rt_unit[0].left, rt_unit[0].top, 
			rt_turn[world_island_infor_unitNS::MAX_UNIT - 1].right,
			rt_turn[world_island_infor_unitNS::MAX_UNIT - 1].bottom, 
			world_island_infor_unitNS::DESTROY_WEIGHT, world_island_infor_unitNS::DESTROY_COLOR
		);
		m_pGraphics->drawLine(
			rt_turn[0].left, rt_turn[0].bottom,
			rt_unit[world_island_infor_unitNS::MAX_UNIT - 1].right,
			rt_unit[world_island_infor_unitNS::MAX_UNIT - 1].top, 
			world_island_infor_unitNS::DESTROY_WEIGHT, world_island_infor_unitNS::DESTROY_COLOR
		);

		m_pGraphics->drawLine(
			rt_box[0].left, rt_box[0].top,
			rt_box[world_island_infor_unitNS::MAX_BOX - 1].right, 
			rt_box[world_island_infor_unitNS::MAX_BOX - 1].bottom, 
			world_island_infor_unitNS::DESTROY_WEIGHT, world_island_infor_unitNS::DESTROY_COLOR
		);
		m_pGraphics->drawLine(
			rt_box[world_island_infor_unitNS::MAX_BOX / 2].left, 
			rt_box[world_island_infor_unitNS::MAX_BOX / 2].bottom,
			rt_box[world_island_infor_unitNS::MAX_BOX / 2 - 1].right, 
			rt_box[world_island_infor_unitNS::MAX_BOX / 2 - 1].top, 
			world_island_infor_unitNS::DESTROY_WEIGHT, world_island_infor_unitNS::DESTROY_COLOR
		);
	}
}

void CWorld_Island_Infor_Unit_UI::destroy_button_render(UINT _index)
{
	m_pGraphics->drawLine(
		rt_unit[_index].left, rt_unit[_index].top, rt_turn[_index].right, rt_turn[_index].bottom,
		world_island_infor_unitNS::DESTROY_WEIGHT, world_island_infor_unitNS::DESTROY_COLOR
	);
	m_pGraphics->drawLine(
		rt_turn[_index].left, rt_turn[_index].bottom, rt_unit[_index].right, rt_unit[_index].top,
		world_island_infor_unitNS::DESTROY_WEIGHT, world_island_infor_unitNS::DESTROY_COLOR
	);
}

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

	//mouse_up_unit = false;
	mouse_up = false;

	ship_infor = new CWorld_Ship_Buy_Infor;
}


CWorld_Island_Infor_Unit_UI::~CWorld_Island_Infor_Unit_UI()
{
}

void CWorld_Island_Infor_Unit_UI::initialize(Graphics * g, Input * i, UINT _index, RECT _rtM, RECT _rtR)
{
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

	ship_infor->initialize(g, i);
}

void CWorld_Island_Infor_Unit_UI::update(float frameTime)
{
	if (player->get_select_island()->get_Building(index)->get_is_destroy() == true)
		return;
	//for (int i = 0; i < world_island_infor_unitNS::MAX_UNIT; i++)
	//{
	//	if (m_pInput->getMouseLButton())
	//		mouse_up_unit = true;
	//	else
	//	{
	//		if (mouse_up_unit == true)
	//		{
	//			if (PtInRect(&rt_unit[i], m_pInput->getMousePt()))
	//				current_action = i;
	//		}
	//		if (i == world_island_infor_unitNS::MAX_UNIT - 1)
	//			mouse_up_unit = false;
	//	}
	//}

	//������ �ǹ��� �谡 �ִ��� Ȯ�� �� �谡 �ִٸ� �� �踦 �߰�
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
					for (auto iter : player->get_data()->get_Ship())	//�ش� �� Ȯ��
					{
						if (iter->getID() == player->get_select_island()->get_Building(index)->get_ship()[i] && is_build(iter) == true)	//�� ��ũ Ȯ��
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
							ship[i]->set_is_destroy(true);
						else
							ship[i]->set_is_destroy(false);
					}
				}
			}
		}
		mouse_up = false;
	}

	bool flag = false;
	for (int i = 0; i < world_island_infor_unitNS::MAX_BOX; i++)
	{
		if (PtInRect(&rt_box[i], m_pInput->getMousePt()))
		{
			for (auto iter : player->get_data()->get_Ship())	//�ش� �� Ȯ��
			{
				if (player->get_select_island()->get_Building(index)->get_ship_size() > 0)
				{
					if (iter->getID() == player->get_select_island()->get_Building(index)->get_ship()[i] && is_build(iter) == true)	//�� ��ũ Ȯ��
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

	for (int i = 0; i < world_island_infor_unitNS::MAX_UNIT; i++)	//������ or ������ �ǹ�
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

	build_destroy_render();
	ship_infor->render();
}

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

	//if (ship[current_action] != nullptr)
	//	SAFE_DELETE(ship[current_action]);

	if (player->spend_resource(MONEY, _ship->get_resource(MONEY)) == false)
	{
		player->print_world_log("Not Create Ship : Short supply money");
		return;	//imposible build;
	}
	if (player->spend_resource(IRON, _ship->get_resource(IRON)) == false)
	{
		player->add_resource(IRON, _ship->get_resource(IRON));
		player->print_world_log("Not Create Ship : Short supply IRON");
		//imposible build;
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

	obj->SetLoadLinkUser(player);

	for (auto iter : obj->get_building())
		obj->add_building(iter);

	ship[current_action] = obj;
}
