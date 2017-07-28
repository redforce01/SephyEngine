#pragma once
#ifndef _MY_UTIL_H            // Prevent multiple definitions if this 
#define _MY_UTIL_H            // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include <cmath>
#include <vector>
//-----------------------------------------------
// #Defines
//-----------------------------------------------
#define MY_MATH_PI		3.141592654f
#define MY_MATH_PI2		(MY_MATH_PI * 2)
#define MY_MATH_PI8		float(MY_MATH_PI / 8.0f)
#define MY_MATH_PI16	float(MY_MATH_PI / 16.f)
#define MY_MATH_PI32	float(MY_MATH_PI / 32.f)
#define MY_MATH_PI64	float(MY_MATH_PI / 64.f)
#define MY_MATH_PI128	float(MY_MATH_PI / 128.f)

#define MY_MATH_EPSILON 0.0001f

#define ONE_RAD (PI / 180)

namespace MyUtil
{
	// 거리 구하는 함수
	float getDistance(float startX, float startY, float endX, float endY);

	// 각도 구하는 함수
	float getAngle(float startX, float startY, float endX, float endY);

	// Object in Screen? Function. return bool
	bool getScreenIn(int objX, int objY, int screenSizeW, int screenSizeH);

	// Object in Screen(with Object Width/Height)? Function. return bool
	bool getScreenIn(int objX, int objY, int objWidth, int objHeight, int screenSizeW, int screenSizeH);
		
	// Not Implementated
	bool getObjectIn(int objX, int objY, int objWidth, int objHeight, int targetX, int targetY);

	// Get Horizon Center Value(float) In Rect
	float getCenterHorizonInRect(RECT &rc);

	// Get Vertical Center Value(float) In Rect
	float getCenterVerticalInRect(RECT &rc);

	// Get Isometric In Bool used (RECT, POINT)
	bool getIsometricIn(RECT &rc, POINT pt);

	// Get Isometric In Bool used (RECT, float x,y)
	bool getIsometricIn(RECT &rc, float x, float y);	 
}

#endif