#include "stdafx.h"
#include "sceneManager.h"


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
}

void SceneManager::update()
{
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

	arrScene.emplace(make_pair(sceneName, pScene));
}

void SceneManager::addLoadingScene(std::string sceneName, Game * pScene)
{
	for (auto iter : arrLoadingScene)
	{
		if (iter.first.compare(sceneName) == false)
			return;
	}

	arrLoadingScene.emplace(make_pair(sceneName, pScene));
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
		m_pLoadingScene->setInitialized(false);

		auto iterNextScene = arrScene.find(sceneName);		
		m_pNextScene = iterNextScene->second;
		m_pNextScene->setInitialized(false);

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
	SCENEMANAGER->m_pCurrentScene = SCENEMANAGER->m_pNextScene;
}