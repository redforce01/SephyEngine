#include "stdafx.h"
#include "world_Island.h"
#include "world_User.h"


//**********	initialize child node (Money, Iron, Fuel)	**********//
void CWorld_Island::add_Child()
{
	CChild_Island* obj1 = new CChild_Island;
	CChild_Island* obj2 = new CChild_Island;
	CChild_Island* obj3 = new CChild_Island;

	obj1->initialize(MONEY, 5);		//money increase 10
	obj2->initialize(IRON, 5);		//iron increase 10
	obj3->initialize(FUEL, 5);		//fuel increase 10

	child_node.emplace_back(obj1);
	child_node.emplace_back(obj2);
	child_node.emplace_back(obj3);

	obj1->SetLoadLinkUser(user);
	obj2->SetLoadLinkUser(user);
	obj3->SetLoadLinkUser(user);

	switch (id)
	{
	case 0:
	case 13:
		obj1->initialize(MONEY, 0);		//money increase 10
		obj2->initialize(IRON, 0);		//iron increase 10
		obj3->initialize(FUEL, 0);		//fuel increase 10
		break;
	case 1:
	case 2:
	case 3:
	case 4:
	case 10:
	case 11:
	case 12:
		//+1 하나
		break;
	case 5:
	case 8:
		obj1->initialize(MONEY, 7);		//money increase 10
		break;
	case 6:
	case 9:
		obj2->initialize(IRON, 7);		//money increase 10
		break;
	case 7:
		obj1->initialize(MONEY, 7);		//money increase 10
		obj2->initialize(IRON, 7);		//iron increase 10
		break;
	case 14:
	case 15:
	case 16:
	case 17:
		obj3->initialize(FUEL, 15);		//fuel increase 10
		break;
	default:
		break;
	}
}

CWorld_Island::CWorld_Island()
{
	for (int i = 0; i < worldislandNS::MAX_BUILDING; i++)
		building_node[i] = nullptr;
}


CWorld_Island::~CWorld_Island()
{
	for (auto iter : current_ship)
	{
		if (iter != nullptr)
			SAFE_DELETE(iter);
	}
	current_ship.clear();

	for (auto iter : show_ship)
	{
		if (iter != nullptr)
			SAFE_DELETE(iter);
	}
	show_ship.clear();

	for (auto iter : child_node)
	{
		if (iter != nullptr)
			SAFE_DELETE(iter);
	}
	child_node.clear();
	delete_node.clear();
	nextnode.clear();

	for (int i = 0; i < worldislandNS::MAX_BUILDING; i++)
	{
		if (building_node[i] != nullptr)
			SAFE_DELETE(building_node[i]);
	}
}

void CWorld_Island::turn_end()
{
	if (c_turn > 0)
	{
		for (auto iter : child_node)
		{
			iter->SetLoadLinkUser(user);
			iter->turn_end();
		}

		for (auto iter : current_ship)
		{
			if (user->is_rand_ship())
			{
				CProduction_Ship* sObj = new CProduction_Ship;

				sObj->initialize(
					iter->getName(),
					iter->getID(),
					iter->getTurn(),
					iter->get_resource(MONEY),
					iter->get_resource(IRON),
					iter->get_resource(FUEL),
					iter->get_resource(RESEARCH),
					iter->getCost()
				);

				sObj->SetLoadLinkUser(user);

				for (auto aIter : iter->get_building())
					sObj->add_building(aIter);

				sObj->load(true, true);
				sObj->set_is_create(true);
				sObj->set_is_complete(true);
				sObj->set_turn(0);

				add_ship(sObj);

				user->add_decrease_resource(FUEL, sObj->getCost());
			}

			iter->SetLoadLinkUser(user);
			iter->turn_end();
		}

		for (int i = 0; i < worldislandNS::MAX_BUILDING; i++)
		{
			if (building_node[i] != nullptr)
			{
				building_node[i]->SetLoadLinkUser(user);
				building_node[i]->turn_end();

				if (building_node[i]->get_is_destroy() == true)
				{
					user->print_world_log("Destroy Building : " + building_node[i]->getName());
					SAFE_DELETE(building_node[i]);
				}
			}
		}
	}
	c_turn++;
}

