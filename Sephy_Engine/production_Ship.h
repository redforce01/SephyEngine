#pragma once

class CWorld_User;
class CProduction_Ship
{
private :
	CWorld_User* user;

private:
	std::string name;

	int id;
	int turn;
	int money;
	int iron;
	int fuel;
	int research;
	int fuel_cost;
	int current_island;
	int start_turn;

	bool is_create;
	bool is_complete;
	bool is_destroy;
	bool is_fuel;
	bool is_move;

	std::vector<int> building;

public:
	void SetLoadLinkUser(CWorld_User* _user) { user = _user; }

	CProduction_Ship();
	~CProduction_Ship();

	void turn_end();

	void initialize(std::string _name, int _id, int _turn, int _money, int _iron, int _fuel, int _research, int _cost);
	void release();
	void add_building(int build) { building.emplace_back(build); }
	void setIsland(int _island) { current_island = _island; }
	void set_is_create(bool _is) { is_create = _is; }
	void set_is_complete(bool _is) { is_complete = _is; }
	void set_is_destroy(bool _is) { is_destroy = _is; }
	void set_is_move(bool _is) { is_move = _is; }
	void set_turn(int _turn) { turn = _turn; }
	void load(bool _move, bool _fuel);

	std::vector<int> get_building() { return building; }
	std::string getName() { return name; }

	int get_building_size() { return building.size(); }
	int getID() { return id; }
	int getIsland() { return current_island; }
	int getTurn() { return turn; }
	int getCost() { return fuel_cost; }
	int get_resource(int _type);

	bool get_is_create() { return is_create; }
	bool get_is_complete() { return is_complete; }
	bool get_is_destroy() { return is_destroy; }
	bool get_is_fuel() { return is_fuel; }
	bool get_is_move() { return is_move; }
};
