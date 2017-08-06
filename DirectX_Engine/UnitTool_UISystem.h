#pragma once
#include "systemBase.h"
class CUnitTool_UISystem : public SystemBase
{
private:
	

public:
	CUnitTool_UISystem();
	~CUnitTool_UISystem();

	virtual bool initialize(Game* gamePtr) override;
	virtual void update(float frameTime) override;
	virtual void render() override;
};

