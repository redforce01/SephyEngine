#ifndef _SCENEMAPTOOL_H
#define _SCENEMAPTOOL_H

class Scene_Maptool;

#include "game.h"
#include "mapSystem.h"
#include "CameraSystem.h"
#include "viewerSystem.h"

namespace MapToolNS
{
	const UCHAR ESCAPE_KEY = VK_ESCAPE;
	const UCHAR SCENE_CHANGE_KEY = VK_SPACE;
}

class Scene_MapTool : public Game
{
private:
	MapSystem* mapSystem;
	CameraSystem* cameraSystem;
	ViewerSystem* viewerSystem;

public:
	Scene_MapTool();
	~Scene_MapTool();

	virtual void initialize(HWND hwnd)	override;
	virtual void update()				override;
	virtual void release()				override;
	virtual void ai()					override;
	virtual void collisions()			override;
	virtual void render()				override;
	virtual void releaseAll()			override;
	virtual void resetAll()				override;
};

#endif // !_SCENEMAPTOOL_H