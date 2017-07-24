#include "stdafx.h"
#include "txtDataParser.h"


TxtDataParser::TxtDataParser()
{
}


TxtDataParser::~TxtDataParser()
{
}

// =======================================================================
// TXT FILE DATA PARSER 
// Load Data to Array Function
// Parameter (std::string fileName)
// return std::vector<std::string>
// The Parser Will Expect included "#". Each Line
// and "" void Line Too.
// =======================================================================
std::vector<std::string> TxtDataParser::loadDataToArray(std::string fileName)
{
	auto filePath = FILEMANAGER->getDataFile(fileName)->projectPath;

	std::vector<std::string> vData;
	std::ifstream openFile(filePath.data());
	if (openFile.is_open())
	{
		std::string line;
		while (std::getline(openFile, line))
		{
			if (line.find("#") != std::string::npos)
				continue;

			if (line.compare("") == false)
				continue;

			vData.emplace_back(line);
		}
		openFile.close();
	}	

	return vData;
}

// =======================================================================
// TXT FILE DATA PARSER
// Save Data From Array Function
// Parameter(std::string FilePath, std::vector<std::string> vData)
// return true(successed) / false(failed)
// =======================================================================
bool TxtDataParser::saveDataFromArray(std::string filePath, std::vector<std::string> vData)
{
	std::string strfilePath = filePath;
	std::ofstream writeFile(strfilePath.data());
	if (writeFile.is_open())
	{
		for (auto iter : vData)
		{
			writeFile << iter;
		}
		writeFile.close();
		return true;
	}
	else
		return false;
}
