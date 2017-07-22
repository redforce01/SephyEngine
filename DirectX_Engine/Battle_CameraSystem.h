#pragma once
#include "systemBase.h"
class CBattle_CameraSystem : public SystemBase
{
public:
	CBattle_CameraSystem();
	~CBattle_CameraSystem();

	virtual bool initialize(Game* gamePtr) override;
	virtual void update(float frameTime) override;
	virtual void render() override;

	
};

