#ifndef _UNITTOOL_UNITCONTROL_SYSTEM_H
#define _UNITTOOL_UNITCONTROL_SYSTEM_H
#define WIN32_LEAN_AND_MEAN

class CUnitTool_UnitControlSystem;

#include "systemBase.h"
#include "Battle_Ship.h"

class CUnitTool_UnitControlSystem : public SystemBase
{
private:
	bool m_bUpdatable;
	bool m_bClicked;


	int m_nSelectUnitNumber;
	bool m_bSelectPlayerUnit;
private:
	std::vector<CBattle_Ship*> m_vPlayerShips;
	std::vector<CBattle_Ship*> m_vComputerShips;
	std::vector<CBattle_Bullet*> m_vBulletInBattle;

public:
	CUnitTool_UnitControlSystem();
	~CUnitTool_UnitControlSystem();


	virtual bool initialize(Game* gamePtr) override;
	virtual void update(float frameTime) override;
	virtual void render() override;
	void ai();
	void collision();

	//==============================================
	// Member Functions
	//==============================================

	void updateUnitControl(float frameTime);
	void updateUnitDelete(float frameTime);



	void addPlayerShip(CBattle_Ship* pShip)
	{
		m_vPlayerShips.emplace_back(pShip);
	}
	void addComputerShip(CBattle_Ship* pShip)
	{
		m_vComputerShips.emplace_back(pShip);
	}
	void addBulletInBattle(CBattle_Bullet* pBullet)
	{
		m_vBulletInBattle.emplace_back(pBullet);
	}

	void resetAllUnits();
	
	void moveX(float distance);
	void moveY(float distance);

	//==============================================
	// Setter Functions
	//==============================================
	
	void setUpdatable(bool bUpdate)
	{
		m_bUpdatable = bUpdate;
	}

	//==============================================
	// Getter Functions
	//==============================================

	bool getUpdatable() const
	{
		return m_bUpdatable;
	}

	std::vector<CBattle_Ship*> getPlayerShips() const
	{
		return m_vPlayerShips;
	}
	std::vector<CBattle_Ship*> getComputerShips() const
	{
		return m_vComputerShips;
	}
};

#endif // !_UNITTOOL_UNITCONTROL_SYSTEM_H
