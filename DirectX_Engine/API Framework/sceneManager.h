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

	//�� �߰�
	gameNode* addScene(string sceneName, gameNode* scene);

	//�ε��� �߰�
	gameNode* addLoadingScene(string loadingSceneName, gameNode* scene);

	//�� ü����
	HRESULT changeScene(string sceneName);
	HRESULT changeScene(string sceneName, string loadingSceneName);

	//�ε� ������ �Լ� ������ ����
	friend DWORD CALLBACK loadingThread(LPVOID prc);
};

