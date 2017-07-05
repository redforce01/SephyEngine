//#pragma once
//
//#include "gameNode.h"
//
//typedef void(*CALLBACK_FUNCTION)(void);
//typedef void(*CALLBACK_FUNCTION_PARAMETER)(void*);
//
//enum BUTTONDIRECTION
//{
//	BUTTONDIRECTION_NULL,
//	BUTTONDIRECTION_UP,
//	BUTTONDIRECTION_DOWN,
//	BUTTONDIRECTION_OVER
//};
//
//class button : public gameNode
//{
//private:
//	BUTTONDIRECTION _direction;
//	const char* _imageName;
//	image* _image;
//	string _string;
//	bool _border;
//
//	image* _imageN;
//	image* _imageO;
//	image* _imageP;
//
//	RECT _rc;
//	int _x, _y;
//	void* _obj;
//
//	POINT _btnDownFramePoint;
//	POINT _btnUpFramePoint;
//	POINT _btnOverFramePoint;
//	bool _bFrameButton;
//	bool _bStringButton;
//
//	int _timeFrame;
//	int _nFrame;
//
//	CALLBACK_FUNCTION _callbackFunction; //콜백함수 원형 선언
//	CALLBACK_FUNCTION_PARAMETER _callbackFunctionParameter;
//public:
//	button();
//	~button();
//
//	HRESULT init(const char* imageName, int x, int y, POINT btnDownFramePoint, POINT btnUpFramePoint, CALLBACK_FUNCTION cbFunction);
//	HRESULT init(const char* imageName, int x, int y, POINT btnDownFramePoint, POINT btnUpFramePoint, POINT btnOverFramePoint, CALLBACK_FUNCTION cbFunction);
//	HRESULT init(const char* imageName, int x, int y, POINT btnDownFramePoint, POINT btnUpFramePoint, CALLBACK_FUNCTION_PARAMETER cbFunction, void* obj);
//	HRESULT init(const char* imageName, int x, int y, POINT btnDownFramePoint, POINT btnUpFramePoint, POINT btnOverFramePoint, CALLBACK_FUNCTION_PARAMETER cbFunction, void* obj);
//
//	HRESULT init(const char* imageNameN, const char* imageNameO, const char* imageNameP, int x, int y, CALLBACK_FUNCTION_PARAMETER cbFunction, void* obj);
//
//	HRESULT init(const char* string, int x, int y, CALLBACK_FUNCTION_PARAMETER cbFunction, void* obj);
//	HRESULT init(const char* string, int x, int y, CALLBACK_FUNCTION_PARAMETER cbFunction, void* obj, bool border);
//
//
//	void release();
//	void update();
//	void render();
//};
//
