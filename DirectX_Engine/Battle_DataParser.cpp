#include "stdafx.h"
#include "Battle_DataParser.h"


CBattle_DataParser::CBattle_DataParser()
{
}


CBattle_DataParser::~CBattle_DataParser()
{
}

void CBattle_DataParser::loadBattleData()
{
	auto vData = TXTDATA_PARSER->loadDataToArray(battleDataParserNS::BATTLE_DATA_FILENAME);
	battleDataRecognize(vData);
}

void CBattle_DataParser::battleDataRecognize(std::vector<std::string> vArray)
{
	if (vArray.size() <= 0)
		return;

	int recogCount = 0;
	std::string befMapName;
	std::vector<std::string> vbefPlayerData;
	std::vector<std::string> vbefAIData;
	
	bool bRecogMap = false;
	bool bRecogPlayerShip = false;
	bool bRecogAIShip = false;
	for (auto iter : vArray)
	{
		if (iter.compare(battleDataParserNS::DATA_FORMAT_BEGIN_KEY + " " + battleDataParserNS::BATTLE_MAP_KEY) == false)
		{
			bRecogMap = true;
			continue;
		}
		else if(iter.compare(battleDataParserNS::BATTLE_MAP_KEY + " " + battleDataParserNS::DATA_FORMAT_END_KEY) == false)
		{
			bRecogMap = false;
			continue;
		}

		if (bRecogMap)
		{
			befMapName = iter;
			continue;
		}

		if (iter.compare(battleDataParserNS::DATA_FORMAT_BEGIN_KEY + " " + battleDataParserNS::BATTLE_PLAYER_KEY) == false)
		{
			bRecogPlayerShip = true;
			continue;
		}
		else if (iter.compare(battleDataParserNS::BATTLE_PLAYER_KEY + " " + battleDataParserNS::DATA_FORMAT_END_KEY) == false)
		{
			bRecogPlayerShip = false;
			continue;
		}

		if (bRecogPlayerShip)
		{
			vbefPlayerData.emplace_back(iter);
			continue;
		}

		if (iter.compare(battleDataParserNS::DATA_FORMAT_BEGIN_KEY + " " + battleDataParserNS::BATTLE_AI_KEY) == false)
		{
			bRecogAIShip = true;
			continue;
		}
		else if (iter.compare(battleDataParserNS::BATTLE_AI_KEY + " " + battleDataParserNS::DATA_FORMAT_END_KEY) == false)
		{
			bRecogAIShip = false;
			continue;
		}

		if (bRecogAIShip)
		{
			vbefAIData.emplace_back(iter);
			continue;
		}
	}

	battleMapDataRecognize(befMapName);
	battlePlayerDataRecognize(vbefPlayerData);
	battleAIDataRecognize(vbefAIData);
}

void CBattle_DataParser::battleMapDataRecognize(std::string mapName)
{
	int startKeyPos = mapName.rfind(battleDataParserNS::DATA_FORMAT_BEGIN_KEY);
	int endKeyPos = mapName.rfind(battleDataParserNS::DATA_FORMAT_END_KEY);

	std::string strMapName = mapName.substr(
		startKeyPos + battleDataParserNS::DATA_FORMAT_BEGIN_KEY.length() + 1,
		endKeyPos - (battleDataParserNS::DATA_FORMAT_END_KEY.length() * 2) - 2);

	m_strMapName = strMapName;
}

void CBattle_DataParser::battlePlayerDataRecognize(std::vector<std::string> vArray)
{
	for (auto iter : vArray)
	{
		int startKeyPos = iter.rfind(battleDataParserNS::DATA_FORMAT_BEGIN_KEY);
		int endKeyPos = iter.rfind(battleDataParserNS::DATA_FORMAT_END_KEY);

		std::string shipData = iter.substr(startKeyPos + battleDataParserNS::DATA_FORMAT_BEGIN_KEY.length() + 1,
			endKeyPos - battleDataParserNS::DATA_FORMAT_BEGIN_KEY.length() - battleDataParserNS::DATA_FORMAT_END_KEY.length());

		m_vPlayerShipData.emplace_back(shipData);
	}	
}

void CBattle_DataParser::battleAIDataRecognize(std::vector<std::string> vArray)
{
	for (auto iter : vArray)
	{
		int startKeyPos = iter.rfind(battleDataParserNS::DATA_FORMAT_BEGIN_KEY);
		int endKeyPos = iter.rfind(battleDataParserNS::DATA_FORMAT_END_KEY);

		std::string shipData = iter.substr(startKeyPos + battleDataParserNS::DATA_FORMAT_BEGIN_KEY.length() + 1,
			endKeyPos - battleDataParserNS::DATA_FORMAT_BEGIN_KEY.length() - battleDataParserNS::DATA_FORMAT_END_KEY.length());

		m_vAIShipData.emplace_back(shipData);
	}
}
