#ifndef _BATTLE_TURERET_H
#define _BATTLE_TURERET_H
#define WIN32_LEAN_AND_MEAN

class CBattle_Turret;

#include "Battle_TurretParser.h"
#include "Battle_Bullet.h"

namespace battleTurretNS
{
	const std::string ERROR_MESSAGE = "Battle Ship-Turret Initialize Failed";
}

class CBattle_Ship;
class CBattle_Turret
{
private:
	Graphics* m_pGraphics;
	CBattle_Ship* m_pShip;
private:
	//=================================================
	int			m_TurretID;
	std::string m_strTurretName;
	float		m_fTurretRotateSpeed;
	float		m_fFireReteOriginal;
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
private:
	float m_turretX, m_turretY;

	float m_fDeltaTime;
	bool m_bReloading;
	
public:
	CBattle_Turret();
	~CBattle_Turret();

	bool initialize(Graphics* g, std::string strTurretName, CBattle_Ship* pShip);
	void update(float frameTime);
	void render();

	//=================================================
	// Member Functions
	//=================================================

	void Fire(float targetX, float targetY);
	void FireInUnitTool(float targetX, float targetY);

	bool IsReloading() const
	{
		return m_bReloading;
	}
private:
	void setupTurretDataFormat(std::vector<std::string> vArray);

private:
	CBattle_TurretParser m_turretDataParser;

};

#endif // !_BATTLE_TURERET_H
