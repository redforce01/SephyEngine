#ifndef _SCENE_BATTLE_H
#define _SCENE_BATTLE_H

class Scene_Battle;

#include "game.h"

class Scene_Battle : public Game
{
private:
	Image* m_pTop;
	Image* m_pBody;
	Image* m_pBottom;
	Image* m_pShadow;
	Image* m_pWave;
	Image* m_pSunken;
	Image* m_pSunkenSh;
	Image* m_Back;
public:
	Scene_Battle();
	~Scene_Battle();

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
