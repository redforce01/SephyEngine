#include "stdafx.h"
#include "engineSetting.h"


EngineSetting::EngineSetting()
{
	m_strSystemPath = FILEMANAGER->getCurrentSystemDir();
	m_strSystemPath += engineSettingNS::DEFAULT_PATH;
	
	ZeroMemory(&m_EngineSettings, sizeof(m_EngineSettings));
}


EngineSetting::~EngineSetting()
{
}

void EngineSetting::LoadEngineSetting()
{
	LoadEngineSection();
	LoadDisplaySection();
	LoadSoundSection();
	LoadDebugSection();
	LoadLanguageSection();
}

void EngineSetting::SaveEngineSetting()
{	
	SaveEngineSection();
	SaveDisplaySection();
	SaveSoundSection();
	SaveDebugSection();
	SaveLanguageSection();
}

// Engine Setting Information Setup to Global Extern Variables
void EngineSetting::RealEngineSetup()
{
	g_fWindowPosX = m_EngineSettings.nScreenPosX;
	g_fWindowPosY = m_EngineSettings.nScreenPosY;
	g_fScreenWidth = m_EngineSettings.nScreenWidth;
	g_fScreenHeight = m_EngineSettings.nScreenHeight;
	g_bWindowed = m_EngineSettings.bFullScreen;

	g_fSoundMasterVolume = m_EngineSettings.fSoundMasterVolume;
	g_fSoundEffectVolume = m_EngineSettings.fSoundEffectVolume;
	g_fSoundBGMVolume = m_EngineSettings.fSoundBGMVolume;

	g_bDebugMode = m_EngineSettings.bDebugMode;
	g_strDebugSceneName = m_EngineSettings.strDebugScene;
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
	m_EngineSettings.strEngineKey = loadBuffer;
	// End - ENGINE SECTION
	//===================================================================	
}

void EngineSetting::LoadDisplaySection()
{
	//===================================================================
	// DISPLAY SECTION - Start
	int nResult = 0;
	nResult = GetPrivateProfileInt(engineSettingNS::DISPLAY_SECTION.c_str(),
		engineSettingNS::DISPLAY_POS_X_KEY.c_str(),
		engineSettingDefaultNS::WINDOW_X,
		m_strSystemPath.c_str());
	m_EngineSettings.nScreenPosX = nResult;

	nResult = GetPrivateProfileInt(engineSettingNS::DISPLAY_SECTION.c_str(),
		engineSettingNS::DISPLAY_POS_Y_KEY.c_str(),
		engineSettingDefaultNS::WINDOW_Y,
		m_strSystemPath.c_str());
	m_EngineSettings.nScreenPosY = nResult;

	nResult = GetPrivateProfileInt(engineSettingNS::DISPLAY_SECTION.c_str(),
		engineSettingNS::DISPLAY_WIDTH_KEY.c_str(),
		engineSettingDefaultNS::WINDOW_WIDTH,
		m_strSystemPath.c_str());
	m_EngineSettings.nScreenWidth = nResult;

	nResult = GetPrivateProfileInt(engineSettingNS::DISPLAY_SECTION.c_str(),
		engineSettingNS::DISPLAY_HEIGHT_KEY.c_str(),
		engineSettingDefaultNS::WINDOW_HEIGHT,
		m_strSystemPath.c_str());
	m_EngineSettings.nScreenHeight = nResult;
	
	bool bFullScreen = false;
	bFullScreen = GetPrivateProfileInt(engineSettingNS::DISPLAY_SECTION.c_str(),
		engineSettingNS::DISPLAY_FULLSCREEN_KEY.c_str(),
		engineSettingDefaultNS::FULLSCREEN,
		m_strSystemPath.c_str());
	m_EngineSettings.bFullScreen = bFullScreen;
	// End - DISPLAY SECTION
	//===================================================================
}

void EngineSetting::LoadSoundSection()
{
	//===================================================================
	// SOUND SECTION - Start
	float fResult = 0.f;
	fResult = GetPrivateProfileInt(engineSettingNS::SOUND_SECTION.c_str(),
		engineSettingNS::SOUND_MASTER_VOLUME_KEY.c_str(),
		engineSettingDefaultNS::DEFAULT_VOLUME,
		m_strSystemPath.c_str());
	m_EngineSettings.fSoundMasterVolume = fResult / 1000;

	fResult = GetPrivateProfileInt(engineSettingNS::SOUND_SECTION.c_str(),
		engineSettingNS::SOUND_EFFECT_VOLUME_KEY.c_str(),
		engineSettingDefaultNS::DEFAULT_VOLUME,
		m_strSystemPath.c_str());
	m_EngineSettings.fSoundEffectVolume = fResult / 1000;

	fResult = GetPrivateProfileInt(engineSettingNS::SOUND_SECTION.c_str(),
		engineSettingNS::SOUND_BGM_VOLUME_KEY.c_str(),
		engineSettingDefaultNS::DEFAULT_VOLUME,
		m_strSystemPath.c_str());
	m_EngineSettings.fSoundBGMVolume = fResult / 1000;
	// End - SOUND SECTION
	//===================================================================
}

