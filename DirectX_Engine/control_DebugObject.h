#ifndef _CONTROL_DEBUG_OBJECT_H
#define _CONTROL_DEBUG_OBJECT_H

class Control_DebugObject;

#include "systemUIButton.h"


class Control_DebugObject : public SystemUIButton
{
private:


public:
	Control_DebugObject();
	~Control_DebugObject();

	bool initialize(Graphics* g, Input* i, int controlID, SystemUIDialog* pDialog, int x, int y, int w, int h, int m) override;
	virtual void update(float frameTime) override;
	virtual void render() override;
};

#endif // !_CONTROL_DEBUG_OBJECT_H
