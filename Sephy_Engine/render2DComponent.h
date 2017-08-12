#ifndef _RENDER2DCOMPONENT_H
#define _RENDER2DCOMPONENT_H
#define WIN32_LEAN_AND_MEAN

class Render2DComponent;

#include "renderComponent.h"

class Render2DComponent : public RenderComponent
{
public:
	Render2DComponent();
	~Render2DComponent();

	virtual const goc_id_type& familyID() const
	{ return goc_id_type("Render2D"); }

	virtual void render() override;
	virtual void HandleMessage(GOCMessage message) override;
};

#endif // !_RENDER2DCOMPONENT_H
