#include "stdafx.h"
#include "Battle_Turret.h"


CBattle_Turret::CBattle_Turret()
{
	m_pGraphics = nullptr;
	//=================================================
	m_TurretID				= -1;
	m_fTurretRotateSpeed	= 0.f;
	m_fFireRate				= 0.f;
	m_nTurretBarrelCount	= -1;
	//=================================================
	m_fBulletSpeed			= 0.f;
	m_fBulletDamage			= 0.f;
	//=================================================
	m_nBulletMaxFrame_Hit	= 0;
	m_nBulletMaxFrame_Miss	= 0;
}


CBattle_Turret::~CBattle_Turret()
{
}

bool CBattle_Turret::initialize(Graphics * g, std::string strTurretName)
{
	m_pGraphics = g;

	auto vData = m_turretDataParser.loadTurretData(strTurretName);
	if (vData.size() <= 0)
		return false;

	return false;
}

void CBattle_Turret::update(float frameTime)
{
}

void CBattle_Turret::render()
{
}
