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

	float getCenterHorizonInRect(RECT & rc)
	{
		return rc.left + ((rc.right - rc.left) / 2);
	}

	float getCenterVerticalInRect(RECT & rc)
	{
		return rc.top + ((rc.bottom - rc.top) / 2);
	}

	
	//=============================================================================
	//					----/\---- TOP CENTER [x+(w/2)][y]
	//					|  /  \  |
	//					| /	   \ |
	//	     LEFT MIDDLE|/		\| RIGHT MIDDLE
	//		[x][y+(h/2)]|\		/| [x+w][y+(h/2)]
	//					| \	   / |
	//					|  \  /  |
	//					----\/---- BOTTOM CENTER [x+(w/2)][y+h]
	//=============================================================================
	bool getIsometricIn(RECT & rc, POINT pt)
	{
		int TopCenterX = rc.left + (rc.right - rc.left) / 2;
		int TopCenterY = rc.top;
		int LeftCenterX = rc.left;
		int LeftCenterY = rc.top + (rc.bottom - rc.top) / 2;
		int RightCenterX = rc.right;
		int RightCenterY = rc.top + (rc.bottom - rc.top) / 2;
		int BottomCenterX = rc.left + (rc.right - rc.left) / 2;
		int BottomCenterY = rc.bottom;

		float m = 0.5f;
		VECTOR2 p1 = VECTOR2(TopCenterX, TopCenterY);
		VECTOR2 p2 = VECTOR2(LeftCenterX, LeftCenterY);
		VECTOR2 p3 = VECTOR2(RightCenterX, RightCenterY);
		VECTOR2 p4 = VECTOR2(BottomCenterX, BottomCenterY);

		float d1 = p1.y - (-m * p1.x);
		float d2 = p2.y - (m * p2.x);
		float d3 = p3.y - (-m * p3.x);
		float d4 = p4.y - (m * p4.x);

		float result1 = -m * pt.x - pt.y + d1;
		float result2 = m * pt.x - pt.y + d2;
		float result3 = -m * pt.x - pt.y + d3;
		float result4 = m * pt.x - pt.y + d4;

		if (result1 <= 0.0f && result2 <= 0.0f && result3 >= 0.0f && result4 >= 0.0f)
		{
			return true;
		}
		return false;
	}

	bool getIsometricIn(RECT & rc, float x, float y)
	{
		return false;
	}


}