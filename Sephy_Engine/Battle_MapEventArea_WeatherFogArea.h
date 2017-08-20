#ifndef _BATTLE_MAP_EVENT_AREA_WEATHER_H
#define _BATTLE_MAP_EVENT_AREA_WEATHER_H
#define WIN32_LEAN_AND_MEAN

class CBattle_MapEventArea_WeatherFogArea;

namespace battleMapEventAreaWeatherNS
{
	const std::string ERROR_MESSAGE = "Battle Map Event Area Weather - Fog Initialize Failed";
	const std::string WEATHER_FOG_FILENAME = "Weather_Fog_";
	const UINT WEATHER_FOG_IMAGE_MAX_COUNT = 6;
	const COLOR_ARGB WEATHER_FOG_COLOR_FILTER = SETCOLOR_ARGB(64, 128, 128, 128);
	const float WEATHER_FOG_SMALL_RADIUS = 400.f;
	const float WEATHER_FOG_MEDIUM_RADIUS = 700.f;
	const float WEATHER_FOG_HEAVY_RADIUS = 1000.f;
	const UINT WEATHER_SMALL_FOG_COUNT = 5;
	const UINT WEATHER_MEDIUM_FOG_COUNT = 10;
	const UINT WEATHER_HEAVY_FOG_COUNT = 20;
	//====================================================
	const std::string WEATHER_FOG_IMPACT_A = "FOG_IMPACT_A_";
	const std::string WEATHER_FOG_IMPACT_B = "FOG_IMPACT_B_";
	const std::string WEATHER_FOG_IMPACT_C = "FOG_IMPACT_C_";
	const UINT WEATHER_FOG_IMPACT_A_MAX_FRAME = 16;
	const UINT WEATHER_FOG_IMPACT_B_MAX_FRAME = 14;
	const UINT WEATHER_FOG_IMPACT_C_MAX_FRAME = 13;
	//====================================================
	const int WEATHER_FOG_RANDOM_RANGE_MIN = -200;
	const int WEATHER_FOG_RANDOM_RANGE_MAX = 200;
}

enum class WEATHER_FOG_TYPE
{ WEATHER_FOG_SMALL, WEATHER_FOG_MEDIUM, WEATHER_FOG_HEAVY };

class CBattle_MapEventArea_WeatherFogArea
{
private:
	Graphics* m_pGraphics;
private:
	std::vector<Image*> m_vWeatherFog;
	WEATHER_FOG_TYPE m_enWeatherFogType;
public:
	CBattle_MapEventArea_WeatherFogArea();
	~CBattle_MapEventArea_WeatherFogArea();

	bool initialize(Graphics* g, float centerX, float centerY);
	void update(float frameTime);
	void render();

	void moveX(float distance);
	void moveY(float distance);
};

#endif // !_BATTLE_MAP_EVENT_AREA_WEATHER_H
