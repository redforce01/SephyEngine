//#pragma once
//
//#include "gameNode.h"
//
//class animation;
//
//class effect : public gameNode
//{
//private:
//	animation* _effectAnimation; //이펙트 애니메이션
//
//	int _x;				   //이펙트 터트릴 X
//	int _y;				   //이펙트 터트릴 Y
//						   
//	image* _effectImage;   //이펙트 이미지
//	BOOL _isRunning;	   //이펙트 돌아가고 있는지 여부
//	float _elapsedTime;	   //이펙트 경과 시간
//
//public:
//	effect();
//	virtual ~effect();
//
//	virtual HRESULT init(image* effectImage, int frameW, int frameH, int fps, float elapsedTime);
//	virtual void release();
//	virtual void update();
//	virtual void render();
//
//	void startEffect(int x, int y);
//	virtual void killEffect();
//
//	BOOL getIsRunning() { return _isRunning; }
//
//};
//
