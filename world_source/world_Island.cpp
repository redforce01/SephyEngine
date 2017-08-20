#include "stdafx.h"
#include "world_Island.h"
#include "world_User.h"

void CWorld_Island::add_Child()
{
	//load data 가져오기
	//존재하지 않으면 초기화

	//add child island

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
			iter->SetLoadLinkUser(user);
			iter->turn_end();
		}
		//int count = 0;

		//for (auto iter = current_ship.begin(); iter != current_ship.end(); )
		//{
		//	(*iter)->turn_end();
		//	if ((*iter)->getMove() != (*iter)->getIsland())
		//	{
		//		user->get_data()->get_Island()[(*iter)->getMove()]->add_ship((*iter));	//Island data
		//		(*iter)->setIsland((*iter)->getMove());

		//		current_ship.erase(iter);

		//		remove_ship_img();	//Delete Image Ship
		//	}
		//	else
		//		iter++;
		//}


		//for (auto iter : current_ship)
		//{
		//	iter->turn_end();
		//	
		//	if (iter->getMove() != iter->getIsland())	//다음 섬이 현재 섬이 아닌 경우 이동 실행 (이동할 섬이 있다면)
		//	{
		//		user->get_data()->get_Island()[iter->getMove()]->add_ship(iter);	//Island data
		//		iter->setIsland(iter->getMove());

		//		//for (auto iIter : user->get_data()->get_Island())
		//		//{
		//		//	if (iter->getMove() == iIter->getID())
		//		//	{
		//		//		iter->setIsland(iter->getMove());
		//		//		iIter->add_ship(iter);
		//		//		break;
		//		//	}
		//		//}
		//		
		//		current_ship.erase(current_ship.begin() + count);
		//		iter--;

		//		continue;
		//		//delete_node.emplace_back(count);
		//	}

		//	count++;
		//}

		//for (int i = delete_node.size() - 1; i >= 0; i--)
		//	current_ship.erase(current_ship.begin() + i);
		//delete_node.clear();

		//for (auto iter : building_node)
		//	iter->turn_end();
		for (int i = 0; i < worldislandNS::MAX_BUILDING; i++)
		{
			if (building_node[i] != nullptr)
			{
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

void CWorld_Island::initialize(Graphics* g, Input* i, std::string _name, UINT _id, int _x, int _y, UINT _width, UINT _height, UINT _tilex, UINT _tiley)
{
	m_pGraphics = g;
	m_pInput = i;

	name = _name;
	id = _id;
	x = _x;
	y = _y;
	width = _width;
	height = _height;
	//tile_x = _tilex;
	//tile_y = _tiley;

	//c_turn = 0;
	c_turn = 1;	//삭제할거

	rt = RectMake(_x - _width / 2, _y - _height / 2, width, height);
	tile_rt = RectMake(
		_tilex - (worldislandNS::TILE_WIDTH - worldislandNS::MARGIN) / 2, _tiley - (worldislandNS::TILE_HEIGHT - worldislandNS::MARGIN) / 2,
		worldislandNS::TILE_WIDTH - worldislandNS::MARGIN, worldislandNS::TILE_HEIGHT - worldislandNS::MARGIN
	);

	add_Child();
	//u_island = false;

	//printf("%s\t%d\t%d\t%d\t%d\t%d\t \n", name, id, x, y, width, height);
}

void CWorld_Island::update(float frameTime)
{
	for (auto iter : show_ship)
		iter->update(frameTime);
}

void CWorld_Island::render()
{
	m_pGraphics->spriteBegin();

	m_pGraphics->spriteEnd();

	for (auto iter : show_ship)
		iter->render();

	//m_pGraphics->drawRect(rt, 1.0f, graphicsNS::YELLOW);
	//m_pGraphics->drawRect(RectMake(x - 1, y - 1, 2, 2), 8.0f, graphicsNS::RED);
	//m_pGraphics->drawRect(tile_rt, 1.0f, graphicsNS::BLUE);
	//m_pGraphics->drawLine(tile_x, tile_y, tile_x + 1, tile_y + 1, 10.0f, graphicsNS::BLUE);
}

void CWorld_Island::add_building(UINT _index, CBuilding * _building)
{
	//if (building_node[_index] != nullptr)
	//	SAFE_DELETE(building_node[_index]); 
	
	building_node[_index] = _building;
}

void CWorld_Island::add_ship(CProduction_Ship * _ship)
{
	//for (auto iter : show_ship)
	//	SAFE_DELETE(iter);
	//show_ship.clear();

	//after turn end, ship scheck, little than current size then delete

	current_ship.emplace_back(_ship);

	//for (int i = 0; i < current_ship.size(); i += 5)

	while (show_ship.size() < ((current_ship.size() < 5 && current_ship.size() > 0) ? 1 : (current_ship.size() / 5)))	//5개당 배 이미지 1
	{
		while (true) {
			POINT rand_pt = {
				(rand() % tile_rt.right) + tile_rt.left
				, (rand() % tile_rt.bottom) + tile_rt.top
			};	//-r ~ r

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

				//obj->initialize(m_pGraphics, m_pInput, getName(), rand_pt.x, rand_pt.y, { getX(), getY() });
				obj->initialize(m_pGraphics, m_pInput, "SN_BC_Stalingrad_sd", rand_pt.x, rand_pt.y, { (int)getX(), (int)getY() });
				show_ship.emplace_back(obj);

				break;
			}
		}
	}

	//if (current_ship.size() % 5 == 1)
	//{
	//	while (true) {
	//		POINT rand_pt = { 
	//			(rand() % tile_rt.right) + tile_rt.left
	//			, (rand() % tile_rt.bottom) + tile_rt.top
	//		};	//-r ~ r

	//		if (MyUtil::getIsometricIn(tile_rt, rand_pt) && !MyUtil::getIsometricIn(rt, rand_pt))	//tile_rt = tile size / rt = island size
	//		{
	//			bool flag = false;

	//			for (auto iter : show_ship)	//ship position check
	//			{
	//				if (MyUtil::getIsometricIn(iter->get_rt(), rand_pt))
	//				{
	//					flag = true;
	//					break;
	//				}
	//			}

	//			if (flag == true)
	//				continue;

	//			CWorld_Ship* obj = new CWorld_Ship;

	//			//obj->initialize(m_pGraphics, m_pInput, getName(), rand_pt.x, rand_pt.y, { getX(), getY() });
	//			obj->initialize(m_pGraphics, m_pInput, "SN_BC_Stalingrad_sd", rand_pt.x, rand_pt.y, { (int)getX(), (int)getY() });
	//			show_ship.emplace_back(obj);

	//			break;
	//		}
	//	}
	//}
}

void CWorld_Island::remove_ship_img()
{
	while (show_ship.size() > ((current_ship.size() < 5 && current_ship.size() > 0) ? 1 : (current_ship.size() / 5)))	//5개당 배 이미지 1
	{
		SAFE_DELETE(show_ship[0]);

		show_ship.erase(show_ship.begin());
	}
	//if (current_ship.size() % 5 == 1)
	//	show_ship.pop_back();
}

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
	//tile_y += _speed;

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
	//tile_x += _speed;

	for (auto iter : show_ship)
		iter->worldMoverl(_speed);
}

//CBuilding * CWorld_Island::get_Building(int _index)
//{
//	int index = 0;
//
//	for (auto iter : building_node)
//	{
//		if (index++ == _index)
//			return iter;
//	}
//}
