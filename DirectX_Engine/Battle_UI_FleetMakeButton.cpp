#include "stdafx.h"
#include "Battle_UI_FleetMakeButton.h"
#include "Battle_UI_FleetMakeViewer.h"

CBattle_UI_FleetMakeButton::CBattle_UI_FleetMakeButton()
{
	m_strButtonKey = battleUIFleetMakeButtonNS::FLEET_MAKE_BUTTON_CLOSE_KEY;
	m_bOpenClose = true;
}


CBattle_UI_FleetMakeButton::~CBattle_UI_FleetMakeButton()
{
}

bool CBattle_UI_FleetMakeButton::initialize(Graphics * g, Input * i)
{
	bool success = SystemButton::initialize(g, i, 
		g_fScreenWidth - battleUIFleetMakeButtonNS::FLEET_MAKE_BUTTON_WIDTH - battleUIFleetMakeButtonNS::FLEET_MAKE_BUTTON_MARGIN,
		battleUIFleetMakeButtonNS::FLEET_MAKE_BUTTON_Y,
		battleUIFleetMakeButtonNS::FLEET_MAKE_BUTTON_CLOSE_KEY, true);
	return success;
}

void CBattle_UI_FleetMakeButton::update(float frameTime)
{
	if (m_bOpenClose)
		SystemButton::setButtonSpriteKey(battleUIFleetMakeButtonNS::FLEET_MAKE_BUTTON_CLOSE_KEY);
	else
		SystemButton::setButtonSpriteKey(battleUIFleetMakeButtonNS::FLEET_MAKE_BUTTON_OPEN_KEY);

	SystemButton::update(frameTime);
}

void CBattle_UI_FleetMakeButton::render()
{
	SystemButton::render();
}