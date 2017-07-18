#ifndef _MAKEOBJECTBUTTON_H
#define _MAKEOBJECTBUTTON_H

class MakeObjectButton;

#include "systemUIButton.h"

namespace makeObjectButtonNS
{
	const std::string NAME = "MAKE";
	const std::string FILENAME = "MakeButton";
	const char FONT[] = "Courier New";  // console font
	const int FONT_HEIGHT = 10;         // height of the font in pixels
	const COLOR_ARGB FONT_COLOR = graphicsNS::WHITE;    // color of console text
	const int IMAGE_WIDTH = 28;
	const int IMAGE_HEIGHT = 23;
}

class MapSystem;
class ObjectControlViewer;
class MakeObjectButton : public SystemUIButton
{
private:
	MapSystem* m_pMapSystem;
	ObjectControlViewer* m_pObjectControlViewer;
public:
	MakeObjectButton();
	~MakeObjectButton();

	virtual bool initialize(Graphics* g, Input* i, int controlID, SystemUIDialog* pDialog, int x, int y, int w, int h, int m) override;
	virtual void update(float frameTime) override;
	virtual void render() override;

	// ObjectControlViewer Pointer MemoryLink Setup 
	void setMemoryLinkObjectControlViewer(ObjectControlViewer* pObjectControlViewer)
	{ m_pObjectControlViewer = pObjectControlViewer; }
	void setMemoryLinkMapSystem(MapSystem* pMapSystem)
	{ m_pMapSystem = pMapSystem; }
public:
	// CALLBACK FUNCTION [STATIC]
	static void functionMakeObject(void * obj);
};

#endif // !_MAKEOBJECTBUTTON_H
