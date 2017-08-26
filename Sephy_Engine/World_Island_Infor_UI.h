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

	const int ICON_WIDTH = 24;
	const int ICON_HEIGHT = 24;

	const std::string SOUND_SAVE = "Save";
	const std::string SOUND_SELECT = "Select";
	const std::string SOUND_BUILD = "Build";
	const std::string SOUND_CANCEL = "Cancel";
	const std::string SOUND_CLOSE = "Close";

	const int WIDTH = 500;	//1200
	const int HEIGHT = 600;
	const int RESOURCE_WIDTH = 100;
	const int RESOURCE_HEIGHT = 30;

	const int MARGIN = 10;

	//number img infor
	const std::string IMG_NUMBER = "Score";
	const int IMG_NUMBER_WIDTH = 9;		//Score -> Image Size
	const int IMG_NUMBER_HEIGHT = 13;

	//exit infor
	const int EXIT_WIDTH = 55;
	const int EXIT_HEIGHT = 30;
	const float EXIT_WEIGHT = 2.0f;
	const COLOR_ARGB EXIT_COLOR = graphicsNS::RED;

	//destroy infor
	const std::string DESTROY_IMG = "Destroy_Overlap";
	const int DESTROY_WIDTH = 150;		//185
	const int DESTROY_HEIGHT = 150;	//185
	const COLOR_ARGB DESTROY_COLOR = SETCOLOR_ARGB(180, 255, 255, 255);

	//building img infor
	const int MAX_BUILDING = 3;
	const int BUILDING_WIDTH = 150;	//185
	const int BUILDING_HEIGHT = 150;	//185

	//margin between building img & unit (all sum create building img margin)
	const int MID_MARGIN = 545;
	const COLOR_ARGB BORDER_COLOR = graphicsNS::BLUE;

	//research & unit infor
	const int MAX_BOX = 6;
	const int BOX_WIDTH = 80;
	const int BOX_HEIGHT = 80;

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
	void destroy_button_render(int _index);

public:
	void SetLoadLinkIsland(CWorld_Player* _player) { player = _player; }

	CWorld_Island_Infor_UI();
	~CWorld_Island_Infor_UI();

	virtual bool initialize(Graphics* g, Input* i) override;
	virtual void update(float frameTime) override;
	virtual void render() override;

	bool get_show() { return is_show; }

	void set_building(int _index, CBuilding* _building);
	void replace_number_img(RECT rect, int _number);
	void save();	//save & close ui
	void w_move_rl(float _speed);
};
