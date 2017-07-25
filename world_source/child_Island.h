#pragma once

#include "building.h"

class CChild_Island	//neighborhood island infor
{
private:
	UINT id;		//n_island unique number
	UINT type;		//n_island type -> build & resouce island

	UINT resource;	//if type == resouce_island else 0

	CBuilding* building;	//if type == build_island else null
public:
	CChild_Island();
	~CChild_Island();

	void initialize(UINT _id, UINT _type)
	{
		id = _id;
		type = _type;
	}

	void set_building(CBuilding _building) { building = new CBuilding(_building); }
	void set_resource(UINT _resource) { resource = _resource; }

	CBuilding* get_building() { return building; }
	UINT get_resource() { return resource; }
	UINT getID() { return id; }
	UINT getType() { return type; }
};