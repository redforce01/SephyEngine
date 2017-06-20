#ifndef _LAYERMANAGER_H
#define _LAYERMANAGER_H

class LayerManager;

#include "cSingletonBase.h"

#include <algorithm>
#include <string>
#include <vector>
#include <map>

class Layer;

//LayerManager enum enLayerList Matched layerName List
namespace LayerManagerNS
{
	const std::string none			= "LAYER_NONE";
	const std::string first			= "LAYER_FIRST";
	const std::string background	= "LAYER_BACKGROUND";
	const std::string default		= "LAYER_DEFAULT";
	const std::string ui			= "LAYER_UI";
	const std::string last			= "LAYER_LAST";
}

//Layer Manager Class has Singleton pattern
class LayerManager : public cSingletonBase<LayerManager>
{
private:
	std::map<std::string, Layer*> layerList;
	std::vector<std::pair<std::string, Layer*>> layerVec;
	enLayerList curLayerState = enLayerList::LAYER_NONE;

public:
	LayerManager();
	~LayerManager();

	//Manager Initialize
	HRESULT initialize();

	// Manager Release
	void release();
	
	// layerList Sorting -> layerVec
	// LayerManager using layerVec
	// Auto Sorting when AddLayer
	void sortLayer();

	//get All Layer Vector
	std::vector<std::pair<std::string, Layer*>> getAllLayer() { return layerVec; }
	
	//get a layer parameter(int layerNum)
	Layer* getLayer(int layerNum);

	//get a Layer parameter(std::string layerName)
	Layer* getLayer(std::string layerName);

	//get a Layer parameter(enum enlayerList)
	Layer* getLayer(enLayerList layerState);

	enLayerList getCurrentLayerState() { return curLayerState; }

	//set currentLayer State
	void setCurrentLayerState(enLayerList layerState) { curLayerState = layerState; }

	void setLayerLoop();

	//add Layer Function
	bool addLayer(std::string layerKey, Layer* layer);

	//delete Layer Function
	bool deleteLayer(std::string layerName);

	void printAllLayer();
};

template<template <typename> class P = std::less >
struct compare_pair_second {
	template<class T1, class T2> bool operator()
		(const std::pair<T1, T2>&left, const std::pair<T1, T2>&right)
	{
		return P<T2>()(left.second, right.second);
	}
};

#define LAYERMANAGER LayerManager::GetInstance()
#endif // !_LAYERMANAGER_H