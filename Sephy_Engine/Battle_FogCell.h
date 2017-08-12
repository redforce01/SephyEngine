#ifndef _BATTLE_FOGCELL_H
#define _BATTLE_FOGCELL_H
#define WIN32_LEAN_AND_MEAN

#include "image.h"


namespace battleFogCellNS
{
	const std::string FOG_NONE_CELL_FILENAME = "FOG_BLACK_FULL";
	const std::string FOG_FULL_CELL_FILENAME = "FOG_WHITE_FULL";
	const std::string FOG_BASIC_KEY = "FOG_";
	const UINT FOG_WIDTH = 100;
	const UINT FOG_HEIGHT = 86;
	const UINT FOG_RADIUS = 45;
	const COLOR_ARGB FOG_COLOR_FILTER = SETCOLOR_ARGB(128, 8, 8, 8);
	const COLOR_ARGB FOG_DARKNESS_COLOR_FILTER = SETCOLOR_ARGB(192, 8, 8, 8);
}

enum class BATTLE_FOG_TYPE
{ FOG_TYPE_FULL, FOG_TYPE_HALF, FOG_TYPE_NONE, };

enum class BATTLE_FOG_VISIBLE_TYPE
{ FOG_VISIBLE_TYPE_DARKNESS, FOG_VISIBLE_TYPE_GRAY, FOG_VISIBLE_TYPE_VISIBLE };

class CBattle_FogCell : public Image
{
private:	
	BATTLE_FOG_TYPE m_enFogType;
	BATTLE_FOG_VISIBLE_TYPE m_enFogVisibleType;
	std::string m_fogKey;

public:
	CBattle_FogCell();
	~CBattle_FogCell();

	bool initialize(Graphics* g, float x, float y);
	void update(float frameTime);
	void render();

	void setFogKey(std::string spriteKey)
	{
		m_fogKey = spriteKey;
		Image::setTextureManager(IMAGEMANAGER->getTexture(m_fogKey));
	}
};

#endif // !_BATTLE_FOGCELL_H
