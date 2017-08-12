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
	SAFE_DELETE(m_pIcon);
}

bool SystemUIButton::initButton(Graphics * g, Input * i, int controlID, CALLBACK_FUNCTION_ cbFunction,
	int x, int y, int w, int h, int m)
{
	m_pGraphics = g;
	m_pInput = i;
	m_CallbackFunction = cbFunction;
	return SystemUIControl::initControl(controlID, SYSTEM_UI_TYPES::UI_TYPE_BUTTON, false, x, y, w, h, m);
}

bool SystemUIButton::initButton(Graphics * g, Input * i, int controlID, CALLBACK_FUNCTION_ cbFunction, SystemUIDialog * pParent, int x, int y, int w, int h, int m)
{
	m_pGraphics = g;
	m_pInput = i;
	m_CallbackFunction = cbFunction;
	return SystemUIControl::initControl(controlID, SYSTEM_UI_TYPES::UI_TYPE_BUTTON, pParent, false, x, y, w, h, m);
}

bool SystemUIButton::initButton(Graphics * g, Input * i, int controlID, CALLBACK_FUNCTION_PARAMETER cbfParam, void * obj,
	int x, int y, int w, int h, int m)
{
	m_pGraphics = g;
	m_pInput = i;
	m_CallbackFunctionParameter = cbfParam;
	m_pObject = obj;
	return SystemUIControl::initControl(controlID, SYSTEM_UI_TYPES::UI_TYPE_BUTTON, false, x, y, w, h, m);
}

bool SystemUIButton::initButton(Graphics * g, Input * i, int controlID, CALLBACK_FUNCTION_PARAMETER cbfParam, void * obj, SystemUIDialog * pParent, int x, int y, int w, int h, int m)
{
	m_pGraphics = g;
	m_pInput = i;
	m_CallbackFunctionParameter = cbfParam;
	m_pObject = obj;
	return SystemUIControl::initControl(controlID, SYSTEM_UI_TYPES::UI_TYPE_BUTTON, pParent, false, x, y, w, h, m);
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
	if (m_pGraphics == nullptr)
		return;

	if (m_State == SYSTEM_UI_CONTROL_STATE::UI_CONTROL_STATE_HIDDEN)
		return;

	SystemUIControl::render();

	if (m_bHasIcon == false)
	{
		m_pGraphics->drawRect(m_rcBoundingBox);
	}

	
	RECT rcMessage = m_rcBoundingBox;	
	rcMessage.left = rcMessage.left + 3;
	rcMessage.right = rcMessage.right + 3;

	m_pGraphics->spriteBegin();
	if (m_bHasIcon)
		m_pIcon->draw(graphicsNS::WHITE);

	if (m_bHasMessage)
	{
		if(m_bHasIcon)
			m_dxFont.print(m_strMessage, rcMessage, DT_CENTER | DT_BOTTOM);
		else
			m_dxFont.print(m_strMessage, rcMessage, DT_LEFT);
	}
	m_pGraphics->spriteEnd();
}

void SystemUIButton::SetIcon(Image * icon)
{
	if (icon)
	{
		m_pIcon = icon;

		int controlX = GetControlPosX();
		int controlY = GetControlPosY();
		int controlMargin = GetControlMargin();

		if (ContainsParent())
		{
			int dialogX = m_pDialog->getDialogX();
			int dialogY = m_pDialog->getDialogY();
			int dialogMargin = m_pDialog->getDialogMargin();
			
			m_pIcon->setX(dialogX + controlMargin + dialogMargin + (controlX - dialogX));
			m_pIcon->setY(dialogY + controlMargin + dialogMargin + (controlY - dialogY));
		}
 		else
		{
			m_pIcon->setX(controlX + controlMargin);
			m_pIcon->setY(controlY + controlMargin);
		}
		m_bHasIcon = true;
	}
}

