#pragma once

#include "systemUIDialog.h"

namespace worldlogNS
{
	const UINT x = 0;
	const UINT y = WINSIZEY - 193;	//Viewer location

	const UINT viewer_width = 470;
	const UINT viewer_height = 193;

	const UINT text_width = 452;
	const UINT text_height = 165;

	const UINT distance_x = 5;	//(viewer_width - text_width) / 2;
	const UINT distance_y = 8;	//(viewer_height - text_height) / 2;

	const UINT MARGIN = 10;					// text margin from Viewer edge

	const UINT MAX_LINES = 128;
	const char FONT[] = "Courier New";		// Viewer font
	const int FONT_SIZE = 14;
	const int FONT_HEIGHT = 15;				// height of the font in pixels
	const COLOR_ARGB FONT_COLOR = graphicsNS::WHITE;    // color of console text
}

class CWorld_Log_UI : public SystemUIDialog
{
private:
	std::map<std::string, std::string> m_eventMessage;
	Image* img_log;
	RECT rect_text;
	RECT rect_scroll;

	Graphics* m_pGraphics;
	Input* m_pInput;

	std::deque<std::string> w_log_message;       // console text
	UINT scroll_mount;
	UINT line;	//line num

public:
	CWorld_Log_UI();
	~CWorld_Log_UI();

	virtual bool initialize(Graphics* g, Input* i) override;
	virtual void update(float frameTime) override;
	virtual void render() override;

	void print_world_log(const std::string message);
	void scroll();
};