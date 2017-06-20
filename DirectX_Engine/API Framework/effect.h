//#pragma once
//
//#include "gameNode.h"
//
//class animation;
//
//class effect : public gameNode
//{
//private:
//	animation* _effectAnimation; //����Ʈ �ִϸ��̼�
//
//	int _x;				   //����Ʈ ��Ʈ�� X
//	int _y;				   //����Ʈ ��Ʈ�� Y
//						   
//	image* _effectImage;   //����Ʈ �̹���
//	BOOL _isRunning;	   //����Ʈ ���ư��� �ִ��� ����
//	float _elapsedTime;	   //����Ʈ ��� �ð�
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
