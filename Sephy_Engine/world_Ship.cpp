#include "stdafx.h"
#include "world_Ship.h"


void CWorld_Ship::move()
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

CWorld_Ship::CWorld_Ship()
{
	top = new Image;
	body = new Image;
	middle = new Image;

	//speed = worldshipNS::speed;
	degree = worldshipNS::degree;
}


CWorld_Ship::~CWorld_Ship()
{
}

void CWorld_Ship::initialize(Graphics * _g, Input * _i, std::string _name, int _x, int _y, POINT _pt)
{
	m_pGraphics = _g;
	m_pInput = _i;
	name = _name;

	top->initialize(_g, 0, 0, 0, IMAGEMANAGER->getTexture(_name + "top0000"));
	body->initialize(_g, 0, 0, 0, IMAGEMANAGER->getTexture(_name + "body0000"));
	middle->initialize(_g, 0, 0, 0, IMAGEMANAGER->getTexture(_name + "middle0000"));
	
	top->setScale(worldshipNS::scale);
	body->setScale(worldshipNS::scale);
	middle->setScale(worldshipNS::scale);

	//Image's Center position
	top->setX(_x - top->getWidth() * top->getScale() / 2);
	top->setY(_y - top->getHeight() * top->getScale() / 2);
	body->setX(_x - body->getWidth() * body->getScale() / 2);
	body->setY(_y - body->getHeight() * body->getScale() / 2);
	middle->setX(_x - middle->getWidth() * middle->getScale() / 2);
	middle->setY(_y - middle->getHeight() * middle->getScale() / 2);

	rt = RectMake(
		_x - top->getWidth() * top->getScale() / 2, 
		_y - top->getHeight() * top->getScale() / 2, 
		top->getWidth() * top->getScale(), 
		top->getHeight() * top->getScale()
	);

	//pt = { _x - top->getWidth() * (int)top->getScale() / 2, _y - top->getHeight() * (int)top->getScale() / 2 };
	pt = _pt;
}

void CWorld_Ship::update(float frameTime)
{
	move();

	std::string index = "";
	
	if (degree >= 360)
		degree -= 360;

	if (degree >= 350) index = "0000";
	else if (degree >= 340) index = "0001";
	else if (degree >= 330) index = "0002";
	else if (degree >= 320) index = "0003";
	else if (degree >= 310) index = "0004";
	else if (degree >= 300) index = "0005";
	else if (degree >= 290) index = "0006";
	else if (degree >= 280) index = "0007";
	else if (degree >= 270) index = "0008";
	else if (degree >= 260) index = "0009";
	else if (degree >= 250) index = "0010";
	else if (degree >= 240) index = "0011";
	else if (degree >= 230) index = "0012";
	else if (degree >= 220) index = "0013";
	else if (degree >= 210) index = "0014";
	else if (degree >= 200) index = "0015";
	else if (degree >= 190) index = "0016";
	else if (degree >= 180) index = "0017";
	else if (degree >= 170) index = "0018";
	else if (degree >= 160) index = "0019";
	else if (degree >= 150) index = "0020";
	else if (degree >= 140) index = "0021";
	else if (degree >= 130) index = "0022";
	else if (degree >= 120) index = "0023";
	else if (degree >= 110) index = "0024";
	else if (degree >= 100) index = "0025";
	else if (degree >= 90) index = "0026";
	else if (degree >= 80) index = "0027";
	else if (degree >= 70) index = "0028";
	else if (degree >= 60) index = "0029";
	else if (degree >= 50) index = "0030";
	else if (degree >= 40) index = "0031";
	else if (degree >= 30) index = "0032";
	else if (degree >= 20) index = "0033";
	else if (degree >= 10) index = "0034";
	else if (degree >= 0) index = "0035";

	auto strResultTop = name + "top" + index;
	auto strResultBody = name + "body" + index;
	auto strResultBottom = name + "middle" + index;
	
	top->setTextureManager(IMAGEMANAGER->getTexture(name + "top" + index));
	body->setTextureManager(IMAGEMANAGER->getTexture(name + "body" + index));
	middle->setTextureManager(IMAGEMANAGER->getTexture(name + "middle" + index));

	top->update(frameTime);
	body->update(frameTime);
	middle->update(frameTime);
}

void CWorld_Ship::render()
{
	m_pGraphics->spriteBegin();
	
	top->draw();
	body->draw();
	middle->draw();

	m_pGraphics->spriteEnd();
	//m_pGraphics->drawLine(pt.x, pt.y, top->getCenterX(), top->getCenterY(), 3.0f, graphicsNS::RED);
	//m_pGraphics->drawRect(rt, 3.0f, graphicsNS::RED);
}
