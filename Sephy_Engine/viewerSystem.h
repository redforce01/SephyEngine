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
#include "objectControlViewer.h"
#include "eventViewer.h"

class MapSystem;
class CameraSystem;
class ViewerSystem : public SystemBase
{
private:
	bool m_bUIMouseOver;
	bool m_bUIHasFocus;

	// Each Viewer Pointer
private:
	ResourceTreeViewer*		m_pResTreeViewer;
	MapTileViewer*			m_pMapTileViewer;
	MinimapViewer*			m_pMinimapViewer;
	ControlViewer*			m_pControlViewer;
	StatsViewer*			m_pStatsViewer;
	LogViewer*				m_pLogViewer;
	ObjectControlViewer*	m_pObjectControlViewer;
	EventViewer*			m_pEventViewer;
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
	bool checkViewerFocus();
	// =========================================
	// Set Momory Linker Connect Functions
	// =========================================
	void setMemoryLinkCameraSystem(CameraSystem* pCameraSystem)
	{
		m_pMinimapViewer->setMemoryLinkCameraSystem(pCameraSystem);
		m_pStatsViewer->setMemoryLinkCameraSystem(pCameraSystem);
	}
	void setMemoryLinkMapSystem(MapSystem* pMapSystem)
	{
		m_pMapSystem = pMapSystem;
		m_pMapTileViewer->setMemoryLinkMapSystem(pMapSystem);
		m_pControlViewer->setMemoryLinkMapSystem(pMapSystem);
		m_pObjectControlViewer->setMemoryLinkMapSystem(pMapSystem);
		m_pEventViewer->setMemoryLinkMapSystem(pMapSystem);
	}
	// =========================================
	// Getter Functions
	// =========================================
	inline bool getUIMouseOver() const
	{
		return m_bUIMouseOver;
	}
	inline bool getUIHasFocus() const
	{
		return m_bUIHasFocus;
	}

	// =========================================
	// Getter : Each Viewer Pointer
	// =========================================
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
