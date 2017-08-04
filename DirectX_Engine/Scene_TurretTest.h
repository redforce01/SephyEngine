#pragma once
#include "game.h"

#include "Battle_Ship.h"

struct Bullet
{
	float startX, startY;
	float currentX, currentY;
	float targetX, targetY;
	float deltaTime = 0.f;
	float arriveTime = 0.f;
	float angle = 0.f;
	float aimAngle = 0.f;
	float fg = 0.f;
	float fV_X = 0.f;
	float fV_Y = 0.f;
	Image* bullet;
	bool bFire = false;


	void PreFunction();
	bool MoveFunction(float frameTime);
};


class Scene_TurretTest : public Game
{
private:
	std::vector<Bullet*> m_vBullet;
	CBattle_Ship* m_pShip;

	float m_targetX, m_targetY;


public:
	Scene_TurretTest();
	~Scene_TurretTest();

	virtual void initialize(HWND hwnd)	override;
	virtual void update()				override;
	virtual void release()				override;
	virtual void ai()					override;
	virtual void collisions()			override;
	virtual void render()				override;
	virtual void releaseAll()			override;
	virtual void resetAll()				override;
};

