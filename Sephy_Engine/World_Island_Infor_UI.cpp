#include "stdafx.h"
#include "World_Island_Infor_UI.h"
#include "world_Player.h"


void CWorld_Island_Infor_UI::rect_initialize()
{
	for (auto iter : img_list)
		SAFE_DELETE(iter);
	img_list.clear();

	rt_vertex = RectMake(
		SystemUIDialog::getDialogX(), SystemUIDialog::getDialogY(), 
		SystemUIDialog::getDialogWidth(), SystemUIDialog::getDialogHeight()
	);

	rt_exit = RectMake(
		SystemUIDialog::getDialogX() + world_island_inforNS::MARGIN,
		SystemUIDialog::getDialogY() + world_island_inforNS::MARGIN,
		world_island_inforNS::EXIT_WIDTH, world_island_inforNS::EXIT_HEIGHT
	);
	rt_money = RectMake(
		rt_exit.right + world_island_inforNS::MARGIN, rt_exit.top,
		world_island_inforNS::RESOURCE_WIDTH,
		world_island_inforNS::RESOURCE_HEIGHT
	);
	rt_iron = RectMake(
		rt_money.right + world_island_inforNS::MARGIN / 2, rt_exit.top,
		world_island_inforNS::RESOURCE_WIDTH,
		world_island_inforNS::RESOURCE_HEIGHT
	);
	rt_fuel = RectMake(
		rt_iron.right + world_island_inforNS::MARGIN / 2, rt_exit.top,
		world_island_inforNS::RESOURCE_WIDTH,
		world_island_inforNS::RESOURCE_HEIGHT
	);
	rt_research = RectMake(
		rt_fuel.right + world_island_inforNS::MARGIN / 2, rt_exit.top,
		world_island_inforNS::RESOURCE_WIDTH,
		world_island_inforNS::RESOURCE_HEIGHT
	);

	Image* _money = new Image;
	Image* _iron = new Image;
	Image* _fuel = new Image;
	Image* _research = new Image;

	_money->initialize(
		m_pGraphics, world_island_inforNS::ICON_WIDTH, world_island_inforNS::ICON_HEIGHT,
		0, IMAGEMANAGER->getTexture(world_island_inforNS::MONEY)
	);
	_iron->initialize(
		m_pGraphics, world_island_inforNS::ICON_WIDTH, world_island_inforNS::ICON_HEIGHT,
		0, IMAGEMANAGER->getTexture(world_island_inforNS::IRON)
	);
	_fuel->initialize(
		m_pGraphics, world_island_inforNS::ICON_WIDTH, world_island_inforNS::ICON_HEIGHT,
		0, IMAGEMANAGER->getTexture(world_island_inforNS::FUEL)
	);
	_research->initialize(
		m_pGraphics, world_island_inforNS::ICON_WIDTH, world_island_inforNS::ICON_HEIGHT,
		0, IMAGEMANAGER->getTexture(world_island_inforNS::RESEARCH)
	);

	_money->setX(rt_money.left + world_island_inforNS::MARGIN);
	_money->setY(rt_money.top + (rt_money.bottom - rt_money.top) / 2 - world_island_inforNS::ICON_HEIGHT / 2);
	_iron->setX(rt_iron.left + world_island_inforNS::MARGIN);
	_iron->setY(rt_iron.top + (rt_iron.bottom - rt_money.top) / 2 - world_island_inforNS::ICON_HEIGHT / 2);
	_fuel->setX(rt_fuel.left + world_island_inforNS::MARGIN);
	_fuel->setY(rt_fuel.top + (rt_fuel.bottom - rt_money.top) / 2 - world_island_inforNS::ICON_HEIGHT / 2);
	_research->setX(rt_research.left + world_island_inforNS::MARGIN);
	_research->setY(rt_research.top + (rt_research.bottom - rt_money.top) / 2 - world_island_inforNS::ICON_HEIGHT / 2);

	img_list.emplace_back(_money);
	img_list.emplace_back(_iron);
	img_list.emplace_back(_fuel);
	img_list.emplace_back(_research);

	for (int i = 0; i < world_island_inforNS::MAX_BUILDING; i++)
	{
		rt_building[i] = RectMake(
			rt_exit.left + (world_island_inforNS::BUILDING_WIDTH + world_island_inforNS::MARGIN) * i,
			rt_exit.bottom + world_island_inforNS::MARGIN,
			world_island_inforNS::BUILDING_WIDTH, 
			world_island_inforNS::BUILDING_HEIGHT
		);

		rt_destroy[i] = RectMake(
			rt_building[i].left, rt_building[i].top, world_island_inforNS::DESTROY_WIDTH, world_island_inforNS::DESTROY_HEIGHT
		);
	}

	rt_build_border = RectMake(
		rt_building[0].left, rt_building[0].bottom + world_island_inforNS::MARGIN,
		rt_building[world_island_inforNS::MAX_BUILDING - 1].right - rt_building[0].left,
		world_island_inforNS::BOX_HEIGHT + world_island_inforNS::MARGIN * 2
	);

	rt_box_border = RectMake(
		rt_build_border.left, rt_build_border.bottom + world_island_inforNS::MARGIN,
		rt_building[world_island_inforNS::MAX_BUILDING - 1].right - rt_building[0].left,
		(world_island_inforNS::BOX_HEIGHT + world_island_inforNS::MARGIN) * 3
	);

	for (int i = 0; i < world_island_inforNS::MAX_BUILDING; i++)
	{
		build[i] = new CWorld_Island_Infor_Build_UI;

		build[i]->SetLoadLinkPlayer(player);
		build[i]->SetLoadLinkInfor(this);
		build[i]->initialize(m_pGraphics, m_pInput, i, rt_box_border);

		unit[i] = new CWorld_Island_Infor_Unit_UI;

		unit[i]->SetLoadLinkPlayer(player);
		unit[i]->SetLoadLinkInfor(this);
		unit[i]->initialize(m_pGraphics, m_pInput, i, rt_build_border, rt_box_border);
	}
}

