#ifndef _BATTLE_UI_DUMMYSHIP_H
#define _BATTLE_UI_DUMMYSHIP_H
#define WIN32_LEAN_AND_MEAN

class CBattle_UI_DummyShip;

#include "Battle_Ship.h"

namespace battleUIDummyShipNS
{
	const float DEFAULT_SETUP_TIME = 3.f;
	const COLOR_ARGB DUMMY_FILTER = SETCOLOR_ARGB(128, 16, 16, 16);
}

class CBattle_UI_DummyShip : public CBattle_Ship
{
private:
	float	m_fDeltaTime;
	float	m_fSetupTime;
	int		m_nShipIndex;
	bool	m_bSetup;
public:
	CBattle_UI_DummyShip();
	~CBattle_UI_DummyShip();

	bool initialize(Game* gamePtr, std::string shipName, int shipIndex, float setupTime = 3.0f);
	void update(float frameTime);
	void render();

	//=================================================
	// Member Functions
	//=================================================

	void setupPosition(float x, float y)
	{
		CBattle_Ship::setCurrentCenterX(x);
		CBattle_Ship::setCurrentCenterY(y);
	}

	void moveX(float fDistance)
	{
		CBattle_Ship::moveX(fDistance);
	}
	void moveY(float fDistance)
	{
		CBattle_Ship::moveY(fDistance);
	}

	//=================================================
	// Getter Functions
	//=================================================

	bool getSetup() const
	{
		return m_bSetup;
	}	

	int getShipIndex() const
	{
		return m_nShipIndex;
	}
};

#endif // !_BATTLE_UI_DUMMYSHIP_H
