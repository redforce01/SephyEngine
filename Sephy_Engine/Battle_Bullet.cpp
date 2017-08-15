#include "stdafx.h"
#include "Battle_Bullet.h"
#include "Battle_Ship.h"

CBattle_Bullet::CBattle_Bullet()
{
	m_pGraphics		= nullptr;
	m_pFiredShip	= nullptr;
	//========================================
	m_strBulletKey	= battleBulletNS::BULLET_RED;
	m_pBullet		= nullptr;
	m_pMiss			= nullptr;
	m_pExplosion	= nullptr;
	m_bPlayerShoot	= false;
	m_nExplosionSpriteNumber	= 0;
	m_nMissSpriteNumber			= 0;
	m_nExplosionMaxFrame		= 0;
	m_nMissMaxFrame				= 0;
	//========================================
	m_x				= 0.f;
	m_y				= 0.f;
	m_startX		= 0.f;
	m_startY		= 0.f;
	m_targetX		= 0.f;
	m_targetY		= 0.f;
	m_radius		= battleBulletNS::BULLET_RADIUS;
	//========================================
	m_fBulletSpeed	= 0.f;
	m_fGravity		= battleBulletNS::BULLET_GRAVITY;
	m_fDamage		= 0.f;
	m_fAimAngle		= 0.f;
	m_fDeltaTime	= 0.f;
	m_fArriveTime	= 0.f;
	m_fAirTime		= 0.f;
	m_fV_X			= 0.f;
	m_fV_Y			= 0.f;
	m_nDeltaTime	= 0.f;
	//========================================
	m_bActive		= false;
	m_bArrived		= false;
	m_bExplosion	= false;
	m_bHit			= false;
}


CBattle_Bullet::~CBattle_Bullet()
{
	SAFE_DELETE(m_pBullet);
	SAFE_DELETE(m_pMiss);
	SAFE_DELETE(m_pExplosion);
}

bool CBattle_Bullet::initialize(CBattle_Ship* pFiredShip, float startX, float startY, float targetX, float targetY, float speed, float damage, bool bPlayerShoot)
{
	bool success = false;
	try
	{
		m_pFiredShip = pFiredShip;
		m_pGame = pFiredShip->getGamePtr();
		m_pGraphics = m_pGame->getGraphics();
		//==============================================
		m_x = m_startX = startX;
		m_y = m_startY = startY;
		m_targetX = targetX;
		m_targetY = targetY;
		m_fBulletSpeed = speed;
		m_fDamage = damage;
		m_bPlayerShoot = bPlayerShoot;
		//==============================================
		PreCalculate();


		//==============================================
		if (m_bPlayerShoot)
			m_strBulletKey = battleBulletNS::BULLET_WHITE;

		m_pBullet = new Entity;
		m_bActive = success = m_pBullet->initialize(m_pGame, 0, 0, 0, IMAGEMANAGER->getTexture(m_strBulletKey));
		m_pBullet->setCollisionType(entityNS::COLLISION_TYPE::CIRCLE);
		m_pBullet->setX(m_x);
		m_pBullet->setY(m_y);
	}
	catch (...)
	{
		MessageBox(g_hWndEngine, battleBulletNS::ERROR_MESSAGE.c_str(), "Error", MB_OK);
	}

	return success;
}

