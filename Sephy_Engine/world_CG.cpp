#include "stdafx.h"
#include "world_CG.h"
#include "world_Player.h"


CWorld_CG::CWorld_CG()
{
	img = nullptr;
	battle_ui = nullptr;

	current_cg = e_worldcg::NONE;
	is_complete = false;
	is_click = false;
	mouse_up = false;
}


CWorld_CG::~CWorld_CG()
{
	SAFE_DELETE(img);

	if (battle_ui != nullptr)
		SAFE_DELETE(battle_ui);
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

	switch (current_cg)
	{
	case e_worldcg::BATTLE:
		update_battle_cg(frameTime);
		break;
	case e_worldcg::MOVE:
		update_move_ship_cg();
		break;
	}
}

void CWorld_CG::render()
{
	if (current_cg == e_worldcg::NONE)
		return;

	m_pGraphics->spriteBegin();

	img->draw();

	m_pGraphics->spriteEnd();
	
	if (is_click == true)
		battle_ui->render();

	//img->drawRect();
	//m_pGraphics->drawLine(temp1.x, temp1.y, temp2.x, temp2.y, 2.0f, graphicsNS::RED);
	//m_pGraphics->drawLine(pt.x, pt.y, destination.x, destination.y, 2.0f, graphicsNS::RED);
}

void CWorld_CG::create_battle_cg(UINT _x, UINT _y)
{
	img = new Image;
	//battle effect initialize
	std::string str = worldcgNS::img_battle;
	img_num = worldcgNS::battle_min;
	str += std::to_string(img_num);
	
	img->initialize(m_pGraphics, 0, 0, 0, IMAGEMANAGER->getTexture(str));

	current_cg = e_worldcg::BATTLE;

	pt = { (int)_x, (int)_y };

	img->setX(pt.x);
	img->setY(pt.y);
	speed = 0;

	battle_ui = new CWorld_Battle_UI;
	battle_ui->SetLoadLinkPlayer(user);
	battle_ui->SetLoadLinkCG(this);
	battle_ui->set_battle_island(move_island);
	battle_ui->initialize(m_pGraphics, m_pInput, img->getCenterX(), img->getCenterY());

	is_click = true;
}

void CWorld_CG::update_battle_cg(float frameTime)
{
	//끝 2자리 빼서 int 전환 후 ++ 후 다시 붙이기
	//19~72
	std::string str = worldcgNS::img_battle;

	//img index++
	if (++img_num > worldcgNS::battle_max)
		img_num = worldcgNS::battle_min;

	str += std::to_string(img_num);

	speed += frameTime;

	//img change (after delay time)
	if (speed > worldcgNS::delay)
	{
		img->setTextureManager(IMAGEMANAGER->getTexture(str));
		speed = 0;
	}

	/* ======= Delete ======= */
	if (is_click == true)
	{
		battle_ui->update(frameTime);
		
		if (battle_ui->get_visible() == false)
		{
			SAFE_DELETE(battle_ui);
			is_click = false;
		}
	}
	//else {
	//	if (m_pInput->getMouseLButton())
	//		mouse_up = true;
	//	else
	//	{
	//		if (mouse_up == true)
	//		{
	//			RECT rt = RectMake(img->getX(), img->getY(), img->getSpriteData().width, img->getSpriteData().height);

	//			if (PtInRect(&rt, m_pInput->getMousePt()))
	//			{
	//				battle_ui = new CWorld_Battle_UI;
	//				battle_ui->initialize(m_pGraphics, m_pInput, img->getCenterX(), img->getCenterY());
	//				battle_ui->SetLoadLinkPlayer(user);

	//				is_click = true;
	//			}
	//		}
	//		mouse_up = false;
	//	}
	//}
}

