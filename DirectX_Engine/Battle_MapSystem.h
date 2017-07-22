#pragma once
#include "systemBase.h"

class CBattle_MapSystem : public SystemBase
{
private:

public:
	CBattle_MapSystem();
	~CBattle_MapSystem();

	virtual bool initialize(Game* gamePtr) override;
	virtual void update(float frameTime) override;
	virtual void render() override;
};

