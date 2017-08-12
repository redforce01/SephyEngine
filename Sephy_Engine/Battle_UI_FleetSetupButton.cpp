#include "stdafx.h"
#include "Battle_UI_FleetSetupButton.h"

CBattle_UI_FleetSetupButton::CBattle_UI_FleetSetupButton()
{
}


CBattle_UI_FleetSetupButton::~CBattle_UI_FleetSetupButton()
{
}

bool CBattle_UI_FleetSetupButton::initialize(Graphics * g, Input * i)
{
	bool success = SystemButton::initialize(g, i,
		g_fScreenWidth - battleUIFleetSetupButtonNS::FLEET_MAKE_VIEW_WIDTH + battleUIFleetSetupButtonNS::FLEET_SETUP_BUTTON_MARGIN,
		battleUIFleetSetupButtonNS::FLEET_SETUP_BUTTON_Y,
		battleUIFleetSetupButtonNS::FILENAME, true);
	return success;
}

void CBattle_UI_FleetSetupButton::update(float frameTime)
{
	SystemButton::update(frameTime);
}

void CBattle_UI_FleetSetupButton::render()
{
	SystemButton::render();
}