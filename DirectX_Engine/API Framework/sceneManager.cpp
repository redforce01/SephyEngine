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
//	//��ü�� init �Լ��� �����Ѵ�
//	sceneManager::_readyScene->init();
//
//	//���� ���� ��ü�� ������ �ٲ۴�.
//	sceneManager::_currentScene = sceneManager::_readyScene;
//
//	//�ε����� ���� �Ѵ�.
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
//	//�� ��ü ���鼭 ������
//	mapSceneIter miSceneList = _mSceneList.begin();
//
//	for (; miSceneList != _mSceneList.end(); )
//	{
//		//�������� �ݺ��ڸ� �������� �ʾƾ߰���?
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
//	//���� �ٲ���
//	//�ٲٷ� �ϴ� ���� ã��
//	mapSceneIter find = _mSceneList.find(sceneName);
//
//	//�ٲ��� ���ϸ� �޽� ����...
//	if (find == _mSceneList.end()) return E_FAIL;
//
//	//�ٲٷ��ϴ� ���� ������� ������ ���Ͻ�Ű��
//	if (find->second == _currentScene) return S_OK;
//
//	//���Ӱ� ����Ǵ� ���� �ʱ�ȭ����
//	if (SUCCEEDED(find->second->init())) //init �����ؼ� S_OK ������ if �� ������ ���´�.
//	{
//		//������ ���� ������ ������..
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
//	//���� �ٲ���
//	//�ٲٷ� �ϴ� ���� ã��
//	mapSceneIter find = _mSceneList.find(sceneName);
//
//	//�ٲ��� ���ϸ� �޽� ����...
//	if (find == _mSceneList.end()) return E_FAIL;
//
//	//�ٲٷ��ϴ� ���� ������� ������ ���Ͻ�Ű��
//	if (find->second == _currentScene) return S_OK;
//
//	//�ٲٷ� �ϴ� ���� ã�´�.
//	mapSceneIter findLoading = _mLoadingSceneList.find(loadingSceneName);
//
//	//ã�� ���ϸ� �Ϲ� �ε�...
//	if (findLoading == _mLoadingSceneList.end()) return changeScene(sceneName);
//
//
//	//���Ӱ� ����Ǵ� ���� �ʱ�ȭ����
//	if (SUCCEEDED(findLoading->second->init())) //init �����ؼ� S_OK ������ if �� ������ ���´�.
//	{
//		//������ ���� ������ ������..
//		if (_currentScene) _currentScene->release();
//
//		//�ε���
//		_loadingScene = findLoading->second;
//
//		//�ε������� ����� ��
//		_readyScene = find->second;
//
//		//�ε��� ȣ��
//		CloseHandle(CreateThread(NULL, 0, loadingThread, NULL, 0, &_loadThreadID));
//
//		return S_OK;
//	}
//
//	return E_FAIL;
//}