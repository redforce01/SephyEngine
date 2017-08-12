#ifndef _RENDERCOMPONENT_H
#define _RENDERCOMPONENT_H
#define WIN32_LEAN_AND_MEAN

class RenderComponent;

#include "componentBase.h"

class RenderComponent : public ComponentBase
{
public:
	virtual const goc_id_type& componentID() const
	{ return goc_id_type("RenderComponent"); }
	
	virtual void render() override;
};

#endif // !_RENDERCOMPONENT_H
