#include "stdafx.h"
#include "myUtil.h"

namespace MyUtil
{
	//거리 구하는 함수
	float getDistance(float startX, float startY, float endX, float endY)
	{
		float x = endX - startX;
		float y = endY - startY;

		return sqrtf(x * x + y * y);
	}

	//각도 구하는 함수
	float getAngle(float startX, float startY, float endX, float endY)
	{
		float x = endX - startX;
		float y = endY - startY;

		float distance = sqrtf(x * x + y * y);
		float angle = acosf(x / distance);

		if (y > 0) angle = MY_UTIL_PI2 - angle;

		return angle;
	}

	bool getScreenIn(float objX, float objY, float screenSizeW, float screenSizeH)
	{
		if (objX > 0 && objX < screenSizeW)
		{
			if (objY > 0 && objY < screenSizeH)
			{
				return true;
			}
		}
		
		return false;
	}

	bool getScreenIn(float objX, float objY, float objWidth, float objHeight, float screenSizeW, float screenSizeH)
	{
		if (objX > -objWidth && objX < screenSizeW + objWidth)
		{
			if (objY > -objHeight && objY < screenSizeH + objHeight)
			{
				return true;
			}
		}

		return false;
	}


}