//**********	image render	**********//
void CWorld_Island_Infor_UI::resource_render()
{
	m_dxFont.print("Save", rt_exit, DT_CENTER | DT_VCENTER);

	for (auto iter : img_list)
		iter->draw();

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

void CWorld_Island_Infor_UI::destroy_button_render(int _index)
{
	//m_pGraphics->drawRect(rt_destroy[_index], 0.1f);
	Image* img = new Image;
	img->initialize(
		m_pGraphics, world_island_inforNS::DESTROY_WIDTH
		, world_island_inforNS::DESTROY_HEIGHT, 0,
		IMAGEMANAGER->getTexture(world_island_inforNS::DESTROY_IMG)
	);
	img->setX(rt_destroy[_index].left);
	img->setY(rt_destroy[_index].top);
	img->setColorFilter(world_island_inforNS::DESTROY_COLOR);

	m_pGraphics->spriteBegin();
	img->draw();
	m_pGraphics->spriteEnd();

	building_image.emplace_back(img);
}

CWorld_Island_Infor_UI::CWorld_Island_Infor_UI()
{
	rt_vertex = { 0, };
	rt_money = { 0, };
	rt_iron = { 0, };
	rt_fuel = { 0, };
	rt_research = { 0, };
	
	rt_exit = { 0, };
	rt_box_border = { 0, };
	rt_build_border = { 0, };

	for (int i = 0; i < world_island_inforNS::MAX_BUILDING; i++)
	{
		rt_building[i] = { 0, };
		build[i] = nullptr;
		rt_destroy[i] = { 0, };

		is_destroy[i] = false;
	}

	cur_building = -1;

	is_show = true;
	mouse_up = false;

	SystemUIDialog::backColor = world_island_inforNS::BACKGROUND_COLOR;
}


CWorld_Island_Infor_UI::~CWorld_Island_Infor_UI()
{
	for (auto iter : list_number)
		SAFE_DELETE(iter);
	list_number.clear();

	for (auto iter : img_list)
		SAFE_DELETE(iter);
	img_list.clear();

	for (auto iter : building_image)
		SAFE_DELETE(iter);
	building_image.clear();

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
		g, i, g_fScreenWidth - world_island_inforNS::MARGIN,
		g_fScreenHeight / 2 - world_island_inforNS::HEIGHT / 2 - world_island_inforNS::MARGIN,
		world_island_inforNS::WIDTH, world_island_inforNS::HEIGHT,
		world_island_inforNS::MARGIN
	);

	rect_initialize();

	m_dxFont.initialize(g, world_island_inforNS::FONT_SIZE, true, false, world_island_inforNS::FONT);

	int _money = 0;
	int _iron = 0;
	int _fuel = 0;
	int _research = 0;
	
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
		if (i != cur_building)
			continue;

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
			if (PtInRect(&rt_exit, m_pInput->getMousePt()) || PtInRect(&rt_vertex, m_pInput->getMousePt()) == false)	//Exit button
				save();

			for (int i = 0; i < world_island_inforNS::MAX_BUILDING; i++)
			{
				if (PtInRect(&rt_destroy[i], m_pInput->getMousePt()))	//지어지는 & 완료된 건물 파괴
				{
					bool is_equal = false;

					if (i == cur_building)
						is_equal = true;

					if (building[i] != nullptr && is_equal == true)
					{
						if (building[i]->getID() == 0)	//Command Center
							break;

						if (building[i]->get_is_destroy() == false)
						{
							SOUNDMANAGER->play(world_island_inforNS::SOUND_SELECT, g_fSoundMasterVolume * g_fSoundEffectVolume);
							building[i]->set_is_destroy(true);
						}
						else
						{
							SOUNDMANAGER->play(world_island_inforNS::SOUND_CANCEL, g_fSoundMasterVolume * g_fSoundEffectVolume);
							building[i]->set_is_destroy(false);
						}
					}
				}
			}

			for (int i = 0; i < world_island_inforNS::MAX_BUILDING; i++)
			{
				if (PtInRect(&rt_building[i], m_pInput->getMousePt()))	//지으려는 건물 지우기
				{
					bool is_equal = false;

					if (i == cur_building)
						is_equal = true;

					cur_building = i;

					if (building[i] != nullptr && is_equal == true) {
						if (building[i]->getID() == 0)	//Command Center
							break;

						if (building[i]->get_is_building() == false)
						{
							player->add_resource(MONEY, building[i]->get_need_resource()[MONEY]);
							player->add_resource(IRON, building[i]->get_need_resource()[IRON]);

							SOUNDMANAGER->play(world_island_inforNS::SOUND_CANCEL, g_fSoundMasterVolume * g_fSoundEffectVolume);

							SAFE_DELETE(building[i]);
						}
					}
				}
			}
		}
		mouse_up = false;
	}
}

