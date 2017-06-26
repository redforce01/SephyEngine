#ifndef _MAPTILEDATA_H
#define _MAPTILEDATA_H

class MapTileData;

#include <string>
#include "image.h"

class MapTileData : public Image
{
private:
	std::string m_strName;
	float		m_x, m_y;

	Graphics*	m_pGraphics;
	Input*		m_pInput;
	RECT		m_rcImage;
public:
	MapTileData();
	~MapTileData();

	bool initialize(Graphics* g, Input* i, std::string name, float startX, float startY);
	void draw();

	inline std::string getTileName() const
	{
		return m_strName;
	}
};

#endif // !_MAPTILEDATA_H
