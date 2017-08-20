#include "stdafx.h"
#include "Battle_SoundSystem.h"


CBattle_SoundSystem::CBattle_SoundSystem()
{
	m_strCurrentBGM = battleSoundSystemNS::BATTLE_BGM_START;
	m_strNextBGM = battleSoundSystemNS::BATTLE_BGM_START;
	m_fCurrentVolume = g_fSoundBGMVolume * g_fSoundMasterVolume;
	m_enSituationType = SOUND_SITUATION_TYPE::BATTLE_SOUND_PEACE;
}


CBattle_SoundSystem::~CBattle_SoundSystem()
{
}

bool CBattle_SoundSystem::initialize()
{
	bool success = false;
	try
	{
		m_mBGM.try_emplace(battleSoundSystemNS::BATTLE_BGM_START, battleSoundSystemNS::BATTLE_BGM_START);
		m_mBGM.try_emplace(battleSoundSystemNS::BATTLE_BGM_BATTLE, battleSoundSystemNS::BATTLE_BGM_BATTLE);
		m_mBGM.try_emplace(battleSoundSystemNS::BATTLE_BGM_WINNING, battleSoundSystemNS::BATTLE_BGM_WINNING);
		m_mBGM.try_emplace(battleSoundSystemNS::BATTLE_BGM_LOSING, battleSoundSystemNS::BATTLE_BGM_LOSING);
		success = true;
	}
	catch (...)
	{
		MessageBox(g_hWndEngine, battleSoundSystemNS::ERROR_MESSAGE.c_str(), "Error", MB_OK);
	}

	return success;
}

void CBattle_SoundSystem::update(float frameTime)
{
	if (SOUNDMANAGER->isPlaySound(m_strCurrentBGM) == false)
	{
		SOUNDMANAGER->play(m_strCurrentBGM, m_fCurrentVolume);
	}

	if (m_bChange)
	{
		m_fCurrentVolume -= battleSoundSystemNS::SOUND_CHANGE_SPEED;
		if (m_fCurrentVolume <= 0)
		{
			pauseBGM(m_strCurrentBGM);
			m_strCurrentBGM = m_strNextBGM;
			m_fCurrentVolume = g_fSoundBGMVolume * g_fSoundMasterVolume;
			SOUNDMANAGER->play(m_strCurrentBGM, m_fCurrentVolume);
			m_bChange = false;
		}
	}
}

void CBattle_SoundSystem::changeSituation(SOUND_SITUATION_TYPE situation)
{
	if (m_enSituationType == situation)
		return;

	m_enSituationType = situation;
	switch (m_enSituationType)
	{
	case SOUND_SITUATION_TYPE::BATTLE_SOUND_PEACE:
		changeBGM(battleSoundSystemNS::BATTLE_BGM_START);
		break;
	case SOUND_SITUATION_TYPE::BATTLE_SOUND_BATTLE:
		changeBGM(battleSoundSystemNS::BATTLE_BGM_BATTLE);
		break;
	case SOUND_SITUATION_TYPE::BATTLE_SOUND_WINNING:
		changeBGM(battleSoundSystemNS::BATTLE_BGM_WINNING);
		break;
	case SOUND_SITUATION_TYPE::BATTLE_SOUND_LOSING:
		changeBGM(battleSoundSystemNS::BATTLE_BGM_LOSING);
		break;
	}	
}

void CBattle_SoundSystem::changeBGM(std::string bgmKey)
{
	m_bChange = true;

	for (auto iter : m_mBGM)
	{
		if (iter.first == bgmKey)
		{
			m_strNextBGM = bgmKey;
			m_fCurrentVolume = g_fSoundBGMVolume * g_fSoundMasterVolume;
			return;
		}
	}
	return;
}

void CBattle_SoundSystem::stopBGM(std::string bgmKey)
{
	for (auto iter : m_mBGM)
	{
		if (iter.first == bgmKey)
		{
			SOUNDMANAGER->stop(iter.second);
			return;
		}
	}
	return;
}

void CBattle_SoundSystem::pauseBGM(std::string bgmKey)
{
	for (auto iter : m_mBGM)
	{
		if (iter.first == bgmKey)
		{
			SOUNDMANAGER->pause(iter.second);
			return;
		}
	}
	return;
}
