#ifndef _UITAB_H
#define _UITAB_H
#define WIN32_LEAN_AND_MEAN

class UITab;

#include "input.h"
#include "uiParent.h"
#include "uiFrame.h"
#include "uiButton.h"
#include <string>
#include <vector>

struct TabStruct
{
	std::string title;
	UIButton* icon;
	UIFrame* content;
};

namespace uiTabNS
{
	const int tabBtwWidth = 10;		// TAB Back.Left Between First Icon Distance
	const int tabBtwHeight = 10;	// TAB Back.Top Between First Icon Distance
}

class UITab : public UIParent
{
private:
	std::vector<TabStruct> vecTabs;
	int currentTab;
	bool bOpen;

	UCHAR hotKey;

	Input* input;
public:
	UITab();
	~UITab();

	bool initialize(
		Graphics* pGraphics, Input* pInput, Layer* pLayer,
		bool bNinePatch, UCHAR tabHotkey,
		COLOR_ARGB color, const char* textureName,
		float startX, float startY,
		float width, float height
	);

	bool addTab(
		std::string tabTitle, UIFrame* tabContents,
		COLOR_ARGB color, const char* iconTexName,
		float startXinTab, float startYinTab,
		float iconWidth, float iconHeight);

	void update(float frameTime) override;
	void render() override;

	void release() override;
	void releaseAll() override;
	void resetAll() override;

};

#endif // !_UITAB_H