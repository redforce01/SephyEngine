#pragma once

#include <sstream>
#include "world_Island.h"

namespace world_island_dataNS
{
	const std::string ISLAND_NAME = "World_Island_Information";
	const std::string BUILDING_NAME = "World_Building_Information";
	const std::string SHIP_NAME = "World_Ship_Information";
}

class CWorld_User;
class CWorld_Island_Data
{
private:
	Graphics* m_pGraphics;
	Input* m_pInput;

	CWorld_User* player;
	CWorld_User* computer;

	std::vector<CWorld_Island*> island_node;	//0~17번의 섬
	std::vector<CBuilding*> building_node;		//1~11번의 건물
	std::vector<CProduction_Ship*> ship_node;	//1~24번의 배

	void island_data();
	void building_data();
	void ship_data();

public:
	CWorld_Island_Data();
	~CWorld_Island_Data();

	void SetLoadLinkPlayer(CWorld_User* _player) { player = _player; }
	void SetLoadLinkComputer(CWorld_User* _computer) { computer = _computer; }

	virtual bool initialize(Graphics* g, Input* i);
	virtual void update(float frameTime);
	void release();

	std::string ship_IdtoName(int _id);	//id -> name
	std::vector<std::string> loadObjectData(std::string name);
	std::vector<CWorld_Island*> get_Island() { return island_node; }
	std::vector<CBuilding*> get_Building() { return building_node; }
	std::vector<CProduction_Ship*> get_Ship() { return ship_node; }

	int ship_NametoId(std::string _name);	//name -> id
	int get_Building_Size() { return building_node.size(); }
	int get_Ship_Size() { return ship_node.size(); }

	void ReplaceStringInPlace(std::string& subject, const std::string& search, const std::string& replace);
};
