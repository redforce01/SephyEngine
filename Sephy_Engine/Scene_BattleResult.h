#ifndef _SCENE_BATTLE_RESULT_H
#define _SCENE_BATTLE_RESULT_H
#define WIN32_LEAN_AND_MEAN

#include "game.h"
#include "systemUIDialog.h"
#include "Battle_ResultSystem.h"

namespace scenebattleResultNS
{
	const std::string LOADING_BLACK_BACKGROUND = "1080p_WHITE";
	const COLOR_ARGB LOADING_BLACK_BACK_COLOR_FILTER = SETCOLOR_ARGB(255, 1, 1, 1);
	const std::string BATTLE_RESULT_BACKGROUND = "Battle_Result_Background";
}

class CScene_BattleResult : public Game
{
private:
	CBattle_ResultSystem* m_pResultSystem;
private:
	Image* m_pBlackBack;
	Image* m_pResultBackground;	

	SystemUIDialog* m_pPlayerShipListView;
	SystemUIDialog* m_pComputerShipListView;

	std::vector<std::string> m_vRemainPlayerShips;
	std::vector<std::string> m_vRemainComputerShips;
	
public:
	CScene_BattleResult();
	~CScene_BattleResult();

	virtual void initialize(HWND hwnd)	override;
	virtual void update()				override;
	virtual void release()				override;
	virtual void ai()					override;
	virtual void collisions()			override;
	virtual void render()				override;
	virtual void releaseAll()			override;
	virtual void resetAll()				override;
};

#endif // !_SCENE_BATTLE_RESULT_H
