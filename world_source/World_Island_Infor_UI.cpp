#include "stdafx.h"
#include "World_Island_Infor_UI.h"
#include "world_Player.h"


void CWorld_Island_Infor_UI::rect_initialize()
{
	rt_title = RectMake(
		g_fScreenWidth / 2 - world_island_inforNS::WIDTH / 2 + world_island_inforNS::MARGIN,
		g_fScreenHeight / 2 - world_island_inforNS::HEIGHT / 2 + world_island_inforNS::MARGIN,
		world_island_inforNS::RESOURCE_WIDTH,
		world_island_inforNS::RESOURCE_HEIGHT
	);
	rt_money = RectMake(
		rt_title.left, rt_title.bottom + world_island_inforNS::MARGIN,
		world_island_inforNS::RESOURCE_WIDTH,
		world_island_inforNS::RESOURCE_HEIGHT
	);
	rt_iron = RectMake(
		rt_money.left, rt_money.bottom + world_island_inforNS::MARGIN,
		world_island_inforNS::RESOURCE_WIDTH,
		world_island_inforNS::RESOURCE_HEIGHT
	);
	rt_fuel = RectMake(
		rt_iron.left, rt_iron.bottom + world_island_inforNS::MARGIN,
		world_island_inforNS::RESOURCE_WIDTH,
		world_island_inforNS::RESOURCE_HEIGHT
	);
	rt_research = RectMake(
		rt_fuel.left, rt_fuel.bottom + world_island_inforNS::MARGIN,
		world_island_inforNS::RESOURCE_WIDTH,
		world_island_inforNS::RESOURCE_HEIGHT
	);

	rt_exit = RectMake(
		rt_title.left, rt_title.top - world_island_inforNS::MARGIN * 2 + world_island_inforNS::HEIGHT - world_island_inforNS::EXIT_HEIGHT,
		world_island_inforNS::EXIT_WIDTH, world_island_inforNS::EXIT_HEIGHT
	);

	for (int i = 0; i < world_island_inforNS::MAX_BUILDING; i++)
	{
		rt_building[i] = RectMake(
			rt_title.right + world_island_inforNS::MARGIN,
			rt_title.top + (world_island_inforNS::BUILDING_HEIGHT + world_island_inforNS::MARGIN) * i,
			world_island_inforNS::BUILDING_WIDTH, world_island_inforNS::BUILDING_HEIGHT
		);

		rt_build_border[i] = RectMake(
			rt_building[i].right + world_island_inforNS::MARGIN,
			rt_building[i].top,
			world_island_inforNS::MID_MARGIN - world_island_inforNS::MARGIN * 2,
			world_island_inforNS::BUILDING_HEIGHT
		);

		rt_box_border[i] = RectMake(
			rt_build_border[i].right + world_island_inforNS::MARGIN,
			rt_build_border[i].top,
			(world_island_inforNS::BOX_WIDTH + world_island_inforNS::MARGIN / 2) * world_island_inforNS::MAX_BOX / 2 + world_island_inforNS::MARGIN / 2,
			//(world_island_inforNS::BOX_WIDTH + world_island_inforNS::MARGIN / 2) * world_island_inforNS::MAX_BOX / (world_island_inforNS::MAX_BOX / 2) + world_island_inforNS::MARGIN / 2
			world_island_inforNS::BUILDING_HEIGHT
		);

		rt_destroy[i] = RectMake(
			rt_building[i].left, rt_building[i].top, world_island_inforNS::DESTROY_WIDTH, world_island_inforNS::DESTROY_HEIGHT
		);

		//rt_destroy[i] = RectMake(
		//	rt_building[i].right - world_island_inforNS::DESTROY_WIDTH - world_island_inforNS::MARGIN / 2,
		//	rt_building[i].top + world_island_inforNS::MARGIN / 2, 
		//	world_island_inforNS::DESTROY_WIDTH, world_island_inforNS::DESTROY_HEIGHT
		//);
	}

	//for (int i = 0; i < world_island_inforNS::MAX_BUILDING; i++)
	//{
	//	for (int j = 0; j < world_island_inforNS::MAX_BOX; j++)
	//	{
	//		if (j >= world_island_inforNS::MAX_BOX / 2)
	//		{
	//			//rt_box[i][j].left = rt_box[i][j - world_island_inforNS::MAX_BOX].left;
	//			//rt_box[i][j].right = rt_box[i][j - world_island_inforNS::MAX_BOX].right;
	//			rt_box[i][j] = rt_box[i][j - world_island_inforNS::MAX_BOX / 2];
	//			rt_box[i][j].top = rt_box[i][j - world_island_inforNS::MAX_BOX / 2].top + world_island_inforNS::BOX_HEIGHT + world_island_inforNS::MARGIN / 2;
	//			rt_box[i][j].bottom = rt_box[i][j - world_island_inforNS::MAX_BOX / 2].bottom + world_island_inforNS::BOX_HEIGHT + world_island_inforNS::MARGIN / 2;

	//			continue;
	//		}

	//		rt_box[i][j] = RectMake(
	//			rt_box_border[i].left + world_island_inforNS::MARGIN / 2 + (world_island_inforNS::BOX_WIDTH + world_island_inforNS::MARGIN / 2) * j,
	//			rt_box_border[i].top + world_island_inforNS::MARGIN, world_island_inforNS::BOX_WIDTH, world_island_inforNS::BOX_HEIGHT
	//		);
	//	}
	//}

	for (int i = 0; i < world_island_inforNS::MAX_BUILDING; i++)
	{
		build[i] = new CWorld_Island_Infor_Build_UI;

		build[i]->SetLoadLinkPlayer(player);
		build[i]->SetLoadLinkInfor(this);
		build[i]->initialize(m_pGraphics, m_pInput, i, rt_build_border[i]);

		unit[i] = new CWorld_Island_Infor_Unit_UI;

		unit[i]->SetLoadLinkPlayer(player);
		unit[i]->SetLoadLinkInfor(this);
		unit[i]->initialize(m_pGraphics, m_pInput, i, rt_build_border[i], rt_box_border[i]);
	}
}

