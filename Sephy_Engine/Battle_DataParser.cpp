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

void CBattle_DataParser::saveBattleData(std::string worldIndex, std::string battleMap, std::vector<std::string> vPlayerShip, std::vector<std::string> vEnemyShip)
{
	std::vector<std::string> vResult;

	//==============================================
	// World Index Data Save To BattleData File
	//==============================================
	vResult.emplace_back(battleDataParserNS::DATA_FORMAT_BEGIN_KEY + " " + battleDataParserNS::BATTLE_DATA_WORLD_INDEX_KEY);
	vResult.emplace_back('\t' + battleDataParserNS::DATA_FORMAT_BEGIN_KEY + " " + worldIndex + " " + battleDataParserNS::DATA_FORMAT_END_KEY);
	vResult.emplace_back(battleDataParserNS::BATTLE_DATA_WORLD_INDEX_KEY + " " + battleDataParserNS::DATA_FORMAT_END_KEY);

	//==============================================
	// Map Data Save To BattleData File
	//==============================================
	vResult.emplace_back(battleDataParserNS::DATA_FORMAT_BEGIN_KEY + " " + battleDataParserNS::BATTLE_MAP_KEY);
	vResult.emplace_back('\t' + battleDataParserNS::DATA_FORMAT_BEGIN_KEY + " " + battleMap + " " + battleDataParserNS::DATA_FORMAT_END_KEY);
	vResult.emplace_back(battleDataParserNS::BATTLE_MAP_KEY + " " + battleDataParserNS::DATA_FORMAT_END_KEY);

	//==============================================
	// Player Ship Data Save To BattleData File
	//==============================================
	vResult.emplace_back(battleDataParserNS::DATA_FORMAT_BEGIN_KEY + " " + battleDataParserNS::BATTLE_PLAYER_KEY);
	for (auto iter : vPlayerShip)
	{
		vResult.emplace_back('\t' + battleDataParserNS::DATA_FORMAT_BEGIN_KEY + " " + iter + " " + battleDataParserNS::DATA_FORMAT_END_KEY);
	}
	vResult.emplace_back(battleDataParserNS::BATTLE_PLAYER_KEY + " " + battleDataParserNS::DATA_FORMAT_END_KEY);

	//==============================================
	// Computer Ship Data Save To BattleData File	
	//==============================================
	vResult.emplace_back(battleDataParserNS::DATA_FORMAT_BEGIN_KEY + " " + battleDataParserNS::BATTLE_AI_KEY);
	for (auto iter : vEnemyShip)
	{
		vResult.emplace_back('\t' + battleDataParserNS::DATA_FORMAT_BEGIN_KEY + " " + iter + " " + battleDataParserNS::DATA_FORMAT_END_KEY);
	}
	vResult.emplace_back(battleDataParserNS::BATTLE_AI_KEY + " " + battleDataParserNS::DATA_FORMAT_END_KEY);

	TXTDATA_PARSER->saveDataFromArray(battleDataParserNS::SAVE_DATA_PATH, vResult);
}

void CBattle_DataParser::battleDataRecognize(std::vector<std::string> vArray)
{
	if (vArray.size() <= 0)
		return;

	std::string befWorldIndexName;
	std::string befMapName;
	std::vector<std::string> vbefPlayerData;
	std::vector<std::string> vbefAIData;
	
	bool bRecogWorld = false;
	bool bRecogMap = false;
	bool bRecogPlayerShip = false;
	bool bRecogAIShip = false;
	for (auto iter : vArray)
	{
		if (iter.compare(battleDataParserNS::DATA_FORMAT_BEGIN_KEY + " " + battleDataParserNS::BATTLE_DATA_WORLD_INDEX_KEY) == false)
		{
			bRecogWorld = true;
			continue;
		}
		else if (iter.compare(battleDataParserNS::BATTLE_DATA_WORLD_INDEX_KEY + " " + battleDataParserNS::DATA_FORMAT_END_KEY) == false)
		{
			bRecogWorld = false;
			continue;
		}

		if (bRecogWorld)
		{
			befWorldIndexName = iter;
			continue;
		}

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

	battleWorldIndexRecognize(befWorldIndexName);
	battleMapDataRecognize(befMapName);
	battlePlayerDataRecognize(vbefPlayerData);
	battleAIDataRecognize(vbefAIData);
}

void CBattle_DataParser::battleWorldIndexRecognize(std::string worldIndex)
{
	int startKeyPos = worldIndex.rfind(battleDataParserNS::DATA_FORMAT_BEGIN_KEY);
	int endKeyPos = worldIndex.rfind(battleDataParserNS::DATA_FORMAT_END_KEY);

	std::string strMapName = worldIndex.substr(
		startKeyPos + battleDataParserNS::DATA_FORMAT_BEGIN_KEY.length() + 1,
		endKeyPos - (battleDataParserNS::DATA_FORMAT_END_KEY.length() * 2) - 2);

	m_strWorldIndex = strMapName;
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
