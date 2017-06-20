#include "stdafx.h"
#include "uiFrame.h"

//=============================================================================
// default constructor
//=============================================================================
UIFrame::UIFrame() : UIParent()
{
	layer = NULL;
	input = NULL;
	bFrameSelected = false;
	frameSelectPosX = 0;
	frameSelectPosY = 0;
}

//=============================================================================
// destructor
//=============================================================================
UIFrame::~UIFrame()
{
	release();
	releaseAll();
}

//=============================================================================
// UIFrame initializer
// receive All Parameter send Image::initialize
//=============================================================================
bool UIFrame::initialize(
	Graphics* pGraphics, Input* pInput, Layer* player,
	bool bNinePatch,
	COLOR_ARGB color, const char* textureName,
	float startX, float startY,
	float width, float height)
{
	bool success = false;
	try
	{
		graphics = pGraphics;
		input = pInput;
		layer = player;

		spriteData.x = startX;
		spriteData.y = startY;

		spriteData.width = width;
		spriteData.height = height;
		
		mainStruct.rect = RectMake(startX, startY, width, height);
		mainStruct.bNinePatch = bNinePatch;
		mainStruct.texture = IMAGEMANAGER->getTexture(textureName);
		
		frameTitleWidth = width;
		frameTitleHeight = uiFrameNS::FRAME_TITLE_S_HEIGHT;
		frameTitleRect = RectMake(spriteData.x, spriteData.y, frameTitleWidth, frameTitleHeight);

		if (mainStruct.bNinePatch)
			mainStruct.vecNineRect = makeNinePatch(&mainStruct.rect);
		
		colorFilter = color;
		success = Image::initialize(graphics, 0, 0, 0, mainStruct.texture, layer);
	}
	catch (...)
	{
		GameError(gameErrorNS::FATAL_ERROR, "uiFrame Initialize Failed");
	}
	
	return success;
}

//=============================================================================
// UIFrame Update
//=============================================================================
void UIFrame::update(float frameTime)
{
	//check Clicked UIFrame Title
	if (input->getMouseLButton())
	{
		if(PtInRect(&frameTitleRect, PointMake(input->getMouseX(), input->getMouseY())))
		{
			bFrameSelected = true;
		}
	}
	else if (false == input->getMouseLButton())
	{
		// Save Mouse Position in TitleRect before Selected
		if (PtInRect(&frameTitleRect, PointMake(input->getMouseX(), input->getMouseY())))
		{
			frameSelectPosX = frameTitleRect.right - input->getMouseX();
			frameSelectPosY = frameTitleRect.bottom - input->getMouseY();
		}
		bFrameSelected = false;
	}

	// UIFrame Title Click ? true = Move UIFrame
	if (bFrameSelected)
	{
		spriteData.x = input->getMouseX() - frameSelectPosX;
		spriteData.y = input->getMouseY() - frameSelectPosY;
	}

	mainStruct.rect = RectMake(spriteData.x, spriteData.y, spriteData.width, spriteData.height);
	frameTitleRect = RectMake(spriteData.x, spriteData.y, frameTitleWidth, frameTitleHeight);

	if (mainStruct.bNinePatch)
		mainStruct.vecNineRect = makeNinePatch(&mainStruct.rect);
}

void UIFrame::render()
{
	drawFrame();
}

void UIFrame::release()
{
}

void UIFrame::releaseAll()
{
	mainStruct.texture->onLostDevice();
}

void UIFrame::resetAll()
{
	mainStruct.texture->onResetDevice();
}

//=============================================================================
// UIFrame DrawFrame
// Layer State == Current Layer State ? draw : return
// check visible == TRUE || graphics != NULL
// check NinePatch Value
//=============================================================================
void UIFrame::drawFrame()
{
	//if using NinePatch Draw with FrameRectVec
	if (mainStruct.bNinePatch)
	{
		// 나인패치 존나 구현해야됨. 미친듯이 작업해야할듯...
		// 근데 하기싫음...나중에 하자 xD

	}
	//not using NinePatch. just Draw Texture
	else
	{
		Image::draw();
	}		
}

//=============================================================================
// Set This UIFrame Position
//=============================================================================
void UIFrame::setFrame(float startX, float startY, float width, float height)
{
	spriteData.x = startX;
	spriteData.y = startY;
	spriteData.width = width;
	spriteData.height = height;

	this->frameTitleWidth = width;
}
