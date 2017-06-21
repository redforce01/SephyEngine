#ifndef _MAPTILEDATA_H
#define _MAPTILEDATA_H

class MapTileData;

#include <string>
#include "image.h"

class MapTileData : public Image
{
private:
	std::string strName;
	float x, y;

public:
	MapTileData();
	~MapTileData();

	bool initialize(Graphics* g, Input* i, std::string name, float startX, float startY);
	
	inline std::string getTileName() const
	{
		return strName;
	}
};

#endif // !_MAPTILEDATA_H
