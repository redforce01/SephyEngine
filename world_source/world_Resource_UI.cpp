#include "stdafx.h"
#include "world_Resource_UI.h"

void CWorld_Resource_UI::resource_initialize(int index, std::string img)
{
	img_resource[index]->initialize(m_pGraphics, worldresourceNS::img_width, worldresourceNS::img_height, 0, IMAGEMANAGER->getTexture(img));

	img_resource[index]->setX(worldresourceNS::x);
	img_resource[index]->setY(worldresourceNS::y + (worldresourceNS::img_height + worldresourceNS::distance_y) * index);

	//standrad img_resource's position
	UINT pos_rect_x = img_resource[index]->getX() + img_resource[index]->getWidth() + worldresourceNS::distance_x;
	UINT pos_rect_y = img_resource[index]->getY() + (worldresourceNS::img_height - worldresourceNS::save_height) / 2;

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

	resource_initialize(0, worldresourceNS::img_name);
	resource_initialize(1, "ExitButton");
	resource_initialize(2, "ExitButton");
	resource_initialize(3, "ExitButton");

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
	setMessage("increase_1", "+ 111", false);
	setMessage("save_2", "22222", true);
	setMessage("increase_2", "+ 222", false);
	setMessage("save_3", "33333", true);
	setMessage("increase_3", "+ 333", false);
	setMessage("save_4", "44444", true);
	setMessage("increase_4", "+ 444", false);
}

void CWorld_Resource_UI::render()
{
	m_pGraphics->spriteBegin();

	for (int i = 0; i < worldresourceNS::num; i++)
		img_resource[i]->draw();

	int index = 0;

	for (auto iter : m_saveMessage)
	{
		dxfont_save.print(iter.second, rect_save[index], DT_VCENTER + DT_CENTER);

		index++;
	}

	index = 0;

	for (auto iter : m_increaseMessage)
	{
		dxfont_increase.print(iter.second, rect_increase[index], DT_VCENTER + DT_CENTER);

		index++;
	}

	m_pGraphics->spriteEnd();

	for (int i = 0; i < worldresourceNS::num; i++)
	{
		m_pGraphics->drawRect(rect_save[i]);
		m_pGraphics->drawRect(rect_increase[i]);
	}
}
