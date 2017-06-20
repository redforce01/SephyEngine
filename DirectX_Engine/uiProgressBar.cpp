#include "stdafx.h"
#include "uiProgressBar.h"


UIProgressBar::UIProgressBar() : UIParent()
{
	barMaxGauge = 0;
	barCurrentGauge = 0;
	bHasBack = false;
	barType = UIPROGRESSBAR_TYPE::UIPROGRESSBAR_DEFAULT;
}


UIProgressBar::~UIProgressBar()
{
	release();
	releaseAll();
}

bool UIProgressBar::initialize(
	UIPROGRESSBAR_TYPE type,
	const char * textureName,
	bool ninePatch, COLOR_ARGB color,
	float maxGauge, float currentGauge,
	float startX, float startY, float width, float height)
{
	bool success = false;

	barType = type;
	barMaxGauge = maxGauge;
	barCurrentGauge = currentGauge;

	spriteData.x = startX;
	spriteData.y = startY;
	spriteData.width = width;
	spriteData.height = height;
	colorFilter = color;

	barTexture = IMAGEMANAGER->getTexture(textureName);

	if (bar.initialize(g_Graphics, 0, 0, 0, barTexture) == false)
	{
		throw(GameError(gameErrorNS::INTERFACE_ERROR, "barTexture Load Failed"));
		return false;
	}
		
	mainStruct.bNinePatch = ninePatch;

	success = true;

	return success;
}

bool UIProgressBar::initialize(
	UIPROGRESSBAR_TYPE type,
	const char * textureName, const char * backTextureName,
	bool ninePatch, COLOR_ARGB color,
	float maxGauge, float currentGauge,
	float startX, float startY, float width, float height)
{
	bool success = false;

	try
	{
		bHasBack = true;

		barType = type;
		barMaxGauge = maxGauge;
		barCurrentGauge = currentGauge;

		spriteData.x = startX;
		spriteData.y = startY;
		spriteData.width = width;
		spriteData.height = height;
		colorFilter = color;

		barTexture = IMAGEMANAGER->getTexture(textureName);
		backTexture = IMAGEMANAGER->getTexture(backTextureName);

		if (bar.initialize(g_Graphics, 0, 0, 0, barTexture) == false)
		{
			throw(GameError(gameErrorNS::INTERFACE_ERROR, "ProgressBar barTexture Load Failed"));
			return false;
		}

		if (background.initialize(g_Graphics, 0, 0, 0, backTexture) == false)
		{
			throw(GameError(gameErrorNS::INTERFACE_ERROR, "ProgressBar BackTexture Load Failed"));
			return false;
		}

		mainStruct.bNinePatch = ninePatch;

		bar.setX(spriteData.x);
		bar.setY(spriteData.y);
		background.setX(spriteData.x);
		background.setY(spriteData.y);

		success = true;
	}
	catch (...)
	{
		GameError(gameErrorNS::INTERFACE_ERROR, "ProgressBar Initialize Failed");
	}	

	return success;
}

void UIProgressBar::update(float frameTime)
{
	float ratio = (barCurrentGauge / barMaxGauge) * 100;
	float currentWidth = spriteData.width * (ratio / 100);
	
	bar.setWidth(currentWidth);
	bar.setRect();
}

void UIProgressBar::render()
{
	if (barCurrentGauge <= 0)
		return;

	if (bHasBack)
		background.draw();

	bar.draw();
}

void UIProgressBar::release()
{
}

void UIProgressBar::releaseAll()
{
	mainStruct.texture->onLostDevice();
	barTexture->onLostDevice();
	backTexture->onLostDevice();
}

void UIProgressBar::resetAll()
{
	mainStruct.texture->onResetDevice();
	barTexture->onResetDevice();
	backTexture->onResetDevice();
}

void UIProgressBar::setGauge(float currentGauge)
{
	barCurrentGauge = currentGauge;
}
