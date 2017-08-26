#include "stdafx.h"
#include "world_ShipList_UI.h"
#include "World_Island_Data.h"
#include "world_Player.h"


//**********	x button draw	**********//
void CWorld_ShipList_UI::exit_button_render()
{
	m_pGraphics->drawRect(rt_exit);
	m_pGraphics->drawLine(
		rt_exit.left + world_all_shiplistNS::MARGIN / 2,
		rt_exit.bottom - world_all_shiplistNS::MARGIN / 2,
		rt_exit.right - world_all_shiplistNS::MARGIN / 2,
		rt_exit.top + world_all_shiplistNS::MARGIN / 2,
		world_all_shiplistNS::EXIT_WEIGHT, world_all_shiplistNS::EXIT_COLOR
	);
	m_pGraphics->drawLine(
		rt_exit.left + world_all_shiplistNS::MARGIN / 2,
		rt_exit.top + world_all_shiplistNS::MARGIN / 2,
		rt_exit.right - world_all_shiplistNS::MARGIN / 2,
		rt_exit.bottom - world_all_shiplistNS::MARGIN / 2,
		world_all_shiplistNS::EXIT_WEIGHT, world_all_shiplistNS::EXIT_COLOR
	);
}

//**********	initialize rect	**********//
void CWorld_ShipList_UI::rt_make_list()
{
	rt_island.clear();
	rt_current.clear();
	island_ship_name.clear();
	current_ship_name.clear();

	int line = world_all_shiplistNS::LINE;

	int count_scroll = 0;
	int count_line = 0;

	std::map<std::string, int> _ship;
	
	for (auto iter : player->get_select_island()->get_ship())
	{
		if (iter->get_is_move() == true || iter->get_is_fuel() == false)	//이동 한 배 -> 다른 색 처리
			continue;

		bool is_ship = false;

		auto mIter = _ship.find(iter->getName());

		if (mIter != _ship.end())
		{
			mIter->second++;
			is_ship = true;
		}

		if (is_ship == false)
		{
			_ship.emplace(iter->getName(), 1);
			island_ship_name.emplace_back(iter->getName());
		}
	}

	for (auto iter : _ship)
	{
		if (count_scroll++ < scroll_mount_island)
			continue;

		if (line < count_line++)
			break;

		RECT rt = RectMake(
			rt_ship_island.left + world_all_shiplistNS::MARGIN,
			rt_ship_island.top + world_all_shiplistNS::LIST_HEIGHT * (count_line - 1),	//count_line++ 로 인하여 -1
			world_all_shiplistNS::LIST_WIDTH, world_all_shiplistNS::LIST_HEIGHT
		);

		if (PtInRect(&rt, m_pInput->getMousePt()))
		{
			m_dxFont_over.print(iter.first, rt, DT_LEFT | DT_VCENTER);
			m_dxFont_over.print(std::to_string(iter.second), rt, DT_RIGHT | DT_VCENTER);
		}
		else
		{
			m_dxFont.print(iter.first, rt, DT_LEFT | DT_VCENTER);
			m_dxFont.print(std::to_string(iter.second), rt, DT_RIGHT | DT_VCENTER);
		}

		rt_island.emplace_back(rt);
	}
	_ship.clear();

	count_scroll = 0;
	count_line = 0;

	for (auto iter : player->get_cur_ship())
	{
		if (iter->get_is_move() == true || iter->get_is_fuel() == false)	//이동 한 배 -> 다른 색 처리
			continue;

		bool is_ship = false;

		auto mIter = _ship.find(iter->getName());

		if (mIter != _ship.end())
		{
			mIter->second++;
			is_ship = true;
		}

		if (is_ship == false)
		{
			_ship.emplace(iter->getName(), 1);
			current_ship_name.emplace_back(iter->getName());
		}
	}

	for (auto iter : _ship)
	{
		if (count_scroll++ < scroll_mount_current)
			continue;

		if (line < count_line++)
			break;

		RECT rt = RectMake(
			rt_ship_current.left + world_all_shiplistNS::MARGIN,
			rt_ship_current.top + world_all_shiplistNS::LIST_HEIGHT * (count_line - 1),	//count_line++ 로 인하여 -1
			world_all_shiplistNS::LIST_WIDTH, world_all_shiplistNS::LIST_HEIGHT
		);

		if (PtInRect(&rt, m_pInput->getMousePt()))
		{
			m_dxFont_over.print(iter.first, rt, DT_LEFT + DT_VCENTER);
			m_dxFont_over.print(std::to_string(iter.second), rt, DT_RIGHT + DT_VCENTER);
		}
		else
		{
			m_dxFont.print(iter.first, rt, DT_LEFT + DT_VCENTER);
			m_dxFont.print(std::to_string(iter.second), rt, DT_RIGHT + DT_VCENTER);
		}

		rt_current.emplace_back(rt);
	}
}