void CWorld_CG::create_move_ship_cg(POINT _pt, POINT _destination, UINT _move)
{
	if (SOUNDMANAGER->isPlaySound(worldcgNS::SOUND_MOVE) == false)
		SOUNDMANAGER->play(worldcgNS::SOUND_MOVE, g_fSoundMasterVolume * g_fSoundEffectVolume);

	img = new Image;

	move_island = _move;
	//ship move effect initialize
	current_cg = e_worldcg::MOVE;

	pt = _pt;
	destination = _destination;

	speed = worldcgNS::speed;

	std::string img_name = worldcgNS::img_move;

	float posx = pt.x - destination.x;
	float posy = destination.y - pt.y;
	float distance = sqrt(posx*posx + posy*posy);
	float pt_degree = (atan2(posx, posy) * 180) / PI;

	degree = pt_degree;

	if (pt.x <= destination.x)
	{
		if (pt.y <= destination.y)
		{
			direct = e_direct::RB;
			img_name += worldcgNS::MOVE_RB;
		}
		else
		{
			direct = e_direct::RT;
			img_name += worldcgNS::MOVE_RT;
		}
	}
	else
	{
		if (pt.y <= destination.y)
		{
			direct = e_direct::LB;
			img_name += worldcgNS::MOVE_LB;
		}
		else
		{
			direct = e_direct::LT;
			img_name += worldcgNS::MOVE_LT;
		}
	}

	img->initialize(m_pGraphics, 0, 0, 0, IMAGEMANAGER->getTexture(img_name));
	img->setX(pt.x - img->getWidth() / 2);
	img->setY(pt.y - img->getHeight() / 2);

	if (direct == e_direct::RB)	// (img->getWidth() / 2) - (img->getWidth() / 2)
	{
		destination.x += 0;
		destination.y += 0;
	}
	else if (direct == e_direct::LB)
	{
		destination.x -= img->getWidth();
		destination.y += 0;
	}
	else if (direct == e_direct::LT)	// (img->getWidth() / 2) + (img->getWidth() / 2)
	{
		destination.x -= img->getWidth();
		destination.y -= img->getHeight();
	}
	else
	{
		destination.x += 0;
		destination.y -= img->getHeight();
	}
}

void CWorld_CG::update_move_ship_cg()
{
	//float posx = pt.x - top->getX();
	//float posy = pt.y - top->getY();
	//float distance = sqrt(posx*posx + posy*posy);

	float posx = pt.x - destination.x;
	float posy = destination.y - pt.y;
	float distance = sqrt(posx*posx + posy*posy);
	float pt_degree = (atan2(posx, posy) * 180) / PI;

	degree = pt_degree;

	//if (degree < 0)
	//	degree += 360;

	//img->setDegrees(direct - degree);
	// ====================== 해당 지점으로 이동 ==========================
	//float targetPtRad = 1.0f;   // 타겟지점으로부터의 반지름 For Circle   
	//float objectRad = img->getWidth() / 4;   // 오브젝트의 반지름

	//Double ang = RadianToDegree(Math.Atan2(ydf, xdf));
	//return ang + 90;

	//if (distance < targetPtRad + objectRad)
	if (distance <= img->getWidth())
	{
		// ================= 그자리에 멈춤 ======================
		//top->setX(pt.x - top->getWidth() * top->getScale() / 2);
		//top->setY(pt.y - top->getHeight() * top->getScale() / 2);
		//body->setX(pt.x - body->getWidth() * body->getScale() / 2);
		//body->setY(pt.y - body->getHeight() * body->getScale() / 2);
		//middle->setX(pt.x - middle->getWidth() * middle->getScale() / 2);
		//middle->setY(pt.y - middle->getHeight() * middle->getScale() / 2);
		//SAFE_DELETE(img);
		current_cg = e_worldcg::NONE;

		SAFE_DELETE(img);

		for (auto iter : user->get_island())
		{
			if (iter->getID() == user->get_data()->get_Island()[move_island]->getID())
			{
				for (auto sIter : user->get_cur_ship())
					user->get_data()->get_Island()[move_island]->add_ship(sIter);
				user->clear_cur_ship();

				is_complete = true;

				return;
			}
		}

		create_battle_cg(user->get_data()->get_Island()[move_island]->getPt().x, user->get_data()->get_Island()[move_island]->getPt().y);

		//SAFE_DELETE(this); //자기 자신 없애기..

		return;
	}

	img->moveX(cos(degree) * speed);
	img->moveY(sin(degree) * speed);
	
	pt.x = img->getX();
	pt.y = img->getY();
}

void CWorld_CG::w_move_ud(float _speed)
{
	if (current_cg == e_worldcg::NONE)
		return;

	img->moveY(_speed);
	pt.y = img->getY();
	destination.y += _speed;

	if (is_click == true)
		battle_ui->w_move_ud(_speed);
}

void CWorld_CG::w_move_lr(float _speed)
{
	if (current_cg == e_worldcg::NONE)
		return;

	img->moveX(_speed);
	pt.x = img->getX();
	destination.x += _speed;

	if (is_click == true)
		battle_ui->w_move_rl(_speed);
}