void EngineSetting::LoadDebugSection()
{
	//===================================================================
	// DEBUG SECTION - Start
	bool bDebugMode = false;
	bDebugMode = GetPrivateProfileInt(engineSettingNS::DEBUG_SECTION.c_str(),
		engineSettingNS::DEBUG_MODE_STATE.c_str(),
		engineSettingDefaultNS::DEFAULT_DEBUGED,
		m_strSystemPath.c_str());
	m_EngineSettings.bDebugMode = bDebugMode;
	
	char loadBuffer[MAX_PATH] = { 0, };
	GetPrivateProfileString(engineSettingNS::DEBUG_SECTION.c_str(),
		engineSettingNS::DEBUG_MODE_KEY.c_str(),
		engineSettingDefaultNS::DEFAULT_DEBUG_MODE.c_str(),
		loadBuffer, MAX_PATH,
		m_strSystemPath.c_str());
	m_EngineSettings.strDebugScene = loadBuffer;
	// End - ENGINE SECTION
	//===================================================================
}

void EngineSetting::LoadLanguageSection()
{
	//===================================================================
	// LANGUAGE SECTION - Start
	char loadBuffer[MAX_PATH] = { 0, };
	GetPrivateProfileString(engineSettingNS::LANGUAGE_SECTION.c_str(),
		engineSettingNS::LANGUAGE_KEY.c_str(),
		engineSettingDefaultNS::DEFAULT_LANGUAGE.c_str(),
		loadBuffer, MAX_PATH,
		m_strSystemPath.c_str());
	m_EngineSettings.strLanguageKey = loadBuffer;

	GetPrivateProfileString(engineSettingNS::LANGUAGE_SECTION.c_str(),
		engineSettingNS::LANGUAGE_PATH.c_str(),
		engineSettingDefaultNS::DEFAULT_LANGUAGE_PATH.c_str(),
		loadBuffer, MAX_PATH,
		m_strSystemPath.c_str());
	m_EngineSettings.strLanguageFilePath = loadBuffer;
	// End - LANGUAGE SECTION
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
		std::to_string(g_fWindowPosX).c_str(),
		m_strSystemPath.c_str());

	// SCREEN Y
	WritePrivateProfileString(engineSettingNS::DISPLAY_SECTION.c_str(),
		engineSettingNS::DISPLAY_POS_Y_KEY.c_str(),
		std::to_string(g_fWindowPosY).c_str(),
		m_strSystemPath.c_str());

	// SCREEN WIDTH
	WritePrivateProfileString(engineSettingNS::DISPLAY_SECTION.c_str(),
		engineSettingNS::DISPLAY_WIDTH_KEY.c_str(),
		std::to_string(g_fScreenWidth).c_str(),
		m_strSystemPath.c_str());

	// SCREEN HEIGHT
	WritePrivateProfileString(engineSettingNS::DISPLAY_SECTION.c_str(),
		engineSettingNS::DISPLAY_HEIGHT_KEY.c_str(),
		std::to_string(g_fScreenHeight).c_str(),
		m_strSystemPath.c_str());

	// SCREEN - WINDOWED
	WritePrivateProfileString(engineSettingNS::DISPLAY_SECTION.c_str(),
		engineSettingNS::DISPLAY_FULLSCREEN_KEY.c_str(),
		std::to_string(g_bWindowed).c_str(),
		m_strSystemPath.c_str());
	// End - DISPLAY SECTION
	//===================================================================

}

void EngineSetting::SaveSoundSection()
{
	//===================================================================
	// SOUND SECTION - Start
	WritePrivateProfileString(engineSettingNS::SOUND_SECTION.c_str(),
		engineSettingNS::SOUND_MASTER_VOLUME_KEY.c_str(),
		std::to_string(g_fSoundMasterVolume).c_str(),
		m_strSystemPath.c_str());

	WritePrivateProfileString(engineSettingNS::SOUND_SECTION.c_str(),
		engineSettingNS::SOUND_EFFECT_VOLUME_KEY.c_str(),
		std::to_string(g_fSoundEffectVolume).c_str(),
		m_strSystemPath.c_str());

	WritePrivateProfileString(engineSettingNS::SOUND_SECTION.c_str(),
		engineSettingNS::SOUND_BGM_VOLUME_KEY.c_str(),
		std::to_string(g_fSoundBGMVolume).c_str(),
		m_strSystemPath.c_str());
	// End - SOUND SECTION
	//===================================================================
}

void EngineSetting::SaveDebugSection()
{
	//===================================================================
	// DEBUG SECTION - Start
	WritePrivateProfileString(engineSettingNS::DEBUG_SECTION.c_str(),
		engineSettingNS::DEBUG_MODE_STATE.c_str(),
		std::to_string(engineSettingDefaultNS::DEFAULT_DEBUGED).c_str(),
		m_strSystemPath.c_str());

	WritePrivateProfileString(engineSettingNS::DEBUG_SECTION.c_str(),
		engineSettingNS::DEBUG_MODE_KEY.c_str(),
		engineSettingDefaultNS::DEFAULT_DEBUG_MODE.c_str(),
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
		engineSettingDefaultNS::DEFAULT_LANGUAGE.c_str(),
		m_strSystemPath.c_str());

	WritePrivateProfileString(engineSettingNS::LANGUAGE_SECTION.c_str(),
		engineSettingNS::LANGUAGE_PATH.c_str(),
		engineSettingDefaultNS::DEFAULT_LANGUAGE_PATH.c_str(),
		m_strSystemPath.c_str());
	// End - LANGUAGE SECTION
	//===================================================================
}
