#ifndef _BATTLE_MAP_EVENT_AREA_OBSERVER_H
#define _BATTLE_MAP_EVENT_AREA_OBSERVER_H
#define WIN32_LEAN_AND_MEAN

class CBattle_MapEventArea_ObserverArea;

namespace battleMapEventAreaObserverAreaNS
{
	const std::string ERROR_MESSAGE = "Battle Event Area - Repair Area Initialize Failed";
	const float CAPTURE_TIME = 60.f;
	const float CAPTURE_RADIUS = 800.f;
	const float OBSERVER_AREA_SIGHT_RADIUS = 1500.f;
	//==================================================
	const std::string PLAYER_FLAG = "GreenFlag";
	const std::string ENEMY_FLAG = "RedFlag";
	const float FLAG_RELATE_X = 70.f;
	const float FLAG_RELATE_Y = 160.f;
	//==================================================
	const std::string PROGRESS_BACK = "ProgressBack";
	const std::string PROGRESS_BLUE = "ProgressBlue";
	const std::string PROGRESS_RED = "ProgressRed";
	const float PROGRESS_WIDTH = 287.f;
	const float PROGRESS_RELATE_X = -(290.f / 2.f);
	const float PROGRESS_RELATE_Y = 180.f;
}

enum class CAPTURE_TYPE
{ CAPTURE_TO_PLAYER, CAPTURE_TO_ENEMY };

class CBattle_MapEventArea_ObserverArea
{
private:
	Graphics* m_pGraphics;
private:
	Image* m_pFlag;
	bool m_bDebug;
	Image* m_pProgressback;
	Image* m_pProgress;
private:
	float m_AreaCenterX, m_AreaCenterY;
	float m_AreaSightRadius;
	float m_AreaCaptureRadius;
	float m_fCaptureTime;
private:
	bool m_bPlayerArea;
	bool m_bCapturing;
	bool m_bCaptureToPlayer;
public:
	CBattle_MapEventArea_ObserverArea();
	~CBattle_MapEventArea_ObserverArea();

	bool initialize(Graphics* g, float centerX, float centerY);
	void update(float frameTime);
	void render();

	void moveX(float distance);
	void moveY(float distance);

	void capturing(bool bPlayerTo);

	//===================================================
	// Getter Functions
	//===================================================
	bool isPlayerArea() const
	{
		return m_bPlayerArea;
	}

	float getAreaCenterX() const
	{
		return m_AreaCenterX;
	}

	float getAreaCenterY() const
	{
		return m_AreaCenterY;
	}
	float getAreaCaptureRadius() const
	{
		return m_AreaCaptureRadius;
	}
	float getAreaSightRadius() const
	{
		return m_AreaSightRadius;
	}
};

#endif // !_BATTLE_MAP_EVENT_AREA_OBSERVER_H
