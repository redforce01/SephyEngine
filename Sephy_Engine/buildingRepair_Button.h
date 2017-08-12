#ifndef _BUILDINGREPAIR_BUTTON_H
#define _BUILDINGREPAIR_BUTTON_H

class BuildingRepair_Button;

#include "systemUIButton.h"

namespace buildingRepairButtonNS
{
	const std::string NAME = "BUILDING_REPAIR";
	const char FONT[] = "Courier New";  // console font
	const int FONT_HEIGHT = 14;         // height of the font in pixels
	const COLOR_ARGB FONT_COLOR_INACTIVE = graphicsNS::WHITE;    // color of console text
	const COLOR_ARGB FONT_COLOR_ACTIVE = graphicsNS::GREEN;
}

class MapSystem;
class BuildingRepair_Button : public SystemUIButton
{
private:
	bool m_bActive;

	MapSystem* m_pMapSystem;
public:
	BuildingRepair_Button();
	~BuildingRepair_Button();

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

	void setMemoryLinkMapSystem(MapSystem* pMapSystem)
	{
		m_pMapSystem = pMapSystem;
	}
public:
	// CALLBACK FUNCTION [STATIC]
	static void functionBuildingRepair(void * obj);
};

#endif // !_BUILDINGREPAIR_BUTTON_H
