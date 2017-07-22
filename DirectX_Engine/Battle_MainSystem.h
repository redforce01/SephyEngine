#pragma once
#include "systemBase.h"
class CBattle_MainSystem : public SystemBase
{
public:
	CBattle_MainSystem();
	~CBattle_MainSystem();

	virtual bool initialize(Game* gamePtr) override;
	virtual void update(float frameTime) override;
	virtual void render() override;
};

