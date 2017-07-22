#ifndef _MAPOBJECT_H
#define _MAPOBJECT_H

class MapObject;

#include <string>
#include "image.h"

enum class OBJECT_COLLISION_TYPE
{
	COLLISION_BOX, COLLISION_CIRCLE, COLLISION_ISOMETRIC, COLLISION_PIXEL
};

namespace mapObjectNS
{
	const UINT BASIC_OBJECT_WIDTH = 256;
	const UINT BASIC_OBJECT_HEIGHT = 128;
}

class MapObject : public Image
{
private:
	UINT			m_Number;
	std::string		m_strTextureName;
	float			m_x, m_y;				// Not using...
	float			m_width, m_height;
	UINT			m_layer;
	RECT			m_rcObject;
	RECT			m_rcCollisionBox;
	OBJECT_COLLISION_TYPE m_collisionType;
public:
	MapObject();
	~MapObject();

	bool initialize(Graphics* g, UINT PID, std::string textureName, OBJECT_COLLISION_TYPE collisionType, UINT layer,
		int startX, int startY,	int width = mapObjectNS::BASIC_OBJECT_WIDTH, int height = mapObjectNS::BASIC_OBJECT_HEIGHT);
	void update(float frameTime);
	void render();

	// ==========================================
	// Memeber Functions	
	// ==========================================



	// render Sketch Function
	// draw Border Line with each Collision Types
	void renderSketch(COLOR_ARGB color = graphicsNS::WHITE);

	// Move Object & Object RECT with Camera Move Horizontal
	inline void moveRectWidth(int distance)
	{
		m_x += distance;
		m_rcObject.left += distance;
		m_rcObject.right += distance;
		m_rcCollisionBox.left += distance;
		m_rcCollisionBox.right += distance;
	}
	// Move Object & Object RECT with Camera Move Vertical
	inline void moveRectHeight(int distance)
	{
		m_y += distance;
		m_rcObject.top += distance;
		m_rcObject.bottom += distance;
		m_rcCollisionBox.top += distance;
		m_rcCollisionBox.bottom += distance;
	}

	// Object Change Texture Function
	inline bool changeTexture(std::string textureName)
	{
		if (m_strTextureName.compare(textureName) == 0)
			return false;

		if (IMAGEMANAGER->getTexture(textureName) == nullptr)
			return false;

		m_strTextureName = textureName;
		setTextureManager(IMAGEMANAGER->getTexture(m_strTextureName));
		return true;
	}

	// ==========================================
	// Getter Functions
	// ==========================================
	inline RECT getObjectRect() const
	{
		return m_rcObject;
	}
	std::string getTextureName() const
	{
		return m_strTextureName;
	}
	int getPID() const
	{
		return m_Number;
	}
};

#endif // !_MAPOBJECT_H
