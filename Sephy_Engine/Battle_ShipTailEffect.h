#ifndef _BATTLE_SHIP_TAIL_EFFECT_H
#define _BATTLE_SHIP_TAIL_EFFECT_H
#define WIN32_LEAN_AND_MEAN

class CBattle_ShipTailEffect;

#include "image.h"

namespace battleShipTailEffectNS
{
	const std::string ERROR_MESSAGE = "Ship Tail Effect Initialize Failed";
	const std::string TAIL_EFFECT_FILENAME = "Ship_Tail_Effect";
	const COLOR_ARGB TAIL_EFFECT_COLOR_FILTER = SETCOLOR_ARGB(128, 128, 128, 128);
	const float TAIL_EFFECT_MAX_ALPHA = 64.f;
	const float TAIL_EFFECT_TIME = 20.f;
}

class CBattle_Ship;
class CBattle_ShipTailEffect : public Image
{
private:
	Graphics* m_pGraphics;
	CBattle_Ship* m_pMaster;
	//===============================================
	bool	m_bActive;
	float	m_fEffectAlpha;
	float	m_fEffectTime;
public:
	CBattle_ShipTailEffect();
	~CBattle_ShipTailEffect();

	bool initialize(Graphics* g, CBattle_Ship* pMaster);
	void update(float frameTime);
	void render();

	void setActive();
	bool getActive() const
	{
		return m_bActive;
	}
};

#endif // !_BATTLE_SHIP_TAIL_EFFECT_H
