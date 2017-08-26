#include "stdafx.h"
#include "world_User.h"
#include "world_MainSystem.h"


CWorld_User::CWorld_User()
{
	is_update = true;

	rt_rand = { 0, };

	buf_type = -1;
	buf_turn = 0;

	for (int i = 0; i < world_userNS::MAX_BUILD; i++)
		current_building[i] = 0;
}


CWorld_User::~CWorld_User()
{
	SAFE_DELETE(event_log);

	for (auto iter : island_node)
		SAFE_DELETE(iter);

	for (auto iter : current_ship)
		SAFE_DELETE(iter);

	current_ship.clear();
	island_node.clear();
}

void CWorld_User::initialize(Graphics* g, Input* i, int _money, int _iron, int _fuel, int _research)
{
	m_pGraphics = g;
	m_pInput = i;

	money = _money;
	iron = _iron;
	fuel = _fuel;
	research = _research;

	rt_rand = RectMake(0, 0, world_userNS::RAND_RANGE * world_userNS::PROBABILITY, world_userNS::RAND_RANGE * world_userNS::PROBABILITY);
}

void CWorld_User::release()
{
	if (event_log != nullptr)
	{
		event_log->release();
		SAFE_DELETE(event_log);
	}

	for (auto iter : island_node)
	{
		if (iter != nullptr)
		{
			iter->release();
			SAFE_DELETE(iter);
		}
	}
	island_node.clear();

	for (auto iter : current_ship)
	{
		if (iter != nullptr)
		{
			iter->release();
			SAFE_DELETE(iter);
		}
	}
	current_ship.clear();
}

//**********	active world event	**********//
void CWorld_User::active_event()
{
	buf_turn--;

	if (buf_type < 0)
		return;

	std::vector<std::string> message;

	int amount = 0;

	switch (buf_type)
	{
	case 0:
		amount = (increase_resource[IRON] + decrease_resource[IRON]) * 0.1f;
		add_decrease_resource(IRON, amount);
		spend_resource(IRON, amount);

		message.emplace_back(world_userNS::EVENT_ZERO + world_userNS::EVENT_TURN + std::to_string(buf_turn));
		message.emplace_back(world_userNS::EVENT_ZERO_2);
		event_log->set_message(message);

		break;
	case 1:
		amount = (increase_resource[MONEY] + decrease_resource[MONEY]) * 0.1f;
		add_decrease_resource(MONEY, amount);
		spend_resource(MONEY, amount);

		message.emplace_back(world_userNS::EVENT_ONE + world_userNS::EVENT_TURN + std::to_string(buf_turn));
		message.emplace_back(world_userNS::EVENT_ONE_2);
		event_log->set_message(message);

		break;
	case 2:
		message.emplace_back(world_userNS::EVENT_TWO + world_userNS::EVENT_TURN + std::to_string(buf_turn));
		message.emplace_back(world_userNS::EVENT_TWO_1);
		event_log->set_message(message);

		break;
	case 3:
		amount = (increase_resource[MONEY] + decrease_resource[MONEY]) * 0.1f;
		add_increase_resource(MONEY, amount);
		add_resource(MONEY, amount);

		message.emplace_back(world_userNS::EVENT_THREE + world_userNS::EVENT_TURN + std::to_string(buf_turn));
		message.emplace_back(world_userNS::EVENT_THREE_1);
		event_log->set_message(message);

		break;
	case 4:
		amount = decrease_resource[FUEL] * 0.1f;
		add_decrease_resource(FUEL, -amount);
		add_resource(FUEL, amount);

		message.emplace_back(world_userNS::EVENT_FOUR + world_userNS::EVENT_TURN + std::to_string(buf_turn));
		message.emplace_back(world_userNS::EVENT_FOUR_1);
		event_log->set_message(message);

		break;
	case 5:
		message.emplace_back(world_userNS::EVENT_FIVE + world_userNS::EVENT_TURN + std::to_string(buf_turn));
		message.emplace_back(world_userNS::EVENT_FIVE_1);
		event_log->set_message(message);

		break;
	case 6:
		random_create_ship();

		break;
	default:
		break;
	}
}

