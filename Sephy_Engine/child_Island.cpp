#include "stdafx.h"
#include "child_Island.h"
#include "world_User.h"

CChild_Island::CChild_Island()
{
}


CChild_Island::~CChild_Island()
{
}

void CChild_Island::turn_end()
{
	//자원 증가
	user->add_resource(type, resource);
	user->add_increase_resource(type, resource);
}

void CChild_Island::release()
{
}
