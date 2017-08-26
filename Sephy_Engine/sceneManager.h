#ifndef _SCENEMANAGER_H
#define _SCENEMANAGER_H

class SceneManager;

#include "cSingletonBase.h"
#include "game.h"
#include <string>
#include <thread>
#include <map>

class SceneManager : public cSingletonBase<SceneManager>
{
protected:
	typedef Game* LP_SCENE;
	typedef std::string KEY_SCENE;
	typedef std::map<KEY_SCENE, LP_SCENE> MAP_SCENE;

private:
	// Manager initialized flag
	// when Manager initialized change true
	bool initialized;

	// SceneChange Loading Flag
	bool isWithLoading;
	
	// Loading std::thread
	std::thread loadingThread;

private:
	LP_SCENE m_pCurrentScene;		// current Update Scene
	LP_SCENE m_pNextScene;			// change next Scene
	LP_SCENE m_pLoadingScene;		// loading Scene
	LP_SCENE m_pReleaseScene;		// release Scene

	MAP_SCENE		   	arrScene;
	MAP_SCENE		   	arrLoadingScene;
	
public:
	SceneManager();
	~SceneManager();

	bool initialize();
	void update();
	void release();
	void addScene(std::string sceneName, Game* pScene);	
	void addLoadingScene(std::string sceneName, Game* pScene);
	
	bool changeScene(std::string sceneName);
	bool changeSceneWithLoading(std::string sceneName, std::string loadingScene);

private:
	static void sceneChangeThreadFunction();

public:
	int getTotalSceneSize() const
	{
		return arrScene.size();
	}

	Game* getCurrentScene() { return m_pCurrentScene; }

	bool getInitialized() { return initialized; }
};

#define SCENEMANAGER SceneManager::GetInstance()
#endif // !_SCENEMANAGER_H