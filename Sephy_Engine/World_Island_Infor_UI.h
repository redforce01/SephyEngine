#pragma once

#include "systemUIDialog.h"
#include "world_Island_Infor_Build_UI.h"
#include "world_Island_Infor_Unit_UI.h"

//780 x 185
namespace world_island_inforNS
{
	const COLOR_ARGB BACKGROUND_COLOR = SETCOLOR_ARGB(255, 26, 32, 44);

	const std::string MONEY = "Money";	//resource img * 4
	const std::string IRON = "Iron";
	const std::string FUEL = "Fuel";
	const std::string RESEARCH = "Research";

	const UINT ICON_WIDTH = 24;
	const UINT ICON_HEIGHT = 24;

	const std::string SOUND_SAVE = "Save";
	const std::string SOUND_SELECT = "Select";
	const std::string SOUND_BUILD = "Build";
	const std::string SOUND_CANCEL = "Cancel";
	const std::string SOUND_CLOSE = "Close";

	const UINT WIDTH = 500;	//1200
	const UINT HEIGHT = 600;
	const UINT RESOURCE_WIDTH = 100;
	const UINT RESOURCE_HEIGHT = 30;

	const UINT MARGIN = 10;

	//number img infor
	const std::string IMG_NUMBER = "Score";
	const UINT IMG_NUMBER_WIDTH = 9;		//Score -> Image Size
	const UINT IMG_NUMBER_HEIGHT = 13;

	//exit infor
	const UINT EXIT_WIDTH = 55;
	const UINT EXIT_HEIGHT = 30;
	const float EXIT_WEIGHT = 2.0f;
	const COLOR_ARGB EXIT_COLOR = graphicsNS::RED;

	//destroy infor
	const std::string DESTROY_IMG = "Destroy_Overlap";
	const UINT DESTROY_WIDTH = 150;		//185
	const UINT DESTROY_HEIGHT = 150;	//185
	const COLOR_ARGB DESTROY_COLOR = SETCOLOR_ARGB(180, 255, 255, 255);

	//building img infor
	const UINT MAX_BUILDING = 3;
	const UINT BUILDING_WIDTH = 150;	//185
	const UINT BUILDING_HEIGHT = 150;	//185

	//margin between building img & unit (all sum create building img margin)
	const UINT MID_MARGIN = 545;
	const COLOR_ARGB BORDER_COLOR = graphicsNS::BLUE;

	//research & unit infor
	const UINT MAX_BOX = 6;
	const UINT BOX_WIDTH = 80;
	const UINT BOX_HEIGHT = 80;

	const char FONT[] = "Courier New";		// Viewer font
	const int FONT_SIZE = 17;
	const int FONT_HEIGHT = 20;				// height of the font in pixels
	const COLOR_ARGB FONT_COLOR = graphicsNS::WHITE;    // color of console text
}

class CWorld_Player;
class CWorld_Island_Infor_UI : public SystemUIDialog
{
private:
	CWorld_Player* player;
	CWorld_Island_Infor_Build_UI* build[world_island_inforNS::MAX_BUILDING];	//Mid UI
	CWorld_Island_Infor_Unit_UI* unit[world_island_inforNS::MAX_BUILDING];		//Mid UI
	CBuilding* building[world_island_inforNS::MAX_BUILDING];
	
	Graphics* m_pGraphics;
	Input* m_pInput;
	TextDX m_dxFont;

	//show resource
	//RECT rt_title;
	RECT rt_vertex;
	RECT rt_money;
	RECT rt_iron;
	RECT rt_fuel;
	RECT rt_research;

	//event
	RECT rt_exit;	//save & close ui
	RECT rt_destroy[world_island_inforNS::MAX_BUILDING];	//building destroy

	//after replace building img
	RECT rt_building[world_island_inforNS::MAX_BUILDING];
	RECT rt_box_border;
	RECT rt_build_border;
	//RECT rt_box_border[world_island_inforNS::MAX_BUILDING];
	//RECT rt_build_border[world_island_inforNS::MAX_BUILDING];	//가장 우측 이동시키기
	//RECT rt_box[world_island_inforNS::MAX_BUILDING][world_island_inforNS::MAX_BOX];

	std::vector<Image*> list_number;
	std::vector<Image*> building_image;
	std::vector<Image*> img_list;

	int cur_building;

	bool is_show;
	bool mouse_up;
	bool is_destroy[world_island_inforNS::MAX_BUILDING];

	void rect_initialize();

	void resource_render();
	void exit_button_render();
	void destroy_button_render(UINT _index);

public:
	void SetLoadLinkIsland(CWorld_Player* _player) { player = _player; }

	CWorld_Island_Infor_UI();
	~CWorld_Island_Infor_UI();

	virtual bool initialize(Graphics* g, Input* i) override;
	virtual void update(float frameTime) override;
	virtual void render() override;

	void set_building(int _index, CBuilding* _building);
	void replace_number_img(RECT rect, UINT _number);

	void save();	//save & close ui

	bool get_show() { return is_show; }

	//void w_move_ud(float _speed);
	void w_move_rl(float _speed);
};
