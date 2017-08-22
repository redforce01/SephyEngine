#pragma once

#include "World_Island_Data.h"

namespace world_userNS
{
	const UINT MAX_BUILD = 12;
	const UINT KIND_RESOURCE = 4;
}

class CWorld_MainSystem;
class CWorld_User
{
protected:
	Graphics* m_pGraphics;
	Input* m_pInput;

	CWorld_MainSystem* scene;
	CWorld_Island_Data* island_data;

	std::vector<CWorld_Island*> island_node;	//현재 보유 섬
	std::vector<CProduction_Ship*> ship_node;	//현재 보유한 배

	std::vector<CProduction_Ship*> current_ship;	//현재 선택 배(이동할 배)
	int current_building[world_userNS::MAX_BUILD];

	int money;
	int iron;
	int fuel;
	int research;

	int increase_resource[world_userNS::KIND_RESOURCE];
	int decrease_resource[world_userNS::KIND_RESOURCE];

	bool is_update;

public:
	void SetLoadLinkData(CWorld_Island_Data* _data) { island_data = _data; }
	void SetLoadLinkScene(CWorld_MainSystem* _scene) { scene = _scene; }

	CWorld_User();
	~CWorld_User();

	virtual void initialize(Graphics* g, Input* i, int _money, int _iron, int _fuel, int _research);
	void add_island(CWorld_Island* _island) { island_node.emplace_back(_island); }
	void add_ship(CProduction_Ship* _ship, CWorld_Island* _island);
	void add_cur_ship(CProduction_Ship* _ship) { current_ship.emplace_back(_ship); }
	void add_cur_building(UINT _index) { current_building[_index]++; }
	void destroy_cur_building(UINT _index) { current_building[_index]--; }
	void add_resource(E_RESOURCE _type, int _resource);
	void add_increase_resource(E_RESOURCE _type, int _amount) { increase_resource[_type] += _amount; }
	void add_decrease_resource(E_RESOURCE _type, int _amount) { decrease_resource[_type] += _amount; }
	void remove_cur_ship(UINT _index) { current_ship.erase(current_ship.begin() + _index); }
	void clear_cur_ship() { current_ship.clear(); }
	void set_is_update(bool _is) { is_update = _is; }
	void remove_island(UINT _index);
	void print_world_log(const std::string message);
	std::deque<std::string> get_log_message();

	std::vector<CWorld_Island*> get_island() { return island_node; }
	std::vector<CProduction_Ship*> get_ship() { return ship_node; }
	std::vector<CProduction_Ship*> get_cur_ship() { return current_ship; }
	int get_cur_building(UINT _index) { return current_building[_index]; }
	CWorld_Island_Data* get_data() { return island_data; }
	int get_resource(E_RESOURCE _type);
	int get_increase_resource(E_RESOURCE _type) { return increase_resource[_type]; }
	int get_decrease_resource(E_RESOURCE _type) { return decrease_resource[_type]; }


	bool spend_resource(E_RESOURCE _type, int _amount);
};
