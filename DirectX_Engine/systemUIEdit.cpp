#include "stdafx.h"
#include "systemUIEdit.h"


SystemUIEdit::SystemUIEdit()
{
	m_bShowHint = false;
	m_bEditable = true;
	m_fEditBoxRate = 0.f;
	m_strEditText = "";
}


SystemUIEdit::~SystemUIEdit()
{
}

bool SystemUIEdit::initEdit(Graphics * g, Input * i, int controlID,
	bool bUseHint, std::string strHint, std::string strTitle, bool bEditable,
	float fBoxRate,	int x, int y, int w, int h, int m)
{
	bool success = false;
	try
	{
		m_pGraphics = g;
		m_pInput = i;
		m_bShowHint = bUseHint;
		if(bUseHint)
			m_strHint = strHint;
		m_strEditTitle = strTitle;
		m_bEditable = bEditable;
		m_fEditBoxRate = fBoxRate;

		success = m_dxFont.initialize(g, systemUIEditNS::FONT_HEIGHT, false, false, systemUIEditNS::FONT);
		if (success == false)
			throw("SystemUIEdit DxFont Initialized Failed");
		success  = SystemUIControl::initControl(controlID, SYSTEM_UI_TYPES::UI_TYPE_EDITBOX, false, x, y, w, h, m);
		if (success == false)
			throw("SystemUIEdit SystemUIControl Initialized Failed");
	}
	catch (...)
	{
		MessageBox(g_hWndEngine, "SystemUIEdit Initialized Failed", "Error", MB_OK);
	}

	return success;
}

bool SystemUIEdit::initEdit(Graphics * g, Input * i, int controlID,
	bool bUseHint, std::string strHint, std::string strTitle, bool bEditable, SystemUIDialog * pParent,
	float fBoxRate, int x, int y, int w, int h, int m)
{
	bool success = false;
	try
	{
		m_pGraphics = g;
		m_pInput = i;
		m_bShowHint = bUseHint;
		if (bUseHint)
			m_strHint = strHint;
		m_strEditTitle = strTitle;
		m_bEditable = bEditable;
		m_fEditBoxRate = fBoxRate;

		success = m_dxFont.initialize(g, systemUIEditNS::FONT_HEIGHT, false, false, systemUIEditNS::FONT);
		if (success == false)
			throw("SystemUIEdit DxFont Initialized Failed");
		success = SystemUIControl::initControl(controlID, SYSTEM_UI_TYPES::UI_TYPE_EDITBOX, pParent, false, x, y, w, h, m);
		if (success == false)		
			throw("SystemUIEdit SystemUIControl Initialized Failed");
	}
	catch (...)
	{
		MessageBox(g_hWndEngine, "SystemUIEdit Initialized Failed", "Error", MB_OK);
	}

	return success;
}

void SystemUIEdit::update(float frameTime)
{
	SystemUIControl::update(frameTime);
	
	if (m_pInput->getMouseLButton() || m_pInput->getMouseRButton())
	{
		if (PtInRect(&m_rcBoundingBox, m_pInput->getMousePt()))
		{
			clearInputText();
			OnFocusIn();
		}
		else
			OnFocusOut();
	}

	if (m_bEditable && SystemUIControl::GetFocus())
	{
		m_strEditText = m_pInput->getTextIn();
	}
}

void SystemUIEdit::render()
{
	if (m_State == SYSTEM_UI_CONTROL_STATE::UI_CONTROL_STATE_HIDDEN)
		return;

	SystemUIControl::render();
	
	// spriteDraw Begin
	m_pGraphics->spriteBegin();
	
	// TitleBox Draw And Print Edit Title 
	RECT rcTitleBox;
	float TitleWidth = (m_rcBoundingBox.right - m_rcBoundingBox.left) * m_fEditBoxRate;
	rcTitleBox = RectMake(m_rcBoundingBox.left, m_rcBoundingBox.top, TitleWidth, m_rcBoundingBox.bottom - m_rcBoundingBox.top);
	m_pGraphics->drawRect(rcTitleBox);

	RECT rcTitleTextBox;
	rcTitleTextBox = RectMake(rcTitleBox.left + systemUIEditNS::EDIT_MARGIN, rcTitleBox.top,
		rcTitleBox.right - rcTitleBox.left - (systemUIEditNS::EDIT_MARGIN * 2), rcTitleBox.bottom - rcTitleBox.top);
	// if (EditTitle == empty) Don't Print Title Text
	if (m_strEditTitle != "")
		m_dxFont.print(m_strEditTitle, rcTitleTextBox, DT_LEFT | DT_VCENTER);

	// EditBox Draw And Print Edit Title 
	float EditWidth = (m_rcBoundingBox.right - m_rcBoundingBox.left) * (1.0 - m_fEditBoxRate);
	RECT rcEditBox;
	rcEditBox = RectMake(rcTitleBox.right, rcTitleBox.top, EditWidth, m_rcBoundingBox.bottom - m_rcBoundingBox.top);
	m_pGraphics->drawRect(rcEditBox);
	RECT rcTextBox;
	rcTextBox = RectMake(rcEditBox.left + systemUIEditNS::EDIT_MARGIN, rcEditBox.top,
		rcEditBox.right - rcEditBox.left - (systemUIEditNS::EDIT_MARGIN * 2), rcEditBox.bottom - rcEditBox.top);

	if (m_strEditText.length() <= 0)
	{
		if (m_bShowHint)
			m_dxFont.print(m_strHint, rcTextBox, DT_LEFT | DT_VCENTER);
	}
	else
		m_dxFont.print(m_strEditText, rcTextBox, DT_LEFT | DT_VCENTER);


	

	// spriteDraw End
	m_pGraphics->spriteEnd();
}
