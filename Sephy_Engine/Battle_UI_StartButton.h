#ifndef _BATTLE_UI_STARTBUTTON_H
#define _BATTLE_UI_STARTBUTTON_H
#define WIN32_LEAN_AND_MEAN

class CBattle_UI_StartButton;

#include "systemButton.h"

namespace battleStartButtonNS
{
	const std::string START_BUTTON_FILENAME = "BattleButton";
	const float START_BUTTON_X = 320.f;
	const float START_BUTTON_Y = 20.f;
	const float START_BUTTON_WIDTH = 71.f;
	const float START_BUTTON_HEIGHT = 31.f;
}

class CBattle_UnitSystem;
class CBattle_UI_StartButton : public SystemButton
{
private:
	CBattle_UnitSystem* m_pBattleUnitSystem;
	
public:
	CBattle_UI_StartButton();
	~CBattle_UI_StartButton();

	bool initialize(Graphics* g, Input* i);
	void update(float frameTime);
	void render();

	void setMemoryLinkBattleUnitSystem(CBattle_UnitSystem* pBattleUnitSystem)
	{
		m_pBattleUnitSystem = pBattleUnitSystem;
	}
	
	static void functionBattleStart();
};

#endif // !_BATTLE_UI_STARTBUTTON_H
