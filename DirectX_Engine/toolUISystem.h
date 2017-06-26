#ifndef _TOOLUISYSTEM_H
#define _TOOLUISYSTEM_H

class ToolUISystem;

#include "systemBase.h"


class ToolUISystem : public SystemBase
{
private:
	

public:
	ToolUISystem();
	~ToolUISystem();

	virtual bool initialize(Game* gamePtr) override;
	virtual void update(float frameTime) override;
	virtual void render() override;
};

#endif // !_TOOLUISYSTEM_H
