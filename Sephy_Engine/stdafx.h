// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 및 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once
#pragma comment(linker,"/entry:WinMainCRTStartup /subsystem:console")
#pragma comment(lib, "shlwapi")

#include <stdio.h>
#include "targetver.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>


#include <stdio.h>			//스탠다드 입출력 헤더 인클루드 (printf, scanf 등등)
#include <tchar.h>			//윈도우에서 사용할 문자열 출력 헤더 인클루드
							//MBCS (Multi Byte Character Set)
							//->기존에 사용하던 멀티바이트 형태의 문자열
							//WBCS (Wide Byte Character Set)
							//->모든 문자를 2바이트로 처리. 유니코드 기반

#include "winnetwk.h"
#include "shlobj.h"

#include <shlwapi.h>
//-----------------------------------------
// Util 및 Macro 함수들
//-----------------------------------------
#include "myUtil.h"
#include "commonMacroFunction.h"

//-----------------------------------------
//전역 함수로 활용 되는 Manager
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