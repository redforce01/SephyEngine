#pragma once

class CWorld_User;
class CProduction_Ship
{
private:
	CWorld_User* user;

	std::string name;
	UINT id;
	int turn;
	int money;
	int iron;
	int fuel;
	int research;
	int fuel_cost;

	UINT current_island;
	//UINT move_island;
	UINT start_turn;
	//UINT x;
	//UINT y;

	bool is_create;
	bool is_complete;
	bool is_destroy;

	bool is_fuel;
	bool is_move;

	std::vector<UINT> building;

public:
	void SetLoadLinkUser(CWorld_User* _user) { user = _user; }

	CProduction_Ship();
	~CProduction_Ship();

	void turn_end();

	void initialize(std::string _name, UINT _id, int _turn, int _money, int _iron, int _fuel, int _research, int _cost);
	void add_building(UINT build) { building.emplace_back(build); }
	void setIsland(UINT _island) { current_island = _island; }
	void set_is_create(bool _is) { is_create = _is; }
	void set_is_complete(bool _is) { is_complete = _is; }
	void set_is_destroy(bool _is) { is_destroy = _is; }
	//void set_move_island(UINT _island) { move_island = _island; }
	void set_is_move(bool _is) { is_move = _is; }
	void set_turn(UINT _turn) { turn = _turn; }
	void load(bool _move, bool _fuel);
	//void setX(UINT _x) { x = _x; }
	//void setY(UINT _y) { y = _y; }

	std::vector<UINT> get_building() { return building; }
	std::string getName() { return name; }
	UINT get_building_size() { return building.size(); }
	UINT getID() { return id; }
	UINT getIsland() { return current_island; }
	int getTurn() { return turn; }
	//UINT getMove() { return move_island; }
	int getCost() { return fuel_cost; }
	int get_resource(UINT _type);
	bool get_is_create() { return is_create; }
	bool get_is_complete() { return is_complete; }
	bool get_is_destroy() { return is_destroy; }
	bool get_is_fuel() { return is_fuel; }
	bool get_is_move() { return is_move; }
	//UINT getX() { return x; }
	//UINT getY() { return y; }
};
