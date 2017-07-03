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
	
	POINT m_LastMouse = { 0, 0 };
	ARROWSTATE m_Arrow = ARROWSTATE::CLEAR;

	backColor = systemUIScrollNS::TRACK_COLOR;
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

	

	if (m_type == SCROLL_TYPE::SCROLL_TYPE_VERTICAL)
	{
		m_rcUpButton = RectMake(scrollX, scrollY, scrollWidth, scrollHeight * systemUIScrollNS::SCROLL_BUTTON_RATE);
		m_rcDownButton = RectMake(scrollX, scrollY + scrollHeight - (scrollHeight * systemUIScrollNS::SCROLL_BUTTON_RATE),
			scrollWidth, scrollHeight * systemUIScrollNS::SCROLL_BUTTON_RATE);
		m_rcTrack = RectMake(scrollX, scrollY + scrollHeight * systemUIScrollNS::SCROLL_BUTTON_RATE,
			scrollWidth, scrollHeight - (scrollHeight * systemUIScrollNS::SCROLL_BUTTON_RATE));
		m_rcThumb = RectMake(scrollX, scrollY + scrollHeight * systemUIScrollNS::SCROLL_BUTTON_RATE,
			scrollWidth, scrollHeight * systemUIScrollNS::SCROLL_BUTTON_RATE);
	}
	else if (m_type == SCROLL_TYPE::SCROLL_TYPE_HORIZONTAL)
	{
		m_rcUpButton = RectMake(scrollX, scrollY, scrollWidth * systemUIScrollNS::SCROLL_BUTTON_RATE, scrollHeight);
		m_rcDownButton = RectMake(scrollX + scrollWidth * systemUIScrollNS::SCROLL_BUTTON_RATE, scrollHeight,
			scrollWidth - (scrollWidth * systemUIScrollNS::SCROLL_BUTTON_RATE), scrollHeight);
		m_rcTrack = RectMake(m_rcUpButton.right, m_rcUpButton.top, scrollWidth - 2 * (m_rcUpButton.right - m_rcUpButton.left), scrollHeight);
		m_rcThumb = RectMake(m_rcTrack.left, m_rcTrack.top, scrollWidth * systemUIScrollNS::SCROLL_BUTTON_RATE, scrollHeight);
	}

	

	return SystemUIControl::initControl(controlID, SYSTEM_UI_TYPES::UI_TYPE_SCROLLBAR, pDialog, true, scrollX, scrollY, scrollWidth, scrollHeight, 0);
}

void SystemUIScroll::update(float frameTime)
{
	SystemUIControl::update(frameTime);

	if (m_pInput->getMouseLButton())
	{
		if (PtInRect(&m_rcUpButton, m_pInput->getMousePt()))
		{
			
		}

		if (PtInRect(&m_rcDownButton, m_pInput->getMousePt()))
		{

		}
		
		if (PtInRect(&m_rcTrack, m_pInput->getMousePt()))
		{

		}
	}
}

void SystemUIScroll::render()
{
	SystemUIControl::render();


}

void SystemUIScroll::capture()
{

}

void SystemUIScroll::updateThumb()
{

}