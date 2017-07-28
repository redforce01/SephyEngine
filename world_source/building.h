#pragma once

#include "production_Ship.h"

enum E_RESOURCE
{
	MONEY = 0, IRON = 1, FUEL = 2, RESEARCH = 3
};

class CBuilding		//building infor
{
private:
	std::string name;	//building name
	UINT id;		//building unique number
	UINT n_building;	//need building
	UINT need_resource[2];	//need resource (0:money / 1:iron / 2:fuel / 3:research)
	UINT produce_resource[4];	//produce resource
	
	UINT turn;	//spend turn

	//std::vector<CProduction_Ship*> ship;
	std::vector<UINT> ship;

public:
	CBuilding();
	~CBuilding();
	
	void turn_end();

	void initialize(std::string _name, UINT _id, UINT _turn, UINT _nBuilding, UINT _nMoney, UINT _nIron, UINT _pMoney, UINT _pIron, UINT _pFuel, UINT _pResearch);
	void add_Ship(UINT _nextship) { ship.emplace_back(_nextship); }

	std::vector<UINT> get_ship() { return ship; }
	UINT get_ship_size() { return ship.size(); }
	UINT getID() { return id; }
	UINT get_turn() { return turn; }
	UINT get_building() { return n_building; }	//필요 조건 건물
	UINT* get_need_resource() { return need_resource; }
	UINT* get_produce_resource() { return produce_resource; }
};