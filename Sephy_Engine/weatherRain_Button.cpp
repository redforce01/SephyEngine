#include "stdafx.h"
#include "weatherRain_Button.h"
#include "mapSystem.h"

WeatherRain_Button::WeatherRain_Button()
{
	m_bActive = false;
	m_pMapSystem = nullptr;
}


WeatherRain_Button::~WeatherRain_Button()
{
}

bool WeatherRain_Button::initialize(Graphics * g, Input * i, int controlID, SystemUIDialog * pDialog, int x, int y, int w, int h, int m)
{
	bool success = false;
	try
	{
		success = SystemUIButton::initButton(g, i, controlID, functionWeatherRain, this, pDialog, x, y, w, h, m);
		if (success == false)
			throw("SystemUIButton InitButton Failed");

		success = m_dxFont.initialize(g, weatherRainButtonNS::FONT_HEIGHT, false, false, weatherRainButtonNS::FONT);
		if (success == false)
			throw("Failed");
		m_dxFont.setFontColor(weatherRainButtonNS::FONT_COLOR_INACTIVE);

		SetMessage(weatherRainButtonNS::NAME);
	}
	catch (...)
	{
		MessageBox(g_hWndEngine, "DEBUG Button Initialize Failed", "Error", MB_OK);
	}

	return success;
}

void WeatherRain_Button::update(float frameTime)
{
	SystemUIButton::update(frameTime);
}

void WeatherRain_Button::render()
{
	SystemUIButton::render();
}

void WeatherRain_Button::functionWeatherRain(void * obj)
{
	WeatherRain_Button* pThis = (WeatherRain_Button*)obj;
	pThis->m_pInput->setMouseLButton(false);

	pThis->m_bActive = !pThis->m_bActive;
	if (pThis->m_bActive)
	{
		pThis->m_pMapSystem->setMakeEventObjectMode(true);
		pThis->m_dxFont.setFontColor(weatherRainButtonNS::FONT_COLOR_ACTIVE);
	}
	else
	{
		pThis->m_pMapSystem->setMakeEventObjectMode(false);
		pThis->m_dxFont.setFontColor(weatherRainButtonNS::FONT_COLOR_INACTIVE);
	}
}
