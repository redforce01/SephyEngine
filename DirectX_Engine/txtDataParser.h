#ifndef _TXTDATAPARSER_H
#define _TXTDATAPARSER_H

class TxtDataParser;

#include <string>
#include <vector>
#include <fstream>
#include "cSingletonBase.h"

class TxtDataParser : public cSingletonBase<TxtDataParser>
{
public:
	TxtDataParser();
	~TxtDataParser();

	// =======================================================================
	// TXT FILE DATA PARSER 
	// Load Data to Array Function
	// Parameter (std::string fileName)
	// return std::vector<std::string>
	// The Parser Will Expect included "#". Each Line
	// =======================================================================
	std::vector<std::string> loadDataToArray(std::string fileName);

	// =======================================================================
	// TXT FILE DATA PARSER
	// Save Data From Array Function
	// Parameter(std::string FilePath, std::vector<std::string> vData)
	// return true(successed) / false(failed)
	// =======================================================================
	bool saveDataFromArray(std::string filePath, std::vector<std::string> vData);
};

#define TXTDATA_PARSER TxtDataParser::GetInstance()
#endif // !_TXTDATAPARSER_H