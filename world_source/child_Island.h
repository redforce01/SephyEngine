#pragma once

#include "building.h"

class CChild_Island	//neighborhood island infor
{
private:
	UINT type;	//resource type
	UINT resource;	//resource amount

public:
	CChild_Island();
	~CChild_Island();

	void turn_end();

	void initialize(UINT _type, UINT _resource)
	{
		type = _type;
		resource = _resource;
	}

	UINT get_type() { return type; }
	UINT get_resource() { return resource; }
};