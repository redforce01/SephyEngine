#ifndef _INTRO_MAINSYSTEM_H
#define _INTRO_MAINSYSTEM_H
#define WIN32_LEAN_AND_MEAN

class CIntro_MainSystem;

#include "systemBase.h"

namespace introMainSystemNS
{
	const std::string SOUND_BGM_NAME = "main_theme";

}

class CIntro_MainSystem : public SystemBase
{
private:
	Image* m_pBackground;
	Image* m_pAircraft;
	

public:
	CIntro_MainSystem();
	~CIntro_MainSystem();

	virtual bool initialize(Game* gamePtr) override;
	virtual void update(float frameTime) override;
	virtual void render() override;
};

#endif // !_INTRO_MAINSYSTEM_H
