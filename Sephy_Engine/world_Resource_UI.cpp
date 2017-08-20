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

	//width 20
	//height 9

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

	for (auto iter : player->get_island())
	{
		for (int i = 0; i < iter->get_Building_Size(); i++)
		{
			if (iter->get_Building(i) != nullptr)
			{
				if (iter->get_Building(i)->get_is_complete() == true)
				{
					increase_resource[MONEY] += iter->get_Building(i)->get_produce_resource()[MONEY];
					increase_resource[IRON] += iter->get_Building(i)->get_produce_resource()[IRON];
					increase_resource[FUEL] += iter->get_Building(i)->get_produce_resource()[FUEL];
					increase_resource[RESEARCH] += iter->get_Building(i)->get_produce_resource()[RESEARCH];
				}
			}
		}

		for (auto cIter : iter->get_child())
			increase_resource[cIter->get_type()] += cIter->get_resource();
	}

	for (auto iter : player->get_ship())
		decrease_resource[FUEL] -= iter->getCost();
}

CWorld_Resource_UI::CWorld_Resource_UI()
{
	for (int i = 0; i < worldresourceNS::num; i++)
	{
		icon_resource[i] = new Image;
		img_resource[i] = new Image;

		rect_save[i] = { 0, };
		rect_increase[i] = { 0, };

		increase_resource[i] = 0;
		decrease_resource[i] = 0;
	}

	resource_detail = new CWorld_Resource_Detail;
}

CWorld_Resource_UI::~CWorld_Resource_UI()
{
	SAFE_DELETE(resource_detail);
}

bool CWorld_Resource_UI::initialize(Graphics * g, Input * i)
{
	m_pGraphics = g;
	m_pInput = i;

	//SystemUIDialog::initializeDialog(m_pGraphics, m_pInput, 0, 0, 0, 0, 0);

	//dxfont_increase.initialize(m_pGraphics, worldresourceNS::FONT_SIZE_increase, true, false, worldresourceNS::FONT);

	resource_initialize(0, worldresourceNS::MONEY);
	resource_initialize(1, worldresourceNS::IRON);
	resource_initialize(2, worldresourceNS::FUEL);
	resource_initialize(3, worldresourceNS::RESEARCH);

	resource_detail->initialize(g, i);
	resource_detail->SetLoadLinkPlyaer(player);
	resource_detail->SetLoadLinkUI(this);

	//addMessage("save_1", "", true);
	//addMessage("increase_1", "", false);
	//addMessage("save_2", "", true);
	//addMessage("increase_2", "", false);
	//addMessage("save_3", "", true);
	//addMessage("increase_3", "", false);
	//addMessage("save_4", "", true);
	//addMessage("increase_4", "", false);

	m_dxfont.initialize(m_pGraphics, worldresourceNS::FONT_SIZE, true, false, worldresourceNS::FONT);
	
	return true;
}

void CWorld_Resource_UI::update(float frameTime)
{
	calcu_resource();
	resource_detail->update(frameTime);
	//setMessage("save_1", "11111", true);
	//setMessage("increase_1", "111", false);
	//setMessage("save_2", "22222", true);
	//setMessage("increase_2", "222", false);
	//setMessage("save_3", "33333", true);
	//setMessage("increase_3", "333", false);
	//setMessage("save_4", "44444", true);
	//setMessage("increase_4", "444", false);
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

	replace_number_img(rect_save[MONEY], player->get_resource(MONEY), true);
	replace_number_img(rect_save[IRON], player->get_resource(IRON), true);
	replace_number_img(rect_save[FUEL], player->get_resource(FUEL), true);
	replace_number_img(rect_save[RESEARCH], player->get_resource(RESEARCH), true);

	for (int i = 0; i < worldresourceNS::num; i++)
	{
		int amount = increase_resource[i] + decrease_resource[i];

		std::string str = std::to_string(fabs(amount));
		
		if (amount < 0)
			m_dxfont.print("-", rect_increase[i], DT_LEFT + DT_VCENTER);
		else
			m_dxfont.print("+", rect_increase[i], DT_LEFT + DT_VCENTER);

		replace_number_img(rect_increase[i], amount, false);
	}

	//for (auto iter : m_increaseMessage)
	//{
	//	dxfont_increase.print(iter.second, rect_increase[index], DT_VCENTER + DT_CENTER);

	//	index++;
	//}

	// =============== 생산될 자원 추가하기 ===============
	//for (auto iter : m_increaseMessage)
	//{
	//	replace_number_img(rect_increase[index], iter.second, false);

	//	index++;
	//}

	for (auto iter : list_number)
		iter->draw();

	m_pGraphics->spriteEnd();

	resource_detail->render();

	for (auto iter : list_number)
		SAFE_DELETE(iter);
	list_number.clear();
}

void CWorld_Resource_UI::replace_number_img(RECT rect, UINT _resource, bool big)
{
	//Add kind of number image
	std::string number = std::to_string(_resource);
	std::string name = "";

	int length = number.length();
	int c_temp = _resource;	//atoi(number.c_str());
	RECT rc_temp = rect;

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

		img->setX(rect.right);
		rect.right -= width;
		//else
		//{
		//	img->setX(rect.left);
		//	rect.left += width;
		//}

		img->setY(rect.top + ((rect.bottom - rect.top) / 2 - height / 2));

		list_number.emplace_back(img);
	}

	rect = rc_temp;
}
