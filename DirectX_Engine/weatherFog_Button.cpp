#include "stdafx.h"
#include "weatherFog_Button.h"
#include "mapSystem.h"

WeatherFog_Button::WeatherFog_Button()
{
	m_bActive = false;
	m_pMapSystem = nullptr;
}


WeatherFog_Button::~WeatherFog_Button()
{
}

bool WeatherFog_Button::initialize(Graphics * g, Input * i, int controlID, SystemUIDialog * pDialog, int x, int y, int w, int h, int m)
{
	bool success = false;
	try
	{
		success = SystemUIButton::initButton(g, i, controlID, functionWeatherFog, this, pDialog, x, y, w, h, m);
		if (success == false)
			throw("SystemUIButton InitButton Failed");

		success = m_dxFont.initialize(g, weatherFogButtonNS::FONT_HEIGHT, false, false, weatherFogButtonNS::FONT);
		if (success == false)
			throw("Failed");
		m_dxFont.setFontColor(weatherFogButtonNS::FONT_COLOR_INACTIVE);

		SetMessage(weatherFogButtonNS::NAME);
	}
	catch (...)
	{
		MessageBox(g_hWndEngine, "DEBUG Button Initialize Failed", "Error", MB_OK);
	}

	return success;
}

void WeatherFog_Button::update(float frameTime)
{
	SystemUIButton::update(frameTime);
}

void WeatherFog_Button::render()
{
	SystemUIButton::render();
}

void WeatherFog_Button::functionWeatherFog(void * obj)
{
	WeatherFog_Button* pThis = (WeatherFog_Button*)obj;
	pThis->m_pInput->setMouseLButton(false);

	pThis->m_bActive = !pThis->m_bActive;
	if (pThis->m_bActive)
	{
		pThis->m_pMapSystem->setMakeEventObjectMode(true);
		pThis->m_dxFont.setFontColor(weatherFogButtonNS::FONT_COLOR_ACTIVE);
	}
	else
	{
		pThis->m_pMapSystem->setMakeEventObjectMode(false);
		pThis->m_dxFont.setFontColor(weatherFogButtonNS::FONT_COLOR_INACTIVE);
	}
}
