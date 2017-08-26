#include "stdafx.h"
#include "world_Event_Log.h"


CWorld_Event_Log::CWorld_Event_Log()
{
	is_show = false;
	mouse_over = false;

	rt_text = { 0, };

	SystemUIDialog::backColor = event_logNS::BACKGROUND_COLOR;
}


CWorld_Event_Log::~CWorld_Event_Log()
{
	message.clear();
}

bool CWorld_Event_Log::initialize(Graphics * g, Input * i)
{
	m_pGraphics = g;
	m_pInput = i;

	SystemUIDialog::initializeDialog(
		g, i, g_fScreenWidth / 2 - event_logNS::WIDTH / 2, g_fScreenHeight / 2 - event_logNS::HEIGHT / 2,
		event_logNS::WIDTH, event_logNS::HEIGHT, event_logNS::MARGIN
	);

	rt_text = RectMake(
		SystemUIDialog::getDialogX() + event_logNS::MARGIN,
		SystemUIDialog::getDialogY() + event_logNS::MARGIN,
		event_logNS::RECT_WIDTH, event_logNS::RECT_HEIGHT
	);

	m_dxFont.initialize(g, event_logNS::FONT_SIZE, false, false, event_logNS::FONT);

	return true;
}

void CWorld_Event_Log::update(float frameTime)
{
	if (is_show == false)
		return;

	if (m_pInput->getMouseLButton())
		mouse_over = true;
	else
	{
		if (mouse_over == true)
		{
			is_show = false;
			message.clear();
		}

		mouse_over = false;
	}
}

void CWorld_Event_Log::render()
{
	if (is_show == false)
		return;

	SystemUIDialog::render();

	m_pGraphics->spriteBegin();

	rt_text.top = SystemUIDialog::getDialogY() + event_logNS::MARGIN;
	rt_text.bottom = rt_text.top + event_logNS::RECT_HEIGHT;

	for (auto iter : message)
	{
		m_dxFont.print(iter, rt_text, DT_VCENTER | DT_CENTER);

		rt_text.top = rt_text.bottom;
		rt_text.bottom = rt_text.top + event_logNS::RECT_HEIGHT;
	}
	m_dxFont.print(event_logNS::END_MSG, rt_text, DT_VCENTER | DT_CENTER);

	m_pGraphics->spriteEnd();
}

void CWorld_Event_Log::release()
{
	message.clear();
}
