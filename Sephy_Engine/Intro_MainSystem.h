#ifndef _INTRO_MAINSYSTEM_H
#define _INTRO_MAINSYSTEM_H
#define WIN32_LEAN_AND_MEAN

class CIntro_MainSystem;

#include "systemBase.h"
#include "Intro_AnimeSystem.h"

class CIntro_MainSystem : public SystemBase
{
private:
	CIntro_AnimeSystem m_AnimeSystem;

public:
	CIntro_MainSystem();
	~CIntro_MainSystem();

	virtual bool initialize(Game* gamePtr) override;
	virtual void update(float frameTime) override;
	virtual void render() override;
};

#endif // !_INTRO_MAINSYSTEM_H
