#pragma once

#include "systemUIDialog.h"
#include "systemButton.h"

namespace worldturnNS
{
	const int x = 163;	//Viewer location (cur + pass + distance * 2)
	const int y = 15;

	const std::string TURN_NAME = "cur-wait-00";
	const int TURN_MIN = 1;
	const int TURN_MAX = 17;

	const int COUNT_LIMIT = 48;	//(17 - 1) * 3 -> 모래시계 3 circle
	const float DELAY = 0.04f;

	const std::string SOUND_TURN = "Turn_End";

	const std::string img_name = "Turn_Button_";	//turn img
	const int cur_turn_width = 73;
	const int cur_turn_height = 73;
	const COLOR_ARGB CUR_BACKGROUND_COLOR = SETCOLOR_ARGB(192, 26, 32, 44);

	const int pass_turn_width = 50;	//100
	const int pass_turn_height = 50;	//100

	const int distance = 15;

	const int MARGIN = 4;					// text margin from Viewer edge

	const char FONT[] = "Courier New";		// Viewer font
	const int FONT_SIZE = 26;
	const int FONT_HEIGHT = 30;				// height of the font in pixels
	const COLOR_ARGB FONT_COLOR = graphicsNS::WHITE;    // color of console text
}

class CWorld_Player;
class CWorld_Turn_UI : public SystemUIDialog
{
private:
	CWorld_Player* player;

private:
	Graphics* m_pGraphics;
	Input* m_pInput;

	Image* button;

	RECT rect_turn;
	RECT rt_pass;

	float turn_delay;

	int img_count;

	bool is_turn;
	bool is_update;
	bool mouse_up;

	void click_event();
	void pass_turn(float frameTime);

public:
	void SetLoadLinkPlayer(CWorld_Player* _player) { player = _player; }

	CWorld_Turn_UI();
	~CWorld_Turn_UI();

	virtual bool initialize(Graphics* g, Input* i) override;
	virtual void update(float frameTime) override;
	virtual void render() override;
	void release();

	void set_is_update(bool _is) { is_update = _is; }
};

