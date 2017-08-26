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

	//======================================
	// Get Random - bool
	//  + return bool (true or false)
	//======================================
	bool GetBool() const;

	//======================================
	// Get Random - int
	//  + return -21 * (10 ^ 8) ~ 21 * (10 ^ 8)
	//======================================
	int GetInt() const;

	//======================================
	// Get Random - int( With Seed )
	//  + Using Seed
	//  + This Random Function ( used std::mt19937 )
	//  + return -21 * (10 ^ 8) ~ 21 * (10 ^ 8)
	//======================================
	int GetInt(int seed) const;

	//======================================
	// Get Random - int
	//  + return rangeMin ~ rangeMax
	//  + sample : 
	//   - min, max = (-10, 10)
	//   - result = -10 ~ 10
	//======================================
	int GetInt(int rangeMin, int rangeMax) const;

	//======================================
	// Get Random Vector int
	//  + return 
	//   - emplace random int to - &vec
	//  + sample :
	//   - vec , size(10)
	//   - for(index : 0 ~ 10)
	//     { vec[index] = random int; }
	//======================================
	void GetVectorInt(std::vector<int> &vec, int size);

	std::pair<int, int> GetPairInt() const;
	std::pair<int, int> GetPairInt(int firstMin, int firstMax, int secondMin, int secondMax) const;

	POINT GetPtInCircle(float centerX, float centerY, float radius) const;
	RECT GetRandomRect(float startX, float startY, float maxWidth, float maxHeight) const;
};

#define RANDOM_MAKER RandomMaker::GetInstance()
#endif // !_RANDOM_MAKER_H
