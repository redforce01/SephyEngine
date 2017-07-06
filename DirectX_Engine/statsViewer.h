#ifndef _STATSVIEWER_H
#define _STATSVIEWER_H

class StatsViewer;

#include "systemDebugStats.h"

namespace statsViewerNS
{
	const std::string KEY_WORLD = "worldTime";
	const std::string KEY_DELTA = "deltaTime";
	const std::string KEY_FPS = "fps";
	const std::string KEY_MOUSE = "mouse";
	const std::string KEY_CPU = "cpu";
	const std::string KEY_SCENE = "scene";
	const std::string KEY_CAMERA = "camera";
}

class CameraSystem;
class StatsViewer : public SystemDebugStats
{
private:
	Game* m_pGame;
	CameraSystem* m_pCameraSystem;
public:
	StatsViewer();
	~StatsViewer();

	virtual bool initialize(Graphics* g, Input* i) override;
	virtual void update(float frameTime) override;
	virtual void render() override;

	// Set Game Pointer For Stats Information
	void setGamePtr(Game* gamePtr)
	{ m_pGame = gamePtr; }	
	// Set CameraSystem Pointer For CameraPos Information
	void setMemoryLinkCameraSystem(CameraSystem* pCameraSystem)
	{ m_pCameraSystem = pCameraSystem; }

};

#endif // !_STATSVIEWER_H
