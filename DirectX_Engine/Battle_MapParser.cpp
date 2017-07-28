#include "stdafx.h"
#include "Battle_MapParser.h"
#include "Battle_MapSystem.h"
#include "Battle_CameraSystem.h"

CBattle_MapParser::CBattle_MapParser()
{
	m_pBattleMapSystem = nullptr;
	m_pBattleCameraSystem = nullptr;
}


CBattle_MapParser::~CBattle_MapParser()
{
}

bool CBattle_MapParser::loadBattleMapData(std::string mapFileName)
{	
	//============================================================================
	// MapFile Load - Start
	m_strLoadFileName = mapFileName;
	auto vData = TXTDATA_PARSER->loadDataToArray(mapFileName);
	// End - MapFile Load
	//============================================================================
	bool success = false;
	try
	{	
		//============================================================================
		// Map Data Load And Recognize - Start
		mapDataRecognize(vData);
		m_pBattleMapSystem->setAllTiles(m_loadedCells);
		// End - Map Data Load And Recognize
		//============================================================================
		// MapSystem MapTotal Width/Height/CellWidth/CellHeight Setup - Start
		float cellWidth = m_MapDataInfo.OriginWidth;
		float cellHeight = m_MapDataInfo.OriginHeight;
		float totalWidth = (m_MapDataInfo.CellsX * m_MapDataInfo.OriginWidth);
		float totalHeight = (m_MapDataInfo.CellsY * m_MapDataInfo.OriginHeight * battleMapDataMessageNS::ISOMETRIC_HEIGHT_TOTAL_RATE + cellHeight);
		m_pBattleMapSystem->setMapTotalWidth(totalWidth);
		m_pBattleMapSystem->setMapTotalHeight(totalHeight);
		m_pBattleMapSystem->setCellWidth(cellWidth);
		m_pBattleMapSystem->setCellHeight(cellHeight);
		// End - MapSystem MapTotal Width/Height/CellWidth/CellHeight Setup
		//============================================================================

		success = true;
	}
	catch (...)
	{
		std::string fileName = "FileName : " + m_strLoadFileName;
		std::string result = battleMapParserNS::ERROR_MESSAGE + fileName;
		MessageBox(g_hWndEngine, result.c_str(), "Error", MB_OK);
	}
	
	return success;
}

void CBattle_MapParser::mapDataRecognize(std::vector<std::string> vArray)
{
	if (vArray.size() <= 0)
		return;

	int recogCount = 0;

	m_MapDataInfo.Version = vArray[recogCount].substr(vArray[recogCount].rfind(battleMapDataMessageNS::TAB_ONE));
	m_MapDataInfo.CellsX = std::stoi(vArray[++recogCount].substr(vArray[recogCount].rfind(battleMapDataMessageNS::TAB_ONE)));
	m_MapDataInfo.CellsY = std::stoi(vArray[++recogCount].substr(vArray[recogCount].rfind(battleMapDataMessageNS::TAB_ONE)));
	m_MapDataInfo.OriginX = std::stoi(vArray[++recogCount].substr(vArray[recogCount].rfind(battleMapDataMessageNS::TAB_ONE)));
	m_MapDataInfo.OriginY = std::stoi(vArray[++recogCount].substr(vArray[recogCount].rfind(battleMapDataMessageNS::TAB_ONE)));
	m_MapDataInfo.OriginWidth = std::stoi(vArray[++recogCount].substr(vArray[recogCount].rfind(battleMapDataMessageNS::TAB_ONE)));
	m_MapDataInfo.OriginHeight = std::stoi(vArray[++recogCount].substr(vArray[recogCount].rfind(battleMapDataMessageNS::TAB_ONE)));
	m_MapDataInfo.MadeTime = vArray[++recogCount].substr(vArray[recogCount].rfind(battleMapDataMessageNS::TAB_ONE) + 1);
	m_MapDataInfo.RandomSeed = std::stoi(vArray[++recogCount].substr(vArray[recogCount].rfind(battleMapDataMessageNS::TAB_ONE)));
	m_MapDataInfo.ObjectSize = std::stoi(vArray[++recogCount].substr(vArray[recogCount].rfind(battleMapDataMessageNS::TAB_ONE)));
	m_MapDataInfo.CollisionBoxSize = std::stoi(vArray[++recogCount].substr(vArray[recogCount].rfind(battleMapDataMessageNS::TAB_ONE)));

	std::vector<std::string> vMapCells;
	std::vector<std::string> vMapObject;
	std::vector<std::string> vMapEventObject;

	bool bRecogCells = false;
	bool bRecogObjects = false;
	bool bRecogEventObject = false;
	for (auto iter : vArray)
	{
		// CELLS KEY CHECK
		if (iter.compare(battleMapDataMessageNS::DATA_START_KEY + " " + battleMapDataMessageNS::CELL_START_MESSAGE) == false)
		{
			bRecogCells = true;
			continue;
		}
		else if (iter.compare(battleMapDataMessageNS::CELL_START_MESSAGE + " " + battleMapDataMessageNS::DATA_END_KEY) == false)
		{
			bRecogCells = false;
			continue;
		}

		if (bRecogCells)
		{
			vMapCells.emplace_back(iter);
			continue;
		}

		// OBJECT KEY CHECK
		if (iter.compare(battleMapDataMessageNS::DATA_START_KEY + " " + battleMapDataMessageNS::OBJECT_START_MESSAGE) == false)
		{
			bRecogObjects = true;
			continue;
		}
		else if (iter.compare(battleMapDataMessageNS::OBJECT_START_MESSAGE + " " + battleMapDataMessageNS::DATA_END_KEY) == false)
		{
			bRecogObjects = false;
			continue;
		}

		if (bRecogObjects)
		{
			vMapObject.emplace_back(iter);
			continue;
		}

		// EVENT OBJECT KEY CHECK
		if (iter.compare(battleMapDataMessageNS::DATA_START_KEY + " " + battleMapDataMessageNS::EVENT_OBJECT_START_MESSAGE) == false)
		{
			bRecogEventObject = true;
			continue;
		}
		else if (iter.compare(battleMapDataMessageNS::EVENT_OBJECT_START_MESSAGE + " " + battleMapDataMessageNS::DATA_END_KEY) == false)
		{
			bRecogEventObject = false;
			continue;
		}

		if (bRecogEventObject)
		{
			vMapEventObject.emplace_back(iter);
			continue;
		}
	}

	loadBattleMapCells(vMapCells);
	loadBattleMapObjects(vMapObject);
	loadBattleMapEventObjects(vMapEventObject);
}

