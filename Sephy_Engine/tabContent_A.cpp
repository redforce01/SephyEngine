#include "stdafx.h"
#include "tabContent_A.h"




tabContent_A::tabContent_A()
{
}

tabContent_A::~tabContent_A()
{
	release();
	releaseAll();
}

bool tabContent_A::initialize(
	Graphics * pGraphics, Input * pInput, Layer * pLayer,
	COLOR_ARGB color, const char * textureName,
	float startX, float startY, float width, float height)
{
	bool success = false;

	try
	{
		success = UIFrame::initialize(pGraphics, pInput, pLayer, false, color, textureName, startX, startY, width, height);
	}
	catch (...)
	{
		GameError(gameErrorNS::INTERFACE_ERROR, "tabContent_A initialize Failed");
	}

	return success;
}

void tabContent_A::update(float frameTime)
{
	UIFrame::update(frameTime);	
}

void tabContent_A::render()
{
	UIFrame::render();	
}

void tabContent_A::release()
{
	UIFrame::release();
	return;
}

void tabContent_A::releaseAll()
{	
	UIFrame::releaseAll();
	return;
}

void tabContent_A::resetAll()
{
	UIFrame::resetAll();
	return;
}
