#include "stdafx.h"
#include "mapEventObject.h"


MapEventObject::MapEventObject()
{
	m_bHasImage = false;
	m_eObjectType = EVENT_OBJECT_TYPE::EVENT_OBJECT_COLLISION_BOX;
	m_x = m_y = 0.f;
	m_width = m_height = 0.f;
	m_radius = 0.f;
	m_angle = 0.f;
	m_rcEventObject = { 0, };
	m_bPlayers = false;
	m_bDebug = false;
}


MapEventObject::~MapEventObject()
{
}

bool MapEventObject::initialize(Graphics * g, float x, float y, float width, float height, EVENT_OBJECT_TYPE eventType)
{
	bool success = false;
	try
	{
		success = Image::initialize(g, width, height, 0, IMAGEMANAGER->getTexture("WHITE"));
		if (success == false)
			throw("MapEvent Object Image Initialized Failed");

		success = m_dxFont.initialize(g, mapEventObjectNS::DEBUG_FONT_HEIGHT, false, false, mapEventObjectNS::FONT);

		m_x = x, m_y = y;
		m_width = width, m_height = height;
		m_rcEventObject = RectMake(m_x, m_y, m_width, m_height);
		m_eObjectType = eventType;
		m_bHasImage = false;
		setX(m_x);
		setY(m_y);
		setUpEventKey();
	}
	catch (...)
	{
		MessageBox(g_hWndEngine, "MapEvent Object Initialize Failed", "Error", MB_OK);
	}

	return success;
}

bool MapEventObject::initialize(Graphics * g, std::string textureName, float x, float y, float width, float height, EVENT_OBJECT_TYPE eventType)
{
	bool success = false;
	try
	{
		success = Image::initialize(g, width, height, 0, IMAGEMANAGER->getTexture(textureName));
		if (success == false)
			throw("MapEvent Object Image Initialized Failed");

		success = m_dxFont.initialize(g, mapEventObjectNS::DEBUG_FONT_HEIGHT, false, false, mapEventObjectNS::FONT);

		m_x = x, m_y = y;
		m_width = width, m_height = height;
		m_rcEventObject = RectMake(m_x, m_y, m_width, m_height);
		m_eObjectType = eventType;
		m_bHasImage = true;
		setX(m_x);
		setY(m_y);
		setUpEventKey();
	}
	catch (...)
	{
		MessageBox(g_hWndEngine, "MapEvent Object Initialize Failed", "Error", MB_OK);
	}

	return success;
}

bool MapEventObject::initialize(Graphics * g, float x, float y, float width, float height, std::string strEventType)
{
	bool success = false;
	try
	{
		success = Image::initialize(g, width, height, 0, IMAGEMANAGER->getTexture("WHITE"));
		if (success == false)
			throw("MapEvent Object Image Initialized Failed");

		success = m_dxFont.initialize(g, mapEventObjectNS::DEBUG_FONT_HEIGHT, false, false, mapEventObjectNS::FONT);

		m_x = x, m_y = y;
		m_width = width, m_height = height;
		m_rcEventObject = RectMake(m_x, m_y, m_width, m_height);
		m_eObjectType = recogEventKey(strEventType);
		m_bHasImage = false;
		setX(m_x);
		setY(m_y);
		setUpEventKey();
	}
	catch (...)
	{
		MessageBox(g_hWndEngine, "MapEvent Object Initialize Failed", "Error", MB_OK);
	}

	return success;
}

void MapEventObject::update(float frameTime)
{
	if (m_bHasImage)
		Image::update(frameTime);
}

void MapEventObject::render()
{
	if (m_bHasImage)
		Image::draw();

	if (m_bDebug)
	{
		RECT rc = RectMake(m_x, m_y, mapEventObjectNS::DEBUG_RECT_WIDTH, mapEventObjectNS::DEBUG_RECT_HEIGHT);
		m_dxFont.print(m_strEventType, rc, DT_LEFT | DT_VCENTER);
	}
}

void MapEventObject::setUpEventKey()
{
	switch (m_eObjectType)
	{
	case EVENT_OBJECT_TYPE::EVENT_OBJECT_COLLISION_BOX:
		m_strEventType = EVENT_TYPE_KEY::COLLISION_BOX;
		break;
	case EVENT_OBJECT_TYPE::EVENT_OBJECT_COLLISION_CIRCLE:
		m_strEventType = EVENT_TYPE_KEY::COLLISION_CIRCLE;
		break;
	case EVENT_OBJECT_TYPE::EVENT_OBJECT_COLLISION_ROTATE_BOX:
		m_strEventType = EVENT_TYPE_KEY::COLLISION_ROTATED_BOX;
		break;
	case EVENT_OBJECT_TYPE::EVENT_OBJECT_BUILDING_REPAIR:
		m_strEventType = EVENT_TYPE_KEY::BUILDING_REPAIR;
		break;
	case EVENT_OBJECT_TYPE::EVENT_OBJECT_BUILDING_OBSERVER:
		m_strEventType = EVENT_TYPE_KEY::BUILDING_OBSERVER;
		break;
	case EVENT_OBJECT_TYPE::EVENT_OBJECT_BUILDING_REFUEL:
		m_strEventType = EVENT_TYPE_KEY::BUILDING_REFUEL;
		break;
	case EVENT_OBJECT_TYPE::EVENT_OBJECT_WEATHER_FOG:
		m_strEventType = EVENT_TYPE_KEY::WEATHER_FOG;
		break;
	case EVENT_OBJECT_TYPE::EVENT_OBJECT_WEATHER_RAIN:
		m_strEventType = EVENT_TYPE_KEY::WEATHER_RAIN;
		break;
	case EVENT_OBJECT_TYPE::EVENT_OBJECT_GAME_RESPAWN:
		m_strEventType = EVENT_TYPE_KEY::GAME_RESPAWN;
		break;
	case EVENT_OBJECT_TYPE::EVENT_OBJECT_GAME_STARTING:
		m_strEventType = EVENT_TYPE_KEY::GAME_STARTING;
		break;
	default:
		m_strEventType = EVENT_TYPE_KEY::NONE;
		break;
	}
}

