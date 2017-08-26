#pragma once

#include "systemUIDialog.h"
#include "building.h"
#include "production_Ship.h"

namespace world_ship_buyNS
{
	const UINT MARGIN = 10;

	const UINT WIDTH = 300;
	const UINT HEIGHT = 250;

	const UINT RT_WIDTH = 280;
	const UINT RT_HEIGHT = 40;

	const UINT KIND_RESOURCE = 4;

	const COLOR_ARGB BACK_COLOR = graphicsNS::GRAY;    // color of console text

													   //number img infor
	const std::string IMG_NUMBER = "Score";
	const UINT IMG_NUMBER_WIDTH = 9;		//Score -> Image Size
	const UINT IMG_NUMBER_HEIGHT = 13;

	const char FONT[] = "Courier New";		// Viewer font
	const int FONT_SIZE = 20;
	const int FONT_HEIGHT = 22;				// height of the font in pixels
	const COLOR_ARGB FONT_COLOR = graphicsNS::WHITE;    // color of console text
}

class CWorld_Player;
class CWorld_Ship_Buy_Infor : public SystemUIDialog
{
private :
	CWorld_Player* player;

private :
	CProduction_Ship* ship;
	Graphics* m_pGraphics;
	Input* m_pInput;
	TextDX m_dxFont;

	std::vector<Image*> list_number;

	RECT rt_name;
	RECT rt_turn;
	RECT rt_resource[world_ship_buyNS::KIND_RESOURCE];

public:
	void SetLoadLinkPlayer(CWorld_Player* _player) { player = _player; }

	CWorld_Ship_Buy_Infor();
	~CWorld_Ship_Buy_Infor();

	virtual bool initialize(Graphics* g, Input* i) override;
	virtual void update(float frameTime) override;
	virtual void render() override;

	void replace_number_img(RECT rect, int _number);
	void set_ship(CProduction_Ship* _ship) { ship = _ship; }
	void buy_draw();

	void w_move_rl(float _speed);
};

