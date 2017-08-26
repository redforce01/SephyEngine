#include "stdafx.h"
#include "world_Resource_UI.h"
#include "world_Player.h"

void CWorld_Resource_UI::resource_initialize(int index, std::string img)
{
	icon_resource[index]->initialize(m_pGraphics, worldresourceNS::icon_width, worldresourceNS::icon_height, 0, IMAGEMANAGER->getTexture(img));

	icon_resource[index]->setX(worldresourceNS::x);
	icon_resource[index]->setY(worldresourceNS::y + (worldresourceNS::icon_height + worldresourceNS::distance_y) * index);

	//standrad img_resource's position
	img_resource[index]->initialize(m_pGraphics, worldresourceNS::img_width, worldresourceNS::img_height, 0, IMAGEMANAGER->getTexture(worldresourceNS::img_name));
	img_resource[index]->setX(worldresourceNS::x);
	img_resource[index]->setY(worldresourceNS::y + (worldresourceNS::icon_height + worldresourceNS::distance_y) * index);

	int pos_rect_x = icon_resource[index]->getX() + icon_resource[index]->getWidth();
	int pos_rect_y = icon_resource[index]->getY() + (worldresourceNS::icon_height - worldresourceNS::save_height) / 2;

	rect_save[index] = RectMake(pos_rect_x, pos_rect_y, worldresourceNS::save_width, worldresourceNS::save_height);

	//standrad rect_save's position
	pos_rect_x = rect_save[index].right + worldresourceNS::distance_x;
	pos_rect_y = rect_save[index].top + (worldresourceNS::save_height - worldresourceNS::increase_height) / 2;

	rect_increase[index] = RectMake(pos_rect_x + worldresourceNS::MARGIN, pos_rect_y, worldresourceNS::increase_width, worldresourceNS::increase_height);
}

void CWorld_Resource_UI::calcu_resource()
{
	for (int i = 0; i < worldresourceNS::num; i++)
	{
		increase_resource[i] = 0;
		decrease_resource[i] = 0;
	}

	increase_resource[MONEY] = player->get_increase_resource(MONEY);
	increase_resource[IRON] = player->get_increase_resource(IRON);
	increase_resource[FUEL] = player->get_increase_resource(FUEL);
	increase_resource[RESEARCH] = player->get_increase_resource(RESEARCH);

	decrease_resource[MONEY] = player->get_decrease_resource(MONEY);
	decrease_resource[IRON] = player->get_decrease_resource(IRON);
	decrease_resource[FUEL] = player->get_decrease_resource(FUEL);
	decrease_resource[RESEARCH] = player->get_decrease_resource(RESEARCH);
}

CWorld_Resource_UI::CWorld_Resource_UI()
{
	for (int i = 0; i < worldresourceNS::num; i++)
	{
		rect_save[i] = { 0, };
		rect_increase[i] = { 0, };

		increase_resource[i] = 0;
		decrease_resource[i] = 0;
	}
}

CWorld_Resource_UI::~CWorld_Resource_UI()
{
	SAFE_DELETE(resource_detail);

	for (auto iter : list_number)
		SAFE_DELETE(iter);
	list_number.clear();

	for (int i = 0; i < worldresourceNS::num; i++)
	{
		SAFE_DELETE(img_resource[i]);
		SAFE_DELETE(icon_resource[i]);
	}
}

bool CWorld_Resource_UI::initialize(Graphics * g, Input * i)
{
	for (int i = 0; i < worldresourceNS::num; i++)
	{
		icon_resource[i] = new Image;
		img_resource[i] = new Image;
	}

	resource_detail = new CWorld_Resource_Detail;

	m_pGraphics = g;
	m_pInput = i;

	resource_initialize(0, worldresourceNS::MONEY);
	resource_initialize(1, worldresourceNS::IRON);
	resource_initialize(2, worldresourceNS::FUEL);
	resource_initialize(3, worldresourceNS::RESEARCH);

	resource_detail->initialize(g, i);
	resource_detail->SetLoadLinkPlyaer(player);
	resource_detail->SetLoadLinkUI(this);

	m_dxfont.initialize(m_pGraphics, worldresourceNS::FONT_SIZE, true, false, worldresourceNS::FONT);
	
	return true;
}

void CWorld_Resource_UI::update(float frameTime)
{
	calcu_resource();
	resource_detail->update(frameTime);
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

	replace_number_img(rect_save[MONEY], player->get_resource(MONEY), true);
	replace_number_img(rect_save[IRON], player->get_resource(IRON), true);
	replace_number_img(rect_save[FUEL], player->get_resource(FUEL), true);
	replace_number_img(rect_save[RESEARCH], player->get_resource(RESEARCH), true);

	for (int i = 0; i < worldresourceNS::num; i++)
	{
		int amount = increase_resource[i] - decrease_resource[i];

		std::string str = std::to_string(fabs(amount));
		
		if (amount < 0)
		{
			m_dxfont.print("-", rect_increase[i], DT_LEFT + DT_VCENTER);
			amount = fabs(amount);
		}
		else
			m_dxfont.print("+", rect_increase[i], DT_LEFT + DT_VCENTER);

		replace_number_img(rect_increase[i], amount, false);
	}

	for (auto iter : list_number)
		iter->draw();

	m_pGraphics->spriteEnd();

	resource_detail->render();

	for (auto iter : list_number)
		SAFE_DELETE(iter);
	list_number.clear();
}

void CWorld_Resource_UI::release()
{
	resource_detail->release();
	SAFE_DELETE(resource_detail);

	for (auto iter : list_number)
		SAFE_DELETE(iter);
	list_number.clear();

	for (int i = 0; i < worldresourceNS::num; i++)
	{
		SAFE_DELETE(img_resource[i]);
		SAFE_DELETE(icon_resource[i]);
	}
}

void CWorld_Resource_UI::replace_number_img(RECT rect, int _resource, bool big)
{
	//Add kind of number image
	std::string number = std::to_string(_resource);
	std::string name = "";

	int length = number.length();
	int c_temp = _resource;	//atoi(number.c_str());
	RECT rc_temp = rect;

	int width = 0;
	int height = 0;

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

		img->setX(rect.right);
		rect.right -= width;

		img->setY(rect.top + ((rect.bottom - rect.top) / 2 - height / 2));

		list_number.emplace_back(img);
	}

	rect = rc_temp;
}