void CWorld_Island_Infor_UI::resource_render()
{
	m_dxFont.print("Produce Resource", rt_title, DT_CENTER + DT_VCENTER);
	m_dxFont.print(" Money: ", rt_money, DT_LEFT + DT_VCENTER);
	m_dxFont.print(" Iron: ", rt_iron, DT_LEFT + DT_VCENTER);
	m_dxFont.print(" Fuel: ", rt_fuel, DT_LEFT + DT_VCENTER);
	m_dxFont.print(" Research: ", rt_research, DT_LEFT + DT_VCENTER);

	for (auto iter : list_number)
		iter->draw();
}

void CWorld_Island_Infor_UI::exit_button_render()
{
	m_pGraphics->drawRect(rt_exit);
	m_pGraphics->drawLine(
		rt_exit.left + world_island_inforNS::MARGIN,
		rt_exit.bottom - world_island_inforNS::MARGIN,
		rt_exit.right - world_island_inforNS::MARGIN,
		rt_exit.top + world_island_inforNS::MARGIN,
		world_island_inforNS::EXIT_WEIGHT, world_island_inforNS::EXIT_COLOR
	);
	m_pGraphics->drawLine(
		rt_exit.left + world_island_inforNS::MARGIN,
		rt_exit.top + world_island_inforNS::MARGIN,
		rt_exit.right - world_island_inforNS::MARGIN,
		rt_exit.bottom - world_island_inforNS::MARGIN,
		world_island_inforNS::EXIT_WEIGHT, world_island_inforNS::EXIT_COLOR
	);
}