//**********	world event (create ship)	**********//
void CWorld_User::random_create_ship()
{
	rand_ship_count = 0;

	for (auto iter : island_node)
		rand_ship_count += iter->get_Ship_Size();

	rand_ship_count = RANDOM_MAKER->GetInt(0, rand_ship_count - 1);
}

//**********	world event list	**********//
void CWorld_User::world_event()
{
	if (buf_turn > 0)
		return;

	if (buf_turn <= 0)
		buf_type = -1;

	int temp = RANDOM_MAKER->GetInt(0, world_userNS::RAND_RANGE);

	if (temp < world_userNS::RAND_RANGE * world_userNS::PROBABILITY)
	{
		int start = RANDOM_MAKER->GetInt(0, world_userNS::EVENT_LIST - 1);
		int count = 0;

		while (true)
		{
			std::vector<std::string> message;

			if (count >= 7)
				break;

			int amount = 0;
			start %= world_userNS::EVENT_LIST;

			switch (start)
			{
			case 0:
				if (increase_resource[IRON] >= 150)
				{
					buf_type = 0;
					buf_turn = world_userNS::DBUF_TURN;

					amount = get_resource(IRON) * 0.2f;

					spend_resource(IRON, amount);

					message.emplace_back(world_userNS::EVENT_ZERO + world_userNS::EVENT_TURN + std::to_string(buf_turn));
					message.emplace_back(world_userNS::EVENT_ZERO_1);
					event_log->set_message(message);

					count = 7;

					break;
				}
			case 1:
				if (increase_resource[MONEY] >= 150)
				{
					buf_type = 1;
					buf_turn = world_userNS::DBUF_TURN;

					amount = get_resource(MONEY) * 0.2f;

					spend_resource(MONEY, amount);

					message.emplace_back(world_userNS::EVENT_ONE + world_userNS::EVENT_TURN + std::to_string(buf_turn));
					message.emplace_back(world_userNS::EVENT_ONE_1);
					event_log->set_message(message);

					count = 7;

					break;
				}
			case 2:
				if (increase_resource[IRON] >= 150)
				{
					buf_type = 2;
					buf_turn = world_userNS::BUF_TURN;

					message.emplace_back(world_userNS::EVENT_TWO + world_userNS::EVENT_TURN + std::to_string(buf_turn));
					message.emplace_back(world_userNS::EVENT_TWO_1);
					event_log->set_message(message);

					count = 7;

					break;
				}
			case 3:
				if (get_resource(MONEY) >= 700)
				{
					buf_type = 3;
					buf_turn = world_userNS::BUF_TURN;

					message.emplace_back(world_userNS::EVENT_THREE + world_userNS::EVENT_TURN + std::to_string(buf_turn));
					message.emplace_back(world_userNS::EVENT_THREE_1);
					event_log->set_message(message);

					count = 7;

					break;
				}
			case 4:
				if (get_resource(FUEL) >= 700)
				{
					buf_type = 4;
					buf_turn = world_userNS::BUF_TURN;

					message.emplace_back(world_userNS::EVENT_FOUR + world_userNS::EVENT_TURN + std::to_string(buf_turn));
					message.emplace_back(world_userNS::EVENT_FOUR_1);
					event_log->set_message(message);

					count = 7;

					break;
				}
			case 5:
				if (get_resource(IRON) >= 700)
				{
					buf_type = 5;
					buf_turn = world_userNS::BUF_TURN;

					message.emplace_back(world_userNS::EVENT_FIVE + world_userNS::EVENT_TURN + std::to_string(buf_turn));
					message.emplace_back(world_userNS::EVENT_FIVE_1);
					event_log->set_message(message);

					count = 7;

					break;
				}
			case 6:
				if (get_resource(IRON) >= 500 && get_resource(MONEY) >= 500 && get_resource(FUEL) >= 700)
				{
					buf_type = 6;

					count = 7;

					break;
				}
			default:
				start = 7;
				break;
			}

			count++;
		}
	}
}

//**********	set ship <-> set island		**********//
void CWorld_User::add_ship(CProduction_Ship * _ship, CWorld_Island * _island)
{
	_ship->setIsland(_island->getID());
	_island->add_ship(_ship);
//	ship_node.emplace_back(_ship);
}

