#include "stdafx.h"
#include "World_Island_Data.h"


CWorld_Island_Data::CWorld_Island_Data()
{
}


CWorld_Island_Data::~CWorld_Island_Data()
{
}

bool CWorld_Island_Data::initialize()
{
	island_data = loadObjectData();

	int temp = 0;
	int node_index = 0;
	
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
			island_node.emplace_back(obj);

			if (node_index != 0)
			{
				obj->initialize(name, id, x, y, width, height);
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
			x = std::stoi(iter);
		else if (temp == 3)
			y = std::stoi(iter);
		else if (temp == 4)
			width = std::stoi(iter);
		else if (temp == 5)
			height = std::stoi(iter);
		else
			nodeList.emplace_back(std::stoi(iter));
		
		temp++;
	}

	//for (auto pr : island_data)
	//{
	//	if (!pr.compare(""))
	//		continue;
	//	std::string temp = "";
	//	std::string name = "";
	//	UINT id;
	//	UINT x;
	//	UINT y;
	//	UINT width;
	//	UINT height;

	//	CWorld_Island* obj = new CWorld_Island;

	//	int index = 0;
	//	//split data
	//	while (pr.data()[index] != '\t')
	//		name += pr.data()[index++];
	//	
	//	index++;

	//	while (pr.data()[index] != '\t')
	//		temp += pr.data()[index++];
	//	//std::stoi(temp); -> º¯°æ
	//	id = atoi(temp.c_str());
	//	index++;
	//	temp = "";
	//	while (pr.data()[index] != '\t')
	//		temp += pr.data()[index++];

	//	x = atoi(temp.c_str());
	//	index++;
	//	temp = "";
	//	while (pr.data()[index] != '\t')
	//		temp += pr.data()[index++];

	//	y = atoi(temp.c_str());
	//	index++;
	//	temp = "";
	//	while (pr.data()[index] != '\t')
	//		temp += pr.data()[index++];

	//	width = atoi(temp.c_str());
	//	index++;
	//	temp = "";
	//	while (pr.data()[index] != '\t')
	//		temp += pr.data()[index++];

	//	height = atoi(temp.c_str());
	//	index++;
	//	temp = "";

	//	obj->initialize(name, id, x, y, width, height);

	//	while (index < pr.size())	//connected node
	//	{
	//		while (pr.data()[index] != '\t' && pr.data()[index] != '\n')
	//			temp += pr.data()[index++];

	//		obj->add_node(atoi(temp.c_str()));
	//		index++;
	//		temp = "";
	//	}

	//	island_node[node_index++] = obj;
	//}

	return true;
}

void CWorld_Island_Data::update(float frameTime)
{
}

std::vector<std::string> CWorld_Island_Data::loadObjectData()
{
	std::vector<std::string> vData = TXTDATA_PARSER->loadDataToArray("Island Information");


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
