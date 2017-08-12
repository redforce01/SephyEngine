#include "stdafx.h"
#include "mapDataParser.h"
#include "mapSystem.h"
#include "CameraSystem.h"

// For Thread This Pointer
MapDataParser* pMapDataParser = nullptr;
MapDataParser::MapDataParser()
{
	::pMapDataParser = this;

	m_bLoading = false;
	m_bCallFunction = false;

	m_pMapSystem = nullptr;
	m_pCameraSystem = nullptr;

	ZeroMemory(&m_MapDataInfo, sizeof(m_MapDataInfo));

	m_MapDataInfo.MadeTime = "0";
	m_MapDataInfo.Version = "0";
	m_MapDataInfo.RandomSeed = 0;
	m_MapDataInfo.OriginX = 0;
	m_MapDataInfo.OriginY = 0;
	m_MapDataInfo.CellsX = 128;
	m_MapDataInfo.CellsY = 128;
	m_MapDataInfo.Width = 128;
	m_MapDataInfo.Height = 64;
	m_MapDataInfo.ObjectSize = 0;
	m_MapDataInfo.CollisionBoxSize = 0;
}


MapDataParser::~MapDataParser()
{
}


bool MapDataParser::saveData()
{
	m_bCallFunction = true;
	
	// =====================================
	// Make vData<std::string> For Saving Data
	m_vData.clear();

	std::string filePath = mapDataParserNS::SAVE_FILE_NAME;
	std::ofstream writeFile(filePath.data());
	if (writeFile.is_open())
	{
		//=======================================================================
		// SAVE - TILE
		// MapData Information Title Data Emplace to vData ( std::vector<std::string> ) - Start
		m_vData.emplace_back(mapDataMessageNS::VERSION + mapDataParserNS::TAB_THREE + m_MapDataInfo.Version + "\n");
		m_vData.emplace_back(mapDataMessageNS::CELL_X + mapDataParserNS::TAB_TWO + std::to_string(m_MapDataInfo.CellsX) + "\n");
		m_vData.emplace_back(mapDataMessageNS::CELL_Y + mapDataParserNS::TAB_TWO + std::to_string(m_MapDataInfo.CellsY) + "\n");
		m_vData.emplace_back(mapDataMessageNS::ORIGIN_X + mapDataParserNS::TAB_THREE + std::to_string(m_MapDataInfo.OriginX) + "\n");
		m_vData.emplace_back(mapDataMessageNS::ORIGIN_Y + mapDataParserNS::TAB_THREE + std::to_string(m_MapDataInfo.OriginY) + "\n");
		m_vData.emplace_back(mapDataMessageNS::ORIGIN_W + mapDataParserNS::TAB_THREE + std::to_string(m_MapDataInfo.Width) + "\n");
		m_vData.emplace_back(mapDataMessageNS::ORIGIN_H + mapDataParserNS::TAB_THREE + std::to_string(m_MapDataInfo.Height) + "\n");
		m_vData.emplace_back(mapDataMessageNS::MADE_TIME + mapDataParserNS::TAB_TWO + m_MapDataInfo.MadeTime + "\n");
		m_vData.emplace_back(mapDataMessageNS::RANDOM_SEED + mapDataParserNS::TAB_TWO + std::to_string(m_MapDataInfo.RandomSeed) + "\n");
		m_vData.emplace_back(mapDataMessageNS::OBJECT_SIZE + mapDataParserNS::TAB_TWO + std::to_string(m_MapDataInfo.ObjectSize) + "\n");
		m_vData.emplace_back(mapDataMessageNS::COLLISION_SIZE + mapDataParserNS::TAB_ONE + std::to_string(m_MapDataInfo.CollisionBoxSize) + "\n");
		// MapData Information Title Data Emplace to vData ( std::vector<std::string> ) - End
		//=======================================================================
		// Tile(Cell) Data Emplace to vData( std::vector<std::string> ) - Start
		m_vData.emplace_back(mapDataMessageNS::DATA_START_KEY + " " + mapDataMessageNS::CELL_START_MESSAGE + "\n");
		int count = 0;
		std::string strCellData;
		std::string strTextureNameTab = mapDataParserNS::TAB_THREE;
		for (auto iter : m_arrMapTile)
		{
			if (count > 9)
				strTextureNameTab = mapDataParserNS::TAB_TWO;

			strCellData = mapDataParserNS::TAB_ONE + mapDataMessageNS::DATA_START_KEY + " " +
				std::to_string(count) +	strTextureNameTab + 
				iter->getTextureName() + " " +
				mapDataMessageNS::DATA_END_KEY + "\n";
			m_vData.emplace_back(strCellData);
			count++;
		}
		m_vData.emplace_back(mapDataMessageNS::CELL_START_MESSAGE + " " + mapDataMessageNS::DATA_END_KEY + "\n");
		// Tile(Cell) Data Emplace - End
		//=======================================================================

		//=======================================================================
		// SAVE - OBJECT
		// Object Data Emplace to vData( std::vector<std::string> ) - Start
		m_vData.emplace_back(mapDataMessageNS::DATA_START_KEY + " " + mapDataMessageNS::OBJECT_START_MESSAGE + "\n");
		count = 0;
		std::string strObjectData;
		strTextureNameTab = mapDataParserNS::TAB_THREE;
		for (auto iter : m_arrMapObject)
		{
			if (count > 9)
				strTextureNameTab = mapDataParserNS::TAB_TWO;

			strObjectData = mapDataParserNS::TAB_ONE + mapDataMessageNS::DATA_START_KEY + " " +
				std::to_string(count) +	" " +														// Object Number
				std::to_string((int)iter->getX() + m_pCameraSystem->getCameraX()) + " " +			// Object PosX
				std::to_string((int)iter->getY() + m_pCameraSystem->getCameraY()) + " " +			// Object PosY
				std::to_string((int)iter->getWidth()) + " " +										// Object Width
				std::to_string((int)iter->getHeight()) + " " + 										// Object Height
				iter->getTextureName() + " " + 														// Object Texture
				mapDataMessageNS::DATA_END_KEY + "\n";
			m_vData.emplace_back(strObjectData);
			count++;
		}
		m_vData.emplace_back(mapDataMessageNS::OBJECT_START_MESSAGE + " " + mapDataMessageNS::DATA_END_KEY + "\n");
		// Object Data Emplace to vData( std::vector<std::string> ) - End
		//=======================================================================

		//=======================================================================
		// SAVE - EventObject
		// Event Object Data Emplace to vData( std::vector<std::string> ) - Start
		m_vData.emplace_back(mapDataMessageNS::DATA_START_KEY + " " + mapDataMessageNS::EVENT_OBJECT_START_MESSAGE + "\n");
		count = 0;
		std::string strEventObjectData;
		strTextureNameTab = mapDataParserNS::TAB_THREE;
		for (auto iter : m_arrMapEventObject)
		{
			if (count > 9)
				strTextureNameTab = mapDataParserNS::TAB_TWO;

			strEventObjectData = mapDataParserNS::TAB_ONE + mapDataMessageNS::DATA_START_KEY + " " +
				std::to_string(count) + " " +														// Object Number
				std::to_string((int)iter->getX() + m_pCameraSystem->getCameraX()) + " " +			// Event Object PosX
				std::to_string((int)iter->getY() + m_pCameraSystem->getCameraY()) + " " +			// Event Object PosY
				std::to_string((int)iter->getWidth()) + " " +										// Object Width
				std::to_string((int)iter->getHeight()) + " " + 										// Object Height
				iter->getEventTypeKey() + " " +
				mapDataMessageNS::DATA_END_KEY + "\n";
			m_vData.emplace_back(strEventObjectData);
			count++;
		}
		m_vData.emplace_back(mapDataMessageNS::EVENT_OBJECT_START_MESSAGE + " " + mapDataMessageNS::DATA_END_KEY + "\n");
		// Event Object Data Emplace to vData( std::vector<std::string> ) - End
		//=======================================================================



		for (auto iter : m_vData)
		{
			writeFile << iter;
		}
		writeFile.close();
	}
	else
	{
		return false;
	}

	return true;
}

