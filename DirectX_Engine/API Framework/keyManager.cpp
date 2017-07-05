#include "stdafx.h"
//#include "keyManager.h"
//
//
//keyManager::keyManager()
//{
//}
//
//
//keyManager::~keyManager()
//{
//}
//
//
//HRESULT keyManager::init()
//{
//	for (int i = 0; i < KEYMAX; i++)
//	{
//		this->_keyDown.set(i, false);
//		this->_keyUp.set(i, false);
//	}
//
//	return S_OK;
//	//return E_FAIL;
//}
//
//void keyManager::release()
//{
//
//}
//
//bool keyManager::isOnceKeyDown(int key)
//{
//	if (GetAsyncKeyState(key) & 0x8000 && GetFocus())
//	{
//		if (!this->_keyDown[key])
//		{
//			this->_keyDown.set(key, true);
//			return true;
//		}
//	}
//	else this->_keyDown.set(key, false);
//
//	return false;
//}
//
//bool keyManager::isOnceKeyUp(int key)
//{
//	if (GetAsyncKeyState(key) & 0x8000 && GetFocus() ) this->_keyUp.set(key, true);
//	else
//	{
//		if (this->_keyUp[key])
//		{
//			this->_keyUp.set(key, false);
//			return true;
//		}
//	}
//
//	return false;
//}
//
//bool keyManager::isStayKeyDown(int key)
//{
//	if (GetAsyncKeyState(key) & 0x8000 && GetFocus() ) return true;
//	else return false;
//}
//
//bool keyManager::isToggleKey(int key)
//{
//	if (GetKeyState(key) & 0x0001 && GetFocus() ) return true;
//	else return false;
//}
