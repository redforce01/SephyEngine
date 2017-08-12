#pragma once
#include "systemBase.h"
#include "UnitTool_UIViewer.h"
#include "UnitTool_UnitMakeViewer.h"
#include "UnitTool_ShipDataSetter.h"
#include "UnitTool_SceneControlViewer.h"
#include "UnitTool_RespawnListViewer.h"
#include "UnitTool_MouseOverShip.h"

class CUnitTool_UnitControlSystem;
class CUnitTool_UISystem : public SystemBase
{
private:
	CUnitTool_UIViewer*				m_pUIViewer;
	CUnitTool_UnitMakeViewer*		m_pUnitMakerViewer;
	CUnitTool_ShipDataSetter*		m_pShipDataSetter;
	CUnitTool_RespawnListViewer*	m_pRespawnListViewer;
	CUnitTool_MouseOverShip*		m_pMouseOverShip;
public:
	CUnitTool_UISystem();
	~CUnitTool_UISystem();

	virtual bool initialize(Game* gamePtr) override;
	virtual void update(float frameTime) override;
	virtual void render() override;

	void setMemoryLinkUnitControlSystem(CUnitTool_UnitControlSystem* pUnitControlSystem)
	{
		m_pMouseOverShip->setMemoryLinkUnitControlSystem(pUnitControlSystem);
	}

	CUnitTool_RespawnListViewer* getRespawnListViewer() const
	{
		return m_pRespawnListViewer;
	}
};

