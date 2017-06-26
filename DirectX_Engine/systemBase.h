#ifndef _VIWERSYSTEMBASE_H
#define _VIWERSYSTEMBASE_H

class SystemBase;

#include "game.h"

class SystemBase
{
protected:
	Graphics* pGraphics;
	Input* pInput;

public:
	SystemBase();
	~SystemBase();

	virtual bool initialize(Game* gamePtr) PURE;
	virtual void update(float frameTime) PURE;
	virtual void render() PURE;
};

#endif // !_VIWERSYSTEMBASE_H
