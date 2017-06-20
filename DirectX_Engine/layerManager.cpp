#include "stdafx.h"
#include "layerManager.h"
#include "layer.h"

//=============================================================================
// LayerManager Class Code Start
//=============================================================================
LayerManager::LayerManager()
{
	curLayerState = enLayerList::LAYER_NONE;
}


LayerManager::~LayerManager()
{
	release();
}

HRESULT LayerManager::initialize()
{
	addLayer(LayerManagerNS::none, new Layer(enLayerList::LAYER_NONE));
	addLayer(LayerManagerNS::first, new Layer(enLayerList::LAYER_FIRST));
	addLayer(LayerManagerNS::background, new Layer(enLayerList::LAYER_BACKGROUND));
	addLayer(LayerManagerNS::default, new Layer(enLayerList::LAYER_DEFAULT));
	addLayer(LayerManagerNS::ui, new Layer(enLayerList::LAYER_UI));
	addLayer(LayerManagerNS::last, new Layer(enLayerList::LAYER_LAST));
	
	
	return S_OK;
}

void LayerManager::release()
{
	for (auto iter : layerList)
	{
		if (iter.second == NULL) 
			continue;
		
		SAFE_DELETE(iter.second);
	}
}

void LayerManager::sortLayer()
{
	std::vector<std::pair<std::string, Layer*>> vec(layerList.begin(), layerList.end());

	std::sort(vec.begin(), vec.end(), compare_pair_second<std::less>());

	layerVec = vec;
}

Layer * LayerManager::getLayer(int layerNum)
{
	return layerVec[layerNum].second;
}

Layer * LayerManager::getLayer(enLayerList layerState)
{
	for (auto it : layerVec)
	{
		if (it.second->getLayerState() != layerState)
			continue;

		return it.second;
	}

	return nullptr;
}

void LayerManager::setLayerLoop()
{
	int count = 0;

	count = (int)curLayerState;
	count++;

	count = count % ((int)enLayerList::LAYER_LAST + 1);

	curLayerState = (enLayerList)(count);
}

bool LayerManager::addLayer(std::string layerKey, Layer * layer)
{
	bool success = false;
	
	// if layerKey is meaning none. return false
	if (layerKey.compare(LayerManagerNS::none) == 0)
		return success;	

	//if same layerName value in layerList. return false
	for (auto iter : layerList)
	{
		if (iter.first.compare(layerKey) == 0)
			return success;

	}	

	layerList.emplace(layerKey, layer);
	success = true;

	sortLayer();

	return success;
}

bool LayerManager::deleteLayer(std::string layerKey)
{
	bool success = false;
	for (auto iter : layerList)
	{
		if (iter.first.compare(layerKey) != 0)
			continue;
		
		layerList.erase(layerKey);

		success = true;
		return success;
	}

	return success;
}

void LayerManager::printAllLayer()
{
	printf("=========== Layer List =========== \n");
	if (layerList.size() < 0)
	{
		printf("Layer List Empty \n");
	}

	for (auto iter : layerList)
	{
		enLayerList en = iter.second->getLayerState();

		switch (en)
		{
		case enLayerList::LAYER_NONE:
			printf("Layer State : %s \n", LayerManagerNS::none.c_str());
			break;
		case enLayerList::LAYER_FIRST:
			printf("Layer State : %s \n", LayerManagerNS::first.c_str());
			break;
		case enLayerList::LAYER_BACKGROUND:
			printf("Layer State : %s \n", LayerManagerNS::background.c_str());
			break;
		case enLayerList::LAYER_UI:
			printf("Layer State : %s \n", LayerManagerNS::ui.c_str());
			break;
		case enLayerList::LAYER_DEFAULT:
			printf("Layer State : %s \n", LayerManagerNS::default.c_str());
			break;
		case enLayerList::LAYER_LAST:
			printf("Layer State : %s \n", LayerManagerNS::last.c_str());
			break;
		default:
			printf("Layer State : %s \n", LayerManagerNS::default.c_str());
			break;
		}

	}

}
