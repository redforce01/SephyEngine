#ifndef _BATTLE_DATAPARSER_H
#define _BATTLE_DATAPARSER_H

class CBattle_DataParser;

#include <vector>
#include <string>
#include <fstream>
#include <sstream>

namespace battleDataParserNS
{
	const std::string BATTLE_DATA_FOLDER = "51_Battle";
	const std::string BATTLE_DATA_FILENAME = "Battle_Data";
	const std::string BATTLE_DATA_WORLD_INDEX_KEY = "WorldIndex";
	const std::string BATTLE_MAP_KEY = "MapData";
	const std::string BATTLE_PLAYER_KEY = "PlayerData";
	const std::string BATTLE_AI_KEY = "AIData";
	const std::string DATA_FORMAT_BEGIN_KEY = "BEGIN";
	const std::string DATA_FORMAT_END_KEY = "END";

	const std::string SAVE_DATA_PATH = "Resources\\50_BattleGameData\\Battle_Data.txt";
}

class CBattle_DataParser
{
private:
	std::string m_strWorldIndex;
	std::string m_strMapName;
	std::vector<std::string> m_vPlayerShipData;
	std::vector<std::string> m_vAIShipData;

public:
	CBattle_DataParser();
	~CBattle_DataParser();

	//============================================
	// Member Functions
	//============================================

	// Load Battle Data
	void loadBattleData();

	// Save Battle Data
	void saveBattleData(std::string worldIndex, std::string battleMap, std::vector<std::string> vPlayerShip, std::vector<std::string> vEnemyShip);
private:
	// Recognize Battle Data
	void battleDataRecognize(std::vector<std::string> vArray);
	void battleWorldIndexRecognize(std::string worldIndex);
	void battleMapDataRecognize(std::string mapName);
	void battlePlayerDataRecognize(std::vector<std::string> vArray);
	void battleAIDataRecognize(std::vector<std::string> vArray);
public:
	//============================================
	// Getter Functions
	//============================================
	std::string getBattleWorldIndex() const
	{
		return m_strWorldIndex;
	}
	std::string getBattleMapName() const
	{
		return m_strMapName;
	}
	std::vector<std::string> getBattlePlayerShipData() const
	{
		return m_vPlayerShipData;
	}
	std::vector<std::string> getBattleAIShipData() const
	{
		return m_vAIShipData;
	}
};

#endif // !_BATTLE_DATAPARSER_H
