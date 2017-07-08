#include "stdafx.h"
#include "mapDataParser.h"
#include "mapSystem.h"

// For Thread This Pointer
MapDataParser* pMapDataParser = nullptr;
MapDataParser::MapDataParser()
{
	::pMapDataParser = this;

	m_bLoading = false;
	m_bCallFunction = false;
	m_pMapSystem = nullptr;
}


MapDataParser::~MapDataParser()
{
}

void MapDataParser::saveData()
{
	m_bCallFunction = true;

	std::vector<std::string> vArray;
	vArray.emplace_back(mapDataParserNS::FILE_TITLE);
	vArray.emplace_back("\r\n");
	int count = 0;
	for (auto iter : m_arrMapTile)
	{
		// TILE NUMBER COMBINE
		std::string strNumber = "+";
		strNumber += std::to_string(count);
		count++;
		vArray.emplace_back(strNumber);
		vArray.emplace_back("\r\n");
		// TILE TILE_NAME COMBINE
		std::string strTile = "- ";
		strTile += mapDataParserNS::MAP_TILE_IP;
		std::string str = iter->getTextureName();
		strTile += str;
		vArray.emplace_back(strTile);
		vArray.emplace_back("\r\n");
		vArray.emplace_back("\r\n");

		// TILE OBJECT_NAME COMBINE 
		// Not Using....
		// To do...
	}

	HANDLE file;	
	std::string result;
	result = arrayCombine(vArray);

	DWORD write;
	file = CreateFile(mapDataParserNS::SAVE_FILE_NAME.c_str(), GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	WriteFile(file, result.c_str(), result.size(), &write, NULL);
	CloseHandle(file);


	//// =====================================
	//// Not Using...Mkaing..
	//std::string filePath = mapDataParserNS::SAVE_FILE_NAME;
	//std::ofstream writeFile(filePath.data());
	//if (writeFile.is_open())
	//{
	//	writeFile << result;
	//	writeFile.close();
	//}
	//// =====================================
}

std::string MapDataParser::arrayCombine(std::vector<std::string> vArray)
{
	std::string result;
	for (auto iter : vArray)
	{
		result += iter;
	}
	return result;
}

void MapDataParser::SaveThreadFunc()
{
	pMapDataParser->m_bLoading = true;	
	pMapDataParser->m_bLoading = false;
}

void MapDataParser::loadData()
{
	m_bCallFunction = true;
	
	const char* fileName = mapDataParserNS::LOAD_FILE_NAME.c_str();
	HANDLE file;
	DWORD read;
	char str[65536];
	memset(str, 0, sizeof(str));
	file = CreateFile(fileName, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	ReadFile(file, str, 65536, &read, NULL);
	CloseHandle(file);

	//// =====================================
	//// Not Using....Making..
	//std::vector<std::string> vArray;
	//std::string filePath = mapDataParserNS::LOAD_FILE_NAME;
	//std::ifstream openFile(filePath.data());
	//if (openFile.is_open())
	//{
	//	std::string line;
	//	while (std::getline(openFile, line))
	//	{
	//		vArray.emplace_back(line);
	//	}
	//	openFile.close();
	//}
	//// =====================================
		
	recognizeData(arraySeperation(str));
}

std::vector<std::string> MapDataParser::arraySeperation(char message[])
{
	std::vector<std::string> vArray;

	char* temp;
	char* seperator = { "\t\r\n" };
	char* token;

	token = strtok_s(message, seperator, &temp);
	vArray.emplace_back(token);
	while (nullptr != (token = strtok_s(NULL, seperator, &temp)))
	{
		vArray.emplace_back(token);
	}

	return vArray;
}

void MapDataParser::recognizeData(std::vector<std::string> vArray)
{
	std::vector<std::string> vMapTiles;
	for (auto iter : vArray)
	{
		if (iter.find(":") != std::string::npos)
		{
			int pos = iter.find(":");
			vMapTiles.emplace_back(iter.substr(pos + 1));
		}
	}
	
	mapSetup(vMapTiles);
}

void MapDataParser::mapSetup(std::vector<std::string> vData)
{
	int count = 0;
	auto vMapTiles = m_pMapSystem->getAllTiles();

	for (auto iter : vData)
	{
		vMapTiles[count]->changeTexture(iter);
		count++;
	}
}

void MapDataParser::LoadThreadFunc()
{
	pMapDataParser->m_bLoading = true;
	pMapDataParser->m_bLoading = false;
}