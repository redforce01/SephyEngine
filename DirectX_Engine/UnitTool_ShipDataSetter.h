#pragma once
#include "Battle_Ship.h"

class CUnitTool_UIViewer;
class CUnitTool_ShipDataSetter
{
private:
	Game* m_pGame;
	CUnitTool_UIViewer* m_pUnitToolUIViewer;
public:
	void setMemoryLinkUIViewer(CUnitTool_UIViewer* pUnitToolUIViewer)
	{
		m_pUnitToolUIViewer = pUnitToolUIViewer;
	}

private:
	CBattle_Ship* m_pSettingShip;
	

public:
	CUnitTool_ShipDataSetter();
	~CUnitTool_ShipDataSetter();
	
	bool initialize(Game* gamePtr);
	void setupShipData(std::string shipName);
};

