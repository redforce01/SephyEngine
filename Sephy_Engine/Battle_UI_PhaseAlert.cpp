#include "stdafx.h"
#include "Battle_UI_PhaseAlert.h"


CBattle_UI_PhaseAlert::CBattle_UI_PhaseAlert()
{
	m_pGraphics		= nullptr;
	m_pAlarmLamp	= nullptr;
	m_fAlertTime	= 0.f;
	m_nSpriteNumber = 0;
	m_bAlert		= false;
}


CBattle_UI_PhaseAlert::~CBattle_UI_PhaseAlert()
{
	SAFE_DELETE(m_pAlarmLamp);
}

bool CBattle_UI_PhaseAlert::initialize(Graphics * g)
{
	bool success = false;
	try
	{
		m_pGraphics = g;

		if (m_nSpriteNumber < 10)
		{
			m_strSpriteKey = battleUIPhaseAlertNS::ALARM_LAMP_FILENAME + "00" + std::to_string(m_nSpriteNumber);
		}
		else
			m_strSpriteKey = battleUIPhaseAlertNS::ALARM_LAMP_FILENAME + "0" + std::to_string(m_nSpriteNumber);

		m_pAlarmLamp = new Image;
		m_pAlarmLamp->initialize(m_pGraphics, 0, 0, 0, IMAGEMANAGER->getTexture(m_strSpriteKey));
		m_pAlarmLamp->setX(g_fScreenWidth + battleUIPhaseAlertNS::ALERT_LAMP_RELATE_X);
		m_pAlarmLamp->setY(battleUIPhaseAlertNS::ALERT_LAMP_RELATE_Y);
	}
	catch (...)
	{
		MessageBox(g_hWndEngine, battleUIPhaseAlertNS::ERROR_MESSAGE.c_str(), "Error", MB_OK);
	}
	return success;
}

void CBattle_UI_PhaseAlert::update(float frameTime)
{
	if (m_bAlert == false)
		return;

	if (m_bAlert)
	{
		if (SOUNDMANAGER->isPlaySound(battleUIPhaseAlertNS::ALERT_SOUND_NAME) == false)
		{
			SOUNDMANAGER->play(battleUIPhaseAlertNS::ALERT_SOUND_NAME, g_fSoundMasterVolume * g_fSoundEffectVolume);
		}

		m_fAlertTime += frameTime;
		if (m_fAlertTime >= battleUIPhaseAlertNS::ALERT_TIME)
			m_bAlert = false;

		if (m_nSpriteNumber >= battleUIPhaseAlertNS::ALARM_LAMP_MAX_FRAME)
			m_nSpriteNumber = 0;

		if (m_nSpriteNumber < 10)
		{
			m_strSpriteKey = battleUIPhaseAlertNS::ALARM_LAMP_FILENAME + "00" + std::to_string(m_nSpriteNumber);
		}
		else
			m_strSpriteKey = battleUIPhaseAlertNS::ALARM_LAMP_FILENAME + "0" + std::to_string(m_nSpriteNumber);

		m_pAlarmLamp->setTextureManager(IMAGEMANAGER->getTexture(m_strSpriteKey));
		m_nSpriteNumber++;
	}
}

void CBattle_UI_PhaseAlert::render()
{
	if (m_bAlert == false)
		return;

	m_pGraphics->spriteBegin();
	m_pAlarmLamp->draw();
	m_pGraphics->spriteEnd();
}
