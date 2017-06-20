//#pragma once
//
//#include "singletonBase.h"
//#include <bitset>
//
//using namespace std;
//
//#define KEYMAX 256
//
//class keyManager : public singletonBase<keyManager>
//{
//private:
//	bitset<KEYMAX> _keyUp;
//	bitset<KEYMAX> _keyDown;
//
//public:
//	keyManager();
//	~keyManager();
//
//	HRESULT init();
//	void release();
//
//	bool isOnceKeyDown(int key);
//	bool isOnceKeyUp(int key);
//	bool isStayKeyDown(int key);
//	bool isToggleKey(int key);
//
//	bitset<KEYMAX> getKeyUp() { return _keyUp; }
//	bitset<KEYMAX> getKeyDown() { return _keyDown; }
//
//	void setKeyDown(int key, bool state) { _keyDown.set(key, state); }
//	void setKeyUp(int key, bool state) { _keyUp.set(key, state); }
//};
//
