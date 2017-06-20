#ifndef _SCENEMAIN_H
#define _SCENEMAIN_H

class scene_Main;

#include "game.h"
#include "gameObject.h"
#include <string>

#include "render2DComponent.h"

namespace mainNS
{
	const UCHAR ESCAPE_KEY = VK_ESCAPE;
	const UCHAR SCENE_CHANGE_KEY = VK_SPACE;
}

class scene_Main : public Game
{
public:
	scene_Main();
	~scene_Main();

	virtual void initialize(HWND hwnd)	override;
	virtual void update()				override;
	virtual void release()				override;
	virtual void ai()					override;
	virtual void collisions()			override;
	virtual void render()				override;
	virtual void releaseAll()			override;
	virtual void resetAll()				override;
};

#endif // !_SCENEMAIN_H
