#include "stdafx.h"
#include "Battle_UI_FleetRemoveButton.h"

CBattle_UI_FleetRemoveButton::CBattle_UI_FleetRemoveButton()
{
}


CBattle_UI_FleetRemoveButton::~CBattle_UI_FleetRemoveButton()
{
}

bool CBattle_UI_FleetRemoveButton::initialize(Graphics * g, Input * i)
{
	bool success = SystemButton::initialize(g, i,
		g_fScreenWidth - battleUIFleetRemoveButtonNS::FLEET_MAKE_VIEW_WIDTH + battleUIFleetRemoveButtonNS::FLEET_REMOVE_BUTTON_MARGIN,
		battleUIFleetRemoveButtonNS::FLEET_REMOVE_BUTTON_Y,
		battleUIFleetRemoveButtonNS::FILENAME, true);
	return success;
}

void CBattle_UI_FleetRemoveButton::update(float frameTime)
{
	SystemButton::update(frameTime);
}

void CBattle_UI_FleetRemoveButton::render()
{
	SystemButton::render();
}