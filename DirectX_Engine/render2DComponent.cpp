#include "stdafx.h"
#include "render2DComponent.h"
#include "gameObject.h"

Render2DComponent::Render2DComponent()
{
}


Render2DComponent::~Render2DComponent()
{
}

void Render2DComponent::render()
{
	if (mComponentSwitch)
		mOwnerGO->draw(mOwnerGO->getColorFilter());
}

void Render2DComponent::HandleMessage(GOCMessage message)
{
}
