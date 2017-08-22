#pragma once

enum class E_lobby_world
{
	NORMAL, OVER, CLICK, 
};

namespace lobby_worldNS
{
	const std::string START_IMAGE = "MoveToBattle_000";
	const std::string START_IMAGE_SHADOW = "MoveToBattleShdw_000";
	const std::string NORMAL = "MoveToBattle_0";
	const std::string OVER = "MoveToBattleGlow_0";
	const std::string CLICK = "MoveToBattleClick_0";
	const std::string SHADOW = "MoveToBattleShdw_0";

	const std::string FILE_PATH = "Resources\\40_WorldData\\World_Game_State.txt";
	const std::string PLAY = "Play";

	const UINT MIN_IMG = 0;
	const UINT MAX_IMG = 10;

	const UINT IMG_WIDTH = 105;
	const UINT IMG_HEIGHT = 79;

	const float DELAY = 0.1f;
}

class CLobby_Change_World
{
private :
	Graphics* m_pGraphics;
	Input* m_pInput;

	Image* button;
	Image* shadow;

	RECT rt_button;

	int sprite_number;

	float delay;

	bool mouse_up;

	void animation(E_lobby_world _state);

public:
	CLobby_Change_World();
	~CLobby_Change_World();

	void initialize(Graphics* g, Input* i, int _x, int _y);
	void update(float frameTime);
	void render();

	UINT getWidth() { return button->getWidth(); }
};

