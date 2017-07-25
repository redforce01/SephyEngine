#pragma once

#include "systemUIDialog.h"
#include "world_Ship.h"

class CWorld_Action_Ship : public SystemUIDialog
{
private:
	Graphics* m_pGraphics;
	Input* m_pInput;

	std::vector<CWorld_Ship*> current_ship;
	std::vector<CWorld_Ship*> w_ship;

public:
	CWorld_Action_Ship();
	~CWorld_Action_Ship();

	bool initialize(Graphics* g, Input* i) override;
	virtual void update(float frameTime) override;
	virtual void render() override;

	void add_ship(std::string _name, UINT _x, UINT _y, float _degree);
	std::vector<CWorld_Ship*> get_current_ship() { return current_ship; }
	void worldMoveud(float worldSpeed)
	{
		for (auto iter : w_ship)
			iter->worldMoveud(worldSpeed);
	}

	void worldMoverl(float worldSpeed)
	{
		for (auto iter : w_ship)
			iter->worldMoverl(worldSpeed);
	}
};

