#pragma once

#include "world_User.h"

class CWorld_Player : public CWorld_User
{
private:
	std::vector<CProduction_Ship*> current_ship;

public:
	CWorld_Player();
	~CWorld_Player();

	void add_cur_ship(CProduction_Ship* _ship) { current_ship.emplace_back(_ship); }

	std::vector<CProduction_Ship*> get_cur_ship() { return current_ship; }
};
