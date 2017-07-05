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
}

class StatsViewer : public SystemDebugStats
{
private:
	Game* pGame;

public:
	StatsViewer();
	~StatsViewer();

	virtual bool initialize(Graphics* g, Input* i) override;
	virtual void update(float frameTime) override;
	virtual void render() override;

	// Set Game Pointer For Stats Information
	void setGamePtr(Game* gamePtr)
	{ pGame = gamePtr; }
};

#endif // !_STATSVIEWER_H
