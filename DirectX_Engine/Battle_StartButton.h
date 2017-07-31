#pragma once
#include "systemButton.h"
class CBattle_StartButton : public SystemButton
{
private:

	
public:
	CBattle_StartButton();
	~CBattle_StartButton();

	bool initialize(Graphics* g, Input* i);
	void update(float frameTime);
	void render();
	
	static void functionBattleStart();

};

