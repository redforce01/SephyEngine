#include "stdafx.h"
#include "mapTileData.h"


MapTileData::MapTileData()
{
	m_pGraphics = nullptr;
	m_pInput = nullptr;
	m_x = m_y = 0;
}


MapTileData::~MapTileData()
{
}

bool MapTileData::initialize(Graphics * g, Input * i, std::string name, float startX, float startY)
{
	bool success = false;

	try
	{
		m_pGraphics = g;
		m_pInput = i;
		m_strName = name;
		m_x = startX;
		m_y = startY;

		success = Image::initialize(g, m_x, m_y, 0, IMAGEMANAGER->getTexture(m_strName));
	}
	catch (...)
	{
		std::string strError;
		strError = "MapTileData initialize Failed : ";
		strError.append(name.c_str());
		MessageBox(g_hWndEngine, strError.c_str(), "Error", MB_OK);
	}

	return success;
}

void MapTileData::draw()
{
	m_pGraphics->spriteBegin();

	Image::draw();

	m_pGraphics->spriteEnd();
}
