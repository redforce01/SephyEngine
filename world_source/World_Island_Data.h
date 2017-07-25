#pragma once

#include <sstream>
#include "world_Island.h"

class CWorld_Island_Data
{
private:
	std::vector<std::string> island_data;

public:
	CWorld_Island_Data();
	~CWorld_Island_Data();

	//class -> the other header
	/*          ////////////////////////////////////////             */
	//std::vector<CWorld_Island*> island_node;
	std::vector<CWorld_Island*> island_node;

	virtual bool initialize();
	virtual void update(float frameTime);

	std::vector<std::string> loadObjectData();
	void ReplaceStringInPlace(std::string& subject, const std::string& search, const std::string& replace);
};
