#pragma once
#include "systemBase.h"
class CUnitTool_MainSystem : public SystemBase
{
public:
	CUnitTool_MainSystem();
	~CUnitTool_MainSystem();

	virtual bool initialize(Game* gamePtr) override;
	virtual void update(float frameTime) override;
	virtual void render() override;
	virtual void ai();
	virtual void collision();
};

