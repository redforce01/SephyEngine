#include "stdafx.h"
#include "mapTileData.h"


MapTileData::MapTileData()
{
	m_pGraphics = nullptr;
	m_x = m_y = 0;
	m_width = m_height = 0;
	m_rcImage = { 0, };
	m_bSelected = false;
	m_bObjectable = false;
}


MapTileData::~MapTileData()
{
}

bool MapTileData::initialize(Graphics * g, std::string name, float startX, float startY)
{
	bool success = false;

	try
	{
		m_pGraphics = g;
		m_strName = name;
		m_x = startX;
		m_y = startY;
		m_rcImage = RectMake(m_x, m_y, mapTileDataNS::TILE_WIDTH, mapTileDataNS::TILE_HEIGHT);
		success = Image::initialize(g, 0, 0, 0, IMAGEMANAGER->getTexture(m_strName));
		this->setX(m_x);
		this->setY(m_y);
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

	if (m_bSelected)
		m_pGraphics->drawRect(m_rcImage);
}
