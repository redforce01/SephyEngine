#include "stdafx.h"
#include "Battle_ShipTailEffect.h"
#include "Battle_Ship.h"

CBattle_ShipTailEffect::CBattle_ShipTailEffect()
{
	m_pGraphics		= nullptr;
	m_pMaster		= nullptr;
	m_bActive		= false;
	m_fEffectAlpha	= battleShipTailEffectNS::TAIL_EFFECT_MAX_ALPHA;
	m_fEffectTime	= 0.f;
}


CBattle_ShipTailEffect::~CBattle_ShipTailEffect()
{
}

bool CBattle_ShipTailEffect::initialize(Graphics * g, CBattle_Ship* pMaster)
{
	bool success = false;
	try
	{
		m_pGraphics = g;
		m_pMaster = pMaster;

		success = Image::initialize(m_pGraphics, 0, 0, 0, IMAGEMANAGER->getTexture(battleShipTailEffectNS::TAIL_EFFECT_FILENAME));
		//Image::setColorFilter(battleShipTailEffectNS::TAIL_EFFECT_COLOR_FILTER);
		Image::setX(m_pMaster->getCurrentCenterX() - (Image::getWidth() / 2));
		Image::setX(m_pMaster->getCurrentCenterY() - (Image::getHeight() / 2));
	}
	catch (...)
	{
		MessageBox(g_hWndEngine, battleShipTailEffectNS::ERROR_MESSAGE.c_str(), "Error", MB_OK);
	}

	return success;
}

void CBattle_ShipTailEffect::update(float frameTime)
{
	if (m_bActive == false)
		return;

	m_fEffectTime += frameTime;
	if (m_fEffectTime >= battleShipTailEffectNS::TAIL_EFFECT_TIME)
	{
		m_fEffectTime = 0.f;
		m_bActive = false;

	}
}

void CBattle_ShipTailEffect::render()
{
	if (m_bActive)
	{
		m_pGraphics->spriteBegin();
		Image::draw();
		m_pGraphics->spriteEnd();
	}
}

void CBattle_ShipTailEffect::setActive()
{
	m_bActive = true;
	Image::setX(m_pMaster->getCurrentCenterX() - (Image::getWidth() / 2));
	Image::setY(m_pMaster->getCurrentCenterY() - (Image::getHeight() / 2));
}
