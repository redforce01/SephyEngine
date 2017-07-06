#ifndef _VIEWERSYSTEM_H
#define _VIEWERSYSTEM_H

class ViewerSystem;

#include "systemBase.h"
#include "resourceTreeViewer.h"
#include "mapTileViewer.h"
#include "minimapViewer.h"
#include "controlViewer.h"
#include "statsViewer.h"
#include "logViewer.h"

class MapSystem;
class CameraSystem;
class ViewerSystem : public SystemBase
{
private:
	bool bUIMouseOver;

	ResourceTreeViewer* m_pResTreeViewer;
	MapTileViewer*		m_pMapTileViewer;
	MinimapViewer*		m_pMinimapViewer;
	ControlViewer*		m_pControlViewer;
	StatsViewer*		m_pStatsViewer;
	LogViewer*			m_pLogViewer;
private:
	// Other System Pointer
	MapSystem* m_pMapSystem;
	bool m_bMapSystemWorkableSetup;
public:
	ViewerSystem();
	~ViewerSystem();

	virtual bool initialize(Game* gamePtr) override;
	virtual void update(float frameTime) override;
	virtual void render();

	bool checkMouseOver();
	//=========================================
	// Set Momory Linker Connect Functions
	//=========================================
	void setMemoryLinkCameraSystem(CameraSystem* pCameraSystem)
	{
		m_pMinimapViewer->setMemoryLinkCameraSystem(pCameraSystem);
	}
	void setMemoryLinkMapSystem(MapSystem* pMapSystem)
	{
		m_pMapSystem = pMapSystem;
		m_pMapTileViewer->setMemoryLinkMapSystem(pMapSystem);
		m_pControlViewer->setMemoryLinkMapSystem(pMapSystem);
	}
	//=========================================
	// Getter Functions
	//=========================================
	inline bool getUIMouseOver() const
	{
		return bUIMouseOver;
	}
	inline ResourceTreeViewer* getResTreeViewer() const
	{
		return m_pResTreeViewer;
	}
	inline MapTileViewer* getMapTileViewer() const
	{
		return m_pMapTileViewer;
	}
	inline MinimapViewer* getMinimapViewer() const
	{
		return m_pMinimapViewer;
	}
	inline LogViewer* getLogViewer() const
	{
		return m_pLogViewer;
	}
};

#endif // !_VIEWERSYSTEM_H
