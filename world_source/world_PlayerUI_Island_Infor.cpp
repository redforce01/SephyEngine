#include "stdafx.h"
#include "world_PlayerUI_Island_Infor.h"
#include "world_Player.h"

CWorld_PlayerUI_Island_Infor* pThis = nullptr;
CWorld_PlayerUI_Island_Infor::CWorld_PlayerUI_Island_Infor()
{
	pThis = this;
	button = new SystemButton;

	delay = 0;
	delay_infor = 0;

	is_init = false;
	is_move = false;
	is_click = false;
	is_move_infor = false;
}


CWorld_PlayerUI_Island_Infor::~CWorld_PlayerUI_Island_Infor()
{
}

void CWorld_PlayerUI_Island_Infor::initialize(Graphics * g, Input * i, POINT _pt, UINT _width, UINT _height)
{
	is_init = true;

	m_pGraphics = g;
	m_pInput = i;
	margin = _width;

	button->initialize(g, i, world_p_island_inforNS::img_name, true);
	//button->setButtonPos(_pt.x - _width / 2, _pt.y - _height / 2);
	button->setButtonPos(_pt.x - button->getWidth() / 2, _pt.y - button->getHeight() / 2);
	button->setRegistFunction(std::bind(&CWorld_PlayerUI_Island_Infor::click_event));

	//false, graphicsNS::FILTER, "button_test", 300, 300, 49, 16, 1
}

void CWorld_PlayerUI_Island_Infor::update(float frameTime)
{
	if (is_init == false)
		return;

	if (delay < world_p_island_inforNS::APEAR_TIME)	//Button apear time
	{
		delay += frameTime;

		button->moveX(margin * frameTime / world_p_island_inforNS::APEAR_TIME);
	}
	else is_move = true;

	if (is_move == true && is_click == false)
		button->update(frameTime);

	if (is_click == true)
	{
		if (delay_infor < world_p_shiplistNS::APEAR_TIME)	//Button apear time
		{
			delay_infor += frameTime;
			
			infor_ui->w_move_rl(-(infor_ui->getDialogWidth() * frameTime / world_p_shiplistNS::APEAR_TIME));
		}
		else is_move_infor = true;

		if (is_move_infor == true)
			infor_ui->update(frameTime);

		if (infor_ui->get_show() == false)
		{
			is_click = false;
			delay_infor = 0;
			SAFE_DELETE(infor_ui);
		}
	}
}

void CWorld_PlayerUI_Island_Infor::render()
{
	if (is_init == false)
		return;

	if (infor_ui == nullptr)
		button->render();

	if (is_click == true)
		infor_ui->render();
}

void CWorld_PlayerUI_Island_Infor::click_event()
{
	//if (SOUNDMANAGER->isPlaySound(world_p_island_inforNS::SOUND_OPEN))
	SOUNDMANAGER->play(world_p_island_inforNS::SOUND_OPEN, g_fSoundMasterVolume + g_fSoundEffectVolume);

	pThis->infor_ui = new CWorld_Island_Infor_UI;

	pThis->infor_ui->SetLoadLinkIsland(pThis->player);
	pThis->infor_ui->initialize(pThis->m_pGraphics, pThis->m_pInput);

	pThis->is_click = true;
}

void CWorld_PlayerUI_Island_Infor::w_move_ud(float _speed)
{
	button->moveY(_speed);
}

void CWorld_PlayerUI_Island_Infor::w_move_rl(float _speed)
{
	button->moveX(_speed);
}
