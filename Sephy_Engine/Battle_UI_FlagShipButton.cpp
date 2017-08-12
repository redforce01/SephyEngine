#include "stdafx.h"
#include "Battle_UI_FlagShipButton.h"


CBattle_UI_FlagShipButton::CBattle_UI_FlagShipButton()
{
}


CBattle_UI_FlagShipButton::~CBattle_UI_FlagShipButton()
{
}

bool CBattle_UI_FlagShipButton::initialize(Graphics * g, Input * i)
{
	bool success = SystemButton::initialize(g, i,
		g_fScreenWidth - battleUIFlagShipButtonNS::FLEET_MAKE_VIEW_WIDTH + battleUIFlagShipButtonNS::FLAG_SHIP_BUTTON_MARGIN,
		battleUIFlagShipButtonNS::FLAG_SHIP_BUTTON_Y,
		battleUIFlagShipButtonNS::FILENAME, true);
	return success;
}

void CBattle_UI_FlagShipButton::update(float frameTime)
{
	SystemButton::update(frameTime);
}

void CBattle_UI_FlagShipButton::render()
{
	SystemButton::render();
}
