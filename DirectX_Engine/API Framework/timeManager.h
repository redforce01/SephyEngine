////http://egloos.zum.com/spaurh/v/4270868
//
//#pragma once
//
//#include "singletonBase.h"
//#include "timer.h"
//
//class timeManager : public singletonBase<timeManager>
//{
//private:
//	timer* _timer;
//
//public:
//	timeManager();
//	~timeManager();
//
//	HRESULT init();
//	void release();
//	void update(float lock = 0.0f);
//	void render(HDC hdc);
//
//	//�� ������
//	inline float getElapsedTime() const { return _timer->getElapsedTime(); }
//	inline float getWorldTime() const { return _timer->getWorldTime(); }
//};
//
