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
	const std::string FULLSCREEN_KEY = "Windowed";
	//=======================================================
	// SOUND SETTING
	const std::string SOUND_SECTION = "Sound";
	const std::string SOUND_VOLUME_KEY = "SoundVolume";
	//=======================================================
	// DEBUG SETTING
	const std::string DEBUG_SECTION = "Debug";
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
	const BOOL WINDOWED = FALSE;
	const BOOL DEBUGED = FALSE;
	const std::string LANGUAGE = "English";
	const std::string MODE = "Tool";
	const std::string LANGUAGE_PATH = "Resources\\Language\\English.txt";
	const float DEFAULT_VOLUME = 1.0f;
}

class EngineSetting
{
private:
	std::string m_strSystemPath;	// ENGINE INI SYSTEM PATH
	std::string m_strEngineKey;		// ENGINE SECTION : EngineKey

private: // DEBUG SECTION
	bool m_bDebugMode;

private: // DISPLAY SECTION
	bool m_bFullScreen;
	int m_nScreenWidth;
	int m_nScreenHeight;
	int m_nScreenPosX;
	int m_nScreenPosY;

private: // SOUND SECTION
	float m_fSoundVolume;

private: // Custom Path Vector For FILE SYSTEM
	std::vector<std::string> m_vCustomPath;

public:
	EngineSetting();
	~EngineSetting();

	// ENGINE INI SETTING LOAD FUNCTION
	void LoadEngineSetting();
	// ENGINE INI SETTING SAVE FUNCTION
	void SaveEngineSetting();
public:
	//=====================================================
	// Setter Functions
	//=====================================================

	// Set Debug Mode(bool Flag)
	void SetDebugMode(bool bDebug)
	{
		m_bDebugMode = bDebug;
	}
	// Set Display Pos X
	void SetDisplayPosX(int posX)
	{
		m_nScreenPosX = posX;
	}
	// Set Display Pos Y
	void SetDisPlayPosY(int posY)
	{
		m_nScreenPosY = posY;
	}
	// Set Display Width
	void SetDisPlayWidth(int width)
	{
		m_nScreenWidth = width;
	}
	// Set Display Height
	void SetDisPlayHeight(int height)
	{
		m_nScreenHeight = height;
	}
	// Set Display Windowed
	void SetDisPlayWindowed(bool bWindowed)
	{
		m_bFullScreen = bWindowed;
	}

	//=====================================================
	// Getter Functions
	//=====================================================

private: // ENGINE INI SETTING FUNCTIONS
	//=====================================================
	// Engine Setting For EngineSetting.ini
	// - ENGINE SECTION
	//  + LOAD : Engine Key
	//=====================================================
	void LoadEngineSection();


	//=====================================================
	// Engine Setting For EngineSetting.ini
	// - ENGINE SECTION
	//  + Engine Key : Sephy_s01
	//=====================================================
	void SaveEngineSection();
	
	//=====================================================
	// Engine Setting For EngineSetting.ini
	// - DISPLAY SECTION
	//  + DISPLAY POS X,Y
	//  + DISPLAY SIZE(WIDTH, HEIGHT)
	//  + DISPLAY WINDOWED (DEFAULT : FALSE)
	//=====================================================
	void SaveDisplaySection();

	//=====================================================
	// Engine Setting For EngineSetting.ini
	// - SOUND SECTION
	//  + SOUND VOLUME
	//=====================================================
	void SaveSoundSection();

	//=====================================================
	// Engine Setting For EngineSetting.ini
	// - DEBUG SECTION
	//  + DEBUG MODE
	//=====================================================
	void SaveDebugSection();

	//=====================================================
	// Engine Setting For EngineSetting.ini
	// - LANGUAGE SECTION
	//  + LANGUAGE KEY(Language)
	//  + LANGUAGE FILE PATH
	//=====================================================
	void SaveLanguageSection();
};

#endif // !_ENGINE_SETTING_H
