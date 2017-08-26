#include "stdafx.h"
#include "world_PlayerUI_ShipList.h"
#include "world_Player.h"


CWorld_PlayerUI_ShipList* pThis = nullptr;
CWorld_PlayerUI_ShipList::CWorld_PlayerUI_ShipList()
{
	pThis = this;

	delay = 0;

	rt_font = { 0, };

	is_init = false;
	is_move = false;
}


CWorld_PlayerUI_ShipList::~CWorld_PlayerUI_ShipList()
{
	SAFE_DELETE(button);
}

void CWorld_PlayerUI_ShipList::initialize(Graphics* g, Input* i, POINT _pt, int _width, int _height)
{
	button = new SystemButton;
	is_init = true;
	m_pGraphics = g;
	m_pInput = i;
	margin = _width;	
	button->initialize(g, i, world_p_shiplistNS::img_name, true);
	button->setButtonPos(_pt.x - button->getWidth() / 2, _pt.y - button->getHeight() / 2);
	button->setRegistFunction(std::bind(&CWorld_PlayerUI_ShipList::click_event));
	rt_font = RectMake(button->getX(),	button->getY(),	button->getWidth(),	button->getHeight());
	m_dxFont.initialize(g, world_p_island_inforNS::FONT_SIZE, true, false, world_p_island_inforNS::FONT);
}

void CWorld_PlayerUI_ShipList::update(float frameTime)
{
	if (is_init == false)
		return;

	if (delay < world_p_shiplistNS::APEAR_TIME)	//Button apear time
	{
		delay += frameTime;

		button->moveX(-(margin * frameTime / world_p_shiplistNS::APEAR_TIME));

		rt_font.left = button->getX();
		rt_font.right = rt_font.left + button->getWidth();
	}
	else is_move = true;

	if (is_move == true && is_click == false)
		button->update(frameTime);

	if (is_click == true)
	{
		ship_list->update(frameTime);

		if (ship_list->get_show() == false)
		{
			is_click = false;

			SAFE_DELETE(ship_list);
		}
	}
}

void CWorld_PlayerUI_ShipList::render()
{
	if (is_init == false)
		return;

	if (ship_list == nullptr)
	{
		button->render();
		m_pGraphics->spriteBegin();
		m_dxFont.print(world_p_shiplistNS::BUTTON_MSG, rt_font, DT_CENTER | DT_VCENTER);
		m_pGraphics->spriteEnd();
	}

	if (is_click == true)
		ship_list->render();
}

void CWorld_PlayerUI_ShipList::click_event()
{
	SOUNDMANAGER->play(world_p_shiplistNS::SOUND_UI, g_fSoundMasterVolume * g_fSoundEffectVolume);

	pThis->ship_list = new CWorld_ShipList_UI;

	pThis->ship_list->SetLoadLinkPlayer(pThis->player);
	pThis->ship_list->initialize(pThis->m_pGraphics, pThis->m_pInput);

	pThis->is_click = true;
}

void CWorld_PlayerUI_ShipList::w_move_ud(float _speed)
{
	button->moveY(_speed);

	rt_font.top += _speed;
	rt_font.bottom += _speed;
}

void CWorld_PlayerUI_ShipList::w_move_rl(float _speed)
{
	button->moveX(_speed);

	rt_font.left += _speed;
	rt_font.right += _speed;
}

