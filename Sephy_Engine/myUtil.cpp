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

		if (y > 0) angle = MY_MATH_PI2 - angle;

		return angle;
	}

	bool getObjInScreen(int objX, int objY, int screenSizeW, int screenSizeH)
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

	bool getObjInScreen(int  objX, int objY, int objWidth, int objHeight, int screenSizeW, int screenSizeH)
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

	bool getPtInScreen(float ptX, float ptY, float screenWidth, float screenHeight)
	{

		if (ptX > 0 && ptX < screenWidth)
		{
			if (ptY > 0 && ptY < screenHeight)
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
		float width = rc.right - rc.left;
		float height = rc.bottom - rc.top;
		float centerX = rc.left + ((rc.right - rc.left) / 2);
		float centerY = rc.top + ((rc.bottom - rc.top) / 2);
		
		float m = 0.5f;

		VECTOR2 p1 = VECTOR2(centerX - (width / 2), centerY);	// LEFT MIDDLE
		VECTOR2 p2 = VECTOR2(centerX, centerY - (height / 2));	// TOP CENTER
		VECTOR2 p3 = VECTOR2(centerX + (width / 2), centerY);	// RIGHT MIDDLE
		VECTOR2 p4 = VECTOR2(centerX, centerY + (height / 2));	// BOTTOM CENTER

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
		float width = rc.right - rc.left;
		float height = rc.bottom - rc.top;
		float centerX = rc.left + ((rc.right - rc.left) / 2);
		float centerY = rc.top + ((rc.bottom - rc.top) / 2);

		float m = 0.5f;

		VECTOR2 p1 = VECTOR2(centerX - (width / 2), centerY);
		VECTOR2 p2 = VECTOR2(centerX, centerY - (height / 2));
		VECTOR2 p3 = VECTOR2(centerX + (width / 2), centerY);
		VECTOR2 p4 = VECTOR2(centerX, centerY + (height / 2));

		float d1 = p1.y - (-m * p1.x);
		float d2 = p2.y - (m * p2.x);
		float d3 = p3.y - (-m * p3.x);
		float d4 = p4.y - (m * p4.x);

		float result1 = -m * x - y + d1;
		float result2 = m * x - y + d2;
		float result3 = -m * x - y + d3;
		float result4 = m * x - y + d4;

		if (result1 <= 0.0f && result2 <= 0.0f && result3 >= 0.0f && result4 >= 0.0f)
		{
			return true;
		}
		return false;
	}

	bool ptInCircle(float centerX, float centerY, float radius, float ptX, float ptY)
	{
		float fCircleX = centerX;
		float fCircleY = centerY;
		float fRadius = radius;
		float fMouseX = ptX;
		float fMouseY = ptY;
		float fDistance = MyUtil::getDistance(fCircleX, fCircleY, fMouseX, fMouseY);

		if (fDistance <= radius)
		{
			return true;
		}

		return false;
	}
	bool circleInRect(float cx, float cy, float cr, const LPRECT rc)
	{
		float centerX = cx;
		float centerY = cy;
		float radius = cr;

		if ((rc->left <= centerX && centerX <= rc->right) ||
			(rc->top <= centerY && centerY <= rc->bottom))
		{
			RECT rcEx = {
				rc->left - radius,
				rc->top - radius,
				rc->right + radius,
				rc->bottom + radius
			};

			if ((rcEx.left < centerX && centerX <= rcEx.right) &&
				(rcEx.top < centerY && centerY < rcEx.bottom))
			{
				return true;
			}
		}
		else
		{
			if (ptInCircle(cx, cy, cr, rc->left, rc->top)) return true;
			if (ptInCircle(cx, cy, cr, rc->left, rc->bottom)) return true;
			if (ptInCircle(cx, cy, cr, rc->right, rc->top)) return true;
			if (ptInCircle(cx, cy, cr, rc->right, rc->bottom)) return true;
		}

		return false;
	}
	bool circleIncircle(float c1_x, float c1_y, float c1_rad, float c2_x, float c2_y, float c2_rad)
	{
		auto distance = getDistance(c1_x, c1_y, c2_x, c2_y);
		if (c1_rad + c2_rad > distance)
			return true;
		
		return false;
	}
	std::list<int> splitNumberToDigit(int number)
	{
		std::list<int> vDigits;
		if (number <= 0)
		{
			vDigits.push_front(0);
		}
		else
		{
			int remainNumber = number;
			while (number != 0)
			{
				int last = number % 10;
				vDigits.push_front(last);
				number = (number - last) / 10;
			}
		}

		return vDigits;
	}
}