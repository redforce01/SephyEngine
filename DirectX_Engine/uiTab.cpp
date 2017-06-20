#include "stdafx.h"
#include "uiTab.h"


UITab::UITab()
{
	bOpen = false;
	currentTab = 0;
	input = nullptr;
}


UITab::~UITab()
{
	release();
	releaseAll();
}

bool UITab::initialize(
	Graphics* pGraphics, Input* pInput, Layer* pLayer,
	bool bNinePatch, UCHAR tabHotkey,
	COLOR_ARGB color, const char* textureName,
	float startX, float startY,
	float width, float height)
{
	bool success = false;

	try
	{
		hotKey = tabHotkey;
		input = pInput;

		mainStruct.rect = RectMake(startX, startY, width, height);
		mainStruct.texture = IMAGEMANAGER->getTexture(textureName);
		mainStruct.bNinePatch = bNinePatch;
		
		spriteData.x = startX;
		spriteData.y = startY;
		spriteData.width = width;
		spriteData.height = height;

		colorFilter = color;
		success = Image::initialize(pGraphics, width, height, 0, mainStruct.texture, pLayer);
	}
	catch (...)
	{
		GameError(gameErrorNS::INTERFACE_ERROR, "UITab intialize Failed");
	}
	
	return success;
}

bool UITab::addTab(
	std::string tabTitle, UIFrame* tabContents,
	COLOR_ARGB color, const char* iconTexName,
	float startXinTab, float startYinTab,
	float iconWidth, float iconHeight)
{
	bool success = false;

	try
	{
		TabStruct newTab;

		newTab.title = tabTitle;
		newTab.icon = new UIButton;

		if (vecTabs.size() > 0)
		{
			int refPosX = vecTabs.back().icon->getWidth() * vecTabs.size();

			newTab.icon->initialize(graphics, input, layer,
				false, color, iconTexName,
				this->spriteData.x + startXinTab + refPosX, this->spriteData.y + startYinTab,
				iconWidth, iconHeight, 3);
		}
		else
		{
			newTab.icon->initialize(graphics, input, layer,
				false, color, iconTexName,
				this->spriteData.x + startXinTab, this->spriteData.y + startYinTab,
				iconWidth, iconHeight, 3);
		}
		
		newTab.content = tabContents;
		newTab.content->setX(this->spriteData.x + startXinTab);
		newTab.content->setY(this->spriteData.y + startYinTab + iconHeight);
		
		vecTabs.emplace_back(newTab);
		success = true;
	}
	catch (const GameError &err)
	{
		GameError(gameErrorNS::INTERFACE_ERROR, "TabIcon initialize Failed");
	}

	return success;
}

void UITab::update(float frameTime)
{
	if (input->isKeyDown(hotKey))
	{
		bOpen = !bOpen;
	}

	if (bOpen == false)
		return;

	int tabNum = 0;
	if (input->isKeyDown(VK_LBUTTON))
	{
		for (auto iter : vecTabs)
		{
			if (PtInRect(&iter.icon->getMainRect(), PointMake(input->getMouseX(), input->getMouseY())))
			{
				currentTab = tabNum;
				break;
			}

			tabNum++;
		}
	}

	tabNum = 0;
	for (auto iter : vecTabs)
	{
		iter.icon->update(frameTime);

		if(tabNum == currentTab)
			iter.content->update(frameTime);

		tabNum++;
	}
}

void UITab::render()
{
	if (bOpen == false)
		return;
	
	// Tab Background Draw
	Image::draw();
	Image::drawRect();

	// Tab Icon Draw
	int checkTab = 0;
	for (auto iter : vecTabs)
	{
		//current Tab Icon continue for drawing at Last
		if (checkTab == currentTab)
		{
			checkTab++;
			continue;
		}

		iter.icon->render();
		iter.icon->drawRect();
	}
	
	// Selected Current Icon Drawn at Last
	if(vecTabs.size() > 0)
		vecTabs[currentTab].icon->render();

	// Tab Contents Draw Only Current Tab Contents
	checkTab = 0;
	for (auto iter : vecTabs)
	{
		if (checkTab == currentTab)
		{
			iter.content->render();
			iter.content->drawRect();
			break;
		}
		checkTab++;
	}
}

void UITab::release()
{
}

void UITab::releaseAll()
{
	mainStruct.texture->onLostDevice();
}

void UITab::resetAll()
{
	mainStruct.texture->onResetDevice();
}