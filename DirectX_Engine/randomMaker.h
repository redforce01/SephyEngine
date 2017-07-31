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

	int GetInt() const;
	int GetInt(int rangeMin, int rangeMax) const;
	float GetFloat() const;
	float GetFloat(float rangeMin, float rangeMax) const;
	int GetVectorInt(std::vector<int> &vec, int size);
	int GetVectorFloat(std::vector<float> &vec, int size);
	RECT GetRandomRect(float startX, float startY, float maxWidth, float maxHeight) const;
};

#endif // !_RANDOM_MAKER_H
