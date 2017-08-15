#ifndef _ENGINE_SETTING_H
#define _ENGINE_SETTING_H

class EngineSetting;

#include <vector>
#include <string>

namespace engineSettingNS
{
	//=======================================================
	// Strings FOR ENGINE SETTING PATH AND VARIABLES
	const std::string EQUAL = "=";
	const std::string UNDERBAR = "_";
	const std::string DEFAULT_PATH = "\\EngineSettings\\Settings.ini";
	//=======================================================
	// ENGINE SETTING
	const std::string ENGINE_SECTION = "Engine";
	const std::string ENGINE_KEY = "EngineKey";
	const std::string ENGINE_ALLOWED = "sephy_s01";
	//=======================================================
	// DISPLAY SETTING
	const std::string DISPLAY_SECTION = "Display";
	const std::string DISPLAY_POS_X_KEY = "ScreenPosX";
	const std::string DISPLAY_POS_Y_KEY = "ScreenPosY";
	const std::string DISPLAY_WIDTH_KEY = "ScreenWidth";
	const std::string DISPLAY_HEIGHT_KEY = "ScreenHeight";
	const std::string DISPLAY_FULLSCREEN_KEY = "Fullscreen";
	//=======================================================
	// SOUND SETTING
	const std::string SOUND_SECTION = "Sound";
	const std::string SOUND_MASTER_VOLUME_KEY = "SoundMasterVolume";
	const std::string SOUND_EFFECT_VOLUME_KEY = "SoundEffectVolume";
	const std::string SOUND_BGM_VOLUME_KEY = "SoundBGMVolume";
	//=======================================================
	// DEBUG SETTING
	const std::string DEBUG_SECTION = "Debug";
	const std::string DEBUG_MODE_STATE = "Debug";
	const std::string DEBUG_MODE_KEY = "Mode";
	//=======================================================
	// LANGUAGE SETTING
	const std::string LANGUAGE_SECTION = "Language";
	const std::string LANGUAGE_KEY = "Language";
	const std::string LANGUAGE_PATH = "Path";
	//=======================================================
	// CUSTOM PATH
	const std::string CUSTOM_PATH_SECTION = "CustomResource";
	const std::string CUSTOM_PATH_KEY = "Path";
}

namespace engineSettingDefaultNS
{
	const UINT WINDOW_X = 0;
	const UINT WINDOW_Y = 0;
	const UINT WINDOW_WIDTH = 1900;
	const UINT WINDOW_HEIGHT = 1000;
	const BOOL FULLSCREEN = FALSE;
	const BOOL DEFAULT_DEBUGED = FALSE;
	const std::string DEFAULT_DEBUG_MODE = "MapTool";
	const std::string DEFAULT_LANGUAGE = "English";
	const std::string DEFAULT_LANGUAGE_PATH = "Resources\\Language\\English.txt";
	const float DEFAULT_VOLUME = 300.f;
}

struct tagEngineSettingInfo
{
public:
	std::string strEngineKey;				// Engine Key
	std::vector<std::string> vCustomPath;	// Custom Path Vector For FILE SYSTEM
	bool	bFullScreen;					// Display Fullscreen Flag
	int		nScreenWidth;					// Display Start X
	int		nScreenHeight;					// Display Start Y
	int		nScreenPosX;					// Display Width Size
	int		nScreenPosY;					// Display Height Size
	float	fSoundMasterVolume;				// Sound Master Volume (min : 0 ~ max : 1000)
	float	fSoundEffectVolume;				// Sound Effect Volume (min : 0 ~ max : 1000)
	float	fSoundBGMVolume;				// Sound BGM Volume (min : 0 ~ max : 1000)
	bool	bDebugMode;						// Debug Mode Flag
	std::string strDebugScene;				// Debug Mode Scene Name (std::string)
	std::string strLanguageKey;				// Language Key
	std::string strLanguageFilePath;		// Language File Path
};

class EngineSetting
{
private: // SYSTEM
	std::string m_strSystemPath;	// ENGINE INI SYSTEM PATH
	tagEngineSettingInfo m_EngineSettings;

public:
	EngineSetting();
	~EngineSetting();

	// ENGINE INI SETTING LOAD FUNCTION
	void LoadEngineSetting();
	// ENGINE INI SETTING SAVE FUNCTION
	void SaveEngineSetting();

	void RealEngineSetup();
public:
	//=====================================================
	// Setter Functions
	//=====================================================

