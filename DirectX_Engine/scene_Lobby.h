#ifndef _SCENELOBBY_H
#define _SCENELOBBY_H

class Scene_Lobby;

#include "game.h"


class Scene_Lobby : public Game
{
private:


public:
	Scene_Lobby();
	~Scene_Lobby();

	virtual void initialize(HWND hwnd)	override;
	virtual void update()				override;
	virtual void release()				override;
	virtual void ai()					override;
	virtual void collisions()			override;
	virtual void render()				override;
	virtual void releaseAll()			override;
	virtual void resetAll()				override;
};

#endif // !_SCENELOBBY_H
