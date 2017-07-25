#pragma once

#include "production_Ship.h"

enum E_RESOURCE
{
	E_MONEY = 0, E_FUEL = 1, E_IRON = 2, E_RESEARCH = 3
};

class CBuilding		//building infor
{
private:
	UINT id;		//building unique number
	UINT type;		//building type
	UINT money;	//need build building resource
	UINT fuel;
	UINT iron;
	UINT research;
	UINT turn;	//spend turn

	bool in_production;	//use building
public:
	CBuilding();
	~CBuilding();

	void initialize(UINT _id, UINT _type)
	{
		id = _id;
		type = _type;
		money = fuel = iron = research = turn = 0;
		in_production = false;
	}

	void set_turn(UINT _turn) { turn = _turn; }

	void set_all_resource(UINT _money, UINT _fuel, UINT _iron, UINT _research)
	{
		money = _money;
		fuel = _fuel;
		iron = _iron;
		research = _research;
	}
	void set_production(bool b) { in_production = b; }
	void set_money(UINT _money) { money = _money; }
	void set_fuel(UINT _fuel) { fuel = _fuel; }
	void set_iron(UINT _iron) { iron = _iron; }
	void set_research(UINT _research) { research = _research; }

	bool get_production() { return in_production; }
	UINT getID() { return id; }
	UINT getType() { return type; }
	UINT get_turn() { return turn; }
	UINT get_resource(E_RESOURCE resource)
	{
		switch (resource)
		{
		case E_MONEY:
			return money;
		case E_FUEL:
			return fuel;
		case E_IRON:
			return iron;
		case E_RESEARCH:
			return research;
		default:
			break;
		}
	}
};