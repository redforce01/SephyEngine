#include "stdafx.h"
#include "gameObjectManager.h"


GameObjectManager::GameObjectManager()
{
}


GameObjectManager::~GameObjectManager()
{
}

GameObject * GameObjectManager::beginIteration()
{
	if (goContainer.size() <= 0)
		return nullptr;
	
	goContainerIter = goContainer.begin();

	return goContainer.begin()->second;
}

GameObject * GameObjectManager::nextIteration()
{
	if (++goContainerIter == goContainer.end())
		return nullptr;

	return goContainerIter->second;
}


