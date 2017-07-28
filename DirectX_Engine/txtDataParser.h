#ifndef _TXTDATAPARSER_H
#define _TXTDATAPARSER_H

class TxtDataParser;

#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include "cSingletonBase.h"

class TxtDataParser : public cSingletonBase<TxtDataParser>
{
public:
	TxtDataParser();
	~TxtDataParser();

	//=======================================================================
	// TXT FILE DATA PARSER 
	// Load Data to Array Function
	// Parameter (std::string fileName)
	// return std::vector<std::string>
	// The Parser Will Expect included "#". Each Line
	//=======================================================================
	std::vector<std::string> loadDataToArray(std::string fileName);

	//=======================================================================
	// TXT FILE DATA PARSER
	// Save Data From Array Function
	// Parameter(std::string FilePath, std::vector<std::string> vData)
	// return true(successed) / false(failed)
	//=======================================================================
	bool saveDataFromArray(std::string filePath, std::vector<std::string> vData);

	//=======================================================================
	// TXT FILE DATA PARSER
	// Recog String Function 
	// Parameter : std::string strMessage, char seperator
	// Result : return std::vector<std::string>
	// Example) parameter("Hello-World-Apple-Banana", '-')
	//			result : std::vector<std::string>	
	//				- [0] = "Hello"
	//				- [1] = "World"
	//				- [2] = "Apple"
	//				- [3] = "Banana"
	//=======================================================================
	std::vector<std::string> tokenizeFromString(std::string strMessage, char seperator);
};

#define TXTDATA_PARSER TxtDataParser::GetInstance()
#endif // !_TXTDATAPARSER_H