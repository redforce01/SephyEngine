#pragma once

#include "child_Island.h"

class CWorld_Island	//island infor
{
private:
	std::string name;

	UINT id;		//island unique number

	UINT x;			//island x position (standard world)
	UINT y;			//island y position (standard world)
	UINT width;	//island collision width;
	UINT height;	//island collision height;

	bool u_island;	//can go island

	std::vector<UINT> nextnode;	//island connect nodes
	std::vector<CChild_Island> child_node;	//island's near neighborhood island
public:
	CWorld_Island();
	~CWorld_Island();

	void initialize(std::string _name, UINT _id, UINT _x, UINT _y, UINT _width, UINT _height)
	{
		name = _name;
		id = _id;
		x = _x;
		y = _y;
		width = _width;
		height = _height;

		u_island = false;

		printf("%s\t%d\t%d\t%d\t%d\t%d\t \n", name, id, x, y, width, height);
	}

	void add_node(UINT _nextnode) { nextnode.emplace_back(_nextnode); }
	void add_child(CChild_Island _child) { child_node.emplace_back(_child); }
	void set_use(bool _use) { u_island = _use; }

	std::string getName() { return name; }
	UINT getID() { return id; }
	UINT getX() { return x; }
	UINT getY() { return y; }
	UINT getWidth() { return width; }
	UINT getHeight() { return height; }
	bool set_use() { return u_island; }

	std::vector<UINT> get_node() { return nextnode; }
	std::vector<CChild_Island> get_child() { return child_node; }
};