bool CBattle_Bullet::initializeSprite(std::string explosionKey, int ExplosionMaxFrame, std::string missKey, int missMaxFrame)
{
	bool success = false;
	try
	{
		m_strExplosionKey = explosionKey;
		m_strMissKey = missKey;
		m_nExplosionMaxFrame = ExplosionMaxFrame;
		m_nMissMaxFrame = missMaxFrame;

		std::string resultKey;
		if (m_nExplosionSpriteNumber < 10)
			resultKey = explosionKey + "0" + std::to_string(m_nExplosionSpriteNumber);
		else
			resultKey = explosionKey + std::to_string(m_nExplosionSpriteNumber);

		m_pExplosion = new Image;
		success = m_pExplosion->initialize(m_pGraphics, 0, 0, 0, IMAGEMANAGER->getTexture(resultKey));
		m_pExplosion->setX(m_x);
		m_pExplosion->setY(m_y);

		if (m_nMissSpriteNumber < 10)
			resultKey = missKey + "0" + std::to_string(m_nMissSpriteNumber);
		else
			resultKey = missKey + std::to_string(m_nMissSpriteNumber);

		m_pMiss = new Image;
		success = m_pMiss->initialize(m_pGraphics, 0, 0, 0, IMAGEMANAGER->getTexture(resultKey));
		m_pMiss->setX(m_x);
		m_pMiss->setY(m_y);
	}
	catch (...)
	{
		MessageBox(g_hWndEngine, battleBulletNS::ERROR_MESSAGE.c_str(), "Error", MB_OK);
	}

	return success;
}

void CBattle_Bullet::update(float frameTime)
{
	if (m_bActive == false)
		return;

	if (m_bArrived == false)
	{
		m_bArrived = updateBullet(frameTime);
		return;
	}

	if (m_bExplosion)
	{
		if (m_nExplosionSpriteNumber >= m_nExplosionMaxFrame)
			m_bActive = false;

		if (m_nDeltaTime < battleBulletNS::SPRITE_SPEED)
		{
			m_nDeltaTime += frameTime;
		}
		else
		{
			m_nDeltaTime = 0.f;
			std::string resultKey;
			if (m_nExplosionSpriteNumber < 10)
				resultKey = m_strExplosionKey + "0" + std::to_string(m_nExplosionSpriteNumber);
			else
				resultKey = m_strExplosionKey + std::to_string(m_nExplosionSpriteNumber);

			m_pExplosion->setTextureManager(IMAGEMANAGER->getTexture(resultKey));
			m_nExplosionSpriteNumber++;
		}
	}
	else
	{
		if (m_nMissSpriteNumber >= m_nMissMaxFrame)
			m_bActive = false;

		if (m_nDeltaTime < battleBulletNS::SPRITE_SPEED)
		{
			m_nDeltaTime += frameTime;
		}
		else
		{
			m_nDeltaTime = 0.f;
			std::string resultKey;
			if (m_nMissSpriteNumber < 10)
				resultKey = m_strMissKey + "0" + std::to_string(m_nMissSpriteNumber);
			else
				resultKey = m_strMissKey + std::to_string(m_nMissSpriteNumber);

			m_pMiss->setTextureManager(IMAGEMANAGER->getTexture(resultKey));
			m_nMissSpriteNumber++;
		}
	}
}

void CBattle_Bullet::render()
{
	if (m_bActive == false)
		return;

	if (MyUtil::getObjInScreen(m_x, m_y, m_pBullet->getWidth(), m_pBullet->getHeight(), g_fScreenWidth, g_fScreenHeight) == false)
		return;
	
	m_pGraphics->spriteBegin();
	if (m_bArrived == false)
	{
		m_pBullet->draw();
		return;
	}


	if (m_bExplosion)
	{
		m_pExplosion->draw();
	}
	else
	{
		m_pMiss->draw();
	}	
	m_pGraphics->spriteEnd();
}

void CBattle_Bullet::collision(CBattle_Ship * pShip)
{
	if (m_bActive == false)
		return;

	if (m_bArrived == false)
		return;

	if (m_bHit)
		return;
	
	auto shipX = pShip->getShipCollision().x;
	auto shipY = pShip->getShipCollision().y;
	auto shipRad = pShip->getShipCollision().radius;
	if (MyUtil::circleIncircle(m_x, m_y, m_radius, shipX, shipY, shipRad) == false)
		return;

	VECTOR2 collisionVector;
	//=========================================
	// ORIGINAL BULLET DMANAGE FUNCTION
	//=========================================

	auto parts = pShip->getShipRealParts();
	for (auto iter : parts)
	{
		if (m_pBullet->collidesWith(*iter.second, collisionVector))
		{
			m_bExplosion = true;
			m_bHit = true;
			
			if (RANDOM_MAKER->GetBool())
				m_fDamage += RANDOM_MAKER->GetInt(1, 20);
			else
				m_fDamage -= RANDOM_MAKER->GetInt(1, 20);

			pShip->HitDamage(m_fDamage * battleBulletNS::DAMAGE_RATE_MAX);
			break;
		}
		else
		{
			m_bExplosion = false;
			m_bHit = true;
			pShip->HitDamage(m_fDamage * battleBulletNS::DAMAGE_RATE_MIN);
			SOUNDMANAGER->play(m_strMissSoundName, g_fSoundMasterVolume * g_fSoundEffectVolume);
			break;
		}
	}
}

