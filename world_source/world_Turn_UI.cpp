#include "stdafx.h"
#include "world_Turn_UI.h"


CWorld_Turn_UI::CWorld_Turn_UI()
{
	img_turn = new Image;
	rect_turn = { 0, };
}


CWorld_Turn_UI::~CWorld_Turn_UI()
{
}

bool CWorld_Turn_UI::initialize(Graphics * g, Input * i)
{
	m_pGraphics = g;
	m_pInput = i;

	SystemUIDialog::initializeDialog(m_pGraphics, m_pInput, 
		worldturnNS::x,
		worldturnNS::y,
		worldturnNS::cur_turn_width,
		worldturnNS::cur_turn_height,
		worldturnNS::MARGIN);

	rect_turn = RectMake(
		worldturnNS::x,
		worldturnNS::y,
		worldturnNS::cur_turn_width,
		worldturnNS::cur_turn_height);	//right - start

	dxFont.initialize(m_pGraphics, worldturnNS::FONT_SIZE, true, false, worldturnNS::FONT);

	img_turn->initialize(g, worldturnNS::pass_turn_width, worldturnNS::pass_turn_height, 0, IMAGEMANAGER->getTexture(worldturnNS::img_name));
	img_turn->setX(rect_turn.right + worldturnNS::distance);
	img_turn->setY(rect_turn.top);

	addMessage("turn", "");

	return true;
}

void CWorld_Turn_UI::update(float frameTime)
{
	setMessage("turn", "1 ео");
}

void CWorld_Turn_UI::render()
{
	SystemUIDialog::render();

	m_pGraphics->spriteBegin();

	dxFont.print(m_turnMessage.find("turn")->second, rect_turn, DT_VCENTER + DT_CENTER);
	
	img_turn->draw();

	m_pGraphics->spriteEnd();
}
