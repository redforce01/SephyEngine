#ifndef _BATTLE_UI_FLAGSHIP_BUTTON_H
#define _BATTLE_UI_FLAGSHIP_BUTTON_H
#define WIN32_LEAN_AND_MEAN

class CBattle_UI_FlagShipButton;

#include "systemButton.h"

namespace battleUIFlagShipButtonNS
{
	const std::string FILENAME = "Set";
	const float FLAG_SHIP_BUTTON_X = 0; // ( mean : g_fScreenWidth - VIEW_WIDTH(220) + MarginFromLeft(110))
	const float FLAG_SHIP_BUTTON_Y = 300.f;
	const float FLAG_SHIP_BUTTON_WIDTH = 90.f;
	const float FLAG_SHIP_BUTTON_HEIGHT = 35.f;
	const float FLAG_SHIP_BUTTON_MARGIN = 110.f;
	const float FLEET_MAKE_VIEW_WIDTH = 220.f;
}

class CBattle_UI_FlagShipButton : public SystemButton
{
public:
	CBattle_UI_FlagShipButton();
	~CBattle_UI_FlagShipButton();

	bool initialize(Graphics* g, Input* i);
	void update(float frameTime);
	void render();
};

#endif // !_BATTLE_UI_FLAGSHIP_BUTTON_H
