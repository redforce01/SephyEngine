#pragma once

#include "child_Island.h"
#include "world_Ship.h"

namespace worldislandNS
{
	const UINT MARGIN = 100.0f;
	const UINT TILE_WIDTH = 767;
	const UINT TILE_HEIGHT = 325;

	const int MAX_BUILDING = 3;
}

class CWorld_User;
class CWorld_Island	//island infor
{
private:
	CWorld_User* user;

	Graphics* m_pGraphics;
	Input* m_pInput;

	std::string name;
	UINT id;		//island unique number

	int x;			//island x position (standard world)
	int y;			//island y position (standard world)
	UINT width;		//island collision width;
	UINT height;	//island collision height;

	//UINT tile_x;	//tile size
	//UINT tile_y;

	UINT c_turn;	//점령 후 넘겨진 턴

	RECT rt;	//island Rect
	RECT tile_rt;

	//bool u_island;	//can go island
	std::vector<CProduction_Ship*> current_ship;
	std::vector<CWorld_Ship*> show_ship;
	std::vector<CChild_Island*> child_node;	//island's near neighborhood island
	CBuilding* building_node[worldislandNS::MAX_BUILDING];	//island's build building

	std::vector<UINT> delete_node;
	std::vector<UINT> nextnode;	//island connect nodes
	//CBuilding* building[3]->최대 3개의 건물이라면 이런식으로

	void add_Child();	//about to island's id -> add child island

public:
	void SetLoadLinkUser(CWorld_User* _user) { user = _user; }

	CWorld_Island();
	~CWorld_Island();

	void turn_end();

	void initialize(Graphics* g, Input* i, std::string _name, UINT _id, int _x, int _y, UINT _width, UINT _height, UINT _tilex, UINT _tiley);
	void update(float frameTime);
	void render();

	void add_node(UINT _nextnode) { nextnode.emplace_back(_nextnode); }
	//void add_child(CChild_Island* _child) { child_node.emplace_back(_child); }
	//void set_use(bool _use) { u_island = _use; }
	void add_building(UINT _index, CBuilding* _building);
	void add_child(CChild_Island* _child) { child_node.emplace_back(_child); }
	void add_ship(CProduction_Ship* _ship);
	void setTurn(UINT _turn) { c_turn = _turn; }
	void remove_ship(UINT _index) { current_ship.erase(current_ship.begin() + _index); }
	void remove_ship_img();

	std::string getName() { return name; }
	int getX() { return x; }
	int getY() { return y; }
	//POINT getTilePt() { return { (int)tile_x, (int)tile_y }; }
	POINT getPt() { return { x, y }; }
	UINT getTurn() { return c_turn; }
	UINT getID() { return id; }
	UINT getWidth() { return width; }
	UINT getHeight() { return height; }
	//UINT getTileX() { return tile_x; }
	//UINT getTileY() { return tile_y; }
	RECT getRect() { return rt; }
	RECT getCancelRect();

	void w_move_ud(float _speed);
	void w_move_rl(float _speed);
	//bool get_use() { return u_island; }

	std::vector<UINT> get_node() { return nextnode; }
	std::vector<CChild_Island*> get_child() { return child_node; }
	std::vector<CProduction_Ship*> get_ship() { return current_ship; }
	CBuilding* get_Building(UINT _index) { return building_node[_index]; }
	int get_Ship_Size() { return current_ship.size(); }
	UINT get_Building_Size() { return worldislandNS::MAX_BUILDING; }
	UINT get_Child_Size() { return child_node.size(); }
};