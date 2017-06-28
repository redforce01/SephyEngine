#include "stdafx.h"
#include "systemUIScroll.h"


SystemUIScroll::SystemUIScroll()
{
	m_type = SCROLL_TYPE::SCROLL_TYPE_VERTICAL;
	m_bShowThumb = false;
	m_bDrag = false;
	m_nPosition = 0;
	m_nStart = 0;
	m_nEnd = 0;
	POINT m_LastMouse;
	ARROWSTATE m_Arrow;
}


SystemUIScroll::~SystemUIScroll()
{
}

bool SystemUIScroll::initScroll(Graphics* g, Input* i, int controlID, SystemUIDialog* pDialog, SCROLL_TYPE type,
	int scrollX, int scrollY, int scrollWidth, int scrollHeight)
{
	m_pGraphics = g;
	m_pInput = i;
	m_type = type;
	return SystemUIControl::initControl(controlID, SYSTEM_UI_TYPES::UI_TYPE_SCROLLBAR, pDialog, false, scrollX, scrollY, scrollWidth, scrollHeight, 0);
}

void SystemUIScroll::update(float frameTime)
{
	SystemUIControl::update(frameTime);


}

void SystemUIScroll::render()
{
	SystemUIControl::render();


}
