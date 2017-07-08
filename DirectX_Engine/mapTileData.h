#ifndef _MAPTILEDATA_H
#define _MAPTILEDATA_H

class MapTileData;

#include <string>
#include "image.h"

namespace mapTileDataNS
{
	const UINT TILE_WIDTH = 128;
	const UINT TILE_HEIGHT = 64;
}

class MapTileData : public Image
{
private:
	Graphics*	m_pGraphics;
	std::string m_strName;
	float		m_x, m_y;
	float		m_width, m_height;
	RECT		m_rcImage;
	bool		m_bSelected;
	bool		m_bObjectable;
public:
	MapTileData();
	~MapTileData();

	bool initialize(Graphics* g, std::string name, float startX, float startY);
	void draw();

	// ===========================================
	// Setter Functions 
	// ===========================================
	void setSelected(bool b)
	{
		m_bSelected = b;
	}
	void setObjectable(bool b)
	{
		m_bObjectable = b;
	}

	// ===========================================
	// Getter Functions 
	// ===========================================
	std::string getTextureName() const
	{
		return m_strName;
	}
	RECT getTileDataRECT() const
	{
		return m_rcImage;
	}
	bool getObjectable() const
	{
		return m_bObjectable;
	}
};

#endif // !_MAPTILEDATA_H
