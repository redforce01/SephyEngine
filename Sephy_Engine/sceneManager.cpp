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

bool SceneManager::initialize()
{
	initialized = false;
	
	if (m_pCurrentScene == nullptr)
	{
		if (arrScene.size() > 0)
		{
			m_pCurrentScene = arrScene.begin()->second;
			m_pCurrentScene->initialize(g_hWndEngine);
			//m_pCurrentScene->initialize(g_hWndScene);
			//m_pCurrentScene->initialize(g_hWndGame);
		}
	}
	
	return initialized;
}

void SceneManager::update()
{
	if (m_pReleaseScene != nullptr)
	{
		m_pReleaseScene->release();
		m_pReleaseScene->releaseAll();
		m_pReleaseScene = nullptr;
	}
		
	if (m_pCurrentScene != nullptr)
	{
		m_pCurrentScene->run(g_hWndEngine);
		//m_pCurrentScene->run(g_hWndScene);
		//m_pCurrentScene->run(g_hWndGame);
	}
}

void SceneManager::render()
{
	if (m_pCurrentScene != nullptr)
	{
		m_pCurrentScene->renderGame();
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
		if (iter.first.compare(sceneName) == 0)
			return;
	}

	arrScene.emplace(make_pair(sceneName, pScene));
}

bool SceneManager::changeScene(std::string sceneName)
{
	bool success = false;

	MAP_SCENE::iterator iter;
	iter = arrScene.find(sceneName);

	if (iter->second == nullptr)
		return false;

	if (m_pCurrentScene == nullptr)
	{
		m_pCurrentScene = iter->second;
		success = true;
		
		return success;
	}
	else
	{
		m_pNextScene = iter->second;
		m_pNextScene->setInitialized(false);
		m_pNextScene->getInput()->clearAll();
		success = true;
		isWithLoading = false;
	}

	// None Thread Function
	if (SCENEMANAGER->m_pNextScene == nullptr)
		return false;

	// Next Scene Initialize + Start
	SCENEMANAGER->m_pNextScene->initialize(g_hWndEngine);
	//SCENEMANAGER->m_pNextScene->initialize(g_hWndScene);
	//SCENEMANAGER->m_pNextScene->initialize(g_hWndGame);

	SCENEMANAGER->m_pReleaseScene = SCENEMANAGER->m_pCurrentScene;
	SCENEMANAGER->m_pCurrentScene = SCENEMANAGER->m_pNextScene;

	//loadingThread = std::thread([&](){ SceneChange(); });

	return success;
}

bool SceneManager::changeScene(std::string sceneName, std::string loadingScene)
{
	bool success = false;

	MAP_SCENE::iterator iter;
	iter = arrLoadingScene.find(loadingScene);


	if (m_pLoadingScene = iter->second)
	{
		m_pLoadingScene->setInitialized(false);
		isWithLoading = true;
	}

	iter = arrScene.find(sceneName);

	if (m_pNextScene = iter->second)
	{		
		m_pNextScene->setInitialized(false);
		success = true;
	}

	if (success && isWithLoading)
	{
		loadingThread = std::thread([&]() { SceneChangeWithLoading(); });
		return true;
	}
	else return false;
}

void SceneManager::SceneChange()
{
	if (SCENEMANAGER->m_pNextScene == nullptr)
		return;

	// Next Scene Initialize + Start
	SCENEMANAGER->m_pNextScene->initialize(g_hWndEngine);
	//SCENEMANAGER->m_pNextScene->initialize(g_hWndScene);
	//SCENEMANAGER->m_pNextScene->initialize(g_hWndGame);
	SCENEMANAGER->m_pReleaseScene = SCENEMANAGER->m_pCurrentScene;
	SCENEMANAGER->m_pCurrentScene = SCENEMANAGER->m_pNextScene;
}

void SceneManager::SceneChangeWithLoading()
{
	if (SCENEMANAGER->m_pNextScene == nullptr ||
		SCENEMANAGER->m_pLoadingScene == nullptr)
	{
		return;
	}
	SCENEMANAGER->m_pLoadingScene->initialize(g_hWndEngine);
	//SCENEMANAGER->m_pLoadingScene->initialize(g_hWndScene);
	//SCENEMANAGER->m_pLoadingScene->initialize(g_hWndGame);
	SCENEMANAGER->m_pReleaseScene = SCENEMANAGER->m_pCurrentScene;
	SCENEMANAGER->m_pCurrentScene = SCENEMANAGER->m_pLoadingScene;

	SCENEMANAGER->m_pNextScene->initialize(g_hWndEngine);
	//SCENEMANAGER->m_pNextScene->initialize(g_hWndScene);
	//SCENEMANAGER->m_pNextScene->initialize(g_hWndGame);
	SCENEMANAGER->m_pCurrentScene = SCENEMANAGER->m_pNextScene;
	SCENEMANAGER->m_pReleaseScene->release();
}