void CWorld_Island_Infor_UI::destroy_button_render(UINT _index)
{
	m_pGraphics->drawRect(rt_destroy[_index], 0.1f);

	m_pGraphics->drawLine(
		rt_destroy[_index].left + world_island_inforNS::MARGIN / 2,
		rt_destroy[_index].bottom - world_island_inforNS::MARGIN / 2,
		rt_destroy[_index].right - world_island_inforNS::MARGIN / 2,
		rt_destroy[_index].top + world_island_inforNS::MARGIN / 2,
		world_island_inforNS::EXIT_WEIGHT, world_island_inforNS::EXIT_COLOR
	);
	m_pGraphics->drawLine(
		rt_destroy[_index].left + world_island_inforNS::MARGIN / 2,
		rt_destroy[_index].top + world_island_inforNS::MARGIN / 2,
		rt_destroy[_index].right - world_island_inforNS::MARGIN / 2,
		rt_destroy[_index].bottom - world_island_inforNS::MARGIN / 2,
		world_island_inforNS::EXIT_WEIGHT, world_island_inforNS::EXIT_COLOR
	);
}

CWorld_Island_Infor_UI::CWorld_Island_Infor_UI()
{
	rt_money = { 0, };
	rt_iron = { 0, };
	rt_fuel = { 0, };
	rt_research = { 0, };
	
	rt_exit = { 0, };

	for (int i = 0; i < world_island_inforNS::MAX_BUILDING; i++)
	{
		rt_building[i] = { 0, };
		rt_box_border[i] = { 0, };
		rt_build_border[i] = { 0, };
		build[i] = nullptr;
		//building[i] = nullptr;
		rt_destroy[i] = { 0, };

		is_destroy[i] = false;
	}

	//for (int i = 0; i < world_island_inforNS::MAX_BUILDING; i++)
	//	for (int j = 0; j < world_island_inforNS::MAX_BOX; j++)
	//		rt_box[i][j] = { 0, };

	is_show = true;
	mouse_up = false;
}


CWorld_Island_Infor_UI::~CWorld_Island_Infor_UI()
{
	for (auto iter : list_number)
		SAFE_DELETE(iter);

	for (int i = 0; i < world_island_inforNS::MAX_BUILDING; i++)
	{
		SAFE_DELETE(build[i]);
		SAFE_DELETE(unit[i]);
	}
}

bool CWorld_Island_Infor_UI::initialize(Graphics * g, Input * i)
{
	m_pGraphics = g;
	m_pInput = i;

	SystemUIDialog::initializeDialog(
		g, i, g_fScreenWidth / 2 - world_island_inforNS::WIDTH / 2, 
		g_fScreenHeight / 2 - world_island_inforNS::HEIGHT / 2, 
		world_island_inforNS::WIDTH, world_island_inforNS::HEIGHT, 
		world_island_inforNS::MARGIN
	);

	rect_initialize();

	m_dxFont.initialize(g, world_island_inforNS::FONT_SIZE, true, false, world_island_inforNS::FONT);

	UINT _money = 0;
	UINT _iron = 0;
	UINT _fuel = 0;
	UINT _research = 0;
	
	for (auto iter : player->get_select_island()->get_child())
	{
		switch (iter->get_type())
		{
		case MONEY:
			_money += iter->get_resource();
			break;
		case IRON:
			_iron += iter->get_resource();
			break;
		case FUEL:
			_fuel += iter->get_resource();
			break;
		case RESEARCH:
			_research += iter->get_resource();
			break;
		}
	}

	for (int a = 0; a < player->get_select_island()->get_Building_Size(); a++)
	{
		if (player->get_select_island()->get_Building(a) == nullptr ||
			player->get_select_island()->get_Building(a)->get_is_complete() == false)
			continue;

		_money += player->get_select_island()->get_Building(a)->get_produce_resource()[MONEY];
		_iron += player->get_select_island()->get_Building(a)->get_produce_resource()[IRON];
		_fuel += player->get_select_island()->get_Building(a)->get_produce_resource()[FUEL];
		_research += player->get_select_island()->get_Building(a)->get_produce_resource()[RESEARCH];
	}

	replace_number_img(rt_money, _money);
	replace_number_img(rt_iron, _iron);
	replace_number_img(rt_fuel, _fuel);
	replace_number_img(rt_research, _research);

	for (int a = 0; a < world_island_inforNS::MAX_BUILDING; a++)
		building[a] = player->get_select_island()->get_Building(a);

	return true;
}

