#include "stdafx.h"
#include "World_Island_Data.h"
#include "world_User.h"
#include "world_Scene.h"


//**********	load island data	**********//
void CWorld_Island_Data::island_data()
{
	//divide player & computer
	std::vector<std::string> island_data = loadObjectData(world_island_dataNS::ISLAND_NAME);

	int temp = 0;
	int node_index = 0;

	bool flag = false;

	CWorld_Island* obj;

	std::string name = "";
	int id;
	int x;
	int y;
	int width;
	int height;
	int tile_x;
	int tile_y;

	std::vector<int> nodeList;

	for (auto iter : island_data)
	{
		if (iter.compare("") == false)
			continue;

		if (iter.compare("+") == false)
		{
			obj = new CWorld_Island;
			temp = 0;

			if (node_index != 0)
			{
				//player->add_island(obj);	//Test
				if (flag)
				{
					player->add_island(obj);	//player & computer's island
					obj->SetLoadLinkUser(player);
				}
				else
				{
					computer->add_island(obj);
					obj->SetLoadLinkUser(computer);
				}
				island_node.emplace_back(obj);

				obj->initialize(m_pGraphics, m_pInput, name, id, x, y, width, height, tile_x, tile_y);
				for (auto nIter : nodeList)
					obj->add_node(nIter);
				nodeList.clear();
			}

			node_index++;
			continue;
		}

		if (temp == 0)
			name = iter;
		else if (temp == 1)
			id = std::stoi(iter);
		else if (temp == 2)
			flag = std::stoi(iter);
		else if (temp == 3)
			x = std::stoi(iter);
		else if (temp == 4)
			y = std::stoi(iter);
		else if (temp == 5)
			width = std::stoi(iter);
		else if (temp == 6)
			height = std::stoi(iter);
		else if (temp == 7)
			tile_x = std::stoi(iter);
		else if (temp == 8)
			tile_y = std::stoi(iter);
		else
			nodeList.emplace_back(std::stoi(iter));

		temp++;
	}
}

//**********	load building data	**********//
void CWorld_Island_Data::building_data()
{
	std::vector<std::string> ship_data = loadObjectData(world_island_dataNS::BUILDING_NAME);

	int temp = 0;
	int node_index = 0;

	CBuilding* obj;

	std::string name = "";
	int id;
	int turn;
	int n_building;
	int n_money;
	int n_iron;
	int p_money;
	int p_iron;
	int p_fuel;
	int p_research;

	std::vector<int> nodeList;

	for (auto iter : ship_data)
	{
		if (iter.compare("") == false)
			continue;

		if (iter.compare("+") == false)
		{
			obj = new CBuilding;
			temp = 0;

			if (node_index != 0)
			{
				building_node.emplace_back(obj);
				obj->initialize(name, id, turn, n_building, n_money, n_iron, p_money, p_iron, p_fuel, p_research);
				
				for (auto nIter : nodeList)
					obj->add_Ship(nIter);

				nodeList.clear();
			}

			node_index++;
			continue;
		}

		if (temp == 0)
			name = iter;
		else if (temp == 1)
			id = std::stoi(iter);
		else if (temp == 2)
			turn = std::stoi(iter);
		else if (temp == 3)
			n_building = std::stoi(iter);
		else if (temp == 4)
			n_money = std::stoi(iter);
		else if (temp == 5)
			n_iron = std::stoi(iter);
		else if (temp == 6)
			p_money = std::stoi(iter);
		else if (temp == 7)
			p_iron = std::stoi(iter);
		else if (temp == 8)
			p_fuel = std::stoi(iter);
		else if (temp == 9)
			p_research = std::stoi(iter);
		else
			nodeList.emplace_back(std::stoi(iter));

		temp++;
	}

	for (int i = 0; i < building_node.size(); i++)
		std::cout << i << " : " << building_node[i]->getName() << std::endl;
}

