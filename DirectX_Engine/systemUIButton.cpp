#include "stdafx.h"
#include "systemUIButton.h"
#include "systemUIDialog.h"

SystemUIButton::SystemUIButton()
{
	m_bHasIcon = false;
	m_bHasMessage = false;
	m_pIcon = nullptr;
	m_pObject = nullptr;
}


SystemUIButton::~SystemUIButton()
{
}

bool SystemUIButton::initButton(Graphics * g, Input * i, int controlID, CALLBACK_FUNCTION_ cbFunction,
	int x, int y, int w, int h, int m)
{
	m_pGraphics = g;
	m_pInput = i;
	m_CallbackFunction = cbFunction;
	return SystemUIControl::initControl(controlID, SYSTEM_UI_TYPES::UI_TYPE_BUTTON, x, y, w, h, m);
}

bool SystemUIButton::initButton(Graphics * g, Input * i, int controlID, CALLBACK_FUNCTION_ cbFunction, SystemUIDialog * pParent, int x, int y, int w, int h, int m)
{
	m_pGraphics = g;
	m_pInput = i;
	m_CallbackFunction = cbFunction;
	return SystemUIControl::initControl(controlID, SYSTEM_UI_TYPES::UI_TYPE_BUTTON, pParent, x, y, w, h, m);
}

bool SystemUIButton::initButton(Graphics * g, Input * i, int controlID, CALLBACK_FUNCTION_PARAMETER cbfParam, void * obj,
	int x, int y, int w, int h, int m)
{
	m_pGraphics = g;
	m_pInput = i;
	m_CallbackFunctionParameter = cbfParam;
	m_pObject = obj;
	return SystemUIControl::initControl(controlID, SYSTEM_UI_TYPES::UI_TYPE_BUTTON, x, y, w, h, m);
}

bool SystemUIButton::initButton(Graphics * g, Input * i, int controlID, CALLBACK_FUNCTION_PARAMETER cbfParam, void * obj, SystemUIDialog * pParent, int x, int y, int w, int h, int m)
{
	m_pGraphics = g;
	m_pInput = i;
	m_CallbackFunctionParameter = cbfParam;
	m_pObject = obj;
	return SystemUIControl::initControl(controlID, SYSTEM_UI_TYPES::UI_TYPE_BUTTON, pParent, x, y, w, h, m);
}

void SystemUIButton::update(float frameTime)
{
	SystemUIControl::update(frameTime);

	if (m_State == SYSTEM_UI_CONTROL_STATE::UI_CONTROL_STATE_PRESSED)
	{
		if (m_pObject)
		{
			m_CallbackFunctionParameter(m_pObject);
		}
		else
			m_CallbackFunction();

		m_State = SYSTEM_UI_CONTROL_STATE::UI_CONTROL_STATE_NORMAL;
	}
}

void SystemUIButton::render()
{
	if (m_State == SYSTEM_UI_CONTROL_STATE::UI_CONTROL_STATE_HIDDEN)
		return;

	SystemUIControl::render();
	m_pGraphics->spriteBegin();

	if (m_bHasIcon)
		m_pIcon->draw();

	if (m_bHasMessage)
		m_dxFont.print(m_strMessage, m_rcBoundingBox, DT_CENTER | DT_BOTTOM);

	m_pGraphics->spriteEnd();
}

void SystemUIButton::SetIcon(Image * icon)
{
	if (icon)
	{
		m_pIcon = icon;

		int controlX = GetControlPosX();
		int controlY = GetControlPosY();
		int margin = GetControlMargin();

		if (ContainsParent())
		{
			int dialogX = m_pDialog->getDialogX();
			int dialogY = m_pDialog->getDialogY();
			
			m_pIcon->setX(dialogX + margin);
			m_pIcon->setY(dialogY + margin);
		}
		else
		{
			m_pIcon->setX(controlX + margin);
			m_pIcon->setY(controlY + margin);
		}
		m_bHasIcon = true;
	}
}

