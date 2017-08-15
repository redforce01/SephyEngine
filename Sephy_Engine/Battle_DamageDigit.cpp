#include "stdafx.h"
#include "Battle_DamageDigit.h"


CBattle_DamageDigit::CBattle_DamageDigit()
{
	m_pGraphics		= nullptr;
	m_Damage		= 0;
	m_animeTime		= 0.f;
	m_bComplete		= false;
	m_enDigitType	= DIGIT_TYPE::DIGIT_TYPE_WHITE;
}

CBattle_DamageDigit::~CBattle_DamageDigit()
{
	for (auto iter : m_vDigit)
	{
		SAFE_DELETE(iter);
	}
	m_vDigit.clear();
}

bool CBattle_DamageDigit::initialize(Graphics * g, int damage, DIGIT_TYPE digitType, float startX, float startY)
{
	bool success = false;
	try
	{
		m_pGraphics = g;

		auto vDigit = getSplitNumber(damage);
		m_enDigitType = digitType;

		std::string digitKey;
		switch (m_enDigitType)
		{
		case DIGIT_TYPE::DIGIT_TYPE_WHITE:
			digitKey = battleDamageDigitNS::DIGIT_WHITE_KEY;
			break;
		case DIGIT_TYPE::DIGIT_TYPE_RED:
			digitKey = battleDamageDigitNS::DIGIT_RED_KEY;
			break;
		case DIGIT_TYPE::DIGIT_TYPE_BLUE:
			digitKey = battleDamageDigitNS::DIGIT_BLUE_KEY;
			break;
		}


		int digitCount = 0;
		for (auto iter : vDigit)
		{
			std::string resultKey = digitKey;
			Image* digitImage = new Image;
			resultKey += std::to_string(iter);
			success = digitImage->initialize(m_pGraphics, 0, 0, 0, IMAGEMANAGER->getTexture(resultKey));

			if (digitCount > 0)
				digitImage->setX(m_vDigit[digitCount - 1]->getX() + m_vDigit[digitCount - 1]->getWidth());
			else
				digitImage->setX(startX);
			digitImage->setY(startY);

			m_vDigit.emplace_back(digitImage);
			digitCount++;
		}
	}
	catch (...)
	{
		MessageBox(g_hWndEngine, battleDamageDigitNS::ERROR_MESSAGE.c_str(), "Error", MB_OK);
	}	

	return success;
}

void CBattle_DamageDigit::update(float frameTime)
{
	if (m_bComplete)
		return;
	else
	{
		for (auto iter : m_vDigit)
		{
			iter->moveY(-battleDamageDigitNS::DIGIT_ANIME_SPEED * frameTime);
		}

		if (m_animeTime < battleDamageDigitNS::DIGIT_ANIME_TIME)
		{
			m_animeTime += frameTime;
		}
		else
			m_bComplete = true;
	}
}

void CBattle_DamageDigit::render()
{
	if (m_bComplete)
		return;

	if (m_vDigit.size() > 0)
	{
		float digitX = m_vDigit[0]->getX();
		float digitY = m_vDigit[0]->getY();
		float digitWidth = m_vDigit[0]->getWidth();
		float digitHeight = m_vDigit[0]->getHeight();

		if (MyUtil::getObjInScreen(digitX, digitY, digitWidth, digitHeight, g_fScreenWidth, g_fScreenHeight) == false)
			return;
	}

	m_pGraphics->spriteBegin();
	for (auto iter : m_vDigit)
	{
		iter->draw();
	}
	m_pGraphics->spriteEnd();
}

std::list<int> CBattle_DamageDigit::getSplitNumber(int number)
{
	std::list<int> vDigits;
	if (number <= 0)
	{
		vDigits.push_back(0);
	}
	else
	{
		int remainNumber = number;
		while (number != 0)
		{
			int last = number % 10;
			vDigits.push_front(last);
			number = (number - last) / 10;
		}
	}

	return vDigits;
}

void CBattle_DamageDigit::moveX(float distance)
{
	for (auto iter : m_vDigit)
	{
		iter->moveX(distance);
	}
}

void CBattle_DamageDigit::moveY(float distance)
{
	for (auto iter : m_vDigit)
	{
		iter->moveY(distance);
	}
}
