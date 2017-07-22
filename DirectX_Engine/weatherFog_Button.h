#ifndef _WEATHERFOG_BUTTON_H
#define _WEATHERFOG_BUTTON_H

class WeatherFog_Button;

#include "systemUIButton.h"

namespace weatherFogButtonNS
{
	const std::string NAME = "WEATHER_FOG";
	const char FONT[] = "Courier New";  // console font
	const int FONT_HEIGHT = 14;         // height of the font in pixels
	const COLOR_ARGB FONT_COLOR_INACTIVE = graphicsNS::WHITE;    // color of console text
	const COLOR_ARGB FONT_COLOR_ACTIVE = graphicsNS::GREEN;
}

class WeatherFog_Button : public SystemUIButton
{
private:
	bool m_bActive;

public:
	WeatherFog_Button();
	~WeatherFog_Button();

	virtual bool initialize(Graphics* g, Input* i, int controlID, SystemUIDialog* pDialog, int x, int y, int w, int h, int m) override;
	virtual void update(float frameTime) override;
	virtual void render() override;

	// ===================================================
	// Getter Functions
	// ===================================================
	bool getActive() const
	{
		return m_bActive;
	}
public:
	// CALLBACK FUNCTION [STATIC]
	static void functionWeatherFog(void * obj);
};

#endif // !_WEATHERFOG_BUTTON_H