//**********	load ship data		**********//
void CWorld_Island_Data::ship_data()
{
	std::vector<std::string> ship_data = loadObjectData(world_island_dataNS::SHIP_NAME);

	int temp = 0;
	int node_index = 0;

	CProduction_Ship* obj;

	std::string name = "";
	int id;
	int turn;
	int money;
	int iron;
	int fuel;
	int research;
	int cost;

	std::vector<int> nodeList;

	for (auto iter : ship_data)
	{
		if (iter.compare("") == false)
			continue;

		if (iter.compare("+") == false)
		{
			obj = new CProduction_Ship;
			temp = 0;

			if (node_index != 0)
			{
				ship_node.emplace_back(obj);
				obj->initialize(name, id, turn, money, iron, fuel, research, cost);

				for (auto nIter : nodeList)
					obj->add_building(nIter);
				nodeList.clear();
			}

			node_index++;
			continue;
		}

		if (temp == 0)
			name = iter;
		else if (temp == 1)
			id = std::stoi(iter);
		else if (temp == 2)
			turn = std::stoi(iter);
		else if (temp == 3)
			money = std::stoi(iter);
		else if (temp == 4)
			iron = std::stoi(iter);
		else if (temp == 5)
			fuel = std::stoi(iter);
		else if (temp == 6)
			research = std::stoi(iter);
		else if (temp == 7)
			cost = std::stoi(iter);
		else
			nodeList.emplace_back(std::stoi(iter));

		temp++;
	}
}

CWorld_Island_Data::CWorld_Island_Data()
{
}

CWorld_Island_Data::~CWorld_Island_Data()
{
	for (auto iter : ship_node)
	{
		if (iter != nullptr)
			SAFE_DELETE(iter);
	}
	ship_node.clear();

	for (auto iter : building_node)
	{
		if (iter != nullptr)
			SAFE_DELETE(iter);
	}
	building_node.clear();

	for (auto iter : island_node)
	{
		if (iter != nullptr)
			SAFE_DELETE(iter);
	}
	island_node.clear();
}

bool CWorld_Island_Data::initialize(Graphics* g, Input* i)
{
	m_pGraphics = g;
	m_pInput = i;
	
	island_data();	//load island data
	building_data();	//load building data
	ship_data();	//load ship data

	return true;
}

void CWorld_Island_Data::update(float frameTime)
{
}

void CWorld_Island_Data::release()
{
	for (auto iter : ship_node)
	{
		if (iter != nullptr)
		{
			iter->release();
			SAFE_DELETE(iter);
		}
	}
	ship_node.clear();

	for (auto iter : building_node)
	{
		if (iter != nullptr)
		{
			iter->release();
			SAFE_DELETE(iter);
		}
	}
	building_node.clear();

	island_node.clear();
}

//**********	change ship id -> name		**********//
std::string CWorld_Island_Data::ship_IdtoName(int _id)
{
	for (auto iter : ship_node)
	{
		if (iter->getID() == _id)
			return iter->getName();
	}
}

//**********	change ship name -> id		**********//
int CWorld_Island_Data::ship_NametoId(std::string _name)
{
	for (auto iter : ship_node)
	{
		if (iter->getName().compare(_name) == false)
			return iter->getID();
	}
}

std::vector<std::string> CWorld_Island_Data::loadObjectData(std::string name)
{
	std::vector<std::string> vData = TXTDATA_PARSER->loadDataToArray(name);


	std::vector<std::string> vRecogData;
	for (auto iter : vData)
	{
		ReplaceStringInPlace(iter, "\t", " ");

		std::istringstream iss(iter);
		std::string token;
		while (std::getline(iss, token, ' '))
		{
			vRecogData.emplace_back(token);
		}
	}

	return vRecogData;
}

void CWorld_Island_Data::ReplaceStringInPlace(std::string & subject, const std::string & search, const std::string & replace)
{
	size_t pos = 0;
	while ((pos = subject.find(search, pos)) != std::string::npos)
	{
		subject.replace(pos, search.length(), replace);
		pos += replace.length();
	}
}
