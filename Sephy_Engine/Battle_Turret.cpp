#include "stdafx.h"
#include "Battle_Turret.h"
#include "Battle_Ship.h"
#include "Battle_UnitSystem.h"
#include "UnitTool_UnitControlSystem.h"

CBattle_Turret::CBattle_Turret()
{
	m_pShip					= nullptr;
	m_pGraphics				= nullptr;
	//=================================================
	m_TurretID				= -1;
	m_fTurretRotateSpeed	= 0.f;
	m_fFireReteOriginal		= 0.f;
	m_fFireRate				= 0.f;
	m_nTurretBarrelCount	= -1;
	//=================================================
	m_fBulletSpeed			= 0.f;
	m_fBulletDamage			= 0.f;
	//=================================================
	m_nBulletMaxFrame_Hit	= 0;
	m_nBulletMaxFrame_Miss	= 0;
	//=================================================
	m_bReloading = false;
}


CBattle_Turret::~CBattle_Turret()
{
}

bool CBattle_Turret::initialize(Graphics * g, std::string strTurretName, CBattle_Ship* pShip)
{
	m_pGraphics = g;
	m_pShip = pShip;

	auto vData = m_turretDataParser.loadTurretData(strTurretName);
	if (vData.size() <= 0)
		return false;

	bool success = false;
	try
	{
		setupTurretDataFormat(vData);
		success = true;
	}
	catch (...)
	{
		MessageBox(g_hWndEngine, battleTurretNS::ERROR_MESSAGE.c_str(), "Error", MB_OK);
	}

	return success;
}

void CBattle_Turret::update(float frameTime)
{
	m_turretX = m_pShip->getCurrentCenterX();
	m_turretY = m_pShip->getCurrentCenterY();

	if (m_bReloading)
	{
		m_fDeltaTime += frameTime;
		if (m_fDeltaTime >= m_fFireRate)
		{
			m_fDeltaTime = 0;
			m_bReloading = false;
		}
	}
}

void CBattle_Turret::render()
{
}

void CBattle_Turret::Fire(float targetX, float targetY)
{
	if (m_bReloading)
		return;
	
	bool bPlayerShip = m_pShip->getIsPlayerShip();
	for (int i = 0; i < m_nTurretBarrelCount; i++)
	{
		auto interpolateRand = RANDOM_MAKER->GetInt(-20, 20);
		float startX = m_turretX;
		float startY = m_turretY;
		float aimX = targetX;
		float aimY = targetY;
		startX += interpolateRand;
		startY += interpolateRand;
		aimX += interpolateRand;
		aimY += interpolateRand;

		CBattle_Bullet* bullet = new CBattle_Bullet;
		bullet->initialize(m_pShip, startX, startY, aimX, aimY, m_fBulletSpeed, m_fBulletDamage, bPlayerShip);
		bullet->initializeSprite(m_strBulletTextureKey_Hit, m_nBulletMaxFrame_Hit, m_strBulletTextureKey_Miss, m_nBulletMaxFrame_Miss);
		m_pShip->getBattleUnitSystem()->addBulletInBattle(bullet);

		m_fFireRate = m_fFireReteOriginal;
		if (RANDOM_MAKER->GetBool())
		{
			m_fFireRate += RANDOM_MAKER->GetInt(0, 100) / 1000;
		}
		else
			m_fFireRate -= RANDOM_MAKER->GetInt(0, 100) / 1000;

		SOUNDMANAGER->play(m_strSoundFileName_Fire, g_fSoundMasterVolume * g_fSoundEffectVolume);
	}	
	m_bReloading = true;
}

void CBattle_Turret::FireInUnitTool(float targetX, float targetY)
{
	if (m_bReloading)
		return;

	bool bPlayerShip = m_pShip->getIsPlayerShip();
	for (int i = 0; i < m_nTurretBarrelCount; i++)
	{
		auto interpolateRand = RANDOM_MAKER->GetInt(-20, 20);
		float startX = m_turretX;
		float startY = m_turretY;
		float aimX = targetX;
		float aimY = targetY;
		startX += interpolateRand;
		startY += interpolateRand;
		aimX += interpolateRand;
		aimY += interpolateRand;

		CBattle_Bullet* bullet = new CBattle_Bullet;
		bullet->initialize(m_pShip, startX, startY, aimX, aimY, m_fBulletSpeed, m_fBulletDamage, bPlayerShip);
		bullet->initializeSprite(m_strBulletTextureKey_Hit, m_nBulletMaxFrame_Hit, m_strBulletTextureKey_Miss, m_nBulletMaxFrame_Miss);
		m_pShip->getUnitToolUnitControlSystem()->addBulletInBattle(bullet);

		m_fFireRate = m_fFireReteOriginal;
		if (RANDOM_MAKER->GetBool())
		{
			m_fFireRate += RANDOM_MAKER->GetInt(0, 100) / 1000;
		}
		else
			m_fFireRate -= RANDOM_MAKER->GetInt(0, 100) / 1000;

		SOUNDMANAGER->play(m_strSoundFileName_Fire, g_fSoundMasterVolume * g_fSoundEffectVolume);
	}
	m_bReloading = true;
}

void CBattle_Turret::setupTurretDataFormat(std::vector<std::string> vArray)
{
	if (vArray.size() < 0)
		return;

	int dataNumber = 0;

	m_TurretID					= std::stoi(vArray[dataNumber]);
	m_strTurretName				= vArray[++dataNumber];
	m_fTurretRotateSpeed		= std::stof(vArray[++dataNumber]);
	m_fFireReteOriginal			= std::stof(vArray[++dataNumber]);
	m_nTurretBarrelCount		= std::stoi(vArray[++dataNumber]);
	m_fBulletSpeed				= std::stof(vArray[++dataNumber]);
	m_fBulletDamage				= std::stof(vArray[++dataNumber]);
	m_strBulletTextureKey_Hit	= vArray[++dataNumber];
	m_strBulletTextureKey_Miss	= vArray[++dataNumber];
	m_nBulletMaxFrame_Hit		= std::stoi(vArray[++dataNumber]);
	m_nBulletMaxFrame_Miss		= std::stoi(vArray[++dataNumber]);
	m_strSoundFileName_Miss		= vArray[+dataNumber];
	m_strSoundFileName_Fire		= vArray[++dataNumber];
}
