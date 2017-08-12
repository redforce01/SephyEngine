#ifndef _GAMEOBJECTMANAGER_H
#define _GAMEOBJECTMANAGER_H

class GameObjectManager;

#include "gameObject.h"
#include <map>

class GameObjectManager
{
private:
	typedef std::map<go_id_type, GameObject*> MAP_GO;

	MAP_GO				goContainer;
	MAP_GO::iterator	goContainerIter;

public:
	GameObjectManager();
	~GameObjectManager();

	GameObject* beginIteration();
	GameObject* nextIteration();

	void addGameObject(GameObject* go) { goContainer.emplace(go->getID(), go); }
};

#endif // !_GAMEOBJECTMANAGER_H
