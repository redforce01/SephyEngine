#ifndef _INTRO_CONTROLSYSTEM_H
#define _INTRO_CONTROLSYSTEM_H
#define WIN32_LEAN_AND_MEAN

class CIntro_ControlSystem;

#include "systemBase.h"

namespace introControlSystemNS
{

}

class CIntro_ControlSystem : public SystemBase
{
private:
	

public:
	CIntro_ControlSystem();
	~CIntro_ControlSystem();

	virtual bool initialize(Game* gamePtr) override;
	virtual void update(float frameTime) override;
	virtual void render() override;
};

#endif // !_INTRO_CONTROLSYSTEM_H
