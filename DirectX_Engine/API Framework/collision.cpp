#include "stdafx.h"
//#include "collision.h"
//
//
//namespace MY_UTIL
//{
//	//점이 사각형 안에 있나?
//	bool checkPointInRect( const RECT& rc, const POINT &pt )
//	{
//		if ( ( rc.left <= pt.x && pt.x <= rc.right ) && ( rc.top <= pt.y && pt.y <= rc.bottom ) ) return true;
//		return false;
//	}
//
//	bool checkPointInRect( const RECT& rc, int x, int y )
//	{
//		if ( ( rc.left <= x && x <= rc.right ) && ( rc.top <= y && y <= rc.bottom ) ) return true;
//		return false;
//	}
//
//	bool checkPointInRect( const MYRECT& rc, float x, float y )
//	{
//		if ( ( rc.left <= x && x <= rc.right ) && ( rc.top <= y && y <= rc.bottom ) ) return true;
//		return false;
//	}
//
//	bool checkPointInRect( const MYRECT& rc, const MYPOINT& pt )
//	{
//		if ( ( rc.left <= pt.x && pt.x <= rc.right ) && ( rc.top <= pt.y && pt.y <= rc.bottom ) ) return true;
//		return false;
//	}
//
//	//점이 원 안에 있나?
//	bool checkPointInCircle( float cX, float cY, float cR, const MYPOINT& pt )
//	{
//		float deltaX = pt.x - cX;
//		float deltaY = pt.y - cY;
//
//		//거리 제곱
//		float distSquare = deltaX * deltaX + deltaY * deltaY;
//
//		//반지름 제곱
//		float radiusSquare = cR * cR;
//
//		if ( radiusSquare < distSquare ) return false;
//
//		return true;
//	}
//
//	bool checkPointInCircle( float cX, float cY, float cR, float x, float y )
//	{
//		float deltaX = x - cX;
//		float deltaY = y - cY;
//
//		//거리 제곱
//		float distSquare = deltaX * deltaX + deltaY * deltaY;
//
//		//반지름 제곱
//		float radiusSquare = cR * cR;
//
//		if ( radiusSquare < distSquare ) return false;
//
//		return true;
//	}
//
//	bool checkPointInCircle( const MYCIRCLE& rc, float x, float y )
//	{
//		float deltaX = x - rc.x;
//		float deltaY = y - rc.y;
//
//		//거리 제곱
//		float distSquare = deltaX * deltaX + deltaY * deltaY;
//
//		//반지름 제곱
//		float radiusSquare = rc.r * rc.r;
//
//		if ( radiusSquare < distSquare ) return false;
//
//		return true;
//	}
//
//	bool checkPointInCircle( const MYCIRCLE& rc, const MYPOINT& pt )
//	{
//		float deltaX = pt.x - rc.x;
//		float deltaY = pt.y - rc.y;
//
//		//거리 제곱
//		float distSquare = deltaX * deltaX + deltaY * deltaY;
//
//		//반지름 제곱
//		float radiusSquare = rc.r * rc.r;
//
//		if ( radiusSquare < distSquare ) return false;
//
//		return true;
//	}
//
//	//사각형이 사각형이랑 충돌했나?
//	bool isCollision( const MYRECT& rc1, const MYRECT& rc2 )
//	{
//		if ( ( rc1.left <= rc2.right && rc1.right >= rc2.left ) &&
//			( rc1.top <= rc2.bottom && rc1.bottom >= rc2.top ) ) return true;
//		
//		return false;
//	}
//
//	bool isCollision( const RECT& rc1, const RECT& rc2 )
//	{
//		if ( ( rc1.left <= rc2.right && rc1.right >= rc2.left ) &&
//			( rc1.top <= rc2.bottom && rc1.bottom >= rc2.top ) ) return true;
//
//		return false;
//	}
//
//	//원과 원이 충돌했나?
//	bool isCollision( const MYCIRCLE& cir1, const MYCIRCLE& cir2 )
//	{
//		float deltaX = cir2.x - cir1.x;
//		float deltaY = cir2.y - cir1.y;
//
//		float distSquare = deltaX * deltaX + deltaY * deltaY;
//
//		float radius = cir1.r + cir2.r;
//		float radiusSquare = radius * radius;
//
//		if ( distSquare > radiusSquare ) return false;
//
//		return true;
//	}
//
//	//원과 사각형이 충돌했나?
//	bool isCollision( const MYCIRCLE& cir, const RECT& rc )
//	{
//		int centerX = FLOAT_TO_INT( cir.x );
//		int centerY = FLOAT_TO_INT( cir.y );
//		int radius = FLOAT_TO_INT( cir.r );
//
//		if ( ( rc.left <= centerX && centerX <= rc.right ) ||
//			( rc.top <= centerY && centerY <= rc.bottom ) )
//		{
//			RECT exRect;
//			exRect.left = rc.left - radius;
//			exRect.right = rc.right + radius;
//			exRect.top = rc.top - radius;
//			exRect.bottom = rc.bottom + radius;
//
//			if ( ( exRect.left <= centerX && centerX <= exRect.right ) &&
//				( exRect.top <= centerY && centerY <= exRect.bottom ) )
//			{
//				return true;
//			}
//		}
//		else
//		{
//			//좌상단
//			if ( checkPointInCircle( cir, (float) rc.left, (float) rc.top ) ) return true;
//			//우상단
//			if ( checkPointInCircle( cir, (float) rc.right, (float) rc.top ) ) return true;
//			//좌하단
//			if ( checkPointInCircle( cir, (float) rc.left, (float) rc.bottom ) ) return true;
//			//우하단
//			if ( checkPointInCircle( cir, (float) rc.right, (float) rc.bottom ) ) return true;
//		}
//
//		return false;
//	}
//
//	bool isCollision( const MYCIRCLE& cir, const MYRECT& rc )
//	{
//		int centerX = FLOAT_TO_INT( cir.x );
//		int centerY = FLOAT_TO_INT( cir.y );
//		int radius = FLOAT_TO_INT( cir.r );
//
//		if ( ( rc.left <= centerX && centerX <= rc.right ) ||
//			( rc.top <= centerY && centerY <= rc.bottom ) )
//		{
//			RECT exRect;
//			exRect.left = rc.left - radius;
//			exRect.right = rc.right + radius;
//			exRect.top = rc.top - radius;
//			exRect.bottom = rc.bottom + radius;
//
//			if ( ( exRect.left <= centerX && centerX <= exRect.right ) &&
//				( exRect.top <= centerY && centerY <= exRect.bottom ) )
//			{
//				return true;
//			}
//		}
//		else
//		{
//			//좌상단
//			if ( checkPointInCircle( cir, (float) rc.left, (float) rc.top ) ) return true;
//			//우상단
//			if ( checkPointInCircle( cir, (float) rc.right, (float) rc.top ) ) return true;
//			//좌하단
//			if ( checkPointInCircle( cir, (float) rc.left, (float) rc.bottom ) ) return true;
//			//우하단
//			if ( checkPointInCircle( cir, (float) rc.right, (float) rc.bottom ) ) return true;
//		}
//
//		return false;
//	}
//
//	//충돌후 리액션은?
//	bool isCollisionReaction( const RECT& rcHold, RECT& rcMove )
//	{
//		RECT rcInter;
//
//		if ( !IntersectRect( &rcInter, &rcHold, &rcMove ) ) return false;
//
//		//여기까지 내려오면 충돌
//		int interW = rcInter.right - rcInter.left;
//		int interH = rcInter.bottom - rcInter.top;
//
//		//수직충돌
//		if ( interW > interH )
//		{
//			//위
//			if ( rcInter.top == rcHold.top )
//			{
//				OffsetRect( &rcMove, 0, -interH );
//			}
//			//아래
//			else if ( rcInter.bottom == rcHold.bottom )
//			{
//				OffsetRect( &rcMove, 0, interH );
//			}
//		}
//		else
//		{
//			//좌
//			if ( rcInter.top == rcHold.top )
//			{
//				OffsetRect( &rcMove, -interW, 0 );
//			}
//			//우
//			else if ( rcInter.bottom == rcHold.bottom )
//			{
//				OffsetRect( &rcMove, interW, 0 );
//			}
//		}
//
//		return true;
//	}
//
//	bool isCollisionReaction( const MYRECT& mrcHold, MYRECT& mrcMove )
//	{
//		RECT rcHold;
//		rcHold.left = FLOAT_TO_INT( mrcHold.left );
//		rcHold.top = FLOAT_TO_INT( mrcHold.top );
//		rcHold.right = FLOAT_TO_INT( mrcHold.right );
//		rcHold.bottom = FLOAT_TO_INT( mrcHold.bottom );
//
//		RECT rcMove;
//		rcMove.left = FLOAT_TO_INT( mrcMove.left );
//		rcMove.top = FLOAT_TO_INT( mrcMove.top );
//		rcMove.right = FLOAT_TO_INT( mrcMove.right );
//		rcMove.bottom = FLOAT_TO_INT( mrcMove.bottom );
//
//		RECT rcInter;
//
//		if ( !IntersectRect( &rcInter, &rcHold, &rcMove ) ) return false;
//
//		//여기까지 내려오면 충돌
//		int interW = rcInter.right - rcInter.left;
//		int interH = rcInter.bottom - rcInter.top;
//
//		//수직충돌
//		if ( interW > interH )
//		{
//			//위
//			if ( rcInter.top == rcHold.top )
//			{
//				OffsetRect( &rcMove, 0, -interH );
//			}
//			//아래
//			else if ( rcInter.bottom == rcHold.bottom )
//			{
//				OffsetRect( &rcMove, 0, interH );
//			}
//		}
//		else
//		{
//			//좌
//			if ( rcInter.top == rcHold.top )
//			{
//				OffsetRect( &rcMove, -interW, 0 );
//			}
//			//우
//			else if ( rcInter.bottom == rcHold.bottom )
//			{
//				OffsetRect( &rcMove, interW, 0 );
//			}
//		}
//
//		mrcMove.left	= static_cast<float>( rcMove.left );
//		mrcMove.top		= static_cast<float>( rcMove.top );
//		mrcMove.right	= static_cast<float>( rcMove.right );
//		mrcMove.bottom	= static_cast<float>( rcMove.bottom );
//
//		return true;
//	}
//
//	bool isCollisionReaction( const MYCIRCLE& cirHold, MYCIRCLE& cirMove )
//	{
//		float deltaX = cirMove.x - cirHold.x;
//		float deltaY = cirMove.y - cirHold.y;
//
//		float distance = sqrt( deltaX * deltaX + deltaY * deltaY );
//
//		float radius = cirHold.r + cirMove.r;
//
//		if ( distance < radius )
//		{
//			float angle = getAngle( cirHold.x, cirHold.y, cirMove.x, cirMove.y );
//
//			float moveDelta = radius - distance;
//			float moveX = cos( angle ) * moveDelta;
//			float moveY = -sin( angle ) * moveDelta;
//
//			cirMove.move( moveX, moveY );
//
//			return true;
//		}
//
//		return false;
//	}
//}