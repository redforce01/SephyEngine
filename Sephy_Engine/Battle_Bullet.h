#ifndef _BATTLE_BULLET_H
#define _BATTLE_BULLET_H
#define WIN32_LEAN_AND_MEAN

class CBattle_Bullet;

#include "image.h"
#include "entity.h"

namespace battleBulletNS
{
	const std::string ERROR_MESSAGE = "Battle - Bullet Initialize Failed";
	const std::string BULLET_WHITE = "Bullet_White";
	const std::string BULLET_RED = "Bullet_Red";
	const float BULLET_GRAVITY = 500.f;
	const float BULLET_RADIUS = 5.0f;
	const float SPRITE_SPEED = 0.04f;

	const float DAMAGE_RATE_MIN = 0.143f;
	const float DAMAGE_RATE_MAX = 1.0f;
}


class CBattle_Ship;
class CBattle_Bullet
{
private:
	Game*			m_pGame;
	Graphics*		m_pGraphics;
	CBattle_Ship*	m_pFiredShip;
private:
	std::string m_strBulletKey;
	std::string m_strExplosionKey;
	std::string m_strMissKey;
	Entity*	m_pBullet;
	Image*	m_pMiss;
	Image*	m_pExplosion;
	bool	m_bPlayerShoot;
	int		m_nExplosionSpriteNumber;
	int		m_nMissSpriteNumber;
	int		m_nExplosionMaxFrame;
	int		m_nMissMaxFrame;
	float	m_nDeltaTime;
private:
	std::string m_strMissSoundName;

private:
	//==========================================
	float m_x, m_y;
	float m_startX, m_startY;
	float m_targetX, m_targetY;
	float m_radius;
	//==========================================
	float m_fAimAngle;
	float m_fBulletSpeed;
	float m_fDamage;
	float m_fGravity;
	float m_fDeltaTime;
	float m_fArriveTime;
	float m_fAirTime;
	float m_fV_X;
	float m_fV_Y;
private:
	bool m_bArrived;
	bool m_bExplosion;
	bool m_bActive;
	bool m_bHit;
public:
	CBattle_Bullet();
	~CBattle_Bullet();

	bool initialize(CBattle_Ship* pFiredShip, float startX, float startY, float targetX, float targetY, float speed, float damage, bool bPlayerShoot);
	bool initializeSprite(std::string explosionKey, int ExplosionMaxFrame, std::string missKey, int missMaxFrame);

	void update(float frameTime);
	void render();

	void collision(CBattle_Ship* pShip);
	//================================================
	// Member Functions
	//================================================

	void setupMissSoundName(std::string missSoundName)
	{
		m_strMissSoundName = missSoundName;
	}

	void moveX(float distance);
	void moveY(float distance);

	void PreCalculate();
	bool updateBullet(float frameTime);


	//================================================
	// Getter Functions
	//================================================

	bool IsArrived() const
	{
		return m_bArrived;
	}

	bool IsActive() const
	{
		return m_bActive;
	}
};

#endif // !_BATTLE_BULLET_H
