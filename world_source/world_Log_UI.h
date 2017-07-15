#pragma once

#include "systemUIDialog.h"

namespace worldlogNS
{
	const UINT x = 15;
	const UINT y = WINSIZEY - 225;	//Viewer location

	const UINT viewer_width = 560;
	const UINT viewer_height = 210;

	const UINT text_width = 530;
	const UINT text_height = 180;

	const UINT distance = 15;

	const UINT MARGIN = 4;					// text margin from Viewer edge
	const UINT LIMIT_LINE = 4;				// line limit

	const char FONT[] = "Courier New";		// Viewer font
	const int FONT_SIZE = 27;
	const int FONT_HEIGHT = 45;				// height of the font in pixels
	const COLOR_ARGB FONT_COLOR = graphicsNS::WHITE;    // color of console text
}

class CWorld_Log_UI : public SystemUIDialog
{
private:
	std::map<std::string, std::string> m_eventMessage;
	RECT rect_text;

	Graphics* m_pGraphics;
	Input* m_pInput;

public:
	CWorld_Log_UI();
	~CWorld_Log_UI();

	virtual bool initialize(Graphics* g, Input* i) override;
	virtual void update(float frameTime) override;
	virtual void render() override;

	void addMessage(std::string key, std::string message)
	{
		m_eventMessage.emplace(key, message);
	}
	void setMessage(std::string key, std::string message)
	{
		m_eventMessage.find(key)->second = message;
	}
	void removeMessage(std::string key)
	{
		m_eventMessage.erase(key);
	}
};