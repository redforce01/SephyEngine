#include "stdafx.h"
//#include "sceneManager.h"
//#include "gameNode.h"
//
//gameNode* sceneManager::_currentScene = NULL;
//gameNode* sceneManager::_loadingScene = NULL;
//gameNode* sceneManager::_readyScene = NULL;
//
//DWORD CALLBACK loadingThread(LPVOID prc)
//{
//	//교체될 init 함수를 실행한다
//	sceneManager::_readyScene->init();
//
//	//현재 씬을 교체될 씬으로 바꾼다.
//	sceneManager::_currentScene = sceneManager::_readyScene;
//
//	//로딩씬을 해제 한다.
//	sceneManager::_loadingScene->release();
//	sceneManager::_loadingScene = NULL;
//	sceneManager::_readyScene = NULL;
//
//	return 0;
//}
//
//
//sceneManager::sceneManager()
//{
//}
//
//
//sceneManager::~sceneManager()
//{
//}
//
//HRESULT sceneManager::init()
//{
//	_currentScene = NULL;
//	_loadingScene = NULL;
//	_readyScene = NULL;
//
//	return S_OK;
//}
//
//void sceneManager::release()
//{
//	//맵 전체 돌면서 지우자
//	mapSceneIter miSceneList = _mSceneList.begin();
//
//	for (; miSceneList != _mSceneList.end(); )
//	{
//		//지워지면 반복자를 증가하지 않아야겠지?
//		if (miSceneList->second != NULL)
//		{
//			if (miSceneList->second == _currentScene) miSceneList->second->release();
//			SAFE_DELETE(miSceneList->second);
//			miSceneList = _mSceneList.erase(miSceneList);
//		}
//		else
//		{
//			miSceneList++;
//		}
//	}
//
//	_mSceneList.clear();
//}
//
//void sceneManager::update()
//{
//	if (_currentScene) _currentScene->update();
//}
//
//void sceneManager::render()
//{
//	if (_currentScene) _currentScene->render();
//}
//
//gameNode * sceneManager::addScene(string sceneName, gameNode * scene)
//{
//	if (!scene) return NULL;
//
//	_mSceneList.insert(make_pair(sceneName, scene));
//
//	return scene;
//}
//
//gameNode * sceneManager::addLoadingScene(string loadingSceneName, gameNode * scene)
//{
//	if (!scene) return NULL;
//
//	_mLoadingSceneList.insert(make_pair(loadingSceneName, scene));
//
//	return scene;
//}
//
//HRESULT sceneManager::changeScene(string sceneName)
//{
//	//씬을 바꾸자
//	//바꾸려 하는 씬을 찾자
//	mapSceneIter find = _mSceneList.find(sceneName);
//
//	//바꾸지 못하면 펄스 리턴...
//	if (find == _mSceneList.end()) return E_FAIL;
//
//	//바꾸려하는 씬과 현재씬이 같으면 리턴시키자
//	if (find->second == _currentScene) return S_OK;
//
//	//새롭게 변경되는 씬을 초기화하자
//	if (SUCCEEDED(find->second->init())) //init 성공해서 S_OK 받으면 if 문 안으로 들어온다.
//	{
//		//기존에 씬이 있으면 릴리즈..
//		if (_currentScene) _currentScene->release();
//		_currentScene = find->second;
//
//		return S_OK;
//	}
//
//	return E_FAIL;
//}
//
//HRESULT sceneManager::changeScene(string sceneName, string loadingSceneName)
//{
//	//씬을 바꾸자
//	//바꾸려 하는 씬을 찾자
//	mapSceneIter find = _mSceneList.find(sceneName);
//
//	//바꾸지 못하면 펄스 리턴...
//	if (find == _mSceneList.end()) return E_FAIL;
//
//	//바꾸려하는 씬과 현재씬이 같으면 리턴시키자
//	if (find->second == _currentScene) return S_OK;
//
//	//바꾸려 하는 씬을 찾는다.
//	mapSceneIter findLoading = _mLoadingSceneList.find(loadingSceneName);
//
//	//찾지 못하면 일반 로딩...
//	if (findLoading == _mLoadingSceneList.end()) return changeScene(sceneName);
//
//
//	//새롭게 변경되는 씬을 초기화하자
//	if (SUCCEEDED(findLoading->second->init())) //init 성공해서 S_OK 받으면 if 문 안으로 들어온다.
//	{
//		//기존에 씬이 있으면 릴리즈..
//		if (_currentScene) _currentScene->release();
//
//		//로딩씬
//		_loadingScene = findLoading->second;
//
//		//로딩끝난후 변경될 씬
//		_readyScene = find->second;
//
//		//로딩씬 호출
//		CloseHandle(CreateThread(NULL, 0, loadingThread, NULL, 0, &_loadThreadID));
//
//		return S_OK;
//	}
//
//	return E_FAIL;
//}