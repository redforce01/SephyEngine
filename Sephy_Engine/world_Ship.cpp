#include "stdafx.h"
#include "world_Ship.h"


//**********	calcul degree	**********//
void CWorld_Ship::move()
{
	float posx = pt.x - top->getCenterX();
	float posy = top->getCenterY() - pt.y;
	float distance = sqrt(posx*posx + posy*posy);
	float pt_degree = (atan2(posx, posy) * 180) / PI;
	
	degree = pt_degree + 180;	//해당 지점의 반대편 각
}

CWorld_Ship::CWorld_Ship()
{
	degree = worldshipNS::degree;
}

CWorld_Ship::~CWorld_Ship()
{
	SAFE_DELETE(top);
	SAFE_DELETE(body);
	SAFE_DELETE(middle);
}

void CWorld_Ship::initialize(Graphics * _g, Input * _i, std::string _name, int _x, int _y, POINT _pt)
{
	top = new Image;
	body = new Image;
	middle = new Image;

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
}

void CWorld_Ship::release()
{
	SAFE_DELETE(top);
	SAFE_DELETE(body);
	SAFE_DELETE(middle);
}
