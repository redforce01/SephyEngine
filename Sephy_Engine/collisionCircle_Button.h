#ifndef _COLLISIONCIRCLE_BUTTON_H
#define _COLLISIONCIRCLE_BUTTON_H

class CollisionCircle_Button;

#include "systemUIButton.h"

namespace collisionCircleButtonNS
{
	const std::string NAME = "COLLISION_CIRCLE";
	const char FONT[] = "Courier New";  // console font
	const int FONT_HEIGHT = 14;         // height of the font in pixels
	const COLOR_ARGB FONT_COLOR_INACTIVE = graphicsNS::WHITE;    // color of console text
	const COLOR_ARGB FONT_COLOR_ACTIVE = graphicsNS::GREEN;
}

class MapSystem;
class CollisionCircle_Button : public SystemUIButton
{
private:
	bool m_bActive;

	MapSystem* m_pMapSystem;
public:
	CollisionCircle_Button();
	~CollisionCircle_Button();

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
	static void functionCollisionCircle(void * obj);
};

#endif // !_COLLISIONCIRCLE_BUTTON_H
