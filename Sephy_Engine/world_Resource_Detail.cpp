#include "stdafx.h"
#include "world_Resource_Detail.h"
#include "world_User.h"
#include "world_Resource_UI.h"


CWorld_Resource_Detail::CWorld_Resource_Detail()
{
	is_over = false;
	rt_increase = { 0, };
	rt_decrease = { 0, };
}


CWorld_Resource_Detail::~CWorld_Resource_Detail()
{
	for (auto iter : list_number)
		SAFE_DELETE(iter);
	list_number.clear();
}

bool CWorld_Resource_Detail::initialize(Graphics * g, Input * i)
{
	m_pGraphics = g;
	m_pInput = i;

	SystemUIDialog::initializeDialog(
		g, i, i->getMouseX(), i->getMouseY(), 
		world_resource_detailNS::WIDTH, 
		world_resource_detailNS::HEIGHT, 
		world_resource_detailNS::MARGIN
	);

	rt_increase = RectMake(
		i->getMouseX(), i->getMouseY() + world_resource_detailNS::MARGIN / 2
		, world_resource_detailNS::RT_WIDTH, world_resource_detailNS::RT_HEIGHT
	);
	rt_increase = RectMake(
		i->getMouseX(), rt_increase.bottom,
		world_resource_detailNS::RT_WIDTH, world_resource_detailNS::RT_HEIGHT
	);
	m_dxFont.initialize(g, world_resource_detailNS::FONT_SIZE, true, false, world_resource_detailNS::FONT);

	return false;
}

void CWorld_Resource_Detail::update(float frameTime)
{
	SystemUIDialog::update(frameTime);

	for (int i = 0; i < world_resource_detailNS::KIND_RESOURCE; i++)
	{
		if (PtInRect(&ui->get_rect_increase(i), m_pInput->getMousePt()))
		{
			is_over = true;

			switch (i)
			{
			case 0:
				type = MONEY;
				break;
			case 1:
				type = IRON;
				break;
			case 2:
				type = FUEL;
				break;
			case 3:
				type = RESEARCH;
				break;
			}

			SystemUIDialog::setDialogPos(m_pInput->getMouseX(), m_pInput->getMouseY());
			rt_increase.left = m_pInput->getMouseX();
			rt_increase.right = rt_increase.left + world_resource_detailNS::RT_WIDTH;
			rt_increase.top = m_pInput->getMouseY() + world_resource_detailNS::MARGIN / 2;
			rt_increase.bottom = rt_increase.top + world_resource_detailNS::RT_HEIGHT;

			rt_decrease.left = rt_increase.left;
			rt_decrease.right = rt_increase.right;
			rt_decrease.top = rt_increase.bottom;
			rt_decrease.bottom = rt_decrease.top + world_resource_detailNS::RT_HEIGHT;

			break;
		}
		else is_over = false;
	}
}

void CWorld_Resource_Detail::render()
{
	if (is_over == false)
		return;

	SystemUIDialog::render();

	m_pGraphics->spriteBegin();

	m_dxFont.print("+ ", rt_increase, DT_LEFT + DT_CENTER);
	m_dxFont.print("- ", rt_decrease, DT_LEFT + DT_CENTER);

	replace_number_img(rt_increase, user->get_increase_resource(type));
	replace_number_img(rt_decrease, user->get_decrease_resource(type));

	for (auto iter : list_number)
		iter->draw();

	m_pGraphics->spriteEnd();

	for (auto iter : list_number)
		SAFE_DELETE(iter);
	list_number.clear();
}

void CWorld_Resource_Detail::release()
{
	for (auto iter : list_number)
		SAFE_DELETE(iter);
	list_number.clear();
}

void CWorld_Resource_Detail::replace_number_img(RECT rect, int _number)
{
	//Add kind of number image
	std::string number = std::to_string(_number);
	std::string name = "";

	int length = number.length();
	int c_temp = _number;	//atoi(number.c_str());
	RECT rc_temp = rect;

	Image* img;

	rect.right -= world_resource_detailNS::IMG_NUMBER_WIDTH * 2;

	for (int i = 0; i < length; i++)
	{
		char number = c_temp % 10 + '0';
		c_temp = c_temp / 10;

		img = new Image;

		name = world_resource_detailNS::IMG_NUMBER;	//Image name

		name.push_back(number);

		img->initialize(m_pGraphics, world_resource_detailNS::IMG_NUMBER_WIDTH, world_resource_detailNS::IMG_NUMBER_HEIGHT, 0, IMAGEMANAGER->getTexture(name));

		img->setX(rect.right);
		rect.right -= world_resource_detailNS::IMG_NUMBER_WIDTH;

		img->setY(rect.top + ((rect.bottom - rect.top) / 2 - world_resource_detailNS::IMG_NUMBER_HEIGHT / 2));

		list_number.emplace_back(img);
	}

	rect = rc_temp;
}