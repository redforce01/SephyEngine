#ifndef _ENGINESYSTEM_H
#define _ENGINESYSTEM_H

class EngineSystem;

// Parent Engine Core
#include "engineCore.h"

// Engine System Utilities
#include "mainNode.h"
#include "engineError.h"
#include "engineInput.h"
#include "engineMenebar.h"

// Engine System Interface Header List
#include "engineSceneView.h"
#include "engineInspectorView.h"
#include "engineResourceView.h"
#include "engineSetting.h"
#include "engineBootSystem.h"

class EngineSystem : public EngineCore
{
private:	
	EngineInput* pEngineInput;				// Engine Input
	EngineMenuBar engineMenubar;			// Engine MainWindow Menubar

	// Engine System Interface List
	EngineSceneView* engineSceneView;
	EngineInspectorView* engineInspectorView;
	EngineResourceView* engineResourceView;

private:
	EngineBootSystem engineBootSystem;	// Engine Boot System
	EngineSetting* engineSetting;
	tagEngineSettingInfo m_EngineSettingInfo;

public:
	EngineSystem();
	~EngineSystem();

	bool engineStart(HINSTANCE hInstance, int nCmdShow) override;
	int run() override;
	
	bool CreateMainWindow(HWND &, HINSTANCE, int);	
	LRESULT EngineProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
};

#endif // !_ENGINESYSTEM_H
