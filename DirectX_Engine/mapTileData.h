#ifndef _MAPTILEDATA_H
#define _MAPTILEDATA_H

class MapTileData;

#include <string>
#include "image.h"

namespace mapTileDataNS
{
	const UINT WIDTH = 128;
	const UINT HEIGHT = 64;
}

class MapTileData : public Image
{
private:
	Graphics*	m_pGraphics;
	std::string m_strName;
	float		m_x, m_y;
	RECT		m_rcImage;

	bool		m_bSelected;
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
};

#endif // !_MAPTILEDATA_H
