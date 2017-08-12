#include "stdafx.h"
#include "uIButton.h"


UIButton::UIButton() : UIParent()
{
	input = NULL;
	nButtonCols = 0;
	buttonState = UIBUTTON_STATE::UIBUTTON_STATE_NONE;
	buttonFunction = nullptr;
}

UIButton::~UIButton()
{
	release();
	releaseAll();
}

bool UIButton::initialize(
	Graphics* pGraphics, Input* pInput, Layer* player,
	bool bNinePatch,
	COLOR_ARGB color, const char* textureName,
	float startX, float startY,
	float width, float height, int cols)
{
	bool success = false;

	try
	{
		input = pInput;
		layer = player;

		nButtonCols = cols;

		spriteData.x = startX;
		spriteData.y = startY;
		spriteData.width = width;
		spriteData.height = height;

		mainStruct.rect = RectMake(startX, startY, width, height);
		mainStruct.bNinePatch = bNinePatch;
		mainStruct.texture = IMAGEMANAGER->getTexture(textureName);

		if (mainStruct.bNinePatch)
			mainStruct.vecNineRect = makeNinePatch(&mainStruct.rect);
		
		colorFilter = color;
		success = Image::initialize(pGraphics, width, height, cols, mainStruct.texture, layer);
	}
	catch (...)
	{
		GameError(gameErrorNS::FATAL_ERROR, "uiButton Initialize Failed");
	}

	return success;
}

void UIButton::release()
{
}

void UIButton::update(float frameTime)
{
	// Click MouseLButton
	if (input->getMouseLButton())
	{
		// Check Keep Button Down State For Do Function Only One Time
		if (buttonState == UIBUTTON_STATE::UIBUTTON_STATE_DOWN)
			return;

		if (PtInRect(&mainStruct.rect, PointMake(input->getMouseX(), input->getMouseY())))
		{
			buttonState = UIBUTTON_STATE::UIBUTTON_STATE_DOWN;
			
			// Do buttonFunction
			if(buttonFunction != NULL)
				buttonFunction();
		}
	}
	// Not Click MouseLButton
	else
	{
		// Mouse Cursor Overlab UIButton Update State
		if (PtInRect(&mainStruct.rect, PointMake(input->getMouseX(), input->getMouseY())))
		{
			buttonState = UIBUTTON_STATE::UIBUTTON_STATE_OVERLAB;
		}
		else
		{
			buttonState = UIBUTTON_STATE::UIBUTTON_STATE_UP;
		}
	}	
}

void UIButton::render()
{
	drawButton();
}

void UIButton::releaseAll()
{
	mainStruct.texture->onLostDevice();
}

void UIButton::resetAll()
{
	mainStruct.texture->onResetDevice();
}

void UIButton::regiFunction(std::function<void()> function)
{
	buttonFunction = function;
}

void UIButton::drawButton()
{
	if (buttonState == UIBUTTON_STATE::UIBUTTON_STATE_UP)
	{
		this->setCurrentFrame(uiButtonNS::frame_ButtonUp);

		Image::draw();
	}
	else if (buttonState == UIBUTTON_STATE::UIBUTTON_STATE_DOWN)
	{
		this->setCurrentFrame(uiButtonNS::frame_ButtonDown);

		Image::draw();
	}
	else if (buttonState == UIBUTTON_STATE::UIBUTTON_STATE_OVERLAB)
	{
		this->setCurrentFrame(uiButtonNS::frame_ButtonOverlab);

		Image::draw();
	}
}