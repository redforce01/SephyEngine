#ifndef _MAPEVENTOBJECT_H
#define _MAPEVENTOBJECT_H

class MapEventObject;


enum class EVENT_OBJECT_TYPE
{
	EVENT_OBJECT_NONE,
	EVENT_OBJECT_COLLISION_BOX,			  // 충돌 처리 (박스)
	EVENT_OBJECT_COLLISION_CIRCLE,		  // 충돌 처리 (원)
	EVENT_OBJECT_COLLISION_ROTATE_BOX,	  // 충돌 처리 (회전형 박스)
	EVENT_OBJECT_BUILDING_REPAIR,		  // 수리소 거점
	EVENT_OBJECT_BUILDING_OBSERVER,		  // 관측소 거점
	EVENT_OBJECT_BUILDING_REFUEL,		  // 주유소 거점
	EVENT_OBJECT_WEATHER_FOG,			  // 날씨 이벤트 (안개)
	EVENT_OBJECT_WEATHER_RAIN,			  // 날씨 이벤트 (비)
	EVENT_OBJECT_GAME_RESPAWN,			  // 게임 리스폰 지역
	EVENT_OBJECT_GAME_STARTING			  // 게임 스타팅 지역
};

namespace EVENT_TYPE_KEY
{
	const std::string NONE					= "NONE";
	const std::string COLLISION_BOX			= "COLLISION_BOX";
	const std::string COLLISION_CIRCLE		= "COLLISION_CIRCLE";
	const std::string COLLISION_ROTATED_BOX = "COLLISION_ROTATED_BOX";
	const std::string BUILDING_REPAIR		= "BUILDING_REPAIR";
	const std::string BUILDING_OBSERVER		= "BUILDING_OBSERVER";
	const std::string BUILDING_REFUEL		= "BUILDING_REFUEL";
	const std::string WEATHER_FOG			= "WEATHER_FOG";
	const std::string WEATHER_RAIN			= "WEATHER_RAIN";
	const std::string GAME_RESPAWN			= "GAME_RESPAWN";
	const std::string GAME_STARTING			= "GAME_STARTING";
}

namespace mapEventObjectNS
{
	const char FONT[] = "Courier New";  // console font
	const int FONT_HEIGHT = 12;         // height of the font in pixels
	const COLOR_ARGB FONT_COLOR = graphicsNS::WHITE;    // color of console text
	const int IMAGE_WIDTH = 32;
	const int IMAGE_HEIGHT = 32;

	const int DEBUG_FONT_HEIGHT = 14;
	const float DEBUG_RECT_WIDTH = 200;
	const float DEBUG_RECT_HEIGHT = 15;
}

class MapEventObject : public Image
{
private:
	float	m_x, m_y;
	float	m_width, m_height;
	float	m_radius;
	float	m_angle;
	RECT	m_rcEventObject;
	EVENT_OBJECT_TYPE m_eObjectType;
	std::string m_strEventType;
	TextDX	m_dxFont;
private:
	bool	m_bHasImage;
	bool	m_bPlayers;
	bool	m_bDebug;

public:
	MapEventObject();
	~MapEventObject();

	bool initialize(Graphics* g, float x, float y, float width, float height, EVENT_OBJECT_TYPE eventType);
	bool initialize(Graphics* g, std::string textureName, float x, float y, float width, float height, EVENT_OBJECT_TYPE eventType);
	bool initialize(Graphics* g, float x, float y, float width, float height, std::string strEventType);
	void update(float frameTime);
	void render();

	// ==========================================
	// Memeber Functions	
	// ==========================================
	void setUpEventKey();

	EVENT_OBJECT_TYPE recogEventKey(std::string strKey);

	// render Sketch Function
	// draw Border Line with each Collision Types
	void renderSketch(COLOR_ARGB color = graphicsNS::WHITE);

	// Move Object & Object RECT with Camera Move Horizontal
	inline void moveRectWidth(int distance)
	{
		m_x += distance;
		m_rcEventObject.left += distance;
		m_rcEventObject.right += distance;
	}
	// Move Object & Object RECT with Camera Move Vertical
	inline void moveRectHeight(int distance)
	{
		m_y += distance;
		m_rcEventObject.top += distance;
		m_rcEventObject.bottom += distance;
	}

	// ==========================================
	// Setter Functions	
	// ==========================================
	void setEventObjectType(EVENT_OBJECT_TYPE type)
	{
		m_eObjectType = type;
	}
	void setPlayersObject(bool b)
	{
		m_bPlayers = b;
	}
	void setDebugMode(bool bDebug)
	{
		m_bDebug = bDebug;
	}

	// ==========================================
	// Getter Functions	
	// ==========================================
	RECT getEventObjectRECT() const
	{
		return m_rcEventObject;
	}
	POINT getEventObjectPos() const
	{
		return PointMake(m_x, m_y);
	}
	float getPosX() const
	{
		return m_x;
	}
	float getPosY() const
	{
		return m_y;
	}
	float getCenterPosX() const
	{
		return m_x + (m_width / 2);
	}
	float getCenterPosY() const
	{
		return m_y + (m_height / 2);
	}
	float getWidth() const
	{
		return m_width;
	}
	float getHeight() const
	{
		return m_height;
	}

	std::string getEventTypeKey() const
	{
		return m_strEventType;
	}
	EVENT_OBJECT_TYPE getEventObjectType() const
	{
		return m_eObjectType;
	}
	bool getPlayersObject() const
	{
		return m_bPlayers;
	}
};

#endif // !_MAPEVENTOBJECT_H