//==============================================================
// This Function isn't used Now.
// SaveThreadFunc() = Loading Thread Func
// Not Using Method....
//==============================================================
void MapDataParser::SaveThreadFunc()
{
	pMapDataParser->m_bLoading = true;	
	pMapDataParser->m_bLoading = false;
}

bool MapDataParser::loadData()
{
	m_bCallFunction = true;
	
	//=======================================================================
	// Open BattleMap Data File (*.txt)
	// Load All Data Emplace to vData ( std::vector<std::string> ) - Start
	m_vData.clear();
	std::string filePath = mapDataParserNS::LOAD_FILE_NAME;
	std::ifstream openFile(filePath.data());
	if (openFile.is_open())
	{
		std::string line;
		while (std::getline(openFile, line))
		{
			m_vData.emplace_back(line);
		}
		openFile.close();
	}

	arrayRecognize(m_vData);
	//=======================================================================
	return true;
}

void MapDataParser::arrayRecognize(std::vector<std::string> vArray)
{
	if (vArray.size() <= 0)
		return;

	int recogCount = 0;

	m_MapDataInfo.Version = vArray[recogCount].substr(vArray[recogCount].rfind(mapDataParserNS::TAB_ONE));
	m_MapDataInfo.CellsX = std::stoi(vArray[++recogCount].substr(vArray[recogCount].rfind(mapDataParserNS::TAB_ONE)));
	m_MapDataInfo.CellsY = std::stoi(vArray[++recogCount].substr(vArray[recogCount].rfind(mapDataParserNS::TAB_ONE)));
	m_MapDataInfo.OriginX = std::stoi(vArray[++recogCount].substr(vArray[recogCount].rfind(mapDataParserNS::TAB_ONE)));
	m_MapDataInfo.OriginY = std::stoi(vArray[++recogCount].substr(vArray[recogCount].rfind(mapDataParserNS::TAB_ONE)));
	m_MapDataInfo.Width = std::stoi(vArray[++recogCount].substr(vArray[recogCount].rfind(mapDataParserNS::TAB_ONE)));
	m_MapDataInfo.Height = std::stoi(vArray[++recogCount].substr(vArray[recogCount].rfind(mapDataParserNS::TAB_ONE)));
	m_MapDataInfo.MadeTime = vArray[++recogCount].substr(vArray[recogCount].rfind(mapDataParserNS::TAB_ONE) + 1);
	m_MapDataInfo.RandomSeed = std::stoi(vArray[++recogCount].substr(vArray[recogCount].rfind(mapDataParserNS::TAB_ONE)));
	m_MapDataInfo.ObjectSize = std::stoi(vArray[++recogCount].substr(vArray[recogCount].rfind(mapDataParserNS::TAB_ONE)));
	m_MapDataInfo.CollisionBoxSize = std::stoi(vArray[++recogCount].substr(vArray[recogCount].rfind(mapDataParserNS::TAB_ONE)));
		
	std::vector<std::string> vMapCells;
	std::vector<std::string> vMapObject;
	std::vector<std::string> vMapEventObject;
		
	bool bRecogCells = false;
	bool bRecogObjects = false;
	bool bRecogEventObject = false;
	for (auto iter : vArray)
	{
		// CELLS KEY CHECK
		if (iter.compare(mapDataMessageNS::DATA_START_KEY + " " + mapDataMessageNS::CELL_START_MESSAGE) == false)
		{
			bRecogCells = true;
			continue;
		}
		else if (iter.compare(mapDataMessageNS::CELL_START_MESSAGE + " " + mapDataMessageNS::DATA_END_KEY) == false)
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
		if (iter.compare(mapDataMessageNS::DATA_START_KEY + " " + mapDataMessageNS::OBJECT_START_MESSAGE) == false)
		{
			bRecogObjects = true;
			continue;
		}
		else if (iter.compare(mapDataMessageNS::OBJECT_START_MESSAGE + " " + mapDataMessageNS::DATA_END_KEY) == false)
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
		if (iter.compare(mapDataMessageNS::DATA_START_KEY + " " + mapDataMessageNS::EVENT_OBJECT_START_MESSAGE) == false)
		{
			bRecogEventObject = true;
			continue;
		}
		else if (iter.compare(mapDataMessageNS::EVENT_OBJECT_START_MESSAGE + " " + mapDataMessageNS::DATA_END_KEY) == false)
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

	mapCellSetup(vMapCells);
	mapObjectSetup(vMapObject);
	mapEventObjectSetup(vMapEventObject);
}

void MapDataParser::mapCellSetup(std::vector<std::string> vMapCells)
{
	if (vMapCells.size() <= 0)
		return;

	m_pMapSystem->resetTiles();

	int cellNumber = 0;
	std::string texture;

	auto arrTiles = m_pMapSystem->getAllTiles();
	for (auto iter : vMapCells)
	{
		int startKeyPos = iter.rfind("\t");
		int endKeyPos = iter.rfind(" ");
		texture = iter.substr(startKeyPos + 1, endKeyPos - 1 - startKeyPos);

		arrTiles[cellNumber]->changeTexture(texture);				// Change MapSystem CellTexture
		cellNumber++;
	}
}

void MapDataParser::mapObjectSetup(std::vector<std::string> vObjectCells)
{
	if (vObjectCells.size() <= 0)
		return;

	int objectNumber;
	int objectX, objectY;
	int objectWidth, objectHeight;
	std::string objectTexture;	

	m_pMapSystem->resetObjects();
		
	for (auto iter : vObjectCells)
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
		newObject->initialize(m_pMapSystem->getGraphics(),
			m_pMapSystem->getAllObjects().size() + 1,
			objectTexture,
			OBJECT_COLLISION_TYPE::COLLISION_BOX,
			0,
			objectX - m_pCameraSystem->getCameraX(),
			objectY - m_pCameraSystem->getCameraY(),
			objectWidth,
			objectHeight);

		m_pMapSystem->addObject(newObject);
	}
}

void MapDataParser::mapEventObjectSetup(std::vector<std::string> vEventObject)
{
	if (vEventObject.size() <= 0)
		return;

	int EventObjectNumber;
	int EventObjectX, EventObjectY;
	int EventObjectWidth, EventObjectHeight;
	std::string EventObjectType;

	m_pMapSystem->resetEventObject();

	for (auto iter : vEventObject)
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
		newEventObject->initialize(m_pMapSystem->getGraphics(),
			EventObjectX - m_pCameraSystem->getCameraX(),
			EventObjectY - m_pCameraSystem->getCameraY(),
			EventObjectWidth,
			EventObjectHeight,
			EventObjectType);
		
		if(g_bDebugMode)
			newEventObject->setDebugMode(true);
		
		m_pMapSystem->addEventObject(newEventObject);
	}
}

void MapDataParser::LoadThreadFunc()
{
	pMapDataParser->m_bLoading = true;
	pMapDataParser->m_bLoading = false;
}