#ifndef _BATTLE_TURERET_H
#define _BATTLE_TURERET_H
#define WIN32_LEAN_AND_MEAN

class CBattle_Turret;

#include "Battle_TurretParser.h"


class CBattle_Turret
{
private:
	Graphics* m_pGraphics;

private:
	//=================================================
	int			m_TurretID;
	std::string m_strTurretName;
	float		m_fTurretRotateSpeed;
	float		m_fFireRate;
	int			m_nTurretBarrelCount;
	//=================================================
	float		m_fBulletSpeed;
	float		m_fBulletDamage;
	//=================================================
	std::string m_strBulletTextureKey_Hit;
	std::string m_strBulletTextureKey_Miss;
	int			m_nBulletMaxFrame_Hit;
	int			m_nBulletMaxFrame_Miss;
	//=================================================
	std::string m_strSoundFileName_Fire;
	std::string m_strSoundFileName_Miss;

public:
	CBattle_Turret();
	~CBattle_Turret();

	bool initialize(Graphics* g, std::string strTurretName);
	void update(float frameTime);
	void render();

	//=================================================
	// Member Functions
	//=================================================

private:
	CBattle_TurretParser m_turretDataParser;

};

#endif // !_BATTLE_TURERET_H
