#include "stdafx.h"
#include "lobby_Change_World.h"

void CLobby_Change_World::animation(E_lobby_world _state)
{
	std::string img;

	switch (_state)
	{
	case E_lobby_world::NORMAL:	//mouse normal
		if (sprite_number < 10)
			img = lobby_worldNS::NORMAL + "0" + std::to_string(sprite_number);
		else img = lobby_worldNS::NORMAL + std::to_string(sprite_number);

		break;
	case E_lobby_world::OVER:	//mouse over
		if (sprite_number < 10)
			img = lobby_worldNS::OVER + "0" + std::to_string(sprite_number);
		else img = lobby_worldNS::OVER + std::to_string(sprite_number);

		break;
	case E_lobby_world::CLICK:	//mouse click
		if (sprite_number < 10)
			img = lobby_worldNS::CLICK + "0" + std::to_string(sprite_number);
		else img = lobby_worldNS::CLICK + std::to_string(sprite_number);

		break;
	}

	button->setTextureManager(IMAGEMANAGER->getTexture(img));

	if (sprite_number < 10)
		img = lobby_worldNS::SHADOW + "0" + std::to_string(sprite_number);
	else img = lobby_worldNS::SHADOW + std::to_string(sprite_number);

	shadow->setTextureManager(IMAGEMANAGER->getTexture(img));
}

CLobby_Change_World::CLobby_Change_World()
{
	button = new Image;
	shadow = new Image;

	sprite_number = 0;
	delay = 0;
	rt_button = { 0, };

	mouse_up = false;
}


CLobby_Change_World::~CLobby_Change_World()
{
	SAFE_DELETE(button);
	SAFE_DELETE(shadow);
}

void CLobby_Change_World::initialize(Graphics * g, Input * i, int _x, int _y)
{
	m_pGraphics = g;
	m_pInput = i;

	button->initialize(g, lobby_worldNS::IMG_WIDTH, lobby_worldNS::IMG_HEIGHT, 0, IMAGEMANAGER->getTexture(lobby_worldNS::START_IMAGE));
	shadow->initialize(g, lobby_worldNS::IMG_WIDTH, lobby_worldNS::IMG_HEIGHT, 0, IMAGEMANAGER->getTexture(lobby_worldNS::START_IMAGE_SHADOW));

	button->setX(_x);
	button->setY(_y);
	shadow->setX(_x);
	shadow->setY(_y);

	rt_button = RectMake(button->getX(), button->getY(), button->getWidth(), button->getHeight());
}

void CLobby_Change_World::update(float frameTime)
{
	animation(E_lobby_world::NORMAL);

	if (PtInRect(&rt_button, m_pInput->getMousePt()))
		animation(E_lobby_world::OVER);

	if (m_pInput->getMouseLButton())
	{
		if (PtInRect(&rt_button, m_pInput->getMousePt()))
			animation(E_lobby_world::CLICK);

		mouse_up = true;
	}
	else
	{
		if (mouse_up == true)
		{
			if (PtInRect(&rt_button, m_pInput->getMousePt()))
			{
				std::vector<std::string> temp;
				temp.emplace_back(lobby_worldNS::PLAY);

				TXTDATA_PARSER->saveDataFromArray(lobby_worldNS::FILE_PATH, temp);

				SCENEMANAGER->changeScene("World");

				return;
			}
		}

		mouse_up = false;
	}

	delay += frameTime;
	if (delay >= lobby_worldNS::DELAY)
	{
		sprite_number++;

		if (sprite_number > 10)
			sprite_number = 0;

		delay = 0;
	}
}

void CLobby_Change_World::render()
{
	m_pGraphics->spriteBegin();

	//shadow->draw();
	button->draw();

	m_pGraphics->spriteEnd();
}
