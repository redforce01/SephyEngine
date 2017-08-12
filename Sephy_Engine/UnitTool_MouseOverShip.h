#ifndef _UNITTOOL_MOUSEOVERSHIP_H
#define _UNITTOOL_MOUSEOVERSHIP_H
#define WIN32_LEAN_AND_MEAN

#include "Battle_Ship.h"

class CUnitTool_RespawnListViewer;
class CUnitTool_UnitControlSystem;
class CUnitTool_MouseOverShip
{
private:
	CUnitTool_UnitControlSystem* m_pUnitControlSystem;
	CUnitTool_RespawnListViewer* m_pRespawnListViewer;
public:
	void setMemoryLinkUnitControlSystem(CUnitTool_UnitControlSystem* pUnitControlSystem)
	{
		m_pUnitControlSystem = pUnitControlSystem;
	}
	void setMemoryLinkRespawnListViewer(CUnitTool_RespawnListViewer* pRespawnListViewer)
	{
		m_pRespawnListViewer = pRespawnListViewer;
	}
private:
	Graphics* m_pGraphics;
	Input* m_pInput;

private:
	CBattle_Ship* m_pOverlabShip;
	bool m_bOverlabOn;
public:
	CUnitTool_MouseOverShip();
	~CUnitTool_MouseOverShip();

	bool initialize(Graphics* g, Input* i);
	void update(float frameTime);
	void render();

	void setupOverlabShip(CBattle_Ship* ship)
	{
		m_bOverlabOn = true;
		m_pOverlabShip = ship;
	}
};

#endif // !_UNITTOOL_MOUSEOVERSHIP_H
