#ifndef _TABCONTENT_H
#define _TABCONTENT_H

class tabContent_A;

#include "uiFrame.h"

class tabContent_A : public UIFrame
{
private:


public:
	tabContent_A();
	~tabContent_A();

	bool initialize(
		Graphics* pGraphics, Input* pInput, Layer* pLayer,
		COLOR_ARGB color, const char* textureName,
		float startX, float startY, float width, float height);

	void update(float frameTime) override;
	void render() override;

	void release() override;
	void releaseAll() override;
	void resetAll() override;
};



#endif // !_TABCONTENT_H
