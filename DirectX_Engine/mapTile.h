#ifndef _MAPTILE_H
#define _MAPTILE_H

class MapTile;

#include "image.h"

namespace TileNS
{
	const UINT TYPE_NONE = 0x00000000;
	const UINT TYPE_A = 0x00000001;
	const UINT TYPE_B = 0x00000010;
	const UINT TYPE_C = 0x00000100;
	const UINT TYPE_D = 0x00001000;
	const UINT TYPE_E = 0x00010000;
	const UINT TYPE_F = 0x00100000;
	const UINT TYPE_G = 0x01000000;
	const UINT TYPE_H = 0x10000000;
}

enum class TILEFEATURE : UINT
{
	FEATULRE_UNKNOWN,
	FEATULRE_SQUARE,
	FEATULRE_ISOMETRIC,
	FEATULRE_CIRCLE
};

class MapTile : public Image
{
private:
	UINT			m_Number;
	UINT			m_nType;
	TILEFEATURE		m_Feature;
	RECT			m_rcTile;
	std::string		m_strTextureName;
public:
	MapTile();
	~MapTile();

	bool initialize(Graphics* g, UINT PID, std::string textureName, int startX, int startY,
		 int width, int height);
	void update(float frameTime);
	void render();

	// Draw This Tile Object's Border
	// ( Square / Isometric / Circle )
	void renderSketch();

	inline TILEFEATURE getFeature() const
	{ 
		return m_Feature;
	}

	inline RECT getTileRect() const
	{
		return m_rcTile;
	}

	std::string getTextureName() const
	{
		return m_strTextureName;
	}
	
	inline void moveRectWidth(int distance)
	{
		m_rcTile.left += distance;
		m_rcTile.right += distance;
	}

	inline void moveRectHeight(int distance)
	{
		m_rcTile.top += distance;
		m_rcTile.bottom += distance;
	}

	inline void setFeature(TILEFEATURE f)
	{
		m_Feature = f;
	}

	inline bool changeTexture(std::string textureName)
	{
		if (IMAGEMANAGER->getTexture(textureName) == nullptr)
			return false;

		m_strTextureName = textureName;
		return changeTile(IMAGEMANAGER->getTexture(textureName));
	}

	inline bool changeTile(TextureManager* texture)
	{
		if (texture == nullptr)
			return false;
		setTextureManager(texture);
		return true;
	}
};

#endif // !_MAPTILE_H