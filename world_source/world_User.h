#pragma once

#include "World_Island.h"

class CWorld_User
{
protected:
	Graphics* m_pGraphics;
	Input* m_pInput;

	std::vector<CWorld_Island*> island_node;
	std::vector<CProduction_Ship*> ship_node;
	UINT money;
	UINT iron;
	UINT fuel;
	UINT research;

public:
	CWorld_User();
	~CWorld_User();

	void initialize(Graphics* g, Input* i, UINT _money, UINT _iron, UINT _fuel, UINT _research);
	void add_island(CWorld_Island* _island) { island_node.emplace_back(_island); }
	void add_ship(CProduction_Ship* _ship) { ship_node.emplace_back(_ship); }

	void save_data(std::string p_c);
	std::vector<CWorld_Island*> get_island() { return island_node; }
	std::vector<CProduction_Ship*> get_ship() { return ship_node; }
};
