#include "stdafx.h"
#include "building.h"
#include "world_User.h"
#include "world_Island.h"



void CBuilding::load(bool _building, bool _complete, bool _destroy, int _turn)
{
	is_building = _building;
	is_complete = _complete;
	is_destroy = _destroy;
	turn = _turn;
}

void CBuilding::command_center()
{
	is_building = true;
	is_complete = true;
	turn = 0;

	user->add_cur_building(id);

	user->add_increase_resource(MONEY, produce_resource[MONEY]);
	user->add_increase_resource(IRON, produce_resource[IRON]);
	user->add_increase_resource(FUEL, produce_resource[FUEL]);
	user->add_increase_resource(RESEARCH, produce_resource[RESEARCH]);
}

void CBuilding::asort_action()
{
	//int null_count = 0;

	//for (int i = 0; i < worldbuildingNS::MAX_ACTION; i++)
	//{
	//	if (action[i] != nullptr)
	//		continue;

	//	for (int j = i + 1; j < worldbuildingNS::MAX_ACTION; j++)
	//	{
	//		action[j - 1] = action[j];
	//	}

	//	null_count++;
	//}

	//for (int i = worldbuildingNS::MAX_ACTION - null_count; i < worldbuildingNS::MAX_ACTION; i++)
	//{
	//	action[i] = nullptr;
	//}

	for (int i = 0; i < worldbuildingNS::MAX_ACTION; i++)
	{
		//if (action[i] == nullptr)
		//	break;

		for (int j = i + 1; j < worldbuildingNS::MAX_ACTION; j++)
		{
			if (action[i] == nullptr)
			{
				action[i] = action[j];
				action[j] = nullptr;

				continue;
			}

			if (action[j] == nullptr)
				continue;

			if (action[i]->getTurn() > action[j]->getTurn())
			{
				CProduction_Ship* temp = action[i];
				action[i] = action[j];
				action[j] = temp;
			}
		}
	}
}

void CBuilding::complete_action()
{
	for (int i = 0; i < worldbuildingNS::MAX_ACTION; i++)
	{
		if (action[i] == nullptr)
			continue;

		if (action[i]->get_is_complete())
		{
			user->add_ship(action[i], island);
			action[i] = nullptr;
		}
	}
}

CBuilding::CBuilding()
{
	is_building = false;
	is_complete = false;
	is_destroy = false;

	for (int i = 0; i < worldbuildingNS::MAX_ACTION; i++)
		action[i] = nullptr;
}


CBuilding::~CBuilding()
{
}

void CBuilding::turn_end()
{
	if (is_destroy == true)
	{
		if (SOUNDMANAGER->isPlaySound(worldbuildingNS::SOUND_DESTROY) == false)
			SOUNDMANAGER->play(worldbuildingNS::SOUND_DESTROY, g_fSoundMasterVolume + g_fSoundEffectVolume);

		user->destroy_cur_building(id);
		user->print_world_log("Destroy Building : " + name);
		for (int i = 0; i < worldbuildingNS::MAX_ACTION; i++)
		{
			if (action[i] != nullptr)
				SAFE_DELETE(action[i]);
		}

		return;
	}

	if (start_turn == turn)
	{
		//자원 감소 및 자원 부족한거 체크
		user->print_world_log("Create Start Building : " + name);
		is_building = true;
	}

	if (turn == 1)
		user->print_world_log("Complete Building : " + name);

	if (turn <= 1)	//start turn decrease
	{
		if (is_complete == false)
			user->add_cur_building(id);

		is_complete = true;
		user->add_resource(MONEY, produce_resource[MONEY]);
		user->add_resource(IRON, produce_resource[IRON]);
		user->add_resource(FUEL, produce_resource[FUEL]);
		user->add_resource(RESEARCH, produce_resource[RESEARCH]);

		user->add_increase_resource(MONEY, produce_resource[MONEY]);
		user->add_increase_resource(IRON, produce_resource[IRON]);
		user->add_increase_resource(FUEL, produce_resource[FUEL]);
		user->add_increase_resource(RESEARCH, produce_resource[RESEARCH]);
		//사용 가능 및 자원 생산
		//배 생산
	}

	for (int i = 0; i < worldbuildingNS::MAX_ACTION; i++)
	{
		if (action[i] != nullptr)
		{
			action[i]->turn_end();

			if (action[i]->get_is_destroy() == true)
				SAFE_DELETE(action[i]);
		}
	}

	complete_action();
	asort_action();

	turn--;
}

void CBuilding::initialize(std::string _name, UINT _id, int _turn, UINT _nBuilding, UINT _nMoney, UINT _nIron, UINT _pMoney, UINT _pIron, UINT _pFuel, UINT _pResearch)
{
	name = _name;
	id = _id;
	start_turn = turn = _turn;
	n_building = _nBuilding;
	
	need_resource[MONEY] = _nMoney;
	need_resource[IRON] = _nIron;
	need_resource[FUEL] = 0;
	need_resource[RESEARCH] = 0;
	
	produce_resource[MONEY] = _pMoney;
	produce_resource[IRON] = _pIron;
	produce_resource[FUEL] = _pFuel;
	produce_resource[RESEARCH] = _pResearch;

	//std::cout << "=================================" << std::endl;
	//std::cout << "Name : " << name << std::endl;
	//std::cout << "ID : " << id << std::endl;
	//std::cout << "Turn : " << turn << std::endl;
	//std::cout << "=================================" << std::endl;
	
	//printf("%s\t\n%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t \n", name, id, turn, n_building, need_resource[MONEY], need_resource[IRON], 
	//	produce_resource[MONEY], produce_resource[IRON], produce_resource[FUEL], produce_resource[RESEARCH]);
}

