//#pragma once
//
//#include "singletonBase.h"
//#include <vector>
//
//class action;
//
//class actionManager : public singletonBase<actionManager>
//{
//private:
//	typedef std::vector<action*> arrAction;
//	typedef std::vector<action*>::iterator iterAction;
//
//private:
//	arrAction _vAction;
//	iterAction _viAction;
//
//public:
//	actionManager();
//	~actionManager();
//
//	HRESULT init();
//	void release();
//	void update();
//	void render();
//
//	void moveTo(image* image, float endX, float endY, float time);
//	void moveTo(image* image, float endX, float endY, float time, void* cbFunction);
//};

