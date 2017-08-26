#ifndef _SCENE_INTRO_H
#define _SCENE_INTRO_H
#define WIN32_LEAN_AND_MEAN

#include "game.h"
#include "Intro_MainSystem.h"

class CScene_Intro : public Game
{
	CIntro_MainSystem* m_pIntroMainSystem;
public:
	CScene_Intro();
	~CScene_Intro();

	virtual void initialize(HWND hwnd)	override;
	virtual void update()				override;
	virtual void release()				override;
	virtual void ai()					override;
	virtual void collisions()			override;
	virtual void render()				override;
	virtual void releaseAll()			override;
	virtual void resetAll()				override;
};

#endif // !_SCENE_INTRO_H
