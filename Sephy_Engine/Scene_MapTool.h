#ifndef _SCENE_MAPTOOL_H
#define _SCENE_MAPTOOL_H

class CScene_MapTool;

#include "game.h"
#include "mapSystem.h"
#include "CameraSystem.h"
#include "viewerSystem.h"

namespace MapToolNS
{
	const UCHAR ESCAPE_KEY = VK_ESCAPE;
	const UCHAR SCENE_CHANGE_KEY = VK_SPACE;
}

class CScene_MapTool : public Game	// Scene
{
private:
	MapSystem* mapSystem;
	CameraSystem* cameraSystem;
	ViewerSystem* viewerSystem;

public:
	CScene_MapTool();
	~CScene_MapTool();

	virtual void initialize(HWND hwnd)	override;
	virtual void update()				override;
	virtual void release()				override;
	virtual void ai()					override;
	virtual void collisions()			override;
	virtual void render()				override;
	virtual void releaseAll()			override;
	virtual void resetAll()				override;
};

#endif // !_SCENE_MAPTOOL_H