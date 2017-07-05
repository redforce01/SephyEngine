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
}


MapDataParser::~MapDataParser()
{
}

void MapDataParser::recognizeData(std::vector<std::string> vArray)
{
	for (auto iter : vArray)
	{

	}
}

void MapDataParser::saveData()
{
	m_bCallFunction = true;

	std::vector<std::string> vArray;
	int count = 0;
	for (auto iter : m_arrMapTile)
	{
		// TILE NUMBER COMBINE
		std::string strNumber = "+";
		strNumber += std::to_string(count);
		count++;
		vArray.emplace_back(strNumber);

		// TILE TILE_NAME COMBINE
		std::string strTile = "- ";
		strTile += mapDataParserNS::MAP_TILE_IP;
		std::string str = iter->getTextureName();
		strTile += str;
		vArray.emplace_back(strTile);

		// TILE OBJECT_NAME COMBINE 
		// Not Using....
	}

	HANDLE file;
	char str[65536];
	strncpy_s(str, arrayCombine(vArray).c_str(), 65536);
	DWORD write;
	file = CreateFile(mapDataParserNS::SAVE_FILE_NAME.c_str(), GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	WriteFile(file, str, 65536, &write, NULL);
	CloseHandle(file);
}

std::string MapDataParser::arrayCombine(std::vector<std::string> vArray)
{
	char str[65536];
	ZeroMemory(str, sizeof(str));

	for (auto iter : vArray)
	{
		strncat_s(str, 128, iter.c_str(), 126);
	}
	std::string result = str;
	return result;
}

void MapDataParser::SaveThreadFunc()
{
	pMapDataParser->m_bLoading = true;	
	pMapDataParser->m_bLoading = false;
}

std::vector<std::string> MapDataParser::loadData()
{
	m_bCallFunction = true;
	
	const char* fileName = mapDataParserNS::LOAD_FILE_NAME.c_str();
	HANDLE file;
	char str[65536];
	DWORD read;
	memset(str, 0, sizeof(str));
	file = CreateFile(fileName, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	ReadFile(file, str, 65536, &read, NULL);
	CloseHandle(file);

	return arraySeperation(str);
}

void MapDataParser::LoadThreadFunc()
{
	pMapDataParser->m_bLoading = true;
	pMapDataParser->m_bLoading = false;
}

std::vector<std::string> MapDataParser::arraySeperation(char message[])
{
	std::vector<std::string> vArray;

	char* temp;
	char* seperator = { "# \t\n\r+-" };
	char* token;

	token = strtok_s(message, seperator, &temp);
	vArray.emplace_back(token);
	while (nullptr != (token = strtok_s(message, seperator, &temp)))
	{
		vArray.emplace_back(token);
	}

	return vArray;
}