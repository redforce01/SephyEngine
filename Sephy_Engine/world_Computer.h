#pragma once

#include "world_User.h"

namespace world_computerNS
{
	const std::string FLAG_NAME = "Computer_Flag";
	const int FLAG_WIDTH = 30;
	const int FLAG_HEIGHT = 30;
}

class CWorld_Computer : public CWorld_User
{
private :
	std::vector<Image*> img_list;

public:
	CWorld_Computer();
	~CWorld_Computer();

	void update(float frameTime);
	void render();
	void relase();

	void w_move_ud(float _speed);
	void w_move_rl(float _speed);
};
