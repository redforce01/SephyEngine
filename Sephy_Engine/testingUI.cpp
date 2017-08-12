#include "stdafx.h"
#include "testingUI.h"


testingUI::testingUI()
{
	m_hasFocus = false;
}


testingUI::~testingUI()
{
}

bool testingUI::initialize(Game * gamePtr)
{	
	m_pGraphics = gamePtr->getGraphics();
	m_pInput = gamePtr->getInput();
	m_rcUI = RectMake(600, 200, 100, 100);
	return false;
}

void testingUI::update(float frameTime)
{
	if (PtInRect(&m_rcUI, m_pInput->getMousePt()))
	{
		m_hasFocus = true;
	}
	else
		m_hasFocus = false;
}

void testingUI::render()
{
	m_pGraphics->drawRect(m_rcUI, 3.0f, graphicsNS::BROWN);
}
