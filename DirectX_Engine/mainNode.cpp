#include "stdafx.h"
#include "mainNode.h"
#include "Scene_MapTool.h"
#include "Scene_Battle.h"
#include "Scene_UnitTool.h"

MainNode::MainNode() : initializedMgr(FALSE)
{
}


MainNode::~MainNode()
{
}

HRESULT MainNode::initialize()
{
	//Need Not Hwnd Managers initialize
	//FILEMANAGER->initialize();
	TIMEMANAGER->initialize();
	LAYERMANAGER->initialize();

	//Need Hwnd Managers initialize
	IMAGEMANAGER->initialize(g_Graphics);
	
	// Create the game, sets up message handler
	//game = new scene_Main;	
	SCENEMANAGER->addScene("MapTool", new CScene_MapTool);
	SCENEMANAGER->addScene("Battle", new CScene_Battle);
	SCENEMANAGER->addScene("UnitTool", new CScene_UnitTool);
	
	SCENEMANAGER->initialize();

	if (g_bDebugMode)
		SCENEMANAGER->changeScene(g_strDebugSceneName);
	else
		SCENEMANAGER->changeScene("UnitTool");

	return S_OK;
}

void MainNode::release()
{
	SCENEMANAGER->release();
	TIMEMANAGER->release();
	IMAGEMANAGER->release();
	FILEMANAGER->release();
	LAYERMANAGER->release();
}

void MainNode::update()
{
	//TIMEMANAGER->UpdateTime(mainNodeNS::maxFrameLimit); // Not Using
	SCENEMANAGER->update();
}

void MainNode::render()
{
	SCENEMANAGER->render();
}

LRESULT MainNode::messageHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (SCENEMANAGER->getCurrentScene() == NULL)
	{
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	
	return SCENEMANAGER->getCurrentScene()->messageHandler(hwnd, msg, wParam, lParam);		//SceneManager Proc
}
