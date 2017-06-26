#include "stdafx.h"
#include "myUtil.h"

namespace MyUtil
{
	//�Ÿ� ���ϴ� �Լ�
	float getDistance(float startX, float startY, float endX, float endY)
	{
		float x = endX - startX;
		float y = endY - startY;

		return sqrtf(x * x + y * y);
	}

	//���� ���ϴ� �Լ�
	float getAngle(float startX, float startY, float endX, float endY)
	{
		float x = endX - startX;
		float y = endY - startY;

		float distance = sqrtf(x * x + y * y);
		float angle = acosf(x / distance);

		if (y > 0) angle = MY_UTIL_PI2 - angle;

		return angle;
	}

	bool getScreenIn(int objX, int objY, int screenSizeW, int screenSizeH)
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

	bool getScreenIn(int  objX, int objY, int objWidth, int objHeight, int screenSizeW, int screenSizeH)
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