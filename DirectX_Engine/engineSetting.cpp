#include "stdafx.h"
#include "engineSetting.h"


EngineSetting::EngineSetting()
{
	m_bDebugMode = false;
	

	m_bFullScreen = false;
	m_nScreenWidth = 0;
	m_nScreenHeight = 0;
	m_nScreenPosX = 0;
	m_nScreenPosY = 0;

	m_strSystemPath = FILEMANAGER->getCurrentSystemDir();
	m_strSystemPath += engineSettingNS::DEFAULT_PATH;
}


EngineSetting::~EngineSetting()
{
}

void EngineSetting::LoadEngineSetting()
{
	LoadEngineSection();
}

void EngineSetting::SaveEngineSetting()
{	
	SaveEngineSection();
	SaveDisplaySection();
	SaveSoundSection();
	SaveDebugSection();
	SaveLanguageSection();
}

void EngineSetting::LoadEngineSection()
{
	//===================================================================
	// ENGINE SECTION - Start
	char loadBuffer[MAX_PATH] = { 0, };
	GetPrivateProfileString(engineSettingNS::ENGINE_SECTION.c_str(),
		engineSettingNS::ENGINE_KEY.c_str(),
		engineSettingNS::ENGINE_ALLOWED.c_str(),
		loadBuffer, MAX_PATH,
		m_strSystemPath.c_str());
	m_strEngineKey = loadBuffer;
	// End - ENGINE SECTION
	//===================================================================
}

void EngineSetting::SaveEngineSection()
{
	//===================================================================
	// ENGINE SECTION - Start
	WritePrivateProfileString(engineSettingNS::ENGINE_SECTION.c_str(),
		engineSettingNS::ENGINE_KEY.c_str(),
		engineSettingNS::ENGINE_ALLOWED.c_str(),
		m_strSystemPath.c_str());
	// End - ENGINE SECTION
	//===================================================================
}

void EngineSetting::SaveDisplaySection()
{
	//===================================================================
	// DISPLAY SECTION - Start
	// SCREEN X
	WritePrivateProfileString(engineSettingNS::DISPLAY_SECTION.c_str(),
		engineSettingNS::DISPLAY_POS_X_KEY.c_str(),
		std::to_string(engineSettingDefaultNS::WINDOW_X).c_str(),
		m_strSystemPath.c_str());

	// SCREEN Y
	WritePrivateProfileString(engineSettingNS::DISPLAY_SECTION.c_str(),
		engineSettingNS::DISPLAY_POS_Y_KEY.c_str(),
		std::to_string(engineSettingDefaultNS::WINDOW_Y).c_str(),
		m_strSystemPath.c_str());

	// SCREEN WIDTH
	WritePrivateProfileString(engineSettingNS::DISPLAY_SECTION.c_str(),
		engineSettingNS::DISPLAY_WIDTH_KEY.c_str(),
		std::to_string(engineSettingDefaultNS::WINDOW_WIDTH).c_str(),
		m_strSystemPath.c_str());

	// SCREEN HEIGHT
	WritePrivateProfileString(engineSettingNS::DISPLAY_SECTION.c_str(),
		engineSettingNS::DISPLAY_HEIGHT_KEY.c_str(),
		std::to_string(engineSettingDefaultNS::WINDOW_HEIGHT).c_str(),
		m_strSystemPath.c_str());

	// SCREEN - WINDOWED
	WritePrivateProfileString(engineSettingNS::DISPLAY_SECTION.c_str(),
		engineSettingNS::FULLSCREEN_KEY.c_str(),
		std::to_string(engineSettingDefaultNS::WINDOWED).c_str(),
		m_strSystemPath.c_str());
	// End - DISPLAY SECTION
	//===================================================================

}

void EngineSetting::SaveSoundSection()
{
	//===================================================================
	// SOUND SECTION - Start
	WritePrivateProfileString(engineSettingNS::SOUND_SECTION.c_str(),
		engineSettingNS::SOUND_VOLUME_KEY.c_str(),
		std::to_string(engineSettingDefaultNS::DEFAULT_VOLUME).c_str(),
		m_strSystemPath.c_str());
	// End - SOUND SECTION
	//===================================================================
}

void EngineSetting::SaveDebugSection()
{
	//===================================================================
	// DEBUG SECTION - Start
	WritePrivateProfileString(engineSettingNS::DEBUG_SECTION.c_str(),
		engineSettingNS::DEBUG_MODE_KEY.c_str(),
		engineSettingDefaultNS::MODE.c_str(),
		m_strSystemPath.c_str());
	// End - DEBUG SECTION
	//===================================================================
}

void EngineSetting::SaveLanguageSection()
{
	//===================================================================
	// LANGUAGE SECTION - Start
	WritePrivateProfileString(engineSettingNS::LANGUAGE_SECTION.c_str(),
		engineSettingNS::LANGUAGE_KEY.c_str(),
		engineSettingDefaultNS::LANGUAGE.c_str(),
		m_strSystemPath.c_str());

	WritePrivateProfileString(engineSettingNS::LANGUAGE_SECTION.c_str(),
		engineSettingNS::LANGUAGE_PATH.c_str(),
		engineSettingDefaultNS::LANGUAGE_PATH.c_str(),
		m_strSystemPath.c_str());
	// End - LANGUAGE SECTION
	//===================================================================
}