	// Set Display Windowed
	void SetDisPlayWindowed(bool bWindowed)
	{
		m_EngineSettings.bFullScreen = bWindowed;
	}
	// Set Debug Mode(bool Flag)
	void SetDebugMode(bool bDebug)
	{
		m_EngineSettings.bDebugMode = bDebug;
	}
	// Set Display Pos X
	void SetDisplayPosX(int posX)
	{
		m_EngineSettings.nScreenPosX = posX;
	}
	// Set Display Pos Y
	void SetDisPlayPosY(int posY)
	{
		m_EngineSettings.nScreenPosY = posY;
	}
	// Set Display Width
	void SetDisPlayWidth(int width)
	{
		m_EngineSettings.nScreenWidth = width;
	}
	// Set Display Height
	void SetDisPlayHeight(int height)
	{
		m_EngineSettings.nScreenHeight = height;
	}
	// Set Sound Master Volume
	void SetSoundMasterVolume(int volume)
	{
		m_EngineSettings.fSoundMasterVolume = volume;
	}
	// Set Sound Effect Volume
	void SetSoundEffectVolume(int volume)
	{
		m_EngineSettings.fSoundEffectVolume = volume;
	}
	// Set Sound BGM Volume
	void SetSoundBGMVolume(int volume)
	{
		m_EngineSettings.fSoundBGMVolume = volume;
	}
	// Set Language Key
	void SetLanguage(std::string languageKey)
	{
		m_EngineSettings.strLanguageKey = languageKey;
	}

	//=====================================================
	// Getter Functions
	//=====================================================
	tagEngineSettingInfo GetEngineSettings() const
	{
		return m_EngineSettings;
	}

private: // ENGINE INI SETTING FUNCTIONS
	//=====================================================
	// Engine Setting For EngineSetting.ini
	// - ENGINE SECTION - LOAD
	//  + LOAD : Engine Key
	//=====================================================
	void LoadEngineSection();

	//=====================================================
	// Engine Setting For EngineSetting.ini
	// - DISPLAY SECTION - LOAD
	//  + DISPLAY POS X,Y	(int, int) 
	//	+ DISPLAY SIZE		(int, int) [WIDTH, HEIGHT]
	//	+ DISPLAY WINDOWED	(DEFAULT : FALSE)
	//=====================================================
	void LoadDisplaySection();
	
	//=====================================================
	// Engine Setting For EngineSetting.ini
	// - SOUND SECTION - LOAD
	//  + SOUND MASTER VOLUME (float)
	//  + SOUND EFFECT VOLUME (float)
	//  + SOUND BGM VOLUME (float)
	//=====================================================
	void LoadSoundSection();

	//=====================================================
	// Engine Setting For EngineSetting.ini
	// - DEBUG SECTION - LOAD
	//  + DEBUG SCENE NAME (std::string)
	//=====================================================
	void LoadDebugSection();

	//=====================================================
	// Engine Setting For EngineSetting.ini
	// - LANGUAGE SECTION - LOAD
	//  + Language File Path (std::string)
	//  + 
	//=====================================================
	void LoadLanguageSection();

private: // SAVE SECTION
	//=====================================================
	// Engine Setting For EngineSetting.ini
	// - ENGINE SECTION - SAVE
	//  + Engine Key : Sephy_s01
	//=====================================================
	void SaveEngineSection();
	
	//=====================================================
	// Engine Setting For EngineSetting.ini
	// - DISPLAY SECTION - SAVE
	//  + DISPLAY POS X,Y	(int, int) 
	//  + DISPLAY SIZE		(int, int) [WIDTH, HEIGHT]
	//  + DISPLAY WINDOWED	(DEFAULT : FALSE)
	//=====================================================
	void SaveDisplaySection();

	//=====================================================
	// Engine Setting For EngineSetting.ini
	// - SOUND SECTION - SAVE
	//  + SOUND VOLUME
	//=====================================================
	void SaveSoundSection();

	//=====================================================
	// Engine Setting For EngineSetting.ini
	// - DEBUG SECTION - SAVE
	//  + DEBUG MODE
	//=====================================================
	void SaveDebugSection();

	//=====================================================
	// Engine Setting For EngineSetting.ini
	// - LANGUAGE SECTION - SAVE
	//  + LANGUAGE KEY(Language)
	//  + LANGUAGE FILE PATH
	//=====================================================
	void SaveLanguageSection();
};

#endif // !_ENGINE_SETTING_H
