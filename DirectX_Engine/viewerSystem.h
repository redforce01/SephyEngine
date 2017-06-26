#pragma once
#ifndef _VIEWERSYSTEM_H
#define _VIEWERSYSTEM_H

class ViewerSystem;

#include "systemBase.h"
#include "resourceTreeViewer.h"
#include "mapTileViewer.h"
#include "minimapViewer.h"

class CameraSystem;
class ViewerSystem : public SystemBase
{
private:
	bool bUIMouseOver;

	ResourceTreeViewer* pResTreeViewer;
	MapTileViewer* pMapTileViewer;
	MinimapViewer* pMinimapViewer;
public:
	ViewerSystem();
	~ViewerSystem();

	virtual bool initialize(Game* gamePtr) override;
	virtual void update(float frameTime) override;
	virtual void render();

	void setMemoryLinkCameraSystem(CameraSystem* pCameraSystem) { pMinimapViewer->setMemoryLinkCameraSystem(pCameraSystem); }
	//=========================================
	// Getter Functions
	//=========================================
	inline bool getUIMouseOver() const
	{
		return bUIMouseOver;
	}
	inline ResourceTreeViewer* getResTreeViewer() const
	{
		return pResTreeViewer;
	}
	inline MapTileViewer* getMapTileViewer() const
	{
		return pMapTileViewer;
	}
	inline MinimapViewer* getMinimapViewer() const
	{
		return pMinimapViewer;
	}
};

#endif // !_VIEWERSYSTEM_H
