#pragma once

#include "image.h"

namespace worldshipNS
{
	const int degree = 0;
	const float scale = 0.3f;
};

class CWorld_Ship : public Image
{
private:
	Graphics* m_pGraphics;
	Input* m_pInput;

	std::string name;
	Image* top;
	Image* body;
	Image* middle;

	POINT pt;
	RECT rt;

	float degree;

	void move();
public:
	CWorld_Ship();
	~CWorld_Ship();
	
	void initialize(Graphics* _g, Input* _i, std::string _name, int _x, int _y, POINT _pt);
	void update(float frameTime) override;
	void render();
	void release();

	RECT get_rt() { return rt; }

	void worldMoveud(float worldSpeed)	//world camera move
	{
		top->moveY(worldSpeed);
		body->moveY(worldSpeed);
		middle->moveY(worldSpeed);

		pt.y += worldSpeed;
		rt.top += worldSpeed;
		rt.bottom += worldSpeed;
	}

	void worldMoverl(float worldSpeed)	//world camera move
	{
		top->moveX(worldSpeed);
		body->moveX(worldSpeed);
		middle->moveX(worldSpeed);

		pt.x += worldSpeed;
		rt.left += worldSpeed;
		rt.right += worldSpeed;
	}
};

