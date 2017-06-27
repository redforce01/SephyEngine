#ifndef _LAYER_H
#define _LAYER_H
#define WIN32_LEAN_AND_MEAN

class Layer;

#include "image.h"
#include <vector>

enum class enLayerList {
	LAYER_NONE = 0,
	LAYER_FIRST = 1,
	LAYER_BACKGROUND,
	LAYER_DEFAULT,
	LAYER_UI,
	LAYER_LAST
};

// Layer Class. This Class has Only LayerState Variables
class Layer
{
private:
	enLayerList layer = enLayerList::LAYER_DEFAULT;
	bool bRenderSwitch = TRUE;

public:
	Layer(enLayerList layerState);
	virtual ~Layer();

	//Set layer Function(enLayerList layerState) 
	//This Functions Catch Only <enum enLayerList>
	void setLayerState(enLayerList layerState) { layer = layerState; }

	//Get layer Function return enLayerList Type
	enLayerList getLayerState() { return layer; }

	//Set Switch Function
	//if u want to change render on/off
	//use true/false flag value
	//default value = true
	void setSwitch(bool bLayerSwitch) { bRenderSwitch = bLayerSwitch; }

	//Get bRenderSwitch value
	//default value = true
	bool getSwitch() { return bRenderSwitch; }
};

#endif // !_LAYER_H