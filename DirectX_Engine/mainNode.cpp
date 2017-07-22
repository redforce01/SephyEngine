#include "stdafx.h"
#include "mainNode.h"
#include "scene_Main.h"
#include "scene_Test.h"
#include "scene_MapTool.h"
#include "scene_Battle.h"

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
	SCENEMANAGER->addScene("MapTool", new Scene_MapTool);
	SCENEMANAGER->addScene("Test", new Scene_Test);
	SCENEMANAGER->addScene("Main", new scene_Main);
	SCENEMANAGER->addScene("Battle", new Scene_Battle);
	
	SCENEMANAGER->initialize();
	SCENEMANAGER->changeScene("MapTool");

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