void CWorld_Island_Infor_UI::render()
{
	for (auto iter : building_image)
		SAFE_DELETE(iter);
	building_image.clear();

	SystemUIDialog::render();

	m_pGraphics->spriteBegin();

	resource_render();

	for (int i = 0; i < world_island_inforNS::MAX_BUILDING; i++)	//지어질 or 지어진 건물
	{
		if (building[i] != nullptr)
		{
			Image* img = new Image;

			img->initialize(
				m_pGraphics, world_island_inforNS::BUILDING_WIDTH,
				world_island_inforNS::BUILDING_WIDTH, 0,
				IMAGEMANAGER->getTexture(building[i]->getName())
			);
			img->setX(rt_building[i].left);
			img->setY(rt_building[i].top);

			img->draw();
			building_image.emplace_back(img);

			m_dxFont.print(building[i]->getName(), rt_building[i], DT_CENTER + DT_VCENTER);

			if (building[i]->get_is_complete() == true)
				continue;
			else if (building[i]->get_is_building() == true)
			{
				std::string temp = "D - ";
				temp += std::to_string(building[i]->get_turn());
				temp += " turn";

				m_dxFont.print(temp, rt_building[i], DT_CENTER + DT_BOTTOM);
			}
			else
			{
				std::string temp = "D - ";
				temp += std::to_string(building[i]->get_turn());
				temp += " turn";

				m_dxFont.print(temp, rt_building[i], DT_CENTER + DT_BOTTOM);
			}
		}
	}

	m_pGraphics->spriteEnd();

	//Draw Resource
	m_pGraphics->drawRect(rt_money, 0.1f);
	m_pGraphics->drawRect(rt_iron, 0.1f);
	m_pGraphics->drawRect(rt_fuel, 0.1f);
	m_pGraphics->drawRect(rt_research, 0.1f);

	//Draw Exit Button
	m_pGraphics->drawRect(rt_exit);
	
	m_pGraphics->drawRect(rt_box_border, 0.1f, world_island_inforNS::BORDER_COLOR);
	m_pGraphics->drawRect(rt_build_border, 0.1f, world_island_inforNS::BORDER_COLOR);

	for (int i = world_island_inforNS::MAX_BUILDING - 1; i >= 0 ; i--)
	{
		is_destroy[i] = false;

		if (i == cur_building)
			m_pGraphics->drawRect(rt_building[i], 0.1f, world_island_inforNS::BORDER_COLOR);
		else 
			m_pGraphics->drawRect(rt_building[i], 0.1f);

		if (player->get_select_island()->get_Building(i) != nullptr)
		{
			if (player->get_select_island()->get_Building(i)->get_is_destroy() == true)
				destroy_button_render(i);
		}

		if (i != cur_building)
			continue;

		if (player->get_select_island()->get_Building(i) == nullptr)
			build[i]->render();

		if (player->get_select_island()->get_Building(i) != nullptr)
		{
			if (player->get_select_island()->get_Building(i)->get_is_building() == false)
				build[i]->render();
			else if (player->get_select_island()->get_Building(i)->get_is_complete() == true)
				unit[i]->render();
		}
	}
}

