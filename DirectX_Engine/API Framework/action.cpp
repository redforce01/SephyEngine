#include "stdafx.h"
//#include "action.h"
//
//
//action::action()
//{
//}
//
//
//action::~action()
//{
//}
//
//HRESULT action::init()
//{
//	_callbackFunction = NULL;
//	_worldTimeCount = 0.f;
//	_isMoving = false;
//
//	return S_OK;
//}
//
//void action::release()
//{
//}
//
//void action::update()
//{
//	moving();
//}
//
//void action::render()
//{
//}
//
//void action::moveTo(image * image, float endX, float endY, float time)
//{
//	if (!_isMoving)
//	{
//		_callbackFunction = NULL;
//
//		//이미지 주소 값 담아주자
//		_image = image;
//
//		//이동 시작점
//		_startX = image->getX();
//		_startY = image->getY();
//
//		//도착지점
//		_endX = endX;
//		_endY = endY;
//
//		//이동거리 구하자
//		_travelRange = MY_UTIL::getDistance(_startX, _startY, _endX, _endY);
//
//		//각도 구하자
//		_angle = MY_UTIL::getAngle(_startX, _startY, _endX, _endY);
//
//		//월드 타임 저장하자
//		_worldTimeCount = TIMEMANAGER->getWorldTime();
//
//		//이동 시간
//		_time = time;
//
//		_isMoving = true;
//	}
//}
//
//void action::moveTo(image * image, float endX, float endY, float time, CALLBACK_FUNCTION cbFunction)
//{
//	if (!_isMoving)
//	{
//		_callbackFunction = cbFunction;
//
//		//이미지 주소 값 담아주자
//		_image = image;
//
//		//이동 시작점
//		_startX = image->getX();
//		_startY = image->getY();
//
//		//도착지점
//		_endX = endX;
//		_endY = endY;
//
//		//이동거리 구하자
//		_travelRange = MY_UTIL::getDistance(_startX, _startY, _endX, _endY);
//
//		//각도 구하자
//		_angle = MY_UTIL::getAngle(_startX, _startY, _endX, _endY);
//
//		//월드 타임 저장하자
//		_worldTimeCount = TIMEMANAGER->getWorldTime();
//
//		//이동 시간
//		_time = time;
//
//		_isMoving = true;
//	}
//}
//
//void action::moving()
//{
//	if (!_isMoving) return;
//
//	float elapsedTime = TIMEMANAGER->getElapsedTime();
//	float moveSpeed = (elapsedTime / _time) * _travelRange;
//
//	//이동
//	_image->setX(_image->getX() + cosf(_angle) * moveSpeed);
//	_image->setY(_image->getY() + (-sinf(_angle) * moveSpeed));
//
//	float time = TIMEMANAGER->getElapsedTime();
//	if (_time + _worldTimeCount <= TIMEMANAGER->getWorldTime())
//	{
//		_worldTimeCount = TIMEMANAGER->getWorldTime();
//		_image->setX(_endX);
//		_image->setY(_endY);
//		_isMoving = false;
//
//		if (_callbackFunction != NULL)
//		{
//			//콜백함수 실행
//			_callbackFunction();
//		}
//	}
//}
