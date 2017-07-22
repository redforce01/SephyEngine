#ifndef _BUILDINGOBSERVER_BUTTON_H
#define _BUILDINGOBSERVER_BUTTON_H

class BuildingObserver_Button;

#include "systemUIButton.h"

namespace buildingObserverButtonNS
{
	const std::string NAME = "BUILDING_OBSERVER";
	const char FONT[] = "Courier New";  // console font
	const int FONT_HEIGHT = 14;         // height of the font in pixels
	const COLOR_ARGB FONT_COLOR_INACTIVE = graphicsNS::WHITE;    // color of console text
	const COLOR_ARGB FONT_COLOR_ACTIVE = graphicsNS::GREEN;
}

class BuildingObserver_Button : public SystemUIButton
{
private:
	bool m_bActive;

public:
	BuildingObserver_Button();
	~BuildingObserver_Button();

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
	static void functionBuildingObserver(void * obj);
};

#endif // !_BUILDINGOBSERVER_BUTTON_H