void CWorld_Island_Infor_UI::update(float frameTime)
{
	SystemUIDialog::update(frameTime);

	for (int i = 0; i < world_island_inforNS::MAX_BUILDING; i++)	//not bulding || exist building and not start build
	{
		if (player->get_select_island()->get_Building(i) == nullptr)
			build[i]->update(frameTime);

		if (player->get_select_island()->get_Building(i) != nullptr)
		{
			if (player->get_select_island()->get_Building(i)->get_is_building() == false)
				build[i]->update(frameTime);
			else if (player->get_select_island()->get_Building(i)->get_is_complete() == true)
				unit[i]->update(frameTime);
		}
	}

	if (m_pInput->getMouseLButton())
		mouse_up = true;
	else {
		if (mouse_up == true)
		{
			if (PtInRect(&rt_exit, m_pInput->getMousePt()))	//Exit button
				save();

			for (int i = 0; i < world_island_inforNS::MAX_BUILDING; i++)
			{
				if (PtInRect(&rt_building[i], m_pInput->getMousePt()))	//지으려는 건물 지우기
				{
					if (building[i] != nullptr) {
						if (building[i]->getID() == 0)	//Command Center
							break;

						if (building[i]->get_is_building() == false)
						{
							player->add_resource(MONEY, building[i]->get_need_resource()[MONEY]);
							player->add_resource(IRON, building[i]->get_need_resource()[IRON]);

							SAFE_DELETE(building[i]);
						}
					}
				}
			}

			for (int i = 0; i < world_island_inforNS::MAX_BUILDING; i++)
			{
				if (PtInRect(&rt_destroy[i], m_pInput->getMousePt()))	//지어지는 & 완료된 건물 파괴
				{
					if (building[i] != nullptr)
					{
						if (building[i]->getID() == 0)	//Command Center
							break;

						if (building[i]->get_is_destroy() == false)
							building[i]->set_is_destroy(true);
						else
							building[i]->set_is_destroy(false);
					}
				}
			}
		}
		mouse_up = false;
	}

	//if (PtInRect(&rt_exit, m_pInput->getMousePt()) && m_pInput->getMouseLButton() || m_pInput->isKeyDown(ESC_KEY))	//Exit button
	//	save();

	//for (int i = 0; i < world_island_inforNS::MAX_BUILDING; i++)
	//{
	//	if (m_pInput->getMouseLButton())
	//		mouse_up = true;
	//	else
	//	{
	//		if (mouse_up == true)
	//		{
	//			if (PtInRect(&rt_building[i], m_pInput->getMousePt()))
	//			{
	//				if (building[i] != nullptr) {
	//					if (building[i]->get_is_building() == false)
	//						SAFE_DELETE(building[i]);
	//				}
	//			}
	//		}
	//		if (i == world_island_inforNS::MAX_BUILDING - 1)
	//			mouse_up = false;
	//	}
	//}
}

