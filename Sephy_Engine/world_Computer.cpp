#include "stdafx.h"
#include "world_Computer.h"


CWorld_Computer::CWorld_Computer()
{
}


CWorld_Computer::~CWorld_Computer()
{
	for (auto iter : img_list)
		SAFE_DELETE(iter);
	img_list.clear();
}

void CWorld_Computer::update(float frameTime)
{
	for (auto iter : island_node)
	{
		if (iter != nullptr)
			iter->update(frameTime);
	}
}

void CWorld_Computer::render()
{
	for (auto iter : img_list)
		SAFE_DELETE(iter);
	img_list.clear();

	for (auto iter : island_node)
	{
		Image* img = new Image;
		img->initialize(m_pGraphics, world_computerNS::FLAG_WIDTH, world_computerNS::FLAG_HEIGHT, 0, IMAGEMANAGER->getTexture(world_computerNS::FLAG_NAME));
		img->setX(iter->getX() - world_computerNS::FLAG_WIDTH / 2);
		img->setY(iter->getY() - world_computerNS::FLAG_HEIGHT / 2);

		img_list.emplace_back(img);

		iter->render();
	}

	m_pGraphics->spriteBegin();

	for (auto iter : img_list)
		iter->draw();

	m_pGraphics->spriteEnd();
}

void CWorld_Computer::relase()
{
	for (auto iter : img_list)
	{
		if (iter != nullptr)
			SAFE_DELETE(iter);
	}
	img_list.clear();
}

void CWorld_Computer::w_move_ud(float _speed)
{
	for (auto iter : island_node)
		iter->w_move_ud(_speed);
}

void CWorld_Computer::w_move_rl(float _speed)
{
	for (auto iter : island_node)
		iter->w_move_rl(_speed);
}
