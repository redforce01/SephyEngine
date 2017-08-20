#include "stdafx.h"
#include "Battle_UI_StartButton.h"
#include "Battle_UnitSystem.h"

CBattle_UI_StartButton* pThis = nullptr;
CBattle_UI_StartButton::CBattle_UI_StartButton()
{
	::pThis = this;
	m_pBattleUnitSystem = nullptr;
}


CBattle_UI_StartButton::~CBattle_UI_StartButton()
{
}

bool CBattle_UI_StartButton::initialize(Graphics * g, Input * i)
{	
	bool success = SystemButton::initialize(g, i, 
		(g_fScreenWidth / 2) - (battleStartButtonNS::START_BUTTON_WIDTH / 2),
		battleStartButtonNS::START_BUTTON_Y,
		battleStartButtonNS::START_BUTTON_FILENAME, true);
	SystemButton::setRegistFunction(std::bind(&CBattle_UI_StartButton::functionBattleStart));

	return success;
}

void CBattle_UI_StartButton::update(float frameTime)
{
	SystemButton::update(frameTime);
}

void CBattle_UI_StartButton::render()
{
	SystemButton::render();
}

void CBattle_UI_StartButton::functionBattleStart()
{
	auto ships = pThis->m_pBattleUnitSystem->getPlayerShips();
	bool success = false;
	for (auto iter : ships)
	{
		if (iter->getShipActive())
		{
			success = true;
			break;
		}
	}
	if (success)
	{
		for (auto iter : ships)
		{
			if (iter->getShipActive())
			{
				pThis->m_pBattleUnitSystem->setBattleStart(true);
				pThis->m_pBattleUnitSystem->setBattlePhase(1);
				pThis->m_pBattleUnitSystem->setupActiveForStart();
				pThis->SystemButton::setActive(false);
				break;
			}
		}
		
	}
}
