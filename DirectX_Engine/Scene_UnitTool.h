#pragma once
#include "game.h"
#include "UnitTool_MainSystem.h"

class CScene_UnitTool : public Game
{
private:
	CUnitTool_MainSystem* m_pUnitToolMainSystem;

public:
	CScene_UnitTool();
	~CScene_UnitTool();

	virtual void initialize(HWND hwnd)	override;
	virtual void update()				override;
	virtual void release()				override;
	virtual void ai()					override;
	virtual void collisions()			override;
	virtual void render()				override;
	virtual void releaseAll()			override;
	virtual void resetAll()				override;
};

