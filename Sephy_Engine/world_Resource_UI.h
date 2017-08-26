#pragma once

#include "systemUIDialog.h"
#include "world_Resource_Detail.h"

namespace worldresourceNS
{
	const int num = 4;

	const int x = 10;	//Viewer location
	const int y = 10;

	const std::string MONEY = "Money";	//resource img * 4
	const std::string IRON = "Iron";
	const std::string FUEL = "Fuel";
	const std::string RESEARCH = "Research";
	const int icon_width = 24;
	const int icon_height = 24;

	const std::string img_name = "Resource";
	const int img_width = 183;
	const int img_height = 24;
	
	const std::string img_save = "Score";
	const int num_save_width = 9;		//Score -> Image Size
	const int num_save_height = 13;
	const int save_width = 60;
	const int save_height = 15;	//y position + 2

	const std::string img_increase = "AW";
	const int num_increase_width = 7;		//NumT -> Image Size
	const int num_increase_height = 11;
	const int increase_width = 50;
	const int increase_height = 15;	//y position + 1

	const int distance_x = 15;
	const int distance_y = 9;

	const int MARGIN = 10;					// text margin from Viewer edge

	const char FONT[] = "Courier New";		// Viewer font
	const int FONT_SIZE = 16;
	const COLOR_ARGB FONT_COLOR = graphicsNS::WHITE;    // color of console text
}

class CWorld_Player;
class CWorld_Resource_UI : public SystemUIDialog
{
private :
	CWorld_Player* player;

private:
	CWorld_Resource_Detail* resource_detail;

	Graphics*	m_pGraphics;
	Input*		m_pInput;
	TextDX m_dxfont;

	Image* img_resource[worldresourceNS::num];
	Image* icon_resource[worldresourceNS::num];

	RECT rect_save[worldresourceNS::num];
	RECT rect_increase[worldresourceNS::num];

	std::vector<Image*> list_number;

	int increase_resource[worldresourceNS::num];
	int decrease_resource[worldresourceNS::num];

	void resource_initialize(int index, std::string img);
	void calcu_resource();

public:
	void SetLoadLinkPlayer(CWorld_Player* _player) { player = _player; }

	CWorld_Resource_UI();
	~CWorld_Resource_UI();

	virtual bool initialize(Graphics* g, Input* i) override;
	virtual void update(float frameTime) override;
	virtual void render() ;
	void release();

	void replace_number_img(RECT rect, int _resource, bool big);
	RECT get_rect_increase(int _index) { return rect_increase[_index]; }
};