void CWorld_Island_Infor_UI::render()
{
	SystemUIDialog::render();

	m_pGraphics->spriteBegin();

	resource_render();

	for (int i = 0; i < world_island_inforNS::MAX_BUILDING; i++)	//지어질 or 지어진 건물
	{
		if (building[i] != nullptr)
		{
			m_dxFont.print(building[i]->getName(), rt_building[i], DT_CENTER + DT_VCENTER);

			if (building[i]->get_is_complete() == true)
			{
				m_dxFont.print("Complete", rt_building[i], DT_CENTER + DT_BOTTOM);
				continue;
			}
			else if (building[i]->get_is_building() == true)
			{
				std::string temp = "D - ";
				temp += std::to_string(building[i]->get_turn());
				temp += " turn";

				m_dxFont.print(temp, rt_building[i], DT_CENTER + DT_BOTTOM);
			}
		}
	}

	//for (auto iter : list_number)
	//	iter->draw();

	m_pGraphics->spriteEnd();

	//Draw Resource
	m_pGraphics->drawRect(rt_money, 0.1f);
	m_pGraphics->drawRect(rt_iron, 0.1f);
	m_pGraphics->drawRect(rt_fuel, 0.1f);
	m_pGraphics->drawRect(rt_research, 0.1f);

	//Draw Exit Button
	exit_button_render();

	//for (int i = 0; i < world_island_inforNS::MAX_BUILDING; i++)
	//	for (int j = 0; j < world_island_inforNS::MAX_BOX; j++)
	//		m_pGraphics->drawRect(rt_box[i][j], 0.1f);

	//for (int i = 0; i < world_island_inforNS::MAX_BUILDING; i++)
	//{
	//	is_destroy[i] = false;

	//	m_pGraphics->drawRect(rt_building[i], 0.1f);
	//	m_pGraphics->drawRect(rt_box_border[i], 0.1f, world_island_inforNS::BORDER_COLOR);
	//	m_pGraphics->drawRect(rt_build_border[i], 0.1f, world_island_inforNS::BORDER_COLOR);

	//	if (player->get_select_island()->get_Building(i) == nullptr)
	//		build[i]->render();

	//	if (player->get_select_island()->get_Building(i) != nullptr)
	//	{
	//		if (player->get_select_island()->get_Building(i)->get_is_building() == false)
	//			build[i]->render();
	//		else if (player->get_select_island()->get_Building(i)->get_is_complete() == true)
	//			unit[i]->render();

	//		if (player->get_select_island()->get_Building(i)->get_is_destroy() == true)
	//			destroy_button_render(i);
	//	}
	//}

	for (int i = world_island_inforNS::MAX_BUILDING - 1; i >= 0 ; i--)
	{
		is_destroy[i] = false;

		m_pGraphics->drawRect(rt_building[i], 0.1f);
		m_pGraphics->drawRect(rt_box_border[i], 0.1f, world_island_inforNS::BORDER_COLOR);
		m_pGraphics->drawRect(rt_build_border[i], 0.1f, world_island_inforNS::BORDER_COLOR);

		if (player->get_select_island()->get_Building(i) == nullptr)
			build[i]->render();

		if (player->get_select_island()->get_Building(i) != nullptr)
		{
			if (player->get_select_island()->get_Building(i)->get_is_building() == false)
				build[i]->render();
			else if (player->get_select_island()->get_Building(i)->get_is_complete() == true)
				unit[i]->render();

			if (player->get_select_island()->get_Building(i)->get_is_destroy() == true)
				destroy_button_render(i);
		}
	}

	//for (auto iter : list_number)
	//	SAFE_DELETE(iter);
	//list_number.clear();
}

void CWorld_Island_Infor_UI::set_building(int _index, CBuilding * _building)
{
	if (player->spend_resource(MONEY, _building->get_need_resource()[MONEY]) == false)
	{
		player->print_world_log("Not Create Building : Short supply money");
		return;	//imposible build;
	}
	if (player->spend_resource(IRON, _building->get_need_resource()[IRON]) == false)
	{
		player->add_resource(IRON, _building->get_need_resource()[IRON]);
		player->print_world_log("Not Create Building : Short supply iron");
		//imposible build;
		return;
	}

	if (building[_index] != nullptr)
	{
		player->add_resource(MONEY, building[_index]->get_need_resource()[MONEY]);
		player->add_resource(IRON, building[_index]->get_need_resource()[IRON]);

		SAFE_DELETE(building[_index]);
	}

	CBuilding* obj = new CBuilding;
	
	obj->initialize(
		_building->getName(),
		_building->getID(),
		_building->get_turn(),
		_building->get_building(),
		_building->get_need_resource()[MONEY],
		_building->get_need_resource()[IRON],
		_building->get_produce_resource()[MONEY],
		_building->get_produce_resource()[IRON],
		_building->get_produce_resource()[FUEL],
		_building->get_produce_resource()[RESEARCH]
	);

	for (int i = 0; i < _building->get_ship_size(); i++)
		obj->add_Ship(_building->get_ship()[i]);

	building[_index] = obj;
	building[_index]->SetLoadLinkUser(player);
	building[_index]->SetLoadLinkIsland(player->get_select_island());
}

