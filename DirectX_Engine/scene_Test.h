#pragma once
#include "game.h"
#include "uiButton.h"
#include "uiProgressBar.h"
#include "uiFrame.h"
#include "uiTab.h"
#include "tabContent_A.h"

namespace testNS
{
	const UCHAR ESCAPE_KEY = VK_ESCAPE;
	const UCHAR SCENE_CHANGE_KEY = VK_RETURN;
	const UCHAR UIFRAME_TEST_KEY = 0x31;
	const UCHAR UITAB_TEST_KEY = 0x32;
}

class Scene_Test : public Game
{
private:
	TextureManager* testTexture;
	Image testImage;

	TextureManager* testTexture2;
	Image testImage2;

	UIButton* testButton;
	UIProgressBar* testProgressBar;	
	UITab* tab;
	
public:
	Scene_Test();
	~Scene_Test();

	virtual void initialize(HWND hwnd)	override;
	virtual void update()				override;
	virtual void release()				override;
	virtual void ai()					override;
	virtual void collisions()			override;
	virtual void render()				override;
	virtual void releaseAll()			override;
	virtual void resetAll()				override;

	//test call back function
	static void testFunction(); 
};

