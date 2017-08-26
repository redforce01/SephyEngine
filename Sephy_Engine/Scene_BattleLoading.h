#ifndef _SCENE_BATTLE_LOADING_H
#define _SCENE_BATTLE_LOADING_H
#define WIN32_LEAN_AND_MEAN

class CScene_BattleLoading;

#include "game.h"

namespace sceneBattleLoadingNS
{
	const std::string LOADING_BLACK_BACKGROUND = "1080p_WHITE";
	const COLOR_ARGB LOADING_BLACK_BACK_COLOR_FILTER = SETCOLOR_ARGB(255, 1, 1, 1);
	const std::string LOADING_BACKGROUND_KEY = "Loading";
	const std::string LOADING_BACKGROUND_01_FILENAME = "Loading1";
	const std::string LOADING_BACKGROUND_02_FILENAME = "Loading2";
	const std::string LOADING_BACKGROUND_03_FILENAME = "Loading3";
	const std::string LOADING_BACKGROUND_04_FILENAME = "Loading4";
	const std::string LOADING_PROGRESS_FILENAME = "battleReadyBar";
	const std::string LOADING_PROGRESS_BACK_FILENAME = "WaitForReady";
	const float LOADING_BACKGROUND_RELATE_Y = -50;
	const float LOADING_PROGRESS_BACK_RELATE_Y = -108;
	const float LOADING_PROGRESS_BAR_RELATE_Y = -100;
	const float LOADING_BACKGROUND_ALPHA_SPEED = 1.f;
}

class CScene_BattleLoading : public Game
{
private:
	Image* m_pBlackBack;
	Image* m_pLoadingBackground;
	Image* m_pProgressBar;
	Image* m_pProgressBarBack;

	float m_fBackAlpha;
	float m_fLoadingTime;
	bool m_bLoadingStart;
	bool m_bVisible;
public:
	CScene_BattleLoading();
	~CScene_BattleLoading();

	virtual void initialize(HWND hwnd)	override;
	virtual void update()				override;
	virtual void release()				override;
	virtual void ai()					override;
	virtual void collisions()			override;
	virtual void render()				override;
	virtual void releaseAll()			override;
	virtual void resetAll()				override;
};

#endif // !_SCENE_BATTLE_LOADING_H