//**********	set build	**********//
void CWorld_Island_Infor_UI::set_building(int _index, CBuilding * _building)
{
	if (player->get_buf_type() == 5 && player->spend_resource(MONEY, _building->get_need_resource()[MONEY] * 0.9f) == false)
	{
		player->print_world_log("Not Create Building : Short supply money");
		return;	//imposible build;
	}
	else if (player->spend_resource(MONEY, _building->get_need_resource()[MONEY]) == false)
	{
		player->print_world_log("Not Create Building : Short supply money");
		return;	//imposible build;
	}

	if (player->get_buf_type() == 5 && player->spend_resource(IRON, _building->get_need_resource()[IRON] * 0.9f) == false)
	{
		player->add_resource(MONEY, _building->get_need_resource()[MONEY] * 0.9f);
		player->print_world_log("Not Create Building : Short supply iron");
		return;
	}
	else if (player->spend_resource(IRON, _building->get_need_resource()[IRON]) == false)
	{
		player->add_resource(MONEY, _building->get_need_resource()[MONEY]);
		player->print_world_log("Not Create Building : Short supply iron");
		return;
	}

	if (building[_index] != nullptr)
	{
		player->add_resource(MONEY, building[_index]->get_need_resource()[MONEY]);
		player->add_resource(IRON, building[_index]->get_need_resource()[IRON]);

		SAFE_DELETE(building[_index]);
	}

	SOUNDMANAGER->play(world_island_inforNS::SOUND_BUILD, g_fSoundMasterVolume * g_fSoundEffectVolume);

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

void CWorld_Island_Infor_UI::replace_number_img(RECT rect, int _number)
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

//**********	save current build state	**********//
void CWorld_Island_Infor_UI::save()
{
	SOUNDMANAGER->play(world_island_inforNS::SOUND_SAVE, g_fSoundMasterVolume * g_fSoundEffectVolume);
	//current_island 에 저장하기
	for (int i = 0; i < world_island_inforNS::MAX_BUILDING; i++)
		player->get_select_island()->add_building(i, building[i]);

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

void CWorld_Island_Infor_UI::w_move_rl(float _speed)
{
	SystemUIDialog::moveDialogX(_speed);

	for (auto iter : img_list)
		iter->moveX(_speed);

	for (auto iter : list_number)
		iter->moveX(_speed);

	for (auto iter : building_image)
		iter->moveX(_speed);

	rect_initialize();
}
