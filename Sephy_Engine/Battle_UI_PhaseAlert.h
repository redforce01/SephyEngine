#ifndef _BATTLE_UI_PHASE_ALERT_H
#define _BATTLE_UI_PHASE_ALERT_H
#define WIN32_LEAN_AND_MEAN

class CBattle_PhaseAlert;

#include "image.h"

namespace battleUIPhaseAlertNS
{
	const std::string ERROR_MESSAGE = "Battle Phase Alert Initialize Failed";
	const std::string ALARM_LAMP_FILENAME = "LampRed_";
	const UINT ALARM_LAMP_MAX_FRAME = 18;
	const float ALERT_TIME = 10.f;
	const float ALERT_LAMP_RELATE_X = -138;
	const float ALERT_LAMP_RELATE_Y = 50;
	const std::string ALERT_SOUND_NAME = "02_AlertEnemy";
}

class CBattle_UI_PhaseAlert
{
private:
	Graphics* m_pGraphics;
private:
	Image*	m_pAlarmLamp;
	float	m_fAlertTime;
	int		m_nSpriteNumber;
	std::string m_strSpriteKey;
	bool	m_bAlert;
public:
	CBattle_UI_PhaseAlert();
	~CBattle_UI_PhaseAlert();

	bool initialize(Graphics* g);
	void update(float frameTime);
	void render();

	void setAlert(bool bAlert)
	{
		m_bAlert = bAlert;
	}
};

#endif // !_BATTLE_UI_PHASE_ALERT_H
