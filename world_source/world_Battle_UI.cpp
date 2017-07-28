#include "stdafx.h"
#include "world_Battle_UI.h"


CWorld_Battle_UI::CWorld_Battle_UI()
{
	battle_infor = new Image;
	battle_start = new Image;
	battle_retreat = new Image;
	auto_battle = new Image;

	rt_infor = { 0, };
	rt_start = { 0, };
	rt_retreat = { 0, };
	rt_auto = { 0, };

	visible = false;
}


CWorld_Battle_UI::~CWorld_Battle_UI()
{
}

bool CWorld_Battle_UI::initialize(Graphics * g, Input * i, UINT _x, UINT _y)
{
	m_pGraphics = g;
	m_pInput = i;

	battle_infor->initialize(g, worldbattleNS::width, worldbattleNS::height, 0, IMAGEMANAGER->getTexture(worldbattleNS::INFOR));
	battle_start->initialize(g, worldbattleNS::width, worldbattleNS::height, 0, IMAGEMANAGER->getTexture(worldbattleNS::START));
	battle_retreat->initialize(g, worldbattleNS::width, worldbattleNS::height, 0, IMAGEMANAGER->getTexture(worldbattleNS::RETREAT));
	auto_battle->initialize(g, worldbattleNS::width, worldbattleNS::height, 0, IMAGEMANAGER->getTexture(worldbattleNS::AUTO));

	battle_infor->setX(_x - worldbattleNS::x + worldbattleNS::width / 2);
	battle_infor->setY(_y - worldbattleNS::y + worldbattleNS::height / 2);
	battle_start->setX(_x - worldbattleNS::x + worldbattleNS::width / 2);
	battle_start->setY(_y + worldbattleNS::y + worldbattleNS::height / 2);
	battle_retreat->setX(_x + worldbattleNS::x + worldbattleNS::width / 2);
	battle_retreat->setY(_y - worldbattleNS::y + worldbattleNS::height / 2);
	auto_battle->setX(_x + worldbattleNS::x + worldbattleNS::width / 2);
	auto_battle->setY(_y + worldbattleNS::y + worldbattleNS::height / 2);

	rt_infor = RectMake(
		battle_infor->getX() - worldbattleNS::MARGIN, 
		battle_infor->getY() - worldbattleNS::text_height,
		worldbattleNS::text_width, 
		worldbattleNS::text_height);
	rt_start = RectMake(
		battle_start->getX() - worldbattleNS::MARGIN,
		battle_start->getY() + (worldbattleNS::text_height - worldbattleNS::height / 2),
		worldbattleNS::text_width, 
		worldbattleNS::text_height);
	rt_retreat = RectMake(
		battle_retreat->getX() + worldbattleNS::MARGIN,
		battle_retreat->getY() - worldbattleNS::text_height,
		worldbattleNS::text_width, 
		worldbattleNS::text_height);
	rt_auto = RectMake(
		auto_battle->getX() + worldbattleNS::MARGIN,
		auto_battle->getY() + (worldbattleNS::text_height - worldbattleNS::height / 2),
		worldbattleNS::text_width,
		worldbattleNS::text_height);

	m_dxFont.initialize(g, worldbattleNS::FONT_SIZE, true, false, worldbattleNS::FONT);
	m_dxFont.setFontColor(graphicsNS::YELLOW);

	return true;
}

bool CWorld_Battle_UI::initialize(Graphics * g, Input * i)
{
	return true;
}

void CWorld_Battle_UI::update(float frameTime)
{
	if (visible == false)
		return;
}

void CWorld_Battle_UI::render()
{
	if (visible == false)
		return;

	m_pGraphics->spriteBegin();

	battle_infor->draw();
	battle_start->draw();
	battle_retreat->draw();
	auto_battle->draw();
	
	m_dxFont.print("전투 정보", rt_infor, DT_RIGHT);
	m_dxFont.print("전투 돌입", rt_start, DT_RIGHT);
	m_dxFont.print("전투 후퇴", rt_retreat, DT_LEFT);
	m_dxFont.print("자동 전투", rt_auto, DT_LEFT);

	m_pGraphics->spriteEnd();

	//m_pGraphics->drawRect(rt_infor);
	//m_pGraphics->drawRect(rt_start);
	//m_pGraphics->drawRect(rt_retreat);
	//m_pGraphics->drawRect(rt_auto);
}
