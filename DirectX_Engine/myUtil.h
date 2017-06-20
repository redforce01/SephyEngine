#pragma once
#ifndef _MY_UTIL_H            // Prevent multiple definitions if this 
#define _MY_UTIL_H            // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include <cmath>
#include <vector>
//-----------------------------------------------
// #Defines
//-----------------------------------------------
#define MY_UTIL_PI		3.141592654f
#define MY_UTIL_PI2		(MY_UTIL_PI * 2)
#define MY_UTIL_PI8		float(MY_UTIL_PI / 8.0f)
#define MY_UTIL_PI16	float(MY_UTIL_PI / 16.f)
#define MY_UTIL_PI32	float(MY_UTIL_PI / 32.f)
#define MY_UTIL_PI64	float(MY_UTIL_PI / 64.f)
#define MY_UTIL_PI128	float (MY_UTIL_PI / 128.f)

#define ONE_RAD (PI / 180)

namespace MyUtil
{
	//거리 구하는 함수
	float getDistance(float startX, float startY, float endX, float endY);

	//각도 구하는 함수
	float getAngle(float startX, float startY, float endX, float endY);

	//Object in Screen? Function. return bool
	bool getScreenIn(float objX, float objY, float screenSizeW, float screenSizeH);

	//Object in Screen(with Object Width/Height)? Function. return bool
	bool getScreenIn(float objX, float objY, float objWidth, float objHeight, float screenSizeW, float screenSizeH);
		
	bool getObjectIn(float objX, float objY, float objWidth, float objHeight, float targetX, float targetY);

}

#endif