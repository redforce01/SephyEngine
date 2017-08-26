#ifndef _SCENE_BATTLE_RESULT_H
#define _SCENE_BATTLE_RESULT_H
#define WIN32_LEAN_AND_MEAN

#include "game.h"
#include "Battle_ResultMainSystem.h"

class CScene_BattleResult : public Game
{
private:
	CBattle_ResultMainSystem* m_pBattleResultMainSystem;
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
