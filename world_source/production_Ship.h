#pragma once

class CProduction_Ship
{
private:
	std::string name;
	UINT id;
	UINT money;
	UINT iron;
	UINT fuel;
	UINT research;
	UINT fuel_cost;

	UINT current_island;
	UINT x;
	UINT y;

	std::vector<UINT> building;

public:
	CProduction_Ship();
	~CProduction_Ship();

	void turn_end();

	void initialize(std::string _name, UINT _id, UINT _money, UINT _iron, UINT _fuel, UINT _research, UINT _cost);
	void add_building(UINT build) { building.emplace_back(build); }
	void setIsland(UINT _island) { current_island = _island; }
	void setX(UINT _x) { x = _x; }
	void setY(UINT _y) { y = _y; }

	std::vector<UINT> get_building() { return building; }
	UINT get_building_size() { return building.size(); }
	std::string getName() { return name; }
	UINT getID() { return id; }
	UINT getIsland() { return current_island; }
	UINT getX() { return x; }
	UINT getY() { return y; }
};
