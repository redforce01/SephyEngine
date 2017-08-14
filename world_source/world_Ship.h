#pragma once

#include "image.h"

namespace worldshipNS
{
	//const UINT speed = 5.0f;
	const UINT degree = 0;
	const float scale = 0.3f;
};

class CWorld_Ship : public Image
{
private:
	Graphics* m_pGraphics;
	Input* m_pInput;

	//std::vector<POINT> next_move;

	std::string name;
	Image* top;
	Image* body;
	Image* middle;

	POINT pt;
	RECT rt;

	float degree;
	//float speed;

	void move();
public:
	CWorld_Ship();
	~CWorld_Ship();
	
	void initialize(Graphics* _g, Input* _i, std::string _name, int _x, int _y, POINT _pt);
	void update(float frameTime) override;
	void render();

	//void add_move_point(POINT _pt) { next_move.emplace_back(_pt); }	//목표 지점 추가 (2턴 이상 거리)
	//void turn_end()	//턴 넘기기
	//{
	//	if (next_move.size() < 1)
	//		return;

	//	pt = next_move[next_move.size() - 1]; 
	//	next_move.pop_back(); 
	//}

	//POINT get_pt() { POINT _pt = { top->getCenterX(), top->getCenterY() }; return _pt; }	//현재 배의 위치
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

