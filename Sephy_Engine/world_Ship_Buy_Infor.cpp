#include "stdafx.h"
#include "world_Ship_Buy_Infor.h"
#include "world_Player.h"

CWorld_Ship_Buy_Infor::CWorld_Ship_Buy_Infor()
{
	for (int i = 0; i < world_ship_buyNS::KIND_RESOURCE; i++)
		rt_resource[i] = { 0, };
	rt_name = { 0, };
	rt_turn = { 0, };

	ship = nullptr;
}

CWorld_Ship_Buy_Infor::~CWorld_Ship_Buy_Infor()
{
	list_number.clear();
}

bool CWorld_Ship_Buy_Infor::initialize(Graphics * g, Input * i)
{
	m_pGraphics = g;
	m_pInput = i;

	SystemUIDialog::initializeDialog(
		g, i, i->getMouseX() - world_ship_buyNS::WIDTH, i->getMouseY(),
		world_ship_buyNS::WIDTH,
		world_ship_buyNS::HEIGHT,
		world_ship_buyNS::MARGIN
	);
	SystemUIDialog::setDialogBackColor(world_ship_buyNS::BACK_COLOR);

	rt_name = RectMake(
		i->getMouseX() - world_ship_buyNS::WIDTH + world_ship_buyNS::MARGIN,
		i->getMouseY() + world_ship_buyNS::MARGIN,
		world_ship_buyNS::RT_WIDTH,
		world_ship_buyNS::RT_HEIGHT
	);

	for (int a = 0; a < world_ship_buyNS::KIND_RESOURCE; a++)
	{
		rt_resource[a] = RectMake(
			rt_name.left, rt_name.bottom + world_ship_buyNS::RT_HEIGHT * a,
			world_ship_buyNS::RT_WIDTH, world_ship_buyNS::RT_HEIGHT
		);
	}

	rt_turn = RectMake(
		rt_resource[world_ship_buyNS::KIND_RESOURCE - 1].left, rt_resource[world_ship_buyNS::KIND_RESOURCE - 1].bottom,
		world_ship_buyNS::RT_WIDTH, world_ship_buyNS::RT_HEIGHT
	);

	m_dxFont.initialize(g, world_ship_buyNS::FONT_SIZE, true, false, world_ship_buyNS::FONT);

	return true;
}

void CWorld_Ship_Buy_Infor::update(float frameTime)
{
	if (ship == nullptr)
	return;

	SystemUIDialog::update(frameTime);

	SystemUIDialog::setDialogPos(m_pInput->getMouseX() - world_ship_buyNS::WIDTH, m_pInput->getMouseY());

	rt_name.left = m_pInput->getMouseX() - world_ship_buyNS::WIDTH + world_ship_buyNS::MARGIN;
	rt_name.right = rt_name.left + world_ship_buyNS::RT_WIDTH;
	rt_name.top = m_pInput->getMouseY() + world_ship_buyNS::MARGIN;
	rt_name.bottom = rt_name.top + world_ship_buyNS::RT_HEIGHT;

	for (int i = 0; i < world_ship_buyNS::KIND_RESOURCE; i++)
	{
		rt_resource[i].left = rt_name.left;
		rt_resource[i].right = rt_name.right;
		rt_resource[i].top = rt_name.bottom + world_ship_buyNS::RT_HEIGHT * i;
		rt_resource[i].bottom = rt_resource[i].top + world_ship_buyNS::RT_HEIGHT;
	}

	rt_turn.left = rt_resource[world_ship_buyNS::KIND_RESOURCE - 1].left;
	rt_turn.right = rt_resource[world_ship_buyNS::KIND_RESOURCE - 1].right;
	rt_turn.top = rt_resource[world_ship_buyNS::KIND_RESOURCE - 1].bottom;
	rt_turn.bottom = rt_turn.top + world_ship_buyNS::RT_HEIGHT;
}

void CWorld_Ship_Buy_Infor::render()
{
	if (ship == nullptr)
		return;

	SystemUIDialog::render();

	m_pGraphics->spriteBegin();

	buy_draw();

	for (auto iter : list_number)
		iter->draw();

	m_pGraphics->spriteEnd();

	for (auto iter : list_number)
		SAFE_DELETE(iter);
	list_number.clear();
}

void CWorld_Ship_Buy_Infor::replace_number_img(RECT rect, int _number)
{
	//Add kind of number image
	std::string number = std::to_string(_number);
	std::string name = "";

	int length = number.length();
	int c_temp = _number;	//atoi(number.c_str());
	RECT rc_temp = rect;

	Image* img;

	rect.right -= world_ship_buyNS::IMG_NUMBER_WIDTH * 2;

	for (int i = 0; i < length; i++)
	{
		char number = c_temp % 10 + '0';
		c_temp = c_temp / 10;

		img = new Image;

		name = world_ship_buyNS::IMG_NUMBER;	//Image name

		name.push_back(number);

		img->initialize(m_pGraphics, world_ship_buyNS::IMG_NUMBER_WIDTH, world_ship_buyNS::IMG_NUMBER_HEIGHT, 0, IMAGEMANAGER->getTexture(name));

		img->setX(rect.right);
		rect.right -= world_ship_buyNS::IMG_NUMBER_WIDTH;

		img->setY(rect.top + ((rect.bottom - rect.top) / 2 - world_ship_buyNS::IMG_NUMBER_HEIGHT / 2));

		list_number.emplace_back(img);
	}

	rect = rc_temp;
}

//**********	ship's detail info		**********//
void CWorld_Ship_Buy_Infor::buy_draw()
{
	std::string str = "";

	m_dxFont.print(ship->getName(), rt_name, DT_VCENTER + DT_CENTER);

	m_dxFont.print("MONEY : ", rt_resource[MONEY], DT_VCENTER + DT_LEFT);
	m_dxFont.print("IRON : ", rt_resource[IRON], DT_VCENTER + DT_LEFT);
	m_dxFont.print("FUEL : ", rt_resource[FUEL], DT_VCENTER + DT_LEFT);
	m_dxFont.print("RESEARCH : ", rt_resource[RESEARCH], DT_VCENTER + DT_LEFT);
	m_dxFont.print("TURN : ", rt_turn, DT_VCENTER + DT_LEFT);

	replace_number_img(rt_resource[MONEY], ship->get_resource(MONEY));
	replace_number_img(rt_resource[IRON], ship->get_resource(IRON));
	replace_number_img(rt_resource[FUEL], ship->get_resource(FUEL));
	replace_number_img(rt_resource[RESEARCH], ship->get_resource(RESEARCH));
	
	if (player->get_buf_type() == 2 && ship->getTurn() - 1 > 0)
		replace_number_img(rt_turn, ship->getTurn() - 1);
	else
		replace_number_img(rt_turn, ship->getTurn());
}

void CWorld_Ship_Buy_Infor::w_move_rl(float _speed)
{
	SystemUIDialog::moveDialogX(_speed);

	rt_name.left += _speed;
	rt_name.right += _speed;
	rt_turn.left += _speed;
	rt_turn.right += _speed;

	for (int i = 0; i < world_ship_buyNS::KIND_RESOURCE; i++)
	{
		rt_resource[i].left += _speed;
		rt_resource[i].right += _speed;
	}

	for (auto iter : list_number)
		iter->moveX(_speed);
}
