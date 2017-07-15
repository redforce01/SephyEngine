#include "stdafx.h"
#include "world_Log_UI.h"


CWorld_Log_UI::CWorld_Log_UI()
{
	rect_text = { 0, };
}

CWorld_Log_UI::~CWorld_Log_UI()
{
}

bool CWorld_Log_UI::initialize(Graphics * g, Input * i)
{
	m_pGraphics = g;
	m_pInput = i;

	SystemUIDialog::initializeDialog(m_pGraphics, m_pInput,
		worldlogNS::x,
		worldlogNS::y,
		worldlogNS::viewer_width,
		worldlogNS::viewer_height,
		worldlogNS::MARGIN);

	rect_text = RectMake(
		worldlogNS::x + worldlogNS::distance,
		worldlogNS::y + worldlogNS::distance,
		worldlogNS::text_width, 
		worldlogNS::text_height);
	
	dxFont.initialize(m_pGraphics, worldlogNS::FONT_SIZE, true, false, worldlogNS::FONT);

	//log line is 4
	addMessage("event_log_1", "aa");
	addMessage("event_log_2", "bb");
	addMessage("event_log_3", "cc");
	addMessage("event_log_4", "dd");
	
	return true;;
}

void CWorld_Log_UI::update(float frameTime)
{
	setMessage("event_log_1", "First line event log");
	setMessage("event_log_2", "Second line event log");
	setMessage("event_log_3", "Third line event log");
	setMessage("event_log_4", "Fourth line event log");
}

void CWorld_Log_UI::render()
{
	SystemUIDialog::render();

	m_pGraphics->spriteBegin();

	rect_text.left = worldlogNS::x + worldlogNS::distance + worldlogNS::MARGIN;
	rect_text.top = worldlogNS::y + worldlogNS::distance;
	rect_text.right = rect_text.left + worldlogNS::text_width;
	rect_text.bottom = rect_text.top + worldlogNS::FONT_HEIGHT;

	for (auto iter : m_eventMessage)
	{
		dxFont.print(iter.second, rect_text, DT_VCENTER + DT_LEFT);
		rect_text.top += worldlogNS::FONT_HEIGHT;
		rect_text.bottom += worldlogNS::FONT_HEIGHT;
	}

	m_pGraphics->spriteEnd();
}