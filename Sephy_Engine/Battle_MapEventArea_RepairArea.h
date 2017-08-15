#ifndef _BATTLE_MAPEVENT_AREA_REPAIR_H
#define _BATTLE_MAPEVENT_AREA_REPAIR_H
#define WIN32_LEAN_AND_MEAN

class CBattle_MapEventArea_RepairArea;

namespace battleMapEventAreaRepairAreaNS
{
	const std::string ERROR_MESSAGE = "Battle Event Area - Repair Area Initialize Failed";
	const float CAPTURE_TIME = 120.f;
	const float REPAIR_AREA_RADIUS = 300.f;
	const float REPAIR_AREA_REPAIR_SPEED = 100.f;
	const float REPAIR_AREA_CAPTURE_SPEED = 20.f;
	//==================================================
	const std::string PLAYER_FLAG = "GreenFlag";
	const std::string ENEMY_FLAG = "RedFlag";
	const float FLAG_RELATE_X = 50.f;
	const float FLAG_RELATE_Y = 150.f;
}

class CBattle_MapEventArea_RepairArea
{
private:
	Graphics* m_pGraphics;

private:
	Image* m_pFlag;

private:
	float m_AreaCenterX, m_AreaCenterY;
	float m_AreaRadius;
	float m_fRepairSpeed;
	float m_fCaptureRate;
private:
	bool m_bPlayerArea;
	bool m_bCapturing;
	bool m_bCaptureToPlayer;
public:
	CBattle_MapEventArea_RepairArea();
	~CBattle_MapEventArea_RepairArea();

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

	float getAreaRadius() const
	{
		return m_AreaRadius;
	}

	float getRepairSpeed() const
	{
		return m_fRepairSpeed;
	}
};

#endif // !_BATTLE_MAPEVENT_AREA_REPAIR_H
