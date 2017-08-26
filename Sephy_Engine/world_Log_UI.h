#pragma once

#include "systemUIDialog.h"

namespace worldlogNS
{
	const std::string SOUND_LOG = "Print_Log";

	const std::string img_log = "LogBox";
	const std::string img_log_top = "LogTop";

	const int x = 30;
	const int y = 193;	//Viewer location

	const int viewer_width = 470;
	const int viewer_height = 193;

	const int text_width = 452;
	const int text_height = 165;

	const int distance_x = 5;	//(viewer_width - text_width) / 2;
	const int distance_y = 8;	//(viewer_height - text_height) / 2;

	const int MARGIN = 10;					// text margin from Viewer edge
	const int LINE = 8;		//by top

	const int MAX_LINES = 128;
	const char FONT[] = "Courier New";		// Viewer font
	const int FONT_SIZE = 16;
	const int FONT_HEIGHT = 17;				// height of the font in pixels
	const COLOR_ARGB FONT_COLOR = graphicsNS::WHITE;    // color of console text
}

class CWorld_Log_UI : public SystemUIDialog
{
private:
	Graphics* m_pGraphics;
	Input* m_pInput;

	Image* img_log;
	Image* img_log_top;

	RECT rect_text;
	RECT rect_scroll;

	std::map<std::string, std::string> m_eventMessage;
	std::deque<std::string> w_log_message;       // console text

	int scroll_mount;
	int line;	//line num

public:
	CWorld_Log_UI();
	~CWorld_Log_UI();

	virtual bool initialize(Graphics* g, Input* i) override;
	virtual void update(float frameTime) override;
	virtual void render() override;
	void release();

	std::deque<std::string> get_log_message() { return w_log_message; }

	void print_world_log(const std::string message);
	void scroll();
};