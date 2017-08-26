#include "stdafx.h"
#include "world_Turn_UI.h"
#include "world_Player.h"


CWorld_Turn_UI::CWorld_Turn_UI()
{
	backColor = worldturnNS::CUR_BACKGROUND_COLOR;
	img_count = worldturnNS::TURN_MIN;

	is_update = true;
	is_turn = false;
	mouse_up = false;

	turn_delay = 0;
	rect_turn = { 0, };
	rt_pass = { 0, };
}


CWorld_Turn_UI::~CWorld_Turn_UI()
{
	SAFE_DELETE(button);
}

bool CWorld_Turn_UI::initialize(Graphics * g, Input * i)
{
	button = new Image;

	m_pGraphics = g;
	m_pInput = i;

	SystemUIDialog::initializeDialog(m_pGraphics, m_pInput, 
		g_fScreenWidth - worldturnNS::x,
		worldturnNS::y,
		worldturnNS::cur_turn_width,
		worldturnNS::cur_turn_height,
		worldturnNS::MARGIN);

	rect_turn = RectMake(
		g_fScreenWidth - worldturnNS::x,
		worldturnNS::y,
		worldturnNS::cur_turn_width,
		worldturnNS::cur_turn_height
	);	//right - start

	button->initialize(g, worldturnNS::pass_turn_width, worldturnNS::pass_turn_height, 0, IMAGEMANAGER->getTexture(worldturnNS::TURN_NAME + "01"));
	button->setX(rect_turn.right + worldturnNS::distance);
	button->setY(rect_turn.top + ((rect_turn.bottom - rect_turn.top) / 2 - worldturnNS::pass_turn_height / 2));

	rt_pass = RectMake(button->getX(), button->getY(), button->getWidth(), button->getHeight());

	m_dxFont.initialize(m_pGraphics, worldturnNS::FONT_SIZE, true, false, worldturnNS::FONT);

	return true;
}

void CWorld_Turn_UI::update(float frameTime)
{
	pass_turn(frameTime);

	if (is_update == false)
		return;

	if (m_pInput->getMouseLButton())
		mouse_up = true;
	else
	{
		if (mouse_up == true)
		{
			if (PtInRect(&rt_pass, m_pInput->getMousePt()) && is_turn == false)
				click_event();
		}

		mouse_up = false;
	}
}

void CWorld_Turn_UI::render()
{
	SystemUIDialog::render();

	m_pGraphics->spriteBegin();

	std::string _turn = std::to_string(player->get_turn());
	_turn += " T";

	m_dxFont.print(_turn, rect_turn, DT_VCENTER + DT_CENTER);
	
	button->draw();

	m_pGraphics->spriteEnd();
}

void CWorld_Turn_UI::release()
{
	SAFE_DELETE(button);
}

void CWorld_Turn_UI::click_event()
{
	player->turn_end();

	is_turn = true;
}

//**********	turn button animation	**********//
void CWorld_Turn_UI::pass_turn(float frameTime)
{
	std::string temp = "";

	if (is_turn == true)
	{
		if (turn_delay >= worldturnNS::DELAY)
		{
			turn_delay = 0;
			img_count++;
		}

		if (img_count >= worldturnNS::COUNT_LIMIT)
		{
			SOUNDMANAGER->play(worldturnNS::SOUND_TURN, g_fSoundMasterVolume * g_fSoundEffectVolume);

			is_turn = false;
			turn_delay = 0;
			img_count = 0;

			return;
		}

		turn_delay += frameTime;
	}

	if (img_count % worldturnNS::TURN_MAX + 1 < 10)
		temp = worldturnNS::TURN_NAME + "0" + std::to_string(img_count % worldturnNS::TURN_MAX + 1);
	else
		temp = worldturnNS::TURN_NAME + std::to_string(img_count % worldturnNS::TURN_MAX + 1);

	button->setTextureManager(IMAGEMANAGER->getTexture(temp));
}
