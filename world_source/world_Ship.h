#pragma once

#include "image.h"


class CWorld_Ship : public Image
{
private:
	Graphics* m_pGraphics;
	Input* m_pInput;

	std::vector<POINT> next_move;

	std::string name;
	Image* top;
	Image* body;
	Image* middle;

	POINT pt;

	float degree;
	float speed;

	void move();
public:
	CWorld_Ship();
	~CWorld_Ship();
	
	void initialize(Graphics* _g, Input* _i, std::string _name, int _x, int _y, float _degree);
	void update(float frameTime) override;
	void render();

	void add_move_point(POINT _pt) { next_move.emplace_back(_pt); }
	void turn_end()
	{
		if (next_move.size() < 1)
			return;

		pt = next_move[next_move.size() - 1]; 
		next_move.pop_back(); 
	}

	POINT get_pt() { POINT _pt = { top->getX(), top->getY() }; return _pt; }

	void worldMoveud(float worldSpeed)
	{
		top->moveY(worldSpeed);
		body->moveY(worldSpeed);
		middle->moveY(worldSpeed);

		pt.y += worldSpeed;
	}

	void worldMoverl(float worldSpeed)
	{
		top->moveX(worldSpeed);
		body->moveX(worldSpeed);
		middle->moveX(worldSpeed);

		pt.x += worldSpeed;
	}
};

