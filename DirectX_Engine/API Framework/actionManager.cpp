#include "stdafx.h"
//#include "actionManager.h"
//#include "action.h"
//
//actionManager::actionManager()
//{
//}
//
//
//actionManager::~actionManager()
//{
//}
//
//HRESULT actionManager::init()
//{
//	return S_OK;
//}
//
//void actionManager::release()
//{
//	for (_viAction = _vAction.begin(); _viAction != _vAction.end(); )
//	{
//		if (_vAction.size() != 0)
//		{
//			SAFE_DELETE(*_viAction);
//			_viAction = _vAction.erase(_viAction);
//		}
//		else ++_viAction;
//	}
//
//	_vAction.clear();
//}
//
//void actionManager::update()
//{
//	for (int i = 0; i < _vAction.size(); i++)
//	{
//		_vAction[i]->update();
//		if (!_vAction[i]->getIsMoving())
//		{
//			SAFE_DELETE(_vAction[i]);
//			_vAction.erase(_vAction.begin() + i);
//			break;
//		}
//	}
//}
//
//void actionManager::render()
//{
//}
//
//void actionManager::moveTo(image * image, float endX, float endY, float time)
//{
//	action* moveAction;
//	moveAction = new action;
//	moveAction->init();
//	moveAction->moveTo(image, endX, endY, time);
//	_vAction.push_back(moveAction);
//}
//
////void* [보이드 포인터] : 어떠한 형태의 주소값이든 다 받아낼 수 있다.
//// 예) char, float, double, int, short, long, class, struct
//void actionManager::moveTo(image * image, float endX, float endY, float time, void * cbFunction)
//{
//	action* moveAction;
//	moveAction = new action;
//	moveAction->init();
//	moveAction->moveTo(image, endX, endY, time, (CALLBACK_FUNCTION)cbFunction);
//	_vAction.push_back(moveAction);
//}