//**********	add user's resource		**********//
void CWorld_User::add_resource(E_RESOURCE _type, int _resource)
{
	switch (_type)
	{
	case MONEY:
		money += _resource;
		break;
	case IRON:
		iron += _resource;
		break;
	case FUEL:
		fuel += _resource;
		break;
	case RESEARCH:
		research += _resource;
		break;
	}
}

//**********	remove island	**********//
void CWorld_User::remove_island(int _index)
{
	for (auto iter = island_node.begin(); iter != island_node.end(); iter++)
	{
		if ((*iter)->getID() == _index)
		{
			island_node.erase(iter);
			break;
		}
	}
}

//**********	class CWorld_Log_UI -> log	**********//
void CWorld_User::print_world_log(const std::string message)
{
	scene->print_world_log(message);
}
std::deque<std::string> CWorld_User::get_log_message()
{
	return scene->get_log_message();
}

//**********	world event (create ship)	**********//
void CWorld_User::turn_event()
{
	if ((buf_turn == world_userNS::DBUF_TURN && (buf_type == 0 || buf_type == 1)) || 
		(buf_turn == world_userNS::BUF_TURN && (buf_type == 2 || buf_type == 3 || buf_type == 4 || buf_type == 5)))
		return;

	int temp = RANDOM_MAKER->GetInt(0, world_userNS::RAND_RANGE);

	if (temp < world_userNS::RAND_RANGE * (world_userNS::PROBABILITY / 2))
	{
		std::vector<std::string> message;

		int start = RANDOM_MAKER->GetInt(0, world_userNS::EVENT_RESOURCE_LIST - 1);

		switch (start)
		{
		case 0:
			add_resource(MONEY, world_userNS::RESOURCE_AMOUNT);
			
			message.emplace_back(world_userNS::EVENT_RESOURCE);
			message.emplace_back("Money + " + std::to_string(world_userNS::RESOURCE_AMOUNT));
			event_log->set_message(message);

			break;
		case 1:
			add_resource(IRON, world_userNS::RESOURCE_AMOUNT);

			message.emplace_back(world_userNS::EVENT_RESOURCE);
			message.emplace_back("Iron + " + std::to_string(world_userNS::RESOURCE_AMOUNT));
			event_log->set_message(message);

			break;
		case 2:
			add_resource(FUEL, world_userNS::RESOURCE_AMOUNT);

			message.emplace_back(world_userNS::EVENT_RESOURCE);
			message.emplace_back("Fuel + " + std::to_string(world_userNS::RESOURCE_AMOUNT));
			event_log->set_message(message);

			break;
		default:
			break;
		}
	}
}

int CWorld_User::get_resource(E_RESOURCE _type)
{
	switch (_type)
	{
	case MONEY:
		return money;
	case IRON:
		return iron;
	case FUEL:
		return fuel;
	case RESEARCH:
		return research;
	}
}

//**********	world event (create ship)	**********//
bool CWorld_User::is_rand_ship()
{
	if (buf_type != 6)
		return false;

	rand_ship_count--;

	if (rand_ship_count <= 0)
	{
		std::vector<std::string> message;

		buf_type = -1;

		message.emplace_back(world_userNS::EVENT_SIX);
		message.emplace_back(world_userNS::EVENT_SIX_1);
		event_log->set_message(message);

		return true;
	}
	else 
		return false;
}

//**********	is use resource		**********//
bool CWorld_User::spend_resource(E_RESOURCE _type, int _amount)
{
	switch (_type)
	{
	case MONEY:
		if (money - _amount >= 0)
		{
			money -= _amount;

			return true;
		}
		break;
	case IRON:
		if (iron - _amount >= 0)
		{
			iron -= _amount;

			return true;
		}
		break;
	case FUEL:
		if (fuel - _amount >= 0)
		{
			fuel -= _amount;

			return true;
		}
		break;
	case RESEARCH:
		if (research - _amount >= 0)
		{
			research -= _amount;

			return true;
		}
		break;
	}

	return false;
}
