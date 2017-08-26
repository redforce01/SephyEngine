#pragma once

#include "building.h"
#include "iostream"

class CWorld_User;
class CChild_Island	//neighborhood island infor
{
private :
	CWorld_User* user;

private:
	E_RESOURCE type;	//resource type
	int resource;	//resource amount

public:
	void SetLoadLinkUser(CWorld_User* _user) { user = _user; }

	CChild_Island();
	~CChild_Island();

void initialize(E_RESOURCE _type, int _resource)
	{
		type = _type;
		resource = _resource;
	}
	void release();
	void turn_end();

	int get_resource() { return resource; }

	E_RESOURCE get_type() { return type; }
};