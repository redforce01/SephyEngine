#include "stdafx.h"
#include "sceneManager.h"
#include "Scene_MapTool.h"
#include "Scene_Battle.h"
#include "Scene_UnitTool.h"
#include "Scene_Intro.h"
#include "Scene_BattleLoading.h"
#include "Scene_BattleResult.h"
#include "world_Scene.h"
#include "lobby_Scene.h"

SceneManager::SceneManager()
	: m_pCurrentScene(nullptr)
	, m_pNextScene(nullptr)
	, m_pLoadingScene(nullptr)
	, m_pReleaseScene(nullptr)
	, isWithLoading(false)
	, initialized(false)
{ 
}


SceneManager::~SceneManager()
{
	loadingThread.join();
	for (auto iter : arrScene)
	{
		SAFE_DELETE(iter.second);
	}
	arrScene.clear();
	for (auto iter : arrLoadingScene)
	{
		SAFE_DELETE(iter.second);
	}
	arrLoadingScene.clear();
}

bool SceneManager::initialize()
{
	return false;
}

void SceneManager::update()
{
	if (m_pReleaseScene != nullptr)
	{
		m_pReleaseScene->release();
		m_pReleaseScene = nullptr;
	}

	if (m_pCurrentScene != nullptr)
	{
		m_pCurrentScene->run(g_hWndEngine);
	}
}

void SceneManager::release()
{
	for (auto iter : arrScene)
	{
		if (iter.second != nullptr)
		{
			iter.second->release();
			iter.second->releaseAll();
			iter.second = nullptr;
		}
	}
}

void SceneManager::addScene(std::string sceneName, Game * pScene)
{
	for (auto iter : arrScene)
	{
		if (iter.first.compare(sceneName) == false)
			return;
	}

	arrScene.try_emplace(sceneName, pScene);
}

void SceneManager::addLoadingScene(std::string sceneName, Game * pScene)
{
	for (auto iter : arrLoadingScene)
	{
		if (iter.first.compare(sceneName) == false)
			return;
	}

	arrLoadingScene.try_emplace(sceneName, pScene);
}

bool SceneManager::changeScene(std::string sceneName)
{
	bool success = false;
	try
	{
		auto iter = arrScene.find(sceneName);
		
		if (iter == arrScene.end())
			return false;

		if (m_pCurrentScene == nullptr)
		{
			m_pCurrentScene = iter->second;
			m_pCurrentScene->initialize(g_hWndEngine);
			success = true;
		}
		else
		{			
			m_pNextScene = iter->second;
			m_pNextScene->initialize(g_hWndEngine);
			m_pReleaseScene = m_pCurrentScene;
			m_pCurrentScene = m_pNextScene;
			
			success = true;
		}
	}
	catch (...)
	{
		MessageBox(g_hWndEngine, "Scene Change Failed", "Error", MB_OK);
	}

	return success;
}

bool SceneManager::changeSceneWithLoading(std::string sceneName, std::string loadingScene)
{
	bool success = false;
	try
	{
		auto iter = arrLoadingScene.find(loadingScene);

		if (iter == arrLoadingScene.end())
			return false;

		m_pLoadingScene = iter->second;
		
		auto iterNextScene = arrScene.find(sceneName);		
		if (iterNextScene == arrScene.end())
			return false;

		m_pNextScene = iterNextScene->second;

		//loadingThread = std::thread([&]() { SceneChangeWithLoading(); });
		loadingThread = std::thread(sceneChangeThreadFunction);
	}
	catch (...)
	{
		MessageBox(g_hWndEngine, "Scene Change Failed", "Error", MB_OK);
	}
}

void SceneManager::sceneChangeThreadFunction()
{
	if (SCENEMANAGER->m_pNextScene == nullptr ||
		SCENEMANAGER->m_pLoadingScene == nullptr)
	{
		return;
	}
	SCENEMANAGER->m_pLoadingScene->initialize(g_hWndEngine);
	SCENEMANAGER->m_pCurrentScene = SCENEMANAGER->m_pLoadingScene;
	SCENEMANAGER->m_pNextScene->initialize(g_hWndEngine);
	SCENEMANAGER->m_pReleaseScene = SCENEMANAGER->m_pCurrentScene;
	SCENEMANAGER->m_pCurrentScene = SCENEMANAGER->m_pNextScene;
}