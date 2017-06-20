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
//		//�̹��� �ּ� �� �������
//		_image = image;
//
//		//�̵� ������
//		_startX = image->getX();
//		_startY = image->getY();
//
//		//��������
//		_endX = endX;
//		_endY = endY;
//
//		//�̵��Ÿ� ������
//		_travelRange = MY_UTIL::getDistance(_startX, _startY, _endX, _endY);
//
//		//���� ������
//		_angle = MY_UTIL::getAngle(_startX, _startY, _endX, _endY);
//
//		//���� Ÿ�� ��������
//		_worldTimeCount = TIMEMANAGER->getWorldTime();
//
//		//�̵� �ð�
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
//		//�̹��� �ּ� �� �������
//		_image = image;
//
//		//�̵� ������
//		_startX = image->getX();
//		_startY = image->getY();
//
//		//��������
//		_endX = endX;
//		_endY = endY;
//
//		//�̵��Ÿ� ������
//		_travelRange = MY_UTIL::getDistance(_startX, _startY, _endX, _endY);
//
//		//���� ������
//		_angle = MY_UTIL::getAngle(_startX, _startY, _endX, _endY);
//
//		//���� Ÿ�� ��������
//		_worldTimeCount = TIMEMANAGER->getWorldTime();
//
//		//�̵� �ð�
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
//	//�̵�
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
//			//�ݹ��Լ� ����
//			_callbackFunction();
//		}
//	}
//}
