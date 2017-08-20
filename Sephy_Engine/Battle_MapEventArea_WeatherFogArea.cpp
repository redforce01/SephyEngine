#include "stdafx.h"
#include "Battle_MapEventArea_WeatherFogArea.h"


CBattle_MapEventArea_WeatherFogArea::CBattle_MapEventArea_WeatherFogArea()
{
	m_pGraphics = nullptr; 
	m_enWeatherFogType = WEATHER_FOG_TYPE::WEATHER_FOG_SMALL;
}


CBattle_MapEventArea_WeatherFogArea::~CBattle_MapEventArea_WeatherFogArea()
{
	for (auto iter : m_vWeatherFog)
	{
		SAFE_DELETE(iter);
	}
	m_vWeatherFog.clear();
}

bool CBattle_MapEventArea_WeatherFogArea::initialize(Graphics * g, float centerX, float centerY)
{
	bool success = false;
	try
	{
		m_pGraphics = g;

		int fogCount = 0;
		int weatherType = RANDOM_MAKER->GetInt(0, 2);
		if (weatherType == 0)
		{
			fogCount = battleMapEventAreaWeatherNS::WEATHER_SMALL_FOG_COUNT;
			m_enWeatherFogType = WEATHER_FOG_TYPE::WEATHER_FOG_SMALL;
		}
		else if (weatherType == 1)
		{
			fogCount = battleMapEventAreaWeatherNS::WEATHER_MEDIUM_FOG_COUNT;
			m_enWeatherFogType = WEATHER_FOG_TYPE::WEATHER_FOG_MEDIUM;
		}
		else
		{
			fogCount = battleMapEventAreaWeatherNS::WEATHER_MEDIUM_FOG_COUNT;
			m_enWeatherFogType = WEATHER_FOG_TYPE::WEATHER_FOG_HEAVY;
		}

		for (int i = 0; i < fogCount; i++)
		{
			int spriteNumber = RANDOM_MAKER->GetInt(0, battleMapEventAreaWeatherNS::WEATHER_FOG_IMAGE_MAX_COUNT);
			std::string fogSpriteKey = battleMapEventAreaWeatherNS::WEATHER_FOG_FILENAME + std::to_string(spriteNumber);
			bool bRandom = RANDOM_MAKER->GetBool();
			Image* weatherFog = new Image;
			if (bRandom)
			{
				weatherFog->initialize(m_pGraphics, 0, 0, 0, IMAGEMANAGER->getTexture(fogSpriteKey));
			}
			else
			{
				weatherFog->initialize(m_pGraphics, 0, 0, 0, IMAGEMANAGER->getTexture(fogSpriteKey));
			}
			weatherFog->setColorFilter(battleMapEventAreaWeatherNS::WEATHER_FOG_COLOR_FILTER);
			weatherFog->setX(centerX - (weatherFog->getWidth() / 2) 
				+ RANDOM_MAKER->GetInt(battleMapEventAreaWeatherNS::WEATHER_FOG_RANDOM_RANGE_MIN, battleMapEventAreaWeatherNS::WEATHER_FOG_RANDOM_RANGE_MAX));
			weatherFog->setY(centerY - (weatherFog->getHeight() / 2) 
				+ RANDOM_MAKER->GetInt(battleMapEventAreaWeatherNS::WEATHER_FOG_RANDOM_RANGE_MIN, battleMapEventAreaWeatherNS::WEATHER_FOG_RANDOM_RANGE_MAX));
			m_vWeatherFog.emplace_back(weatherFog);
		}
	}
	catch (...)
	{
		MessageBox(g_hWndEngine, battleMapEventAreaWeatherNS::ERROR_MESSAGE.c_str(), "Error", MB_OK);
	}

	return success;
}

void CBattle_MapEventArea_WeatherFogArea::update(float frameTime)
{

}

void CBattle_MapEventArea_WeatherFogArea::render()
{
	m_pGraphics->spriteBegin();
	for (auto iter : m_vWeatherFog)
	{
		if (MyUtil::getObjInScreen(iter->getX(), iter->getY(), iter->getWidth(), iter->getHeight(), g_fScreenWidth, g_fScreenHeight) == false)
			continue;
		
		iter->draw();
	}
	m_pGraphics->spriteEnd();
}

void CBattle_MapEventArea_WeatherFogArea::moveX(float distance)
{
	for (auto iter : m_vWeatherFog)
	{
		iter->moveX(distance);
	}
}

void CBattle_MapEventArea_WeatherFogArea::moveY(float distance)
{
	for (auto iter : m_vWeatherFog)
	{
		iter->moveY(distance);
	}
}
