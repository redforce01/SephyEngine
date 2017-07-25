#include "stdafx.h"
#include "world_Resource_UI.h"

void CWorld_Resource_UI::resource_initialize(int index, std::string img)
{
	icon_resource[index]->initialize(m_pGraphics, worldresourceNS::icon_width, worldresourceNS::icon_height, 0, IMAGEMANAGER->getTexture(img));

	icon_resource[index]->setX(worldresourceNS::x);
	icon_resource[index]->setY(worldresourceNS::y + (worldresourceNS::icon_height + worldresourceNS::distance_y) * index);

	//standrad img_resource's position
	img_resource[index]->initialize(m_pGraphics, worldresourceNS::img_width, worldresourceNS::img_height, 0, IMAGEMANAGER->getTexture(worldresourceNS::img_name));
	img_resource[index]->setX(worldresourceNS::x);
	img_resource[index]->setY(worldresourceNS::y + (worldresourceNS::icon_height + worldresourceNS::distance_y) * index);

	//width 20
	//height 9

	UINT pos_rect_x = icon_resource[index]->getX() + icon_resource[index]->getWidth();
	UINT pos_rect_y = icon_resource[index]->getY() + (worldresourceNS::icon_height - worldresourceNS::save_height) / 2;

	rect_save[index] = RectMake(pos_rect_x, pos_rect_y, worldresourceNS::save_width, worldresourceNS::save_height);

	//standrad rect_save's position
	pos_rect_x = rect_save[index].right + worldresourceNS::distance_x;
	pos_rect_y = rect_save[index].top + (worldresourceNS::save_height - worldresourceNS::increase_height) / 2;

	rect_increase[index] = RectMake(pos_rect_x, pos_rect_y, worldresourceNS::increase_width, worldresourceNS::increase_height);
}

CWorld_Resource_UI::CWorld_Resource_UI()
{
	for (int i = 0; i < worldresourceNS::num; i++)
	{
		icon_resource[i] = new Image;
		img_resource[i] = new Image;

		rect_save[i] = { 0, };
		rect_increase[i] = { 0, };
	}
}

CWorld_Resource_UI::~CWorld_Resource_UI()
{
}

bool CWorld_Resource_UI::initialize(Graphics * g, Input * i)
{
	m_pGraphics = g;
	m_pInput = i;

	SystemUIDialog::initializeDialog(m_pGraphics, m_pInput, 0, 0, 0, 0, 0);

	dxfont_save.initialize(m_pGraphics, worldresourceNS::FONT_SIZE_save, true, false, worldresourceNS::FONT);
	dxfont_increase.initialize(m_pGraphics, worldresourceNS::FONT_SIZE_increase, true, false, worldresourceNS::FONT);

	resource_initialize(0, worldresourceNS::icon_name);
	resource_initialize(1, worldresourceNS::icon_name);
	resource_initialize(2, worldresourceNS::icon_name);
	resource_initialize(3, worldresourceNS::icon_name);

	addMessage("save_1", "", true);
	addMessage("increase_1", "", false);
	addMessage("save_2", "", true);
	addMessage("increase_2", "", false);
	addMessage("save_3", "", true);
	addMessage("increase_3", "", false);
	addMessage("save_4", "", true);
	addMessage("increase_4", "", false);
	
	return true;
}

void CWorld_Resource_UI::update(float frameTime)
{
	setMessage("save_1", "11111", true);
	setMessage("increase_1", "111", false);
	setMessage("save_2", "22222", true);
	setMessage("increase_2", "222", false);
	setMessage("save_3", "33333", true);
	setMessage("increase_3", "333", false);
	setMessage("save_4", "44444", true);
	setMessage("increase_4", "444", false);
}

void CWorld_Resource_UI::render()
{
	m_pGraphics->spriteBegin();

	for (int i = 0; i < worldresourceNS::num; i++)
	{
		img_resource[i]->draw();
		icon_resource[i]->draw();
	}

	int index = 0;

	//for (auto iter : m_saveMessage)
	//{
	//	dxfont_save.print(iter.second, rect_save[index], DT_VCENTER + DT_CENTER);

	//	index++;
	//}

	for (auto iter : m_saveMessage)
	{
		replace_number_img(rect_save[index], iter.second, true);

		index++;
	}

	index = 0;

	//for (auto iter : m_increaseMessage)
	//{
	//	dxfont_increase.print(iter.second, rect_increase[index], DT_VCENTER + DT_CENTER);

	//	index++;
	//}

	for (auto iter : m_increaseMessage)
	{
		replace_number_img(rect_increase[index], iter.second, false);

		index++;
	}

	m_pGraphics->spriteEnd();
}

void CWorld_Resource_UI::replace_number_img(RECT rect, std::string message, bool big)
{
	//Add kind of number image
	int length = message.length();
	int c_temp = atoi(message.c_str());
	RECT rc_temp = rect;

	std::string name = "";
	UINT width = 0;
	UINT height = 0;

	Image* img;

	rect.right -= worldresourceNS::MARGIN;

	for (int i = 0; i < length; i++)
	{
		char number = c_temp % 10 + '0';
		c_temp = c_temp / 10;

		img = new Image;

		if (big)
		{
			name = worldresourceNS::img_save;	//Image name
			width = worldresourceNS::num_save_width;
			height = worldresourceNS::num_save_height;
		}
		else
		{
			name = worldresourceNS::img_increase;
			width = worldresourceNS::num_increase_width;
			height = worldresourceNS::num_increase_height;
		}

		name.push_back(number);

		img->initialize(m_pGraphics, width, height, 0, IMAGEMANAGER->getTexture(name));

		if (big)
		{
			img->setX(rect.right);
			rect.right -= width;
		}
		else
		{
			img->setX(rect.left);
			rect.left += width;
		}

		img->setY(rect.top + ((rect.bottom - rect.top) / 2 - height / 2));


		img->draw();
	}

	rect = rc_temp;
}
