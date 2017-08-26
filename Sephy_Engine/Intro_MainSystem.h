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
	const float JOIN_BUTTON_RELATE_X = -70;
	const float JOIN_BUTTON_RELATE_Y = 230.f;
	const float CANCEL_BUTTON_RELATE_X = 40;
	const float CANCEL_BUTTON_RELATE_Y = 230.f;

	const char FONT[] = "Courier New";
	const int FONT_HEIGHT = 14;
	const COLOR_ARGB FONT_COLOR = graphicsNS::WHITE;

	const float INTRO_PANEL_RELATE_X = -170;
	const float INTRO_PANEL_RELATE_Y = 90;
	const float INTRO_PANEL_WIDTH = 400;
	const float INTRO_PANEL_HEIGHT = 200;
	const std::string INTRO_COMMENT_00 = "Made by Team.Sephy";
	const std::string INTRO_COMMENT_01 = "Resource From Navy Field 1";
	const std::string INTRO_BUTTON_JOIN = "Intro_Join";
	const std::string INTRO_BUTTON_CANCEL = "Intro_Cancel";
}
class CIntro_MainSystem : public SystemBase
{
private:
	CIntro_AnimeSystem m_AnimeSystem;
	SystemButton* m_pJoinButton;
	SystemButton* m_pCancelButton;
	TextDX m_dxFont;
public:
	CIntro_MainSystem();
	~CIntro_MainSystem();

	virtual bool initialize(Game* gamePtr) override;
	virtual void update(float frameTime) override;
	virtual void render() override;

	static void functionJoinButton();
	static void functionCancelButton();
};

#endif // !_INTRO_MAINSYSTEM_H
