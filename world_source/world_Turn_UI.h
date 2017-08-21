#pragma once

#include "systemUIDialog.h"
#include "systemButton.h"

namespace worldturnNS
{
	const UINT x = 163;	//Viewer location (cur + pass + distance * 2)
	const UINT y = 15;

	const std::string TURN_NAME = "cur-wait-00";
	const UINT TURN_MIN = 1;
	const UINT TURN_MAX = 17;

	const UINT COUNT_LIMIT = 48;	//(17 - 1) * 3 -> �𷡽ð� 3 circle
	const float DELAY = 0.05f;

	const std::string SOUND_TURN = "Turn_End";

	const std::string img_name = "Turn_Button_";	//turn img
	const UINT cur_turn_width = 73;
	const UINT cur_turn_height = 73;
	const COLOR_ARGB CUR_BACKGROUND_COLOR = SETCOLOR_ARGB(192, 26, 32, 44);

	const UINT pass_turn_width = 50;	//100
	const UINT pass_turn_height = 50;	//100

	const UINT distance = 15;

	const UINT MARGIN = 4;					// text margin from Viewer edge

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
	RECT rect_turn;
	RECT rt_pass;

	Graphics* m_pGraphics;
	Input* m_pInput;

	Image* button;
	//SystemButton* button;

	int img_count;

	float turn_delay;
	bool is_turn;
	bool mouse_up;

	bool is_update;
	//std::map<std::string, std::string> m_turnMessage;
	//Image* img_turn;
	void click_event();
	void pass_turn(float frameTime);

public:
	void SetLoadLinkPlayer(CWorld_Player* _player) { player = _player; }

	CWorld_Turn_UI();
	~CWorld_Turn_UI();

	virtual bool initialize(Graphics* g, Input* i) override;
	virtual void update(float frameTime) override;
	virtual void render() override;

	void set_is_update(bool _is) { is_update = _is; }

	//void addMessage(std::string key, std::string message)
	//{
	//	m_turnMessage.emplace(key, message);
	//}
	//void setMessage(std::string key, std::string message)
	//{
	//	m_turnMessage.find(key)->second = message;
	//}
	//void removeMessage(std::string key)
	//{
	//	m_turnMessage.erase(key);
	//}
};

