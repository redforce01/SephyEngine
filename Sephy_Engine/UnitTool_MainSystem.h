#pragma once
#include "systemBase.h"
#include "UnitTool_UISystem.h"
#include "UnitTool_CameraSystem.h"
#include "UnitTool_MapSystem.h"
#include "UnitTool_UnitControlSystem.h"
#include "UnitTool_SceneControlSystem.h"

class CUnitTool_MainSystem : public SystemBase
{
private:
	CUnitTool_UISystem*				m_pUISystem;
	CUnitTool_CameraSystem*			m_pCameraSystem;
	CUnitTool_MapSystem*			m_pMapSystem;
	CUnitTool_UnitControlSystem*	m_pUnitControlSystem;
	CUnitTool_SceneControlSystem*	m_pSceneControlSystem;
public:
	CUnitTool_MainSystem();
	~CUnitTool_MainSystem();

	virtual bool initialize(Game* gamePtr) override;
	virtual void update(float frameTime) override;
	virtual void render() override;
	virtual void ai();
	virtual void collision();
};

