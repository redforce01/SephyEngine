#include "stdafx.h"
#include "mapObjectParser.h"


MapObjectParser::MapObjectParser()
{
}


MapObjectParser::~MapObjectParser()
{
}

std::vector<std::string> MapObjectParser::loadObjectData()
{
	std::vector<std::string> vData = TXTDATA_PARSER->loadDataToArray(mapObjectParserNS::DATA_FILE_NAME);


	std::vector<std::string> vRecogData;
	for (auto iter : vData)
	{
		// ...
		ReplaceStringInPlace(iter, "\t", " ");

		std::istringstream iss(iter);
		std::string token;
		while (std::getline(iss, token, ' '))
		{
			vRecogData.emplace_back(token);
		}
	}

	recogData(vRecogData);
	
	return vRecogData;
}

void MapObjectParser::recogData(std::vector<std::string> vData)
{

}

void MapObjectParser::ReplaceStringInPlace(std::string& subject, const std::string& search, const std::string& replace)
{
	size_t pos = 0;
	while ((pos = subject.find(search, pos)) != std::string::npos) 
	{
		subject.replace(pos, search.length(), replace);
		pos += replace.length();
	}
}