#include "stdafx.h"
#include "world_Battle_Infor_UI.h"
#include "world_Player.h"


void CWorld_Battle_Infor_UI::exit_button_render()
{
	m_pGraphics->drawRect(rt_exit);
	m_pGraphics->drawLine(
		rt_exit.left + world_battle_infor_uiNS::MARGIN / 2,
		rt_exit.bottom - world_battle_infor_uiNS::MARGIN / 2,
		rt_exit.right - world_battle_infor_uiNS::MARGIN / 2,
		rt_exit.top + world_battle_infor_uiNS::MARGIN / 2,
		world_battle_infor_uiNS::EXIT_WEIGHT, world_battle_infor_uiNS::EXIT_COLOR
	);
	m_pGraphics->drawLine(
		rt_exit.left + world_battle_infor_uiNS::MARGIN / 2,
		rt_exit.top + world_battle_infor_uiNS::MARGIN / 2,
		rt_exit.right - world_battle_infor_uiNS::MARGIN / 2,
		rt_exit.bottom - world_battle_infor_uiNS::MARGIN / 2,
		world_battle_infor_uiNS::EXIT_WEIGHT, world_battle_infor_uiNS::EXIT_COLOR
	);
}

void CWorld_Battle_Infor_UI::rt_make_list()
{
	rt_island.clear();
	rt_current.clear();

	m_dxFont.print(world_battle_infor_uiNS::ATK_MSG, rt_island_title, DT_CENTER | DT_VCENTER);
	m_dxFont.print(world_battle_infor_uiNS::DEF_MSG, rt_current_title, DT_CENTER | DT_VCENTER);

	int line = world_battle_infor_uiNS::LINE;

	int count_scroll = 0;
	int count_line = 0;

	std::map<std::string, int> _ship;

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
			rt_ship_island.left + world_battle_infor_uiNS::MARGIN,
			rt_ship_island.top + world_battle_infor_uiNS::LIST_HEIGHT * (count_line - 1),	//count_line++ 로 인하여 -1
			world_battle_infor_uiNS::LIST_WIDTH, world_battle_infor_uiNS::LIST_HEIGHT
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
			rt_ship_battle.left + world_battle_infor_uiNS::MARGIN,
			rt_ship_battle.top + world_battle_infor_uiNS::LIST_HEIGHT * (count_line - 1),	//count_line++ 로 인하여 -1
			world_battle_infor_uiNS::LIST_WIDTH, world_battle_infor_uiNS::LIST_HEIGHT
		);

		m_dxFont.print(iter.first, rt, DT_LEFT + DT_VCENTER);
		m_dxFont.print(std::to_string(iter.second), rt, DT_RIGHT + DT_VCENTER);

		rt_current.emplace_back(rt);
	}
}

void CWorld_Battle_Infor_UI::scroll()
{
	if (PtInRect(&rt_ship_island, m_pInput->getMousePt()))
	{
		if (m_pInput->isMouseWheelUp())
		{
			if (scroll_mount_island == 0)
				scroll_mount_island = 0;
			else scroll_mount_island--;

			m_pInput->mouseWheelIn(0);

			//if (scroll_mount >= w_log_message.size() - worldlogNS::LINE)
			//	scroll_mount = w_log_message.size() - worldlogNS::LINE;
		}
		if (m_pInput->isMouseWheelDown())
		{
			if (scroll_mount_island < player->get_select_island()->get_Ship_Size() - world_all_shiplistNS::LINE)
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
			if (scroll_mount_current < player->get_cur_ship().size() - world_all_shiplistNS::LINE)
				scroll_mount_current++;

			m_pInput->mouseWheelIn(0);
		}
	}
}

CWorld_Battle_Infor_UI::CWorld_Battle_Infor_UI()
{
	mouse_up = false;
	is_show = false;

	scroll_mount_island = 0;
	scroll_mount_current = 0;
}


CWorld_Battle_Infor_UI::~CWorld_Battle_Infor_UI()
{
	rt_island.clear();
	rt_current.clear();

	SAFE_DELETE(background);
}

bool CWorld_Battle_Infor_UI::initialize(Graphics * g, Input * i)
{
	background = new Image;

	m_pGraphics = g;
	m_pInput = i;

	background->initialize(
		g, world_battle_infor_uiNS::WIDTH,
		world_battle_infor_uiNS::HEIGHT, 0,
		IMAGEMANAGER->getTexture(world_battle_infor_uiNS::BACK_NAME)
	);
	background->setX(g_fScreenWidth / 2 - world_battle_infor_uiNS::WIDTH / 2);
	background->setY(g_fScreenHeight / 2 - world_battle_infor_uiNS::HEIGHT / 2);

	rt_exit = RectMake(
		background->getX() + world_battle_infor_uiNS::WIDTH - world_battle_infor_uiNS::MARGIN - world_battle_infor_uiNS::EXIT_WIDTH,
		background->getY() + world_battle_infor_uiNS::MARGIN, world_battle_infor_uiNS::EXIT_WIDTH, world_battle_infor_uiNS::EXIT_HEIGHT
	);
	rt_ship_island = RectMake(
		background->getX() + world_battle_infor_uiNS::X,
		background->getY() + world_battle_infor_uiNS::Y,
		world_battle_infor_uiNS::RT_WIDTH,
		world_battle_infor_uiNS::RT_HEIGHT);
	rt_ship_battle = RectMake(
		rt_ship_island.right + world_battle_infor_uiNS::MID_MARGIN,
		rt_ship_island.top,
		world_battle_infor_uiNS::RT_WIDTH,
		world_battle_infor_uiNS::RT_HEIGHT
	);
	rt_island_title = RectMake(
		rt_ship_island.left,
		rt_ship_island.top - world_battle_infor_uiNS::TITLE_HEIGHT,
		world_battle_infor_uiNS::TITLE_WIDTH,
		world_battle_infor_uiNS::TITLE_HEIGHT
	);
	rt_current_title = RectMake(
		rt_ship_battle.left,
		rt_ship_battle.top - world_battle_infor_uiNS::TITLE_HEIGHT,
		world_battle_infor_uiNS::TITLE_WIDTH,
		world_battle_infor_uiNS::TITLE_HEIGHT
	);

	m_dxFont.initialize(g, world_battle_infor_uiNS::FONT_SIZE, true, false, world_battle_infor_uiNS::FONT);

	return true;
}

void CWorld_Battle_Infor_UI::update(float frameTime)
{
	if (is_show == false)
		return;

	if (m_pInput->getMouseLButton())
		mouse_up = true;
	else
	{
		if (mouse_up == true)
		{
			if (PtInRect(&rt_exit, m_pInput->getMousePt()))
			{
				SOUNDMANAGER->play(world_battle_infor_uiNS::SOUND_CLOSE, g_fSoundMasterVolume * g_fSoundEffectVolume);

				is_show = false;
			}
		}

		mouse_up = false;
	}

	scroll();
}

void CWorld_Battle_Infor_UI::render()
{
	if (is_show == false)
		return;

	m_pGraphics->spriteBegin();

	background->draw();

	rt_make_list();

	m_pGraphics->spriteEnd();

	exit_button_render();
}

void CWorld_Battle_Infor_UI::release()
{
	rt_island.clear();
	rt_current.clear();

	SAFE_DELETE(background);
}
