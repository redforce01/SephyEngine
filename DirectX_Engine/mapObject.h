#ifndef _MAPOBJECT_H
#define _MAPOBJECT_H

class MapObject;

#include <string>
#include "image.h"

class MapObject : public Image
{
private:
	UINT			m_Number;
	RECT			m_rcTile;
	std::string		m_strTextureName;
public:
	MapObject();
	~MapObject();

	bool initialize(Graphics* g, UINT PID, std::string textureName, int startX, int startY,
		int width, int height);
	void update(float frameTime);
	void render();
};

#endif // !_MAPOBJECT_H
