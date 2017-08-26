#ifndef _BATTLE_RESULT_PLAYER_VIEW_H
#define _BATTLE_RESULT_PLAYER_VIEW_H
#define WIN32_LEAN_AND_MEAN

#include "systemUIDialog.h"


namespace battleResultPlayerViewNS
{
	const std::string ERROR_MESSAGE = "Battle Result PlayerView Initialize Failed";
	//====================================================
	const float VIEW_RELATE_X = 100.f;	// X = 100
	const float VIEW_RELATE_Y = -200.f;	// Y = ((g_fScreenHeight / 2) - (VIEW_HEIGHT / 2))
	const float VIEW_WIDTH = 300;
	const float VIEW_HEIGHT = 400;
	//====================================================
	const std::string VIEW_GUIDE_TITLE_PLAYER = "PLAYER";
	const float VIEW_GUIDE_TITLE_PLAYER_RELATE_X	= 10;
	const float VIEW_GUIDE_TITLE_PLAYER_RELATE_Y	= 10;
	const float VIEW_GUIDE_TITLE_PLAYER_WIDTH		= 70;
	const float VIEW_GUIDE_TITLE_PLAYER_HEIGHT		= 20;
	//====================================================	
	const std::string DAMAGE_SCORE_TITLE = "DAMAGE SCORE";
	const float DAMAGE_SCORE_TITLE_RELATE_X = 90;
	const float DAMAGE_SCORE_TITLE_RELATE_Y = 10;
	const float DAMAGE_SCORE_TITLE_WIDTH	= 100;
	const float DAMAGE_SCORE_TITLE_HEIGHT	= 20;
	const float VIEW_GUIDE_SCORE_BOX_RELATE_X	= 190;
	const float VIEW_GUIDE_SCORE_BOX_RELATE_Y	= 10;
	const float VIEW_GUIDE_SCORE_BOX_WIDTH		= 100;
	const float VIEW_GUIDE_SCORE_BOX_HEIGHT		= 20;
	//====================================================
	const std::string VIEW_GUIDE_TITLE_SHIP = "SHIP NAME";
	const float VIEW_GUIDE_START_RELATE_X		= 10;
	const float VIEW_GUIDE_START_RELATE_Y		= 40;
	const float VIEW_GUIDE_TITLE_HEIGHT			= 20;
	const float VIEW_GUIDE_TITLE_NUMBER_WIDTH	= 30;
	const float VIEW_GUIDE_TITLE_SHIPNAME_WIDTH = 250;
	//====================================================
	const char FONT[] = "Courier New";
	const int FONT_HEIGHT = 14;
	const COLOR_ARGB FONT_COLOR = graphicsNS::WHITE;
	const COLOR_ARGB BACK_COLOR = SETCOLOR_ARGB(192, 26, 32, 44);
}

class CBattle_ResultPlayerView : public SystemUIDialog
{
private:
	RECT		m_rcViewTitle;
	std::string m_strViewTitle;
private:
	RECT		m_rcScore;
	RECT		m_rcScoreTitle;
	std::string m_strScore;
private:
	RECT m_rcShipNumberGuide;
	RECT m_rcShipNameGuide;
	std::string m_strShipNameGuide;
private:
	struct tagViewItem
	{
		std::string itemNumber;
		std::string shipName;
		RECT rcNumber;
		RECT rcName;
	};
	std::vector<tagViewItem*> m_vListItem;
public:
	CBattle_ResultPlayerView();
	~CBattle_ResultPlayerView();

	virtual bool initialize(Graphics* g, Input* i) override;
	virtual void update(float frameTime) override;
	virtual void render() override;

	//=====================================================
	// Member Functions
	//=====================================================
	void addListItem(std::string shipName);
	void setupDamageScore(int score)
	{
		m_strScore = std::to_string(score);
	}
};

#endif // !_BATTLE_RESULT_PLAYER_VIEW_H
