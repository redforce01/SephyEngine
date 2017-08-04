#ifndef _BATTLE_UI_FLEETMAKE_BUTTON_H
#define _BATTLE_UI_FLEETMAKE_BUTTON_H
#define WIN32_LEAN_AND_MEAN

class CBattle_UI_FleetMakeButton;

#include "systemButton.h"

namespace battleUIFleetMakeButtonNS
{
	const std::string FLEET_MAKE_BUTTON_CLOSE_KEY = "EscortButtonClose";
	const std::string FLEET_MAKE_BUTTON_OPEN_KEY = "EscortButtonOpen";
	const float FLEET_MAKE_BUTTON_X = 0.f; // ( mean : g_fScreenWidth - BUTTON_WIDTH(200) - MARGIN(10))
	const float FLEET_MAKE_BUTTON_Y = 180.f;
	const float FLEET_MAKE_BUTTON_WIDTH = 200.f;
	const float FLEET_MAKE_BUTTON_HEIGHT = 60.f;
	const float FLEET_MAKE_BUTTON_MARGIN = 20.f;
}

class CBattle_UI_FleetMakeButton : public SystemButton
{
private:
	std::string m_strButtonKey;
	bool		m_bOpenClose;	// true == open : false == close

public:
	CBattle_UI_FleetMakeButton();
	~CBattle_UI_FleetMakeButton();

	bool initialize(Graphics* g, Input* i);
	void update(float frameTime);
	void render();

	void setOpenClose(bool bOpenClose)
	{
		m_bOpenClose = bOpenClose;
	}
};

#endif // !_BATTLE_UI_FLEETMAKE_BUTTON_H
