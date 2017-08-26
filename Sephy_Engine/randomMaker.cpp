#include "stdafx.h"
#include "randomMaker.h"


RandomMaker::RandomMaker()
{
}


RandomMaker::~RandomMaker()
{
}

bool RandomMaker::GetBool() const
{
	std::random_device rand;
	return rand() % 2;
}

int RandomMaker::GetInt() const
{
	std::random_device rand;
	return rand();
}

int RandomMaker::GetInt(int rangeMin, int rangeMax) const
{
	std::random_device rand;
	std::uniform_int_distribution<int> range(rangeMin, rangeMax);
	return range(rand);
}

int RandomMaker::GetInt(int seed) const
{
	std::mt19937 rand(seed);
	return rand();
}

void RandomMaker::GetVectorInt(std::vector<int>& vec, int size)
{
	std::random_device rand;
	for (int i = 0; i < size; i++)
	{
		vec.push_back(rand());
	}
}

std::pair<int, int> RandomMaker::GetPairInt() const
{
	std::random_device rand;
	std::pair<int, int> result;
	result.first = rand();
	result.second = rand();
	return result;
}

std::pair<int, int> RandomMaker::GetPairInt(int firstMin, int firstMax, int secondMin, int secondMax) const
{
	std::random_device rand;
	std::uniform_int_distribution<int> rangeFirst(firstMin, firstMax);
	std::pair<int, int> result;
	result.first = rangeFirst(rand);
	std::uniform_int_distribution<int> rangeSecond(secondMin, secondMax);
	result.second = rangeSecond(rand);
	return result;
}

POINT RandomMaker::GetPtInCircle(float centerX, float centerY, float radius) const
{
	POINT ptResult;
	float ptX = 0.f;
	float ptY = 0.f;
	std::random_device rand;
	std::uniform_int_distribution<int> rangeHorizon(centerX - radius, centerX + radius);
	ptX = rangeHorizon(rand);
	std::uniform_int_distribution<int> rangeVertical(centerY - radius, centerY + radius);
	ptY = rangeVertical(rand);
	ptResult.x = ptX;
	ptResult.y = ptY;

	if (MyUtil::getDistance(centerX, centerY, ptResult.x, ptResult.y) < radius)
		return ptResult;
	else
		return GetPtInCircle(centerX, centerY, radius);
}

RECT RandomMaker::GetRandomRect(float startX, float startY, float maxWidth, float maxHeight) const
{
	RECT rcResult;
	float endX = 0;
	float endY = 0;
	std::random_device rand;
	std::uniform_int_distribution<int> rangeHorizon(startX, startX + maxWidth);
	endX = rangeHorizon(rand);
	std::uniform_int_distribution<int> rangeVertical(startY, startY + maxHeight);
	endY = rangeVertical(rand);
	rcResult.left = startX;
	rcResult.top = startY;
	rcResult.right = endX;
	rcResult.bottom = endY;
	return rcResult;
}
