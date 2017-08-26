#pragma once

#include <sstream>
#include "game.h"
#include "World_MainSystem.h"

class CWorld_Scene : public Game
{
private:
	CWorld_MainSystem* m_pWorldMainSystem;

public:
	CWorld_Scene();
	~CWorld_Scene();

	virtual void initialize(HWND hwnd)	override;
	virtual void update()				override;
	virtual void release()				override;
	virtual void ai()					override;
	virtual void collisions()			override;
	virtual void render()				override;
	virtual void releaseAll()			override;
	virtual void resetAll()				override;
};

