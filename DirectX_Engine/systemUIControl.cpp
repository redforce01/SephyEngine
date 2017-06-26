#include "stdafx.h"
#include "systemUIControl.h"

SystemUIControl::SystemUIControl()
{
	m_x = m_y = 0;
	m_width = m_height = 0;
	m_margin = 0;
	m_nControlID = 0;
	m_Type = SYSTEM_UI_TYPES::UI_TYPE_BUTTON;
	m_State = SYSTEM_UI_CONTROL_STATE::UI_CONTROL_STATE_NORMAL;
	m_bInitialized = false;
	m_bVisible = false;
	m_bHasFocus = false;
	m_bMouseOver = false;
	m_bEnabled = false;
	m_bHasIcon = false;
	m_pIcon = nullptr;
	m_pInput = nullptr;
	m_pGraphics = nullptr;
}


SystemUIControl::~SystemUIControl()
{
}

bool SystemUIControl::initialize(int controlID, SYSTEM_UI_TYPES type,
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
		m_rcBoundingBox = RectMake(x, y, w, h);
		m_bInitialized = success = vertexSetUp(x, y, w, h);
	}
	catch (...)
	{
		MessageBox(g_hWndEngine, "SystemUIControl Initialize Failed", "Error", MB_OK);
	}
	
	return success;
}

bool SystemUIControl::initialize(int controlID, SYSTEM_UI_TYPES type, int x, int y, int w, int h, int m)
{
	return false;
}

void SystemUIControl::update(float frameTime)
{
	//*************
	// Button CONTROL STATE CASE 처리작성중...
	// 내일 일어나면 STATE CASE 처리 및 Bool 변수값들에 대한 처리를 구현해야 됨.
	// 음니ㅏ어 니아퍼미ㅏ퍼밍 ㅏㄹ핌ㄴ알픔이 ;라ㅢㄴㅇㅁ ㄹ프
	//*************


	if (ContainsPoint(PointMake(m_pInput->getMouseX(), m_pInput->getMouseY())))
		m_State = SYSTEM_UI_CONTROL_STATE::UI_CONTROL_STATE_MOUSEOVER;
	else
		m_State = SYSTEM_UI_CONTROL_STATE::UI_CONTROL_STATE_NORMAL;

	if (m_Object)
	{
		m_CallbackFunctionParameter(m_Object);

	}
	else
		m_CallbackFunction();
}

void SystemUIControl::render()
{
	m_pGraphics->drawQuad(vertexBuffer);
	if (m_bHasIcon)
	{
		m_pGraphics->spriteBegin();
		m_pIcon->draw();
		m_pGraphics->spriteEnd();
	}
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