EVENT_OBJECT_TYPE MapEventObject::recogEventKey(std::string strKey)
{
	if (strKey.compare(EVENT_TYPE_KEY::COLLISION_BOX) == false)
		return EVENT_OBJECT_TYPE::EVENT_OBJECT_COLLISION_BOX;
	else if (strKey.compare(EVENT_TYPE_KEY::COLLISION_CIRCLE) == false)
		return EVENT_OBJECT_TYPE::EVENT_OBJECT_COLLISION_CIRCLE;
	else if (strKey.compare(EVENT_TYPE_KEY::COLLISION_ROTATED_BOX) == false)
		return EVENT_OBJECT_TYPE::EVENT_OBJECT_COLLISION_ROTATE_BOX;
	else if (strKey.compare(EVENT_TYPE_KEY::BUILDING_REPAIR) == false)
		return EVENT_OBJECT_TYPE::EVENT_OBJECT_BUILDING_REPAIR;
	else if (strKey.compare(EVENT_TYPE_KEY::BUILDING_OBSERVER) == false)
		return EVENT_OBJECT_TYPE::EVENT_OBJECT_BUILDING_OBSERVER;
	else if (strKey.compare(EVENT_TYPE_KEY::BUILDING_REFUEL) == false)
		return EVENT_OBJECT_TYPE::EVENT_OBJECT_BUILDING_REFUEL;
	else if (strKey.compare(EVENT_TYPE_KEY::WEATHER_FOG) == false)
		return EVENT_OBJECT_TYPE::EVENT_OBJECT_WEATHER_FOG;
	else if (strKey.compare(EVENT_TYPE_KEY::WEATHER_RAIN) == false)
		return EVENT_OBJECT_TYPE::EVENT_OBJECT_WEATHER_RAIN;
	else if (strKey.compare(EVENT_TYPE_KEY::GAME_RESPAWN) == false)
		return EVENT_OBJECT_TYPE::EVENT_OBJECT_GAME_RESPAWN;
	else if (strKey.compare(EVENT_TYPE_KEY::GAME_STARTING) == false)
		return EVENT_OBJECT_TYPE::EVENT_OBJECT_GAME_STARTING;
	else
		return EVENT_OBJECT_TYPE::EVENT_OBJECT_NONE;
}

void MapEventObject::renderSketch(COLOR_ARGB color)
{
	switch (m_eObjectType)
	{
	case EVENT_OBJECT_TYPE::EVENT_OBJECT_NONE:
		color = graphicsNS::WHITE;
		break;
	case EVENT_OBJECT_TYPE::EVENT_OBJECT_COLLISION_BOX:
		color = graphicsNS::BLUE;
		break;
	case EVENT_OBJECT_TYPE::EVENT_OBJECT_COLLISION_CIRCLE:
		color = graphicsNS::BLUE;
		break;
	case EVENT_OBJECT_TYPE::EVENT_OBJECT_COLLISION_ROTATE_BOX:
		color = graphicsNS::BLUE;
		break;
	case EVENT_OBJECT_TYPE::EVENT_OBJECT_BUILDING_REPAIR:
		color = graphicsNS::GREEN;
		break;
	case EVENT_OBJECT_TYPE::EVENT_OBJECT_BUILDING_OBSERVER:
		color = graphicsNS::GREEN;
		break;
	case EVENT_OBJECT_TYPE::EVENT_OBJECT_BUILDING_REFUEL:
		color = graphicsNS::GREEN;
		break;
	case EVENT_OBJECT_TYPE::EVENT_OBJECT_WEATHER_FOG:
		color = graphicsNS::ORANGE;
		break;
	case EVENT_OBJECT_TYPE::EVENT_OBJECT_WEATHER_RAIN:
		color = graphicsNS::ORANGE;
		break;
	case EVENT_OBJECT_TYPE::EVENT_OBJECT_GAME_RESPAWN:
		color = graphicsNS::RED;
		break;
	case EVENT_OBJECT_TYPE::EVENT_OBJECT_GAME_STARTING:
		color = graphicsNS::RED;
		break;
	}

	if (m_bHasImage)
		Image::drawRect(color);
	else
	{
		RECT rc = RectMake(m_x, m_y, m_width, m_height);
		this->graphics->drawRect(rc, 1.0f, color);
	}
}