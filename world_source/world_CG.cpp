#include "stdafx.h"
#include "world_CG.h"


CWorld_CG::CWorld_CG()
{
	img = new Image;

	current_cg = e_worldcg::NONE;
}


CWorld_CG::~CWorld_CG()
{
	SAFE_DELETE(img);
}

bool CWorld_CG::initialize(Graphics * g, Input * i)
{
	m_pGraphics = g;
	m_pInput = i;

	return true;
}

void CWorld_CG::update(float frameTime)
{
	if (current_cg == e_worldcg::NONE)
		return;
}

void CWorld_CG::render()
{
	if (current_cg == e_worldcg::NONE)
		return;

	m_pGraphics->spriteBegin();

	m_pGraphics->spriteEnd();
}

void CWorld_CG::create_battle_cg(UINT _x, UINT _y)
{
}

void CWorld_CG::create_move_ship_cg(POINT _pt, POINT _destination)
{
	//float posx = pt.x - top->getX();
	//float posy = pt.y - top->getY();
	//float distance = sqrt(posx*posx + posy*posy);
	float posx = pt.x - top->getCenterX();
	float posy = top->getCenterY() - pt.y;
	float distance = sqrt(posx*posx + posy*posy);
	float pt_degree = (atan2(posx, posy) * 180) / PI;

	degree = pt_degree + 180;	//해당 지점의 반대편 각

	// ====================== 해당 지점으로 이동 ==========================
	//float targetPtRad = 1.0f;   // 타겟지점으로부터의 반지름 For Circle   
	//float objectRad = top->getWidth() / 4;   // 오브젝트의 반지름

	////Double ang = RadianToDegree(Math.Atan2(ydf, xdf));
	////return ang + 90;
	//
	//if (distance < targetPtRad + objectRad)
	//{
	//	// ================= 그자리에 멈춤 ======================
	//	//top->setX(pt.x - top->getWidth() * top->getScale() / 2);
	//	//top->setY(pt.y - top->getHeight() * top->getScale() / 2);
	//	//body->setX(pt.x - body->getWidth() * body->getScale() / 2);
	//	//body->setY(pt.y - body->getHeight() * body->getScale() / 2);
	//	//middle->setX(pt.x - middle->getWidth() * middle->getScale() / 2);
	//	//middle->setY(pt.y - middle->getHeight() * middle->getScale() / 2);

	//	return;
	//}
	//
	//top->moveX(cos(pt_degree) * speed);
	//top->moveY(sin(pt_degree) * speed);
	//body->moveX(cos(pt_degree) * speed);
	//body->moveY(sin(pt_degree) * speed);
	//middle->moveX(cos(pt_degree) * speed);
	//middle->moveY(sin(pt_degree) * speed);
}
