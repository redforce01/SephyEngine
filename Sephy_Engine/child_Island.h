#pragma once

#include "building.h"
#include "iostream"

class CWorld_User;
class CChild_Island	//neighborhood island infor
{
private:
	CWorld_User* user;

	E_RESOURCE type;	//resource type
	int resource;	//resource amount

public:
	void SetLoadLinkUser(CWorld_User* _user) { user = _user; }

	CChild_Island();
	~CChild_Island();

	void turn_end();

	void initialize(E_RESOURCE _type, int _resource)
	{
		type = _type;
		resource = _resource;
	}

	E_RESOURCE get_type() { return type; }
	int get_resource() { return resource; }
};