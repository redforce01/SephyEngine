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
	const std::string BATTLE_MAP_KEY = "MapData";
	const std::string BATTLE_PLAYER_KEY = "PlayerData";
	const std::string BATTLE_AI_KEY = "AIData";
	const std::string DATA_FORMAT_BEGIN_KEY = "BEGIN";
	const std::string DATA_FORMAT_END_KEY = "END";
}

class CBattle_DataParser
{
private:
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

private:
	// Recognize Battle Data
	void battleDataRecognize(std::vector<std::string> vArray);
	void battleMapDataRecognize(std::string mapName);
	void battlePlayerDataRecognize(std::vector<std::string> vArray);
	void battleAIDataRecognize(std::vector<std::string> vArray);

public:
	//============================================
	// Getter Functions
	//============================================
	std::string getMapName() const
	{
		return m_strMapName;
	}
};

#endif // !_BATTLE_DATAPARSER_H
