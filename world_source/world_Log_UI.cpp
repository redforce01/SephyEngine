#include "stdafx.h"
#include "world_Log_UI.h"


CWorld_Log_UI::CWorld_Log_UI()
{
	rect_text = { 0, };
	rect_scroll = { 0, };
	scroll_mount = 0;
	line = 0;
	img_log = new Image;
	img_log_top = new Image;
}

CWorld_Log_UI::~CWorld_Log_UI()
{
}

bool CWorld_Log_UI::initialize(Graphics * g, Input * i)
{
	//w_log_message.clear();

	m_pGraphics = g;
	m_pInput = i;

	//SystemUIDialog::initializeDialog(m_pGraphics, m_pInput,
	//	worldlogNS::x,
	//	worldlogNS::y,
	//	worldlogNS::viewer_width,
	//	worldlogNS::viewer_height,
	//	worldlogNS::MARGIN);

	img_log->initialize(g, worldlogNS::viewer_width, worldlogNS::viewer_height, 0, IMAGEMANAGER->getTexture(worldlogNS::img_log));
	img_log->setX(worldlogNS::x);
	img_log->setY(g_fScreenHeight - worldlogNS::y);
	img_log->setColorFilter(graphicsNS::ALPHA50);

	img_log_top->initialize(g, worldlogNS::viewer_width, worldlogNS::viewer_height, 0, IMAGEMANAGER->getTexture(worldlogNS::img_log_top));
	img_log_top->setX(0);
	img_log_top->setY(g_fScreenHeight - worldlogNS::y - worldlogNS::MARGIN);

	rect_scroll = RectMake(worldlogNS::x, g_fScreenHeight - worldlogNS::y, worldlogNS::viewer_width, worldlogNS::viewer_height);

	rect_text = RectMake(
		worldlogNS::x + worldlogNS::distance_x,
		g_fScreenHeight - worldlogNS::y + worldlogNS::distance_y,
		worldlogNS::text_width,
		worldlogNS::text_height);
	
	m_dxFont.initialize(m_pGraphics, worldlogNS::FONT_SIZE, true, false, worldlogNS::FONT);

	return true;;
}

void CWorld_Log_UI::update(float frameTime)
{
	scroll();
}

void CWorld_Log_UI::render()
{
	//SystemUIDialog::render();
	m_pGraphics->spriteBegin();

	img_log->draw();

	rect_text.left = worldlogNS::x + worldlogNS::distance_x + worldlogNS::MARGIN;
	rect_text.right = rect_text.left + worldlogNS::text_width - worldlogNS::MARGIN;
	rect_text.bottom = g_fScreenHeight - worldlogNS::y + worldlogNS::distance_y + worldlogNS::text_height - worldlogNS::MARGIN;

	//line = (worldlogNS::text_height - worldlogNS::MARGIN) / worldlogNS::FONT_HEIGHT;

	if (scroll_mount > worldlogNS::MAX_LINES - worldlogNS::LINE)
		scroll_mount = worldlogNS::MAX_LINES - worldlogNS::LINE;

	for (int i = scroll_mount; i < scroll_mount + worldlogNS::LINE && i < w_log_message.size(); i++)
	{
		rect_text.top = rect_text.bottom - worldlogNS::FONT_HEIGHT;
		m_dxFont.print(w_log_message[i], rect_text, DT_LEFT);
		rect_text.bottom -= worldlogNS::FONT_HEIGHT;
	}

	img_log_top->draw();

	m_pGraphics->spriteEnd();
}

void CWorld_Log_UI::print_world_log(const std::string message)
{
	w_log_message.push_front(message);

	if (w_log_message.size() > worldlogNS::MAX_LINES)
		w_log_message.pop_back();
}

void CWorld_Log_UI::scroll()
{
	if (PtInRect(&rect_scroll, m_pInput->getMousePt()))
	{
		if (m_pInput->isMouseWheelUp())
		{
			scroll_mount++;
			m_pInput->mouseWheelIn(0);

			if (scroll_mount >= w_log_message.size() - worldlogNS::LINE)
				scroll_mount = w_log_message.size() - worldlogNS::LINE;
		}
		if (m_pInput->isMouseWheelDown())
		{
			if (scroll_mount == 0)
				scroll_mount = 0;
			else
				scroll_mount--;

			m_pInput->mouseWheelIn(0);
		}
	}
}
