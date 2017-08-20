#ifndef _BATTLE_MAP_EVENT_AREA_RESPAWN_H
#define _BATTLE_MAP_EVENT_AREA_RESPAWN_H
#define WIN32_LEAN_AND_MEAN

class CBattle_MapEventArea_RespawnArea;

namespace battleMapUIRespawnAreaNS
{
	const float RESPAWN_AREA_DEFAULT_RADIUS = 200.f;
}

class CBattle_MapEventArea_RespawnArea
{
private:
	Graphics* m_pGraphics;

private:
	float m_centerX, m_centerY;
	float m_areaRadius;

public:
	CBattle_MapEventArea_RespawnArea();
	~CBattle_MapEventArea_RespawnArea();

	bool initialize(Graphics* g);
	void render();

	//============================================
	// Member Functions
	//============================================

	void moveX(float fDistance)
	{
		m_centerX += fDistance;
	}
	void moveY(float fDistance)
	{
		m_centerY += fDistance;
	}

	//============================================
	// Setter Functions
	//============================================
	void setRespawnAreaCenterX(float centerX)
	{
		m_centerX = centerX;
	}
	void setRespawnAreaCenterY(float centerY)
	{
		m_centerY = centerY;
	}
	void setRespawnAreaRadius(float fRadius)
	{
		m_areaRadius = fRadius;
	}


	//============================================
	// Getter Functions
	//============================================
	float getRespawnAreaCenterX() const
	{
		return m_centerX;
	}

	float getRespawnAreaCenterY() const
	{
		return m_centerY;
	}

	float getRespawnAreaRadius() const
	{
		return m_areaRadius;
	}
};

#endif // !_BATTLE_MAP_EVENT_AREA_RESPAWN_H
