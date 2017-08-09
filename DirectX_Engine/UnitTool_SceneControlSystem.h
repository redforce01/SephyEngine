#ifndef _UNITTOOL_SCENECONTROL_SYSTEM_H
#define _UNITTOOL_SCENECONTROL_SYSTEM_H
#define WIN32_LEAN_AND_MEAN

class CUnitTool_SceneControlSystem;

#include "systemBase.h"
#include "UnitTool_SceneControlViewer.h"

class CUnitTool_SceneControlSystem : public SystemBase
{
private:
	CUnitTool_SceneControlViewer m_SceneControlViewer;

public:
	CUnitTool_SceneControlSystem();
	~CUnitTool_SceneControlSystem();

	virtual bool initialize(Game* gamePtr) override;
	virtual void update(float frameTime) override;
	virtual void render() override;

	void setMemoryLinkUnitControlSystem(CUnitTool_UnitControlSystem* pUnitControlSystem)
	{
		m_SceneControlViewer.setMemoryLinkUnitControlSystem(pUnitControlSystem);
	}
	void setMemoryLinkRespawnListViewer(CUnitTool_RespawnListViewer* pRespawnListViewer)
	{
		m_SceneControlViewer.setMemoryLinkRespawnListViewer(pRespawnListViewer);
	}
};

#endif // !_UNITTOOL_SCENECONTROL_SYSTEM_H
