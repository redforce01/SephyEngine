#include "stdafx.h"
#include "Battle_FogCell.h"


CBattle_FogCell::CBattle_FogCell()
{
	m_enFogType = BATTLE_FOG_TYPE::FOG_TYPE_FULL;
	m_enFogVisibleType = BATTLE_FOG_VISIBLE_TYPE::FOG_VISIBLE_TYPE_DARKNESS;
	m_fogKey = battleFogCellNS::FOG_FULL_CELL_FILENAME;
}


CBattle_FogCell::~CBattle_FogCell()
{
}

bool CBattle_FogCell::initialize(Graphics* g, float x, float y)
{	
	bool success = Image::initialize(g, 0, 0, 0, IMAGEMANAGER->getTexture(m_fogKey));
	if (success == false)
		return success;

	Image::setX(x);
	Image::setY(y);
	Image::setColorFilter(battleFogCellNS::FOG_COLOR_FILTER);
	
	return success;
}

void CBattle_FogCell::update(float frameTime)
{
}

void CBattle_FogCell::render()
{
	Image::draw();
}
