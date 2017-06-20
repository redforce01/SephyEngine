#include "stdafx.h"
#include "layer.h"

//=============================================================================
// Layer Class Code Start
//=============================================================================

Layer::Layer(enLayerList layerState)
{
	layer = layerState;
	bRenderSwitch = true;
}

Layer::~Layer()
{
}