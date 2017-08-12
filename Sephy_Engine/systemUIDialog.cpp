#include "stdafx.h"
#include "systemUIDialog.h"


SystemUIDialog::SystemUIDialog()
{
	fontColor = systemUIDialogNS::basicFontColor;
	backColor = systemUIDialogNS::basicBackColor;

	m_pGraphics = nullptr;
	m_pInput = nullptr;
	m_x = m_y = 0;
	m_width = m_height = 0;
	m_margin = 0;
	m_rcBoundingBox = RectMake(0, 0, 0, 0);
	m_bVisible = false;
	m_bInitialized = false;

	m_bMouseOver = false;
	m_bHasFocus = false;
	m_bDrawBorder = true;
}


SystemUIDialog::~SystemUIDialog()
{
}

bool SystemUIDialog::initializeDialog(Graphics * g, Input * i, int x, int y, int w, int h, int m)
{
	bool success = false;

	try
	{
		if (g == nullptr || i == nullptr)
			return false;
		
		m_x = x;
		m_y = y;
		m_width = w;
		m_height = h;
		m_margin = m;
		m_pGraphics = g;
		m_pInput = i;
		m_rcBoundingBox = RectMake(x, y, w, h);
		success = vertexSetup(x, y, w, h);
		m_bVisible = true;
		m_bInitialized = true;
	}
	catch (...)
	{
		MessageBox(g_hWndEngine, "SystemUIDialog Initialize Failed", "Error", MB_OK);
	}
	
	return success;
}

void SystemUIDialog::update(float frameTime)
{
	if (m_bVisible == false || m_bInitialized == false)
		return;

	if (PtInRect(&m_rcBoundingBox, m_pInput->getMousePt()))
		m_bMouseOver = true;
	else
		m_bMouseOver = false;

	if (m_pInput->getMouseLButton() || m_pInput->getMouseRButton())
	{
		if (PtInRect(&m_rcBoundingBox, m_pInput->getMousePt()))
			m_bHasFocus = true;
		else
			m_bHasFocus = false;
	}
}

void SystemUIDialog::render()
{
	if (m_bVisible == false || m_bInitialized == false)
		return;

	m_pGraphics->drawQuad(vertexBuffer);

	if(m_bDrawBorder)
		m_pGraphics->drawRect(m_rcBoundingBox);
}

bool SystemUIDialog::vertexSetup(int x, int y, int w, int h)
{
	// top left
	vtx[0].x = x;
	vtx[0].y = y;
	vtx[0].z = 0.0f;
	vtx[0].rhw = 1.0f;
	vtx[0].color = backColor;

	// top right
	vtx[1].x = x + w;
	vtx[1].y = y;
	vtx[1].z = 0.0f;
	vtx[1].rhw = 1.0f;
	vtx[1].color = backColor;

	// bottom right
	vtx[2].x = x + w;
	vtx[2].y = y + h;
	vtx[2].z = 0.0f;
	vtx[2].rhw = 1.0f;
	vtx[2].color = backColor;

	// bottom left
	vtx[3].x = x;
	vtx[3].y = y + h;
	vtx[3].z = 0.0f;
	vtx[3].rhw = 1.0f;
	vtx[3].color = backColor;

	if (m_pGraphics->createVertexBuffer(vtx, sizeof vtx, vertexBuffer) == S_OK)
		return true;

	return false;
}
