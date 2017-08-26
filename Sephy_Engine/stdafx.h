// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//

#pragma once
#pragma comment(linker,"/entry:WinMainCRTStartup /subsystem:console")
#pragma comment(lib, "shlwapi")

#include <stdio.h>
#include "targetver.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>


#include <stdio.h>			//���Ĵٵ� ����� ��� ��Ŭ��� (printf, scanf ���)
#include <tchar.h>			//�����쿡�� ����� ���ڿ� ��� ��� ��Ŭ���
							//MBCS (Multi Byte Character Set)
							//->������ ����ϴ� ��Ƽ����Ʈ ������ ���ڿ�
							//WBCS (Wide Byte Character Set)
							//->��� ���ڸ� 2����Ʈ�� ó��. �����ڵ� ���

#include "winnetwk.h"
#include "shlobj.h"

#include <shlwapi.h>
//-----------------------------------------
// Util �� Macro �Լ���
//-----------------------------------------
#include "myUtil.h"
#include "commonMacroFunction.h"

//-----------------------------------------
//���� �Լ��� Ȱ�� �Ǵ� Manager
//-----------------------------------------
#include "fileManager.h"
#include "sceneManager.h"
#include "imageManager.h"
#include "timeManager.h"
#include "layerManager.h"
#include "SoundManager.h"
#include "txtDataParser.h"
#include "randomMaker.h"

//=============================================================================
// Engine System
//=============================================================================
#include "mainNode.h"
#include "engineWindowManager.h"
#include "engineBootLog.h"

// ENGINE System Variables
extern HWND g_hWndEngine;
extern HWND g_hWndGame;
extern HWND g_hWndScene;
extern HINSTANCE g_hInst;
extern MainNode* g_MainNode;
extern Graphics* g_Graphics;
extern Input* g_Input;
extern WNDCLASSEX g_wcx;
extern bool g_EngineShutDown;

//=============================================================================
// Engine Setting Extern Variables
//=============================================================================

// Engine Variables
extern std::string	g_strEngineKey;

// DISPLAY Variables
extern float		g_fWindowPosX;
extern float		g_fWindowPosY;
extern float		g_fScreenWidth;
extern float		g_fScreenHeight;
extern bool			g_bWindowed;

// SOUND Variables
extern float		g_fSoundMasterVolume;
extern float		g_fSoundEffectVolume;
extern float		g_fSoundBGMVolume;

// Debug Variables
extern bool			g_bDebugMode;
extern std::string	g_strDebugSceneName;