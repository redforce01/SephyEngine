#include "stdafx.h"
#include "systemUIControl.h"
#include "systemUIDialog.h"

SystemUIControl::SystemUIControl()
{
	m_x = m_y = 0;
	m_width = m_height = 0;
	m_margin = 0;
	m_nControlID = 0;
	m_Type = SYSTEM_UI_TYPES::UI_TYPE_BUTTON;
	m_State = SYSTEM_UI_CONTROL_STATE::UI_CONTROL_STATE_NORMAL;
	m_bInitialized = false;
	m_bVisible = true;
	m_bMouseOver = false;
	m_bEnabled = false;
	m_bHasFocus = false;
	m_bHasParent = false;
	m_bUseBackground = false;
	m_pInput = nullptr;
	m_pGraphics = nullptr;
}


SystemUIControl::~SystemUIControl()
{
}

bool SystemUIControl::initControl(int controlID, SYSTEM_UI_TYPES type, bool bUseBack,
	int x, int y, int w, int h, int m)
{
	bool success = false;
	try
	{
		m_nControlID = controlID;
		m_Type = type;
		m_x = x;
		m_y = y;
		m_width = w;
		m_height = h;
		m_margin = m;
		m_bUseBackground = bUseBack;
		m_rcBoundingBox = RectMake(m_x, m_y, m_width, m_height);
		m_bInitialized = success = vertexSetUp(m_x, m_y, m_width, m_height);
	}
	catch (...)
	{
		MessageBox(g_hWndEngine, "SystemUIControl Initialize Failed", "Error", MB_OK);
	}

	return success;
}

bool SystemUIControl::initControl(int controlID, SYSTEM_UI_TYPES type, SystemUIDialog * pParent, bool bUseBack,
	int x, int y, int w, int h, int m)
{
	bool success = false;
	try
	{
		m_pDialog = pParent;
		m_nControlID = controlID;
		m_Type = type;
		m_x = x + pParent->getDialogPos().x + pParent->getDialogMargin();
		m_y = y + pParent->getDialogPos().y + pParent->getDialogMargin();
		m_width = w - pParent->getDialogMargin();
		m_height = h - pParent->getDialogMargin();
		m_margin = m;
		m_bUseBackground = bUseBack;
		m_rcBoundingBox = RectMake(m_x, m_y + m_margin, m_width, m_height);
		m_bHasParent = true;
		m_bInitialized = success = vertexSetUp(m_x, m_y, m_width, m_height);
	}
	catch (...)
	{
		MessageBox(g_hWndEngine, "SystemUIControl Initialize Failed", "Error", MB_OK);
	}

	return success;
}

void SystemUIControl::update(float frameTime)
{
	if (m_bVisible == false || m_bInitialized == false)
		return;

	if (m_State == SYSTEM_UI_CONTROL_STATE::UI_CONTROL_STATE_HIDDEN ||
		m_State == SYSTEM_UI_CONTROL_STATE::UI_CONTROL_STATE_DISABLED)
		return;
	
	if (ContainsPoint(m_pInput->getMousePt()))
		if (m_pInput->getMouseLButton())
		{
			m_State = SYSTEM_UI_CONTROL_STATE::UI_CONTROL_STATE_PRESSED;
		}
		else
		{
			m_State = SYSTEM_UI_CONTROL_STATE::UI_CONTROL_STATE_MOUSEOVER;
		}
	else
	{
		m_State = SYSTEM_UI_CONTROL_STATE::UI_CONTROL_STATE_NORMAL;
	}
}

void SystemUIControl::render()
{
	if (m_bVisible == false || m_bInitialized == false)
		return;

	if (m_pGraphics == nullptr)
		return;

	if(m_bUseBackground)
		m_pGraphics->drawQuad(vertexBuffer);
}

bool SystemUIControl::vertexSetUp(int x, int y, int w, int h)
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
