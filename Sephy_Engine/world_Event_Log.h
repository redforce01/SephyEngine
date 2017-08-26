#pragma once

#include "systemUIDialog.h"

namespace event_logNS
{
	const int WIDTH = 200;
	const int HEIGHT = 80;
	const COLOR_ARGB BACKGROUND_COLOR = SETCOLOR_ARGB(192, 26, 32, 44);

	const std::string END_MSG = "Any Click";
	const int RECT_WIDTH = 180;
	const int RECT_HEIGHT = 20;

	const int MARGIN = 10;

	const char FONT[] = "Courier New";		// Viewer font
	const int FONT_SIZE = 16;
	const int FONT_HEIGHT = 17;				// height of the font in pixels
	const COLOR_ARGB FONT_COLOR = graphicsNS::WHITE;    // color of console text
}

class CWorld_Event_Log : public SystemUIDialog
{
private :
	Graphics* m_pGraphics;
	Input* m_pInput;
	TextDX m_dxFont;

	RECT rt_text;

	int type;

	bool is_show;
	bool mouse_over;

	std::vector<std::string> message;

public:
	CWorld_Event_Log();
	~CWorld_Event_Log();

	virtual bool initialize(Graphics* g, Input* i) override;
	virtual void update(float frameTime) override;
	virtual void render() override;
	void release();

	void set_message(std::vector<std::string> _message)
	{
		message = _message; 
		is_show = true;
	}
	void set_is_show(bool _is) { is_show = _is; }
	void set_type(int _type) { type = _type; }

	bool get_is_show() { return is_show; }
};