void CBattle_MapParser::loadBattleMapCells(std::vector<std::string> vMapCells)
{
	if (vMapCells.size() <= 0)
		return;

	m_pBattleMapSystem->resetTiles();

	std::string texture;
	int cellNumber = 0;
	int cellTotalX = m_MapDataInfo.CellsX;
	int cellTotalY = m_MapDataInfo.CellsY;
	int cellPosX = 0;
	int cellPosY = 0;
	int cellWidth = m_MapDataInfo.OriginWidth;
	int cellHeight = m_MapDataInfo.OriginHeight;

	int row = 0;
	for (auto iter : vMapCells)
	{
		int startKeyPos = iter.rfind("\t");
		int endKeyPos = iter.rfind(" ");
		texture = iter.substr(startKeyPos + 1, endKeyPos - 1 - startKeyPos);

		MapTile* newCell = new MapTile;
		newCell->initialize(m_pGraphics, cellNumber, texture, cellPosX, cellPosY, cellWidth, cellHeight);
		m_loadedCells.emplace_back(newCell);
		
		cellPosX += cellWidth;
		if (cellNumber % cellTotalX == 0 && cellNumber != 0)
		{
			if (row % 2)
				cellPosX = 0;
			else
				cellPosX = cellWidth / 2;

			cellPosY += cellHeight / 2;
			row++;			
		}
		cellNumber++;
	}

}

void CBattle_MapParser::loadBattleMapObjects(std::vector<std::string> vMapObjects)
{
	if (vMapObjects.size() <= 0)
		return;

	int objectNumber;
	int objectX, objectY;
	int objectWidth, objectHeight;
	std::string objectTexture;

	m_pBattleMapSystem->resetObjects();

	for (auto iter : vMapObjects)
	{
		int recogPos = 0;
		std::vector<std::string> vData;
		std::istringstream iss(iter);
		std::string token;
		while (std::getline(iss, token, ' '))
		{
			vData.emplace_back(token);
		}

		objectNumber = std::stoi(vData[++recogPos]);
		objectX = std::stoi(vData[++recogPos]);
		objectY = std::stoi(vData[++recogPos]);
		objectWidth = std::stoi(vData[++recogPos]);
		objectHeight = std::stoi(vData[++recogPos]);
		objectTexture = vData[++recogPos];

		MapObject* newObject = new MapObject;
		newObject->initialize(m_pBattleMapSystem->getGraphics(),
			m_pBattleMapSystem->getAllObjects().size() + 1,
			objectTexture,
			OBJECT_COLLISION_TYPE::COLLISION_BOX,
			0,
			objectX - m_pBattleCameraSystem->getCameraX(),
			objectY - m_pBattleCameraSystem->getCameraY(),
			objectWidth,
			objectHeight);

		m_pBattleMapSystem->addObject(newObject);
	}
}

void CBattle_MapParser::loadBattleMapEventObjects(std::vector<std::string> vMapEventObjects)
{
	if (vMapEventObjects.size() <= 0)
		return;

	int EventObjectNumber;
	int EventObjectX, EventObjectY;
	int EventObjectWidth, EventObjectHeight;
	std::string EventObjectType;

	m_pBattleMapSystem->resetEventObject();

	for (auto iter : vMapEventObjects)
	{
		int recogPos = 0;
		std::vector<std::string> vData;
		std::istringstream iss(iter);
		std::string token;
		while (std::getline(iss, token, ' '))
		{
			vData.emplace_back(token);
		}
		EventObjectNumber = std::stoi(vData[++recogPos]);
		EventObjectX = std::stoi(vData[++recogPos]);
		EventObjectY = std::stoi(vData[++recogPos]);
		EventObjectWidth = std::stoi(vData[++recogPos]);
		EventObjectHeight = std::stoi(vData[++recogPos]);
		EventObjectType = vData[++recogPos];

		MapEventObject* newEventObject = new MapEventObject;
		newEventObject->initialize(m_pBattleMapSystem->getGraphics(),
			EventObjectX - m_pBattleCameraSystem->getCameraX(),
			EventObjectY - m_pBattleCameraSystem->getCameraY(),
			EventObjectWidth,
			EventObjectHeight,
			EventObjectType);

		m_pBattleMapSystem->addEventObject(newEventObject);
	}
}
