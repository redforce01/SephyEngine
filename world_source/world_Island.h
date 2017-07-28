#pragma once

#include "child_Island.h"
#include "world_Ship.h"

class CWorld_Island	//island infor
{
private:
	Graphics* m_pGraphics;
	Input* m_pInput;

	std::string name;
	UINT id;		//island unique number

	UINT x;			//island x position (standard world)
	UINT y;			//island y position (standard world)
	UINT width;		//island collision width;
	UINT height;	//island collision height;

	UINT c_turn;	//점령 후 넘겨진 턴

	RECT rt;	//island Rect

	//bool u_island;	//can go island
	std::vector<CProduction_Ship*> current_ship;
	std::vector<CWorld_Ship*> show_ship;

	std::vector<UINT> nextnode;	//island connect nodes
	std::vector<CChild_Island*> child_node;	//island's near neighborhood island
	std::vector<CBuilding*> building_node;	//island's build building
	//CBuilding* building[3]->최대 3개의 건물이라면 이런식으로

	void add_Child();	//about to island's id -> add child island

public:
	CWorld_Island();
	~CWorld_Island();

	void turn_end();

	void initialize(Graphics* g, Input* i, std::string _name, UINT _id, UINT _x, UINT _y, UINT _width, UINT _height);
	void render();

	void add_node(UINT _nextnode) { nextnode.emplace_back(_nextnode); }
	//void add_child(CChild_Island* _child) { child_node.emplace_back(_child); }
	//void set_use(bool _use) { u_island = _use; }
	void set_rt(UINT _x, UINT _y, UINT _width, UINT _height) { rt = RectMake(_x - _width / 2, _y - _height / 2, width, height); }
	void add_building(CBuilding* _building) { building_node.emplace_back(_building); }
	void add_child(CChild_Island* _child) { child_node.emplace_back(_child); }
	void add_ship(CProduction_Ship* _ship);
	void remove_ship(UINT _index) { current_ship.erase(current_ship.begin() + _index); }

	std::string getName() { return name; }
	UINT getID() { return id; }
	UINT getX() { return x; }
	UINT getY() { return y; }
	UINT getWidth() { return width; }
	UINT getHeight() { return height; }
	RECT getRect() { return rt; }

	//bool get_use() { return u_island; }

	std::vector<UINT> get_node() { return nextnode; }
	std::vector<CChild_Island*> get_child() { return child_node; }
	std::vector<CProduction_Ship*> get_ship() { return current_ship; }
	CBuilding* get_Building(int _index);
	UINT get_Building_Size() { return building_node.size(); }
	UINT get_Child_Size() { return child_node.size(); }
};