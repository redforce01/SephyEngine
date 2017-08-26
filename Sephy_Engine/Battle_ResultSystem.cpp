#include "stdafx.h"
#include "Battle_ResultSystem.h"
#include "Battle_UnitSystem.h"


CBattle_ResultSystem::CBattle_ResultSystem()
{
	m_fPlayerScore = 0;
	m_fComputerScore = 0;
}


CBattle_ResultSystem::~CBattle_ResultSystem()
{
}

void CBattle_ResultSystem::saveBattleResult()
{
	std::string filePath = "Resources\\50_BattleGameData\\Battle_Result.txt";
	std::vector<std::string> vResult;
	auto playerShips = m_pBattleUnitSystem->getPlayerShips();
	auto enemyShips = m_pBattleUnitSystem->getComputerShips();

	std::string worldIndex = m_pBattleUnitSystem->getWorldIndex();
	vResult.emplace_back(battleResultSystemNS::DATA_BEGIN_KEY + " " + battleResultSystemNS::WORLD_INDEX_KEY);
	vResult.emplace_back('\t' + battleResultSystemNS::DATA_BEGIN_KEY + " " + worldIndex + " " + battleResultSystemNS::DATA_END_KEY);
	vResult.emplace_back(battleResultSystemNS::WORLD_INDEX_KEY + " " + battleResultSystemNS::DATA_END_KEY);

	std::string strShipKey;
	//====================================================================
	// Player Ship Data Save
	//====================================================================
	vResult.emplace_back(battleResultSystemNS::DATA_BEGIN_KEY + " " + battleResultSystemNS::PLAYER_DATA_KEY);
	vResult.emplace_back('\t' + battleResultSystemNS::DATA_BEGIN_KEY + " " + battleResultSystemNS::DAMAGE_SCORE_KEY + " "
		+ std::to_string((int)m_pBattleUnitSystem->getDamageScoreFromPlayer()) + " " + battleResultSystemNS::DATA_END_KEY);
	for (auto iter : playerShips)
	{
		if (iter->getShipDestroy() == true)
			continue;

		strShipKey = '\t' + battleResultSystemNS::DATA_BEGIN_KEY + " " + iter->getShipName() + " " + battleResultSystemNS::DATA_END_KEY;
		vResult.emplace_back(strShipKey);
	}
	vResult.emplace_back(battleResultSystemNS::PLAYER_DATA_KEY + " " + battleResultSystemNS::DATA_END_KEY);

	//====================================================================
	// Computer Ship Data Save
	//====================================================================
	vResult.emplace_back(battleResultSystemNS::DATA_BEGIN_KEY + " " + battleResultSystemNS::ENEMY_DATA_KEY);
	vResult.emplace_back('\t' + battleResultSystemNS::DATA_BEGIN_KEY + " " + battleResultSystemNS::DAMAGE_SCORE_KEY + " "
		+ std::to_string((int)m_pBattleUnitSystem->getDamageScoreFromComputer()) + " " + battleResultSystemNS::DATA_END_KEY);
	for (auto iter : enemyShips)
	{
		if (iter->getShipDestroy() == true)
			continue;

		strShipKey = '\t' + battleResultSystemNS::DATA_BEGIN_KEY + " " + iter->getShipName() + " " + battleResultSystemNS::DATA_END_KEY;
		vResult.emplace_back(strShipKey);
	}
	vResult.emplace_back(battleResultSystemNS::ENEMY_DATA_KEY + " " + battleResultSystemNS::DATA_END_KEY);

	TXTDATA_PARSER->saveDataFromArray(filePath, vResult);
}

void CBattle_ResultSystem::loadBattleResult()
{
	std::vector<std::string> vArray = TXTDATA_PARSER->loadDataToArray("Battle_Result");

	if (vArray.size() <= 0)
		return;

	std::string strWorldIndex;
	std::vector<std::string> vPlayerShips;
	std::vector<std::string> vComputerShips;

	bool bRecogWorldIndex = false;
	bool bRecogPlayerShips = false;
	bool bRecogComputerShips = false;
	for (auto iter : vArray)
	{
		//=================================================
		// World Index Name - Before Battle
		//=================================================
		if (iter.compare(battleResultSystemNS::DATA_BEGIN_KEY + " " + battleResultSystemNS::WORLD_INDEX_KEY) == false)
		{
			bRecogWorldIndex = true;
			continue;
		}
		else if (iter.compare(battleResultSystemNS::WORLD_INDEX_KEY + " " + battleResultSystemNS::DATA_END_KEY) == false)
		{
			bRecogWorldIndex = false;
			continue;
		}

		if (bRecogWorldIndex)
		{
			strWorldIndex = iter;
			continue;
		}

		//=================================================
		// Emplace Player Ship List
		//  + Damage Score
		//  + Player Ship Name
		//=================================================
		if (iter.compare(battleResultSystemNS::DATA_BEGIN_KEY + " " + battleResultSystemNS::PLAYER_DATA_KEY) == false)
		{
			bRecogPlayerShips = true;
			continue;
		}
		else if (iter.compare(battleResultSystemNS::PLAYER_DATA_KEY + " " + battleResultSystemNS::DATA_END_KEY) == false)
		{
			bRecogPlayerShips = false;
			continue;
		}

		if (bRecogPlayerShips)
		{
			vPlayerShips.emplace_back(iter);
			continue;
		}

		//=================================================
		// Emplace Computer Ship List
		//  + Damage Score
		//  + Computer Ship Name
		//=================================================
		if (iter.compare(battleResultSystemNS::DATA_BEGIN_KEY + " " + battleResultSystemNS::ENEMY_DATA_KEY) == false)
		{
			bRecogComputerShips = true;
			continue;
		}
		else if (iter.compare(battleResultSystemNS::ENEMY_DATA_KEY + " " + battleResultSystemNS::DATA_END_KEY) == false)
		{
			bRecogComputerShips = false;
			continue;
		}

		if (bRecogComputerShips)
		{
			vComputerShips.emplace_back(iter);
			continue;
		}
	}

	recogWorldIndex(strWorldIndex);
	recogPlayerShipData(vPlayerShips);
	recegComputerShipData(vComputerShips);
}

