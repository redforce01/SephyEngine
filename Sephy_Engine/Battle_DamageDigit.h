#ifndef _BATTLE_DAMAGEDIGIT_H
#define _BATTLE_DAMAGEDIGIT_H
#define WIN32_LEAN_AND_MEAN

class CBattle_DamageDigit;

#include <vector>
#include <list>
#include "image.h"

namespace battleDamageDigitNS
{

	const std::string ERROR_MESSAGE = "Battle Digit Initialize Failed";
	const std::string DIGIT_WHITE_KEY	= "NumWht";
	const std::string DIGIT_RED_KEY		= "NumRed";
	const std::string DIGIT_BLUE_KEY	= "NumBlue";

	const float DIGIT_ANIME_SPEED = 30.f;
	const float DIGIT_ANIME_TIME = 3.0f;
}

enum class DIGIT_TYPE
{ DIGIT_TYPE_WHITE, DIGIT_TYPE_RED, DIGIT_TYPE_BLUE };

class CBattle_DamageDigit
{
private:
	Graphics* m_pGraphics;
private:
	std::vector<Image*> m_vDigit;	
	int					m_Damage;
	float				m_animeTime;
	bool				m_bComplete;
	DIGIT_TYPE			m_enDigitType;
public:
	CBattle_DamageDigit();
	~CBattle_DamageDigit();

	bool initialize(Graphics* g, int damage, DIGIT_TYPE digitType, float startX, float startY);
	void update(float frameTime);
	void render();

	std::list<int> getSplitNumber(int number);

	void moveX(float distance);
	void moveY(float distance);

	bool IsAnimeComplete() const
	{
		return m_bComplete;
	}
};

#endif // !_BATTLE_DAMAGEDIGIT_H
