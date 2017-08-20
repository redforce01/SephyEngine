#include "stdafx.h"
#include "world_Turn_UI.h"
#include "world_Player.h"


CWorld_Turn_UI* pThis = nullptr;
CWorld_Turn_UI::CWorld_Turn_UI()
{
	pThis = this;
	button = new SystemButton;
	backColor = worldturnNS::CUR_BACKGROUND_COLOR;
	is_turn = false;
	turn_delay = 0;
	//img_turn = new Image;
	//rect_turn = { 0, };
}


CWorld_Turn_UI::~CWorld_Turn_UI()
{
}

bool CWorld_Turn_UI::initialize(Graphics * g, Input * i)
{
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
		worldturnNS::cur_turn_height);	//right - start


	//img_turn->initialize(g, worldturnNS::pass_turn_width, worldturnNS::pass_turn_height, 0, IMAGEMANAGER->getTexture(worldturnNS::img_name));
	//img_turn->setX(rect_turn.right + worldturnNS::distance);
	//img_turn->setY(rect_turn.top);

	button->initialize(g, i, worldturnNS::img_name, true);
	button->setButtonPos(rect_turn.right + worldturnNS::distance, rect_turn.top);
	//button->setWidth(worldturnNS::pass_turn_width);
	//button->setHeight(worldturnNS::pass_turn_height);

	button->setRegistFunction(std::bind(&CWorld_Turn_UI::click_event));

	m_dxFont.initialize(m_pGraphics, worldturnNS::FONT_SIZE, true, false, worldturnNS::FONT);

	//addMessage("turn", "");

	return true;
}

void CWorld_Turn_UI::update(float frameTime)
{
	//setMessage("turn", "1 ео");

	if (is_turn == true)
	{
		if (turn_delay >= worldturnNS::DELAY)
		{
			SOUNDMANAGER->play(worldturnNS::SOUND_TURN, g_fSoundMasterVolume * g_fSoundEffectVolume);

			is_turn = false;
			turn_delay = 0;

			return;
		}

		turn_delay += frameTime;
	}

	if (is_turn == false)
		button->update(frameTime);
}

void CWorld_Turn_UI::render()
{
	SystemUIDialog::render();

	m_pGraphics->spriteBegin();

	std::string _turn = std::to_string(player->get_turn());
	_turn += " T";

	m_dxFont.print(_turn, rect_turn, DT_VCENTER + DT_CENTER);
	
	//img_turn->draw();

	m_pGraphics->spriteEnd();

	button->render();
}

void CWorld_Turn_UI::click_event()
{
	//if (SOUNDMANAGER->isPlaySound(worldturnNS::SOUND_TURN))
	//SOUNDMANAGER->play(worldturnNS::SOUND_TURN, g_fSoundMasterVolume + g_fSoundEffectVolume);

	pThis->player->turn_end();

	pThis->is_turn = true;
}
