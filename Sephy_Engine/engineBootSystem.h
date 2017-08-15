#ifndef _ENGINEBOOTSYSTEM_H
#define _ENGINEBOOTSYSTEM_H
#define WIN32_LEAN_AND_MEAN

class EngineBootSystem;

#include <thread>
#include <vector>
#include "graphics.h"
#include "engineSetting.h"

namespace engineBootSystemNS
{
	const UINT BOOTSYSTEM_SCREEN_WIDTH	= 600;
	const UINT BOOTSYSTEM_SCREEN_HEIGHT = 450;
	const std::string BOOTSYSTEM_IMAGE_FILEPATH = "Resources\\00_Engine\\Engine_BootScreen.bmp";
	const char CLASS_NAME[] = "Sephy_Engine_BootSystem";
	//============================================================
	const UINT BOOTLOG_BOX_X = 30;
	const UINT BOOTLOG_BOX_Y = 430;
	const UINT BOOTLOG_BOX_WIDTH = 500;
	const UINT BOOTLOG_BOX_HEIGHT = 20;
	//============================================================
	const char			FONT[] = "Courier New";
	const int			FONT_HEIGHT = 14;
	const COLOR_ARGB	FONT_COLOR = graphicsNS::BLACK;
}

class EngineBootSystem
{
private:
	bool bEngineBooted;
	HWND hWndBootSystem;

	Graphics* bootGraphics;
	TextureManager bootTexture;
	Image bootImage;

	TextDX dxFont;
	RECT rcLog;

	EngineSetting* engineSetting;
	tagEngineSettingInfo m_EngineSettingInfo;
	
	std::thread bootThread;
public:
	EngineBootSystem();
	~EngineBootSystem();

	//====================================================
	// Engine Boot System Initialize
	//  + Call Create Boot Window
	//  + Connect Boot Procedure
	//====================================================
	void BootSystemInitialize(HINSTANCE hInst, int nCmdShow);

	//====================================================
	// Engine Boot System Running Function
	//  + Loop Update For Engine Log Print
	//====================================================
	int BootSystemRun();
	
	//====================================================
	// Engine Boot Carete Window Function
	//  + Engine Logo Window Create
	//====================================================
	bool CreateMainWindow(HWND &, HINSTANCE, int);

	//====================================================
	// Engine Boot Window Procedure
	//====================================================
	LRESULT EngineProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);

	//====================================================
	// Engine Boot Function - static void function
	//  + Work On Boot Thread
	//====================================================
	static void EngineBoot();

	bool GetBootFinish() const
	{ 
		return bEngineBooted; 
	}

	HWND GetBootSystemHandle() const
	{
		return hWndBootSystem;
	}
};

#endif // !_ENGINEBOOTSYSTEM_H