//**********	use scroll	**********//
void CWorld_ShipList_UI::scroll()
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
			if (scroll_mount_island < player->get_select_island()->get_Ship_Size() - world_all_shiplistNS::LINE)
				scroll_mount_island++;

			m_pInput->mouseWheelIn(0);
		}
	}

	if (PtInRect(&rt_ship_current, m_pInput->getMousePt()))
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
			if (scroll_mount_current < player->get_cur_ship().size() - world_all_shiplistNS::LINE)
				scroll_mount_current++;

			m_pInput->mouseWheelIn(0);
		}
	}
}

//**********	move current ship	**********//
void CWorld_ShipList_UI::event_click()
{
	if (rt_current.size() <= 0)
	{
		delete_move();
		return;
	}

	SOUNDMANAGER->play(world_all_shiplistNS::SOUND_SELECT, g_fSoundMasterVolume * g_fSoundEffectVolume);

	move = new CWorld_Ship_Move_UI;

	move->SetLoadLinkListUI(this);
	move->SetLoadLinkPlayer(player);
	move->initialize(m_pGraphics, m_pInput);

	for (auto iter : player->get_select_island()->get_node())
	{
		for (auto gIter : player->get_data()->get_Island())
		{
			if (iter == gIter->getID())
			{
				move->add_island(gIter);

				break;
			}
		}
	}
}

CWorld_ShipList_UI::CWorld_ShipList_UI()
{
	mouse_up = false;
	is_show = true;

	scroll_mount_island = 0;
	scroll_mount_current = 0;

	move = nullptr;
}


CWorld_ShipList_UI::~CWorld_ShipList_UI()
{
	if (move != nullptr)
		SAFE_DELETE(move);

	SAFE_DELETE(background);
	rt_current.clear();
	rt_island.clear();
}

bool CWorld_ShipList_UI::initialize(Graphics * g, Input * i)
{
	background = new Image;

	m_pGraphics = g;
	m_pInput = i;

	background->initialize(g, world_all_shiplistNS::WIDTH, world_all_shiplistNS::HEIGHT, 0, IMAGEMANAGER->getTexture(world_all_shiplistNS::BACK_NAME));
	background->setX(g_fScreenWidth / 2 - world_all_shiplistNS::WIDTH / 2);
	background->setY(g_fScreenHeight / 2 - world_all_shiplistNS::HEIGHT / 2);

	rt_move = RectMake(
		background->getX() + (world_all_shiplistNS::WIDTH / 2 - world_all_shiplistNS::MOVE_WIDTH / 2),
		background->getY() + (world_all_shiplistNS::HEIGHT - world_all_shiplistNS::MOVE_HEIGHT - world_all_shiplistNS::MARGIN),
		world_all_shiplistNS::MOVE_WIDTH, world_all_shiplistNS::MOVE_HEIGHT
	);

	rt_exit = RectMake(
		background->getX() + world_all_shiplistNS::WIDTH - world_all_shiplistNS::MARGIN - world_all_shiplistNS::EXIT_WIDTH,
		background->getY() + world_all_shiplistNS::MARGIN, world_all_shiplistNS::EXIT_WIDTH, world_all_shiplistNS::EXIT_HEIGHT
	);
	rt_ship_island = RectMake(
		background->getX() + world_all_shiplistNS::X,
		background->getY() + world_all_shiplistNS::Y,
		world_all_shiplistNS::RT_WIDTH,
		world_all_shiplistNS::RT_HEIGHT
	);
	rt_ship_current = RectMake(
		rt_ship_island.right + world_all_shiplistNS::MID_MARGIN,
		rt_ship_island.top,
		world_all_shiplistNS::RT_WIDTH,
		world_all_shiplistNS::RT_HEIGHT
	);

	m_dxFont.initialize(g, world_all_shiplistNS::FONT_SIZE, true, false, world_all_shiplistNS::FONT);
	m_dxFont_over.initialize(g, world_all_shiplistNS::FONT_SIZE, true, false, world_all_shiplistNS::FONT);
	m_dxFont_over.setFontColor(world_all_shiplistNS::FONT_COLOR_OVER);

	return true;
}