void CWorld_Island_Infor_UI::replace_number_img(RECT rect, UINT _number)
{
	//Add kind of number image
	std::string number = std::to_string(_number);
	std::string name = "";

	int length = number.length();
	int c_temp = _number;	//atoi(number.c_str());
	RECT rc_temp = rect;

	Image* img;

	rect.right -= world_island_inforNS::IMG_NUMBER_WIDTH * 2;

	for (int i = 0; i < length; i++)
	{
		char number = c_temp % 10 + '0';
		c_temp = c_temp / 10;

		img = new Image;

		name = world_island_inforNS::IMG_NUMBER;	//Image name

		name.push_back(number);

		img->initialize(m_pGraphics, world_island_inforNS::IMG_NUMBER_WIDTH, world_island_inforNS::IMG_NUMBER_HEIGHT, 0, IMAGEMANAGER->getTexture(name));

		img->setX(rect.right);
		rect.right -= world_island_inforNS::IMG_NUMBER_WIDTH;
	
		img->setY(rect.top + ((rect.bottom - rect.top) / 2 - world_island_inforNS::IMG_NUMBER_HEIGHT / 2));

		list_number.emplace_back(img);
	}

	rect = rc_temp;
}

void CWorld_Island_Infor_UI::save()
{
	//current_island 에 저장하기
	for (int i = 0; i < world_island_inforNS::MAX_BUILDING; i++)
	{
		//건설 중 & 건설 완료
		//if (player->get_select_island()->get_Building(i) != nullptr)
		//{
		//	//building[i]->SetLoadLinkUser(player);

		//	//if (player->get_select_island()->get_Building(i)->get_is_building() == true ||
		//	//	player->get_select_island()->get_Building(i)->get_is_complete() == true)
		//	continue;
		//}

		player->get_select_island()->add_building(i, building[i]);

		//if (building[i] != nullptr)
		//{
		//	for (int j = 0; j < unit[i]->get_action_size(); j++)
		//	{
		//		if (building[i] != nullptr)
		//			player->get_select_island()->get_Building(i)->add_action(j, unit[i]->get_action(j));
		//	}
		//}
	}

	for (int i = 0; i < world_island_inforNS::MAX_BUILDING; i++)
	{
		for (int j = 0; j < unit[i]->get_action_size(); j++)
		{
			if (player->get_select_island()->get_Building(i) != nullptr)
				player->get_select_island()->get_Building(i)->add_action(j, unit[i]->get_action(j));
		}
	}

	is_show = false;
}

//void CWorld_Island_Infor_UI::w_move_ud(float _speed)
//{
//	rt_money.top += _speed;
//	rt_money.bottom += _speed;
//	rt_iron.top += _speed;
//	rt_iron.bottom += _speed;
//	rt_fuel.top += _speed;
//	rt_fuel.bottom += _speed;
//	rt_research.top += _speed;
//	rt_research.bottom += _speed;
//}
//
//void CWorld_Island_Infor_UI::w_move_rl(float _speed)
//{
//	rt_money.left += _speed;
//	rt_money.right += _speed;
//	rt_iron.left += _speed;
//	rt_iron.right += _speed;
//	rt_fuel.left += _speed;
//	rt_fuel.right += _speed;
//	rt_research.left += _speed;
//	rt_research.right += _speed;
//}
