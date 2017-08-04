#ifndef _BATTLE_UI_FLEETREMOVE_BUTTON_H
#define _BATTLE_UI_FLEETREMOVE_BUTTON_H
#define WIN32_LEAN_AND_MEAN

class CBattle_UI_FleetRemoveButton;

#include "systemButton.h"

namespace battleUIFleetRemoveButtonNS
{
	const std::string FILENAME = "RemoveButton";
	const float FLEET_REMOVE_BUTTON_X = 0; // (mean : g_fScreenWidth - VIEW_WIDTH(220) + MarginFromRight(153)
	const float FLEET_REMOVE_BUTTON_Y = 490 - 24 - 10;
	const float FLEET_REMOVE_BUTTON_WIDTH = 43.f;
	const float FLEET_REMOVE_BUTTON_HEIGHT = 24.f;
	const float FLEET_REMOVE_BUTTON_MARGIN = 153.f;
	const float FLEET_MAKE_VIEW_WIDTH = 220;
}

class CBattle_UI_FleetRemoveButton : public SystemButton
{
public:
	CBattle_UI_FleetRemoveButton();
	~CBattle_UI_FleetRemoveButton();

	bool initialize(Graphics* g, Input* i);
	void update(float frameTime);
	void render();
};

#endif // !_BATTLE_UI_FLEETREMOVE_BUTTON_H
