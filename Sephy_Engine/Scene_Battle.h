#ifndef _SCENE_BATTLE_H
#define _SCENE_BATTLE_H
#define WIN32_LEAN_AND_MEAN

class CScene_Battle;

#include "game.h"
#include "Battle_MainSystem.h"

class CScene_Battle : public Game
{
private:
	CBattle_MainSystem* m_pBattleMainSystem;


public:
	CScene_Battle();
	~CScene_Battle();

	virtual void initialize(HWND hwnd)	override;
	virtual void update()				override;
	virtual void release()				override;
	virtual void ai()					override;
	virtual void collisions()			override;
	virtual void render()				override;
	virtual void releaseAll()			override;
	virtual void resetAll()				override;
};

#endif // !_SCENE_BATTLE_H
