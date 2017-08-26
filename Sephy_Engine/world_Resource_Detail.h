#pragma once

#include "building.h"
#include "systemUIDialog.h"

namespace world_resource_detailNS
{
	const int KIND_RESOURCE = 4;
	const int WIDTH = 150;
	const int HEIGHT = 50;

	const int RT_WIDTH = 130;
	const int RT_HEIGHT = 20;

	const int MARGIN = 10;

	//number img infor
	const std::string IMG_NUMBER = "Score";
	const int IMG_NUMBER_WIDTH = 9;		//Score -> Image Size
	const int IMG_NUMBER_HEIGHT = 13;

	const char FONT[] = "Courier New";		// Viewer font
	const int FONT_SIZE = 17;
	const int FONT_HEIGHT = 19;				// height of the font in pixels
	const COLOR_ARGB FONT_COLOR = graphicsNS::WHITE;    // color of console text
}

class CWorld_User;
class CWorld_Resource_UI;
class CWorld_Resource_Detail : public SystemUIDialog
{
private:
	CWorld_User* user;
	CWorld_Resource_UI* ui;

	Graphics* m_pGraphics;
	Input* m_pInput;
	TextDX m_dxFont;

	RECT rt_increase;
	RECT rt_decrease;

	std::vector<Image*> list_number;

	E_RESOURCE type;

	bool is_over;

public:
	void SetLoadLinkPlyaer(CWorld_User* _user) { user = _user; }
	void SetLoadLinkUI(CWorld_Resource_UI* _ui) { ui = _ui; }

	CWorld_Resource_Detail();
	~CWorld_Resource_Detail();

	virtual bool initialize(Graphics* g, Input* i) override;
	virtual void update(float frameTime) override;
	virtual void render() override;
	void release();

	void replace_number_img(RECT rect, int _number);
};

