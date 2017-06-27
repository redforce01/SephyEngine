#include "stdafx.h"
#include "systemUIDialog.h"


SystemUIDialog::SystemUIDialog()
{
	pGraphics = nullptr;
	pInput = nullptr;
	m_x = m_y = 0;
	m_width = m_height = 0;
	m_margin = 0;
	m_rc = RectMake(0, 0, 0, 0);
	fontColor = systemUIDialogNS::basicFontColor;
	backColor = systemUIDialogNS::basicBackColor;
	m_bMouseOver = false;
}


SystemUIDialog::~SystemUIDialog()
{
}

bool SystemUIDialog::initialize(Graphics * g, Input * i, int x, int y, int w, int h, int m)
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
		pGraphics = g;
		pInput = i;
		m_rc = RectMake(x, y, w, h);			
		success = vertexSetup(x, y, w, h);		
	}
	catch (...)
	{
		MessageBox(g_hWndEngine, "SystemUIDialog Initialize Failed", "Error", MB_OK);
	}
	
	return success;
}

void SystemUIDialog::update(float frameTime)
{
	if (pInput->getMouseLButton())
	{
		if (PtInRect(&m_rc, PointMake(pInput->getMouseX(), pInput->getMouseY())))
		{
			m_bMouseOver = true;
		}
		else
			m_bMouseOver = false;
	}
}

void SystemUIDialog::render()
{
	pGraphics->drawQuad(vertexBuffer);
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

	if (pGraphics->createVertexBuffer(vtx, sizeof vtx, vertexBuffer) == S_OK)
		return true;

	return false;
}
