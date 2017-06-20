#ifndef _UIBUTTON_H				// Prevent multiple definitions if this 
#define _UIBUTTON_H				// file is included in more than one place
#define WIN32_LEAN_AND_MEAN

class UIButton;

#include "uiParent.h"
#include <functional>

enum class UIBUTTON_STATE
{
	UIBUTTON_STATE_NONE,
	UIBUTTON_STATE_DOWN,
	UIBUTTON_STATE_UP,
	UIBUTTON_STATE_OVERLAB
};

namespace uiButtonNS
{
	const int frame_ButtonUp		= 0;	//UIBUTTON UP FRAME
	const int frame_ButtonDown		= 1;	//UIBUTTON DOWN FRAME
	const int frame_ButtonOverlab	= 2;	//UIBUTTON OVERLAB FRAME
}

class UIButton : public UIParent
{
private:
	int						nButtonCols;
	Input*					input;
	UIBUTTON_STATE			buttonState;
	std::function<void()>	buttonFunction;

public:
	UIButton();
	~UIButton();

	bool initialize(
		Graphics* g, Input* pInput, Layer* player,
		bool bNinePatch,
		COLOR_ARGB color, const char* textureName,
		float startX, float startY,
		float width, float height, int cols);
		
	void update(float frameTime) override;
	void render() override;

	void release() override;
	void releaseAll() override;
	void resetAll() override;

	void regiFunction(std::function<void()> function);
	void drawButton();

};

#endif // !_UIFRAME_H