void CWorld_Island::initialize(Graphics* g, Input* i, std::string _name, int _id, int _x, int _y, int _width, int _height, int _tilex, int _tiley)
{
	m_pGraphics = g;
	m_pInput = i;

	name = _name;
	id = _id;
	x = _x;
	y = _y;
	width = _width;
	height = _height;

	c_turn = 1;	//삭제할거

	rt = RectMake(_x - _width / 2, _y - _height / 2, width, height);
	tile_rt = RectMake(
		_tilex - (worldislandNS::TILE_WIDTH - worldislandNS::MARGIN) / 2, _tiley - (worldislandNS::TILE_HEIGHT - worldislandNS::MARGIN) / 2,
		worldislandNS::TILE_WIDTH - worldislandNS::MARGIN, worldislandNS::TILE_HEIGHT - worldislandNS::MARGIN
	);

	add_Child();
}

void CWorld_Island::update(float frameTime)
{
	for (auto iter : show_ship)
	{
		if (iter != nullptr)
			iter->update(frameTime);
	}
}

void CWorld_Island::render()
{
	m_pGraphics->spriteBegin();

	m_pGraphics->spriteEnd();

	for (auto iter : show_ship)
		iter->render();
}

void CWorld_Island::release()
{
	for (auto iter : current_ship)
	{
		iter->release();
		SAFE_DELETE(iter);
	}
	current_ship.clear();

	for (auto iter : show_ship)
	{
		iter->release();
		SAFE_DELETE(iter);
	}
	show_ship.clear();

	for (auto iter : child_node)
	{
		iter->release();
		SAFE_DELETE(iter);
	}

	child_node.clear();
	delete_node.clear();
	nextnode.clear();

	for (int i = 0; i < worldislandNS::MAX_BUILDING; i++)
	{
		if (building_node[i] != nullptr)
		{
			building_node[i]->release();
			SAFE_DELETE(building_node[i]);
		}
	}
}

//**********	add building in island		**********//
void CWorld_Island::add_building(int _index, CBuilding * _building)
{
	building_node[_index] = _building;
}

//**********	add ship in island		**********//
void CWorld_Island::add_ship(CProduction_Ship * _ship)
{
	current_ship.emplace_back(_ship);

	if (show_ship.size() > 15)
		return;

	while (show_ship.size() < ((current_ship.size() < 5 && current_ship.size() > 0) ? 1 : (current_ship.size() / 5)))	//5개당 배 이미지 1
	{
		while (true) {
			int rand_x = RANDOM_MAKER->GetInt(tile_rt.left, tile_rt.right);
			int rand_y = RANDOM_MAKER->GetInt(tile_rt.top, tile_rt.bottom);

			POINT rand_pt = { rand_x, rand_y };	//-r ~ r

			if (MyUtil::getIsometricIn(tile_rt, rand_pt) && !MyUtil::getIsometricIn(rt, rand_pt))	//tile_rt = tile size / rt = island size
			{
				bool flag = false;

				for (auto iter : show_ship)	//ship position check
				{
					if (MyUtil::getIsometricIn(iter->get_rt(), rand_pt))
					{
						flag = true;
						break;
					}
				}

				if (flag == true)
					continue;

				CWorld_Ship* obj = new CWorld_Ship;

				obj->initialize(m_pGraphics, m_pInput, "SN_BC_Stalingrad_sd", rand_pt.x, rand_pt.y, { (int)getX(), (int)getY() });
				show_ship.emplace_back(obj);

				break;
			}
		}
	}
}

void CWorld_Island::remove_ship_img()
{
	while (show_ship.size() > ((current_ship.size() < 5 && current_ship.size() > 0) ? 1 : (current_ship.size() / 5)))	//5개당 배 이미지 1
	{
		SAFE_DELETE(show_ship[0]);

		show_ship.erase(show_ship.begin());
	}
}

//**********	initialize rect		**********//
RECT CWorld_Island::getCancelRect()
{
	RECT re_rt = rt;

	re_rt.left -= rt.right - rt.left;
	re_rt.right += rt.right - rt.left;
	re_rt.top -= rt.bottom - rt.top;
	re_rt.bottom += rt.bottom - rt.top;

	return re_rt;
}

void CWorld_Island::w_move_ud(float _speed)
{
	rt.top += _speed;
	rt.bottom += _speed;

	tile_rt.top += _speed;
	tile_rt.bottom += _speed;

	y += _speed;

	for (auto iter : show_ship)
		iter->worldMoveud(_speed);
}

void CWorld_Island::w_move_rl(float _speed)
{
	rt.left += _speed;
	rt.right += _speed;

	tile_rt.left += _speed;
	tile_rt.right += _speed;

	x += _speed;

	for (auto iter : show_ship)
		iter->worldMoverl(_speed);
}
