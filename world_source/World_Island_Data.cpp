#include "stdafx.h"
#include "World_Island_Data.h"
#include "world_User.h"

void CWorld_Island_Data::island_data()
{
	//divide player & computer
	std::vector<std::string> island_data = loadObjectData("World_Island_Information");

	int temp = 0;
	int node_index = 0;

	bool flag = false;

	CWorld_Island* obj;

	std::string name = "";
	UINT id;
	UINT x;
	UINT y;
	UINT width;
	UINT height;

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
				if (flag) player->add_island(obj);	//player & computer's island
				else computer->add_island(obj);

				obj->initialize(m_pGraphics, m_pInput, name, id, x, y, width, height);
				obj->set_rt(x, y, width, height);
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
		else
			nodeList.emplace_back(std::stoi(iter));

		temp++;
	}
}

void CWorld_Island_Data::building_data()
{
	std::vector<std::string> ship_data = loadObjectData("World_Building_Information");

	int temp = 0;
	int node_index = 0;

	CBuilding* obj;

	std::string name = "";
	UINT id;
	UINT turn;
	UINT n_building;
	UINT n_money;
	UINT n_iron;
	UINT p_money;
	UINT p_iron;
	UINT p_fuel;
	UINT p_research;

	std::vector<int> nodeList;

	for (auto iter : ship_data)
	{
		if (iter.compare("") == false)
			continue;

		if (iter.compare("+") == false)
		{
			obj = new CBuilding;
			temp = 0;
			building_node.emplace_back(obj);

			if (node_index != 0)
			{
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
}

void CWorld_Island_Data::ship_data()
{
	std::vector<std::string> ship_data = loadObjectData("World_Ship_Information");

	int temp = 0;
	int node_index = 0;

	CProduction_Ship* obj;

	std::string name = "";
	UINT id;
	UINT money;
	UINT iron;
	UINT fuel;
	UINT research;
	UINT cost;

	std::vector<int> nodeList;

	for (auto iter : ship_data)
	{
		if (iter.compare("") == false)
			continue;

		if (iter.compare("+") == false)
		{
			obj = new CProduction_Ship;
			temp = 0;
			ship_node.emplace_back(obj);

			if (node_index != 0)
			{
				obj->initialize(name, id, money, iron, fuel, research, cost);

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
			money = std::stoi(iter);
		else if (temp == 3)
			iron = std::stoi(iter);
		else if (temp == 4)
			fuel = std::stoi(iter);
		else if (temp == 5)
			research = std::stoi(iter);
		else if (temp == 6)
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
	
}

bool CWorld_Island_Data::initialize(Graphics* g, Input* i)
{
	m_pGraphics = g;
	m_pInput = i;

	//load 데이터가 없으면 이거 island_data() 실행
	island_data();	//load island data
	building_data();	//load building data
	ship_data();	//load ship data
	
	//로드 데이터 있으면 실행
	//바로 데이터 내용 추가
	//player->initialize(g, i, money, iron, fuel, research);
	//player & computer initialize 하기

	return true;
}

void CWorld_Island_Data::update(float frameTime)
{
}

std::string CWorld_Island_Data::ship_IdtoName(UINT _id)
{
	for (auto iter : ship_node)
	{
		if (iter->getID() == _id)
			return iter->getName();
	}
}

UINT CWorld_Island_Data::ship_NametoId(std::string _name)
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

//CWorld_Island* CWorld_Island_Data::get_Island(int _index)
//{
//	int index = 0;
//
//	for (auto iter : island_node)
//	{
//		if (index++ == _index)
//			return iter;
//	}
//}

CBuilding * CWorld_Island_Data::get_Building(int _index)
{
	int index = 0;

	for (auto iter : building_node)
	{
		if (index++ == _index)
			return iter;
	}
}

CProduction_Ship * CWorld_Island_Data::get_Ship(int _index)
{
	int index = 0;

	for (auto iter : ship_node)
	{
		if (index++ == _index)
			return iter;
	}
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
