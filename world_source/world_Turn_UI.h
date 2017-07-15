#pragma once

#include "systemUIDialog.h"

namespace worldturnNS
{
	const UINT x = WINSIZEX - 273;	//Viewer location (cur + pass + distance * 2)
	const UINT y = 15;

	const std::string img_name = "ExitButton";	//turn img
	const UINT cur_turn_width = 73;
	const UINT cur_turn_height = 73;

	const UINT pass_turn_width = 170;
	const UINT pass_turn_height = 170;

	const UINT distance = 15;

	const UINT MARGIN = 4;					// text margin from Viewer edge

	const char FONT[] = "Courier New";		// Viewer font
	const int FONT_SIZE = 26;
	const int FONT_HEIGHT = 30;				// height of the font in pixels
	const COLOR_ARGB FONT_COLOR = graphicsNS::WHITE;    // color of console text
}

class CWorld_Turn_UI : public SystemUIDialog
{
private:
	std::map<std::string, std::string> m_turnMessage;
	RECT rect_turn;

	Graphics* m_pGraphics;
	Input* m_pInput;

	Image* img_turn;

public:
	CWorld_Turn_UI();
	~CWorld_Turn_UI();

	virtual bool initialize(Graphics* g, Input* i) override;
	virtual void update(float frameTime) override;
	virtual void render() override;

	void addMessage(std::string key, std::string message)
	{
		m_turnMessage.emplace(key, message);
	}
	void setMessage(std::string key, std::string message)
	{
		m_turnMessage.find(key)->second = message;
	}
	void removeMessage(std::string key)
	{
		m_turnMessage.erase(key);
	}
};