void CBattle_Bullet::moveX(float distance)
{
	m_x += distance;
	m_startX += distance;
	m_targetX += distance;
	m_pBullet->moveX(distance);
	m_pExplosion->moveX(distance);
	m_pMiss->moveX(distance);
}

void CBattle_Bullet::moveY(float distance)
{
	m_y += distance;
	m_startY += distance;
	m_targetY += distance;
	m_pBullet->moveY(distance);
	m_pExplosion->moveY(distance);
	m_pMiss->moveY(distance);
}

void CBattle_Bullet::PreCalculate()
{
	 // 초구탄속 & 중력 & 타겟 좌표를 이용한 각도 계산
	float a = (m_fGravity * powf(m_targetX - m_startX, 2.0)) / (2 * powf(m_fBulletSpeed, 2.0));
	float b = -(m_targetX - m_startX);
	float c = a + (m_startY - m_targetY);
	float D = sqrtf(b * b - 4 * a * c);

	float angle1 = 0.f;
	float angle2 = 0.f;

	// 허수제거
	if (D <= 0)
	{
		angle1 = 0.0f;
		angle2 = 0.0f;
	}

	angle1 = fabs(atan2f(-b + D, a + a));
	angle2 = fabs(atan2f(-b - D, a + a));

	// 두 각도중 작은 값 사용
	if (angle1 > angle2)
	{
		D = angle2;
		angle2 = angle1;
		angle1 = D;
	}

	angle1 = fabs(angle1 * 57.2957951); // 45도 이하의 각도값 ex) 1~45
										// END 초구탄속 & 중력 & 타겟 좌표를 이용한 각도 계산

	m_fAimAngle = D3DXToRadian(angle1); //함포 각도

	//체공 시간
	if (m_targetX > m_startX)
	{
		m_fArriveTime = (m_targetX - m_startX) / (m_fBulletSpeed * cos(m_fAimAngle));
	}
	else if (m_targetX < m_startX)
	{
		m_fArriveTime = fabs(m_startX - m_targetX) / (m_fBulletSpeed * cos(m_fAimAngle));
	}

	m_fV_X = ((m_targetX - m_startX) / m_fArriveTime);									//x값 변화
	m_fV_Y = (m_startY - m_targetY) / m_fArriveTime + m_fGravity * m_fArriveTime / 2.0; //y값 변화
}

bool CBattle_Bullet::updateBullet(float frameTime)
{
	m_fDeltaTime += frameTime;

	if (m_fDeltaTime >= m_fArriveTime)
		return true;

	float physicsX = m_fV_X * m_fDeltaTime;
	float physicsY = (m_fV_Y * m_fDeltaTime) - ((m_fGravity * m_fDeltaTime * m_fDeltaTime) / 2);

	m_x = m_startX + physicsX - (m_pBullet->getWidth() / 2);
	m_y = m_startY + -physicsY - (m_pBullet->getHeight() / 2);
	m_pBullet->setX(m_x);
	m_pBullet->setY(m_y);

	auto expWidth = m_pExplosion->getWidth();
	auto expHeight = m_pExplosion->getHeight();
	m_pExplosion->setX(m_x - (expWidth / 2));
	m_pExplosion->setY(m_y - (expHeight / 2));

	auto missWidth = m_pMiss->getWidth();
	auto missHeight = m_pMiss->getHeight();
	m_pMiss->setX(m_x - (missWidth / 2));
	m_pMiss->setY(m_y - (missHeight / 2));

	return false;
}