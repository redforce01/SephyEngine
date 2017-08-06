#ifndef _RANDOM_MAKER_H
#define _RANDOM_MAKER_H
#define WIN32_LEAN_AND_MEAN

class RandomMaker;

#include <chrono>
#include <random>
#include <vector>
#include "cSingletonBase.h"

class RandomMaker : public cSingletonBase<RandomMaker>
{
public:
	RandomMaker();
	~RandomMaker();

	bool GetBool() const;
	int GetInt() const;
	int GetInt(int rangeMin, int rangeMax) const;	
	void GetVectorInt(std::vector<int> &vec, int size);

	std::pair<int, int> GetPairInt() const;
	std::pair<int, int> GetPairInt(int firstMin, int firstMax, int secondMin, int secondMax) const;

	POINT GetPtInCircle(float centerX, float centerY, float radius) const;
	RECT GetRandomRect(float startX, float startY, float maxWidth, float maxHeight) const;
};

#define RANDOM_MAKER RandomMaker::GetInstance()
#endif // !_RANDOM_MAKER_H
