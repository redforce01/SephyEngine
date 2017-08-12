#ifndef _UIFRAME_H			// Prevent multiple definitions if this 
#define _UIFRAME_H			// file is included in more than one place
#define WIN32_LEAN_AND_MEAN

class UIFrame;

#include "uiParent.h"

namespace uiFrameNS
{
	const float FRAME_TITLE_S_HEIGHT = 20.f;
	const float FRAME_TITLE_M_HEIGHT = 30.f;
	const float FRAME_TITLE_H_HEIGHT = 40.f;
}

class UIFrame : public UIParent
{
protected:
	RECT				frameTitleRect;
	float				frameTitleWidth;
	float				frameTitleHeight;


	bool				bFrameSelected;		// default value = false
	float				frameSelectPosX;	// selectPositionX in TitleRect
	float				frameSelectPosY;	// selectPositionY in TitleRect

	Input*				input;

private:


public:
	UIFrame();
	~UIFrame();


	// uiFrame initialize
	// g : Graphics Pointer
	// input : Input Pointer
	// layer : Layer Pointer
	// bNinePatch : bool value for using NinePatch Draw
	// color : for COLOR_FILTER
	// textureName : using TextureName for Image
	// startX = frameX, startY = frameY, width = frameWidth, height = frameHeight
	bool initialize(
		Graphics* pGraphics, Input* pInput, Layer* layer,
		bool bNinePatch,
		COLOR_ARGB color, const char* textureName,
		float startX, float startY,
		float width, float height
	);

	void update(float frameTime) override;
	void render() override;

	void release() override;
	void releaseAll() override;
	void resetAll() override;

	void drawFrame();

	//uiFrame Position & width/height value Change function
	void setFrame(float startX, float startY, float width, float height);

	//uiFrame frameSelected value Setter
	void setSelected(bool flag) { bFrameSelected = flag; }
};

#endif
