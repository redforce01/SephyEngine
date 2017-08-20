#include "stdafx.h"
#include "mainNode.h"
#include "Scene_MapTool.h"
#include "Scene_Battle.h"
#include "Scene_UnitTool.h"
#include "Scene_Intro.h"
#include "Scene_BattleLoading.h"
#include "Scene_BattleResult.h"
#include "world_Scene.h"
#include "lobby_Scene.h"

MainNode::MainNode() : initializedMgr(FALSE)
{
}


MainNode::~MainNode()
{
}

HRESULT MainNode::initialize()
{
	//Need Not Hwnd Managers initialize
	TIMEMANAGER->initialize();
	LAYERMANAGER->initialize();

	//Need Hwnd Managers initialize
	IMAGEMANAGER->initialize(g_Graphics);
	SOUNDMANAGER->initialize();
	
	// Create the game, sets up message handler
	SCENEMANAGER->addScene("Intro", new CScene_Intro);
	SCENEMANAGER->addScene("MapTool", new CScene_MapTool);
	SCENEMANAGER->addScene("Battle", new CScene_Battle);
	SCENEMANAGER->addScene("UnitTool", new CScene_UnitTool);
	SCENEMANAGER->addScene("BattleLoading", new CScene_BattleLoading);
	SCENEMANAGER->addScene("BattleResult", new CScene_BattleResult);
	SCENEMANAGER->addScene("World", new CWorld_Scene);
	SCENEMANAGER->addScene("Lobby", new CLobby_Scene);
	SCENEMANAGER->addLoadingScene("BattleLoading", new CScene_BattleLoading);
	
	if (g_bDebugMode)
		SCENEMANAGER->changeScene(g_strDebugSceneName);
	else
		//SCENEMANAGER->changeScene("BattleLoading");
		SCENEMANAGER->changeSceneWithLoading("Intro", "BattleLoading");
	
	return S_OK;
}

void MainNode::release()
{
	SCENEMANAGER->release();
	TIMEMANAGER->release();
	IMAGEMANAGER->release();
	FILEMANAGER->release();
	LAYERMANAGER->release();
	SOUNDMANAGER->release();

	SCENEMANAGER->ReleaseInstance();
	TIMEMANAGER->ReleaseInstance();
	IMAGEMANAGER->ReleaseInstance();
	FILEMANAGER->ReleaseInstance();
	LAYERMANAGER->ReleaseInstance();
	TXTDATA_PARSER->ReleaseInstance();
	RANDOM_MAKER->ReleaseInstance();
	SOUNDMANAGER->ReleaseInstance();
}

void MainNode::update()
{
	//TIMEMANAGER->UpdateTime(mainNodeNS::maxFrameLimit); // Not Using
	SCENEMANAGER->update();
	SOUNDMANAGER->update();
}

LRESULT MainNode::messageHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (SCENEMANAGER->getCurrentScene() == NULL)
	{
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	
	return SCENEMANAGER->getCurrentScene()->messageHandler(hwnd, msg, wParam, lParam);		//SceneManager Proc
}