void CBattle_ResultSystem::recogWorldIndex(std::string strWorldIndex)
{
	int startKeyPos = strWorldIndex.rfind(battleResultSystemNS::DATA_BEGIN_KEY);
	int endKeyPos = strWorldIndex.rfind(battleResultSystemNS::DATA_END_KEY);

	std::string result = strWorldIndex.substr(startKeyPos + battleResultSystemNS::DATA_BEGIN_KEY.length() + 1,
		endKeyPos - battleResultSystemNS::DATA_BEGIN_KEY.length() - battleResultSystemNS::DATA_END_KEY.length());

	m_strWorldIndex = result;
}

void CBattle_ResultSystem::recogPlayerShipData(std::vector<std::string> vArray)
{
	int scoreIndex = 0;
	for (auto iter : vArray)
	{
		if (scoreIndex == 0)
		{
			int startKeyPos = iter.rfind(battleResultSystemNS::DATA_BEGIN_KEY);
			int endKeyPos = iter.rfind(battleResultSystemNS::DATA_END_KEY);
			std::string damageScore = iter.substr(startKeyPos + battleResultSystemNS::DATA_BEGIN_KEY.length() + 1,
				endKeyPos - battleResultSystemNS::DATA_BEGIN_KEY.length() - battleResultSystemNS::DATA_END_KEY.length());
			auto pairData = TXTDATA_PARSER->tokenizeFromString(damageScore, ' ');
			m_fPlayerScore = std::stoi(pairData[pairData.size() - 1]);
			scoreIndex++;
			continue;
		}

		int startKeyPos = iter.rfind(battleResultSystemNS::DATA_BEGIN_KEY);
		int endKeyPos = iter.rfind(battleResultSystemNS::DATA_END_KEY);

		std::string shipData = iter.substr(startKeyPos + battleResultSystemNS::DATA_BEGIN_KEY.length() + 1,
			endKeyPos - battleResultSystemNS::DATA_BEGIN_KEY.length() - battleResultSystemNS::DATA_END_KEY.length());

		m_vPlayerShips.emplace_back(shipData);
		scoreIndex++;
	}
}

void CBattle_ResultSystem::recegComputerShipData(std::vector<std::string> vArray)
{
	int scoreIndex = 0;
	for (auto iter : vArray)
	{
		if (scoreIndex == 0)
		{
			int startKeyPos = iter.rfind(battleResultSystemNS::DATA_BEGIN_KEY);
			int endKeyPos = iter.rfind(battleResultSystemNS::DATA_END_KEY);
			std::string damageScore = iter.substr(startKeyPos + battleResultSystemNS::DATA_BEGIN_KEY.length() + 1,
				endKeyPos - battleResultSystemNS::DATA_BEGIN_KEY.length() - battleResultSystemNS::DATA_END_KEY.length());
			auto pairData = TXTDATA_PARSER->tokenizeFromString(damageScore, ' ');
			m_fComputerScore = std::stoi(pairData[pairData.size() - 1]);
			scoreIndex++;
			continue;
		}

		int startKeyPos = iter.rfind(battleResultSystemNS::DATA_BEGIN_KEY);
		int endKeyPos = iter.rfind(battleResultSystemNS::DATA_END_KEY);

		std::string shipData = iter.substr(startKeyPos + battleResultSystemNS::DATA_BEGIN_KEY.length() + 1,
			endKeyPos - battleResultSystemNS::DATA_BEGIN_KEY.length() - battleResultSystemNS::DATA_END_KEY.length());

		m_vComputerShips.emplace_back(shipData);
		scoreIndex++;
	}
}