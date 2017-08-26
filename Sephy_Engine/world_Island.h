#pragma once

#include "child_Island.h"
#include "world_Ship.h"

namespace worldislandNS
{
	const int MARGIN = 100.0f;
	const int TILE_WIDTH = 767;
	const int TILE_HEIGHT = 325;

	const int MAX_BUILDING = 3;
}

class CWorld_User;
class CWorld_Island	//island infor
{
private :
	CWorld_User* user;

private:
	Graphics* m_pGraphics;
	Input* m_pInput;

	std::string name;

	int id;		//island unique number
	int x;			//island x position (standard world)
	int y;			//island y position (standard world)
	int width;		//island collision width;
	int height;	//island collision height;
	int c_turn;	//점령 후 넘겨진 턴

	RECT rt;	//island Rect
	RECT tile_rt;

	CBuilding* building_node[worldislandNS::MAX_BUILDING];	//island's build building

	std::vector<CProduction_Ship*> current_ship;
	std::vector<CWorld_Ship*> show_ship;
	std::vector<CChild_Island*> child_node;	//island's near neighborhood island

	std::vector<int> delete_node;
	std::vector<int> nextnode;	//island connect nodes

	void add_Child();	//about to island's id -> add child island

public:
	void SetLoadLinkUser(CWorld_User* _user) { user = _user; }

	CWorld_Island();
	~CWorld_Island();

	void turn_end();

	void initialize(Graphics* g, Input* i, std::string _name, int _id, int _x, int _y, int _width, int _height, int _tilex, int _tiley);
	void update(float frameTime);
	void render();
	void release();

	void add_node(int _nextnode) { nextnode.emplace_back(_nextnode); }
	void add_building(int _index, CBuilding* _building);
	void add_child(CChild_Island* _child) { child_node.emplace_back(_child); }
	void add_ship(CProduction_Ship* _ship);
	void setTurn(int _turn) { c_turn = _turn; }
	void remove_ship(int _index) { current_ship.erase(current_ship.begin() + _index); }
	void clear_ship() { current_ship.clear(); }
	void remove_ship_img();
	void w_move_ud(float _speed);
	void w_move_rl(float _speed);

	int getX() { return x; }
	int getY() { return y; }
	int getTurn() { return c_turn; }
	int getID() { return id; }
	int getWidth() { return width; }
	int getHeight() { return height; }
	int get_Ship_Size() { return current_ship.size(); }
	int get_Building_Size() { return worldislandNS::MAX_BUILDING; }
	int get_Child_Size() { return child_node.size(); }

	RECT getRect() { return rt; }
	RECT getCancelRect();

	POINT getPt() { return { x, y }; }

	std::string getName() { return name; }
	std::vector<int> get_node() { return nextnode; }
	std::vector<CChild_Island*> get_child() { return child_node; }
	std::vector<CProduction_Ship*> get_ship() { return current_ship; }

	CBuilding* get_Building(int _index) { return building_node[_index]; }
};