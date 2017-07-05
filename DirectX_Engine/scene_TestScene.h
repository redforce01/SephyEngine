#pragma once

#include "game.h"


#include "image.h"

#include "entity.h"


class Scene_TestScene : public Game
{
private:
	RECT rcBoundingBox = RectMake(200, 200, 100, 100);
	bool m_bClicked = false;

	Image* m_pTestImage;

	Image* m_pTestShipTop;
	Image* m_pTestShipMiddle;
	Image* m_pTestShipBottom;

	Entity* m_pTestEntity;

public:
	Scene_TestScene();
	~Scene_TestScene();

	virtual void initialize(HWND hwnd)	override;
	virtual void update()				override;
	virtual void release()				override;
	virtual void ai()					override;
	virtual void collisions()			override;
	virtual void render()				override;
	virtual void releaseAll()			override;
	virtual void resetAll()				override;
};

