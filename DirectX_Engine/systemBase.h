#ifndef _VIWERSYSTEMBASE_H
#define _VIWERSYSTEMBASE_H

class SystemBase;

#include "game.h"

class SystemBase
{
protected:
	Graphics*	m_pGraphics;
	Input*		m_pInput;

public:
	SystemBase();
	virtual ~SystemBase();

	virtual bool initialize(Game* gamePtr) PURE;
	virtual void update(float frameTime) PURE;
	virtual void render() PURE;

	Graphics* getGraphics() const
	{
		return m_pGraphics;
	}

	Input* getInput() const
	{
		return m_pInput;
	}
};

#endif // !_VIWERSYSTEMBASE_H