void CWorld_ShipList_UI::update(float frameTime)
{
	if (move != nullptr)
	{
		move->update(frameTime);
		return;
	}

	if (m_pInput->getMouseLButton())
		mouse_up = true;
	else
	{
		if (mouse_up == true)
		{
			if (PtInRect(&rt_move, m_pInput->getMousePt()))
				event_click();

			if (PtInRect(&rt_exit, m_pInput->getMousePt()))
			{
				SOUNDMANAGER->play(world_all_shiplistNS::SOUND_CLOSE, g_fSoundMasterVolume * g_fSoundEffectVolume);

				for (auto iter : player->get_cur_ship())
					player->get_select_island()->add_ship(iter);
				player->clear_cur_ship();

				delete_move();
			}

			int count = 0;

			for (auto iter : rt_island)
			{
				if (player->get_select_island()->get_ship()[count]->get_is_move() == true ||
					player->get_select_island()->get_ship()[count]->get_is_fuel() == false)
					continue;

				//**********	select ship		**********//
				if (PtInRect(&iter, m_pInput->getMousePt()))
				{
					SOUNDMANAGER->play(world_all_shiplistNS::SOUND_SELECT, g_fSoundMasterVolume * g_fSoundEffectVolume);

					int s_count = 0;

					for (auto pIter : player->get_select_island()->get_ship())
					{
						if (pIter->getName() == island_ship_name[count])
						{
							player->add_cur_ship(pIter);

							break;
						}
						s_count++;
					}

					player->get_select_island()->remove_ship(s_count);

					break;
				}
				count++;
			}

			count = 0;

			//**********	cancel ship		**********//
			for (auto iter : rt_current)	//목표로 보낼 배 리스트
			{
				if (PtInRect(&iter, m_pInput->getMousePt()))
				{
					SOUNDMANAGER->play(world_all_shiplistNS::SOUND_CANCEL, g_fSoundMasterVolume * g_fSoundEffectVolume);

					int s_count = 0;

					for (auto pIter : player->get_cur_ship())
					{
						if (pIter->getName() == current_ship_name[count])
						{
							player->get_select_island()->add_ship(pIter);

							break;
						}
						s_count++;
					}

					player->remove_cur_ship(s_count);//player->get_cur_ship().erase(player->get_cur_ship().begin() + count);
					
					break;
				}

				count++;
			}
		}

		mouse_up = false;
	}

	scroll();
}

void CWorld_ShipList_UI::render()
{
	if (move != nullptr)
	{
		move->render();
		return;
	}

	m_pGraphics->spriteBegin();

	background->draw();

	rt_make_list();
	m_dxFont.print("Move", rt_move, DT_VCENTER | DT_CENTER);

	m_pGraphics->spriteEnd();

	exit_button_render();
	m_pGraphics->drawRect(rt_move);
}

//**********	close ship move UI	**********//
void CWorld_ShipList_UI::delete_move()
{
	SOUNDMANAGER->play(world_all_shiplistNS::SOUND_CLOSE, g_fSoundMasterVolume * g_fSoundEffectVolume);

	SAFE_DELETE(move);

	is_show = false;
}
