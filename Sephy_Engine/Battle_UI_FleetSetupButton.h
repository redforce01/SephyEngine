#ifndef _BATTLE_UI_FLEETSETUP_BUTTON_H
#define _BATTLE_UI_FLEETSETUP_BUTTON_H
#define WIN32_LEAN_AND_MEAN

class CBattle_UI_FleetSetupButton;

#include "systemButton.h"

namespace battleUIFleetSetupButtonNS
{
	const std::string FILENAME = "SetUpButton";
	const float FLEET_SETUP_BUTTON_X = 0; // (mean : g_fScreenWidth - VIEW_WIDTH(220) + MarginFromLeft(100))
	const float FLEET_SETUP_BUTTON_Y = 490 - 24 - 10;
	const float FLEET_SETUP_BUTTON_WIDTH = 43.f;
	const float FLEET_SETUP_BUTTON_HEIGHT = 24.f;
	const float FLEET_SETUP_BUTTON_MARGIN = 100.f;
	const float FLEET_MAKE_VIEW_WIDTH = 220;
}

class CBattle_UI_FleetSetupButton : public SystemButton
{
public:
	CBattle_UI_FleetSetupButton();
	~CBattle_UI_FleetSetupButton();

	bool initialize(Graphics* g, Input* i);
	void update(float frameTime);
	void render();
};

#endif // !_BATTLE_UI_FLEETSETUP_BUTTON_H
