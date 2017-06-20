#pragma once

#include <string>
#include <map>
#include "singletonBase.h"

class gameNode;

using namespace std;

class sceneManager : public singletonBase<sceneManager>
{
public:
	typedef map<string, gameNode*> mapSceneList;
	typedef mapSceneList::iterator mapSceneIter;

private:
	static gameNode* _currentScene;
	static gameNode* _loadingScene;
	static gameNode* _readyScene;

	mapSceneList _mSceneList;
	mapSceneList _mLoadingSceneList;

	DWORD _loadThreadID;

public:
	sceneManager();
	~sceneManager();

	HRESULT init();
	void release();
	void update();
	void render();

	//씬 추가
	gameNode* addScene(string sceneName, gameNode* scene);

	//로딩씬 추가
	gameNode* addLoadingScene(string loadingSceneName, gameNode* scene);

	//씬 체인지
	HRESULT changeScene(string sceneName);
	HRESULT changeScene(string sceneName, string loadingSceneName);

	//로딩 쓰레드 함수 프렌드 선언
	friend DWORD CALLBACK loadingThread(LPVOID prc);
};

