#ifndef _COLLISIONBOX_BUTTON_H
#define _COLLISIONBOX_BUTTON_H

class CollisionBox_Button;

#include "systemUIButton.h"

namespace collisionBoxButtonNS
{
	const std::string NAME = "COLLISION_BOX";
	const char FONT[] = "Courier New";  // console font
	const int FONT_HEIGHT = 14;         // height of the font in pixels
	const COLOR_ARGB FONT_COLOR_INACTIVE = graphicsNS::WHITE;    // color of console text
	const COLOR_ARGB FONT_COLOR_ACTIVE = graphicsNS::GREEN;
}

class MapSystem;
class CollisionBox_Button : public SystemUIButton
{
private:
	bool m_bActive;

	MapSystem* m_pMapSystem;
public:
	CollisionBox_Button();
	~CollisionBox_Button();

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
	static void functionCollisionBox(void * obj);
};

#endif // !_COLLISIONBOX_BUTTON_H
