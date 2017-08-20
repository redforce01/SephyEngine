#ifndef _INTRO_MAINSYSTEM_H
#define _INTRO_MAINSYSTEM_H
#define WIN32_LEAN_AND_MEAN

class CIntro_MainSystem;

#include "systemBase.h"
#include "Intro_AnimeSystem.h"
#include "systemButton.h"

namespace introMainSystemNS
{
	const std::string ERROR_MESSAGE = "Intro Main System Initialize Failed";
	const std::string BACKGROUND_MUSIC_FILENAME = "main_theme";
}
class CIntro_MainSystem : public SystemBase
{
private:
	CIntro_AnimeSystem m_AnimeSystem;
	SystemButton* m_pJoinButton;

public:
	CIntro_MainSystem();
	~CIntro_MainSystem();

	virtual bool initialize(Game* gamePtr) override;
	virtual void update(float frameTime) override;
	virtual void render() override;

	static void functionJoinButton();
};

#endif // !_INTRO_MAINSYSTEM_H
