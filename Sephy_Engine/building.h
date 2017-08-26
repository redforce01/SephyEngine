#pragma once

#include "production_Ship.h"

enum E_RESOURCE
{
	MONEY = 0, IRON, FUEL, RESEARCH
};

namespace worldbuildingNS
{
	const std::string SOUND_DESTROY = "Destroy_Building";

	const int KIND_RESOURCE = 4;
	const int MAX_ACTION = 3;
}

class CWorld_Island;
class CWorld_User;
class CBuilding		//building infor
{
private :
	CWorld_Island* island;
	CWorld_User* user;

private:
	CProduction_Ship* action[worldbuildingNS::MAX_ACTION];	//action max 3

	int id;		//building unique number
	int n_building;	//need building
	int need_resource[worldbuildingNS::KIND_RESOURCE];	//need resource (0:money / 1:iron / 2:fuel / 3:research)
	int produce_resource[worldbuildingNS::KIND_RESOURCE];	//produce resource
	int turn;	//spend turn
	int start_turn;
	
	bool is_building;
	bool is_complete;
	bool is_destroy;

	std::string name;	//building name
	std::vector<int> ship;

	void complete_action();	//완성된 배 처리
	void asort_action();	//내림차순 정렬

public:
	void SetLoadLinkUser(CWorld_User* _user) { user = _user; }
	void SetLoadLinkIsland(CWorld_Island* _island) { island = _island; }

	CBuilding();
	~CBuilding();
	
	void turn_end();

	void initialize(std::string _name, int _id, int _turn, int _nBuilding, int _nMoney, int _nIron, int _pMoney, int _pIron, int _pFuel, int _pResearch);
	void release();
	void add_Ship(int _nextship) { ship.emplace_back(_nextship); }
	void set_is_building(bool _is) { is_building = _is; }
	void set_is_complete(bool _is) { is_complete = _is; }
	void set_is_destroy(bool _is) { is_destroy = _is; }
	void add_action(int _index, CProduction_Ship* _ship) { action[_index] = _ship; }
	void set_turn(int _turn) { turn = _turn; }
	void load(bool _building, bool _complete, bool _destroy, int _turn);
	void command_center();

	CProduction_Ship* get_action(int _index) { return action[_index]; }

	std::vector<int> get_ship() { return ship; }
	std::string getName() { return name; }

	bool get_is_building() { return is_building; }
	bool get_is_complete() { return is_complete; }
	bool get_is_destroy() { return is_destroy; }

	int get_ship_size() { return ship.size(); }
	int getID() { return id; }
	int get_turn() { return turn; }
	int get_building() { return n_building; }	//필요 조건 건물
	int* get_need_resource() { return need_resource; }
	int* get_produce_resource() { return produce_resource; }
};