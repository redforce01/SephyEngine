#include "stdafx.h"
//#include "button.h"
//
//
//button::button()
//{
//}
//
//
//button::~button()
//{
//}
//
//HRESULT button::init(const char* imageName, int x, int y,
//	POINT btnDownFramePoint, POINT btnUpFramePoint,
//	CALLBACK_FUNCTION cbFunction)
//{
//	_callbackFunction = cbFunction;
//	_callbackFunctionParameter = NULL;
//	_obj = NULL;
//
//	_direction = BUTTONDIRECTION_NULL;
//
//	_x = x;
//	_y = y;
//
//	_btnDownFramePoint = btnDownFramePoint;
//	_btnUpFramePoint = btnUpFramePoint;
//
//	_imageName = imageName;
//	_image = IMAGEMANAGER->findImage(imageName);
//
//	_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(),
//		_image->getFrameHeight());
//
//	_bFrameButton = false;
//	_bStringButton = false;
//	_border = false;
//	_timeFrame = 0;
//	_nFrame = 0;
//
//	return S_OK;
//}
//
//HRESULT button::init(const char* imageName, int x, int y,
//	POINT btnDownFramePoint, POINT btnUpFramePoint, POINT btnOverFramePoint,
//	CALLBACK_FUNCTION cbFunction)
//{
//	_callbackFunction = cbFunction;
//	_callbackFunctionParameter = NULL;
//	_obj = NULL;
//
//	_direction = BUTTONDIRECTION_NULL;
//
//	_x = x;
//	_y = y;
//
//	_btnDownFramePoint = btnDownFramePoint;
//	_btnUpFramePoint = btnUpFramePoint;
//	_btnOverFramePoint = btnOverFramePoint;
//
//	_imageName = imageName;
//	_image = IMAGEMANAGER->findImage(imageName);
//
//	_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(),
//		_image->getFrameHeight());
//
//	_bFrameButton = false;
//	_bStringButton = false;
//	_border = false;
//	_timeFrame = 0;
//	_nFrame = 0;
//
//	return S_OK;
//}
//
//HRESULT button::init(const char* imageName, int x, int y,
//	POINT btnDownFramePoint, POINT btnUpFramePoint,
//	CALLBACK_FUNCTION_PARAMETER cbFunction, void* obj)
//{
//	_callbackFunction = NULL;
//	_callbackFunctionParameter = cbFunction;
//	_obj = obj;
//
//	_direction = BUTTONDIRECTION_NULL;
//
//	_x = x;
//	_y = y;
//
//	_btnDownFramePoint = btnDownFramePoint;
//	_btnUpFramePoint = btnUpFramePoint;
//
//	_imageName = imageName;
//	_image = IMAGEMANAGER->findImage(imageName);
//
//	_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(),
//		_image->getFrameHeight());
//
//	_bFrameButton = false;
//	_bStringButton = false;
//	_border = false;
//	_timeFrame = 0;
//	_nFrame = 0;
//
//	return S_OK;
//}
//
//HRESULT button::init(const char* imageName, int x, int y,
//	POINT btnDownFramePoint, POINT btnUpFramePoint, POINT btnOverFramePoint,
//	CALLBACK_FUNCTION_PARAMETER cbFunction, void* obj)
//{
//	_callbackFunction = NULL;
//	_callbackFunctionParameter = cbFunction;
//	_obj = obj;
//
//	_direction = BUTTONDIRECTION_NULL;
//
//	_x = x;
//	_y = y;
//
//	_btnDownFramePoint = btnDownFramePoint;
//	_btnUpFramePoint = btnUpFramePoint;
//	_btnOverFramePoint = btnOverFramePoint;
//
//	_imageName = imageName;
//	_image = IMAGEMANAGER->findImage(imageName);
//
//	_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(),
//		_image->getFrameHeight());
//
//	_bFrameButton = false;
//	_bStringButton = false;
//	_border = false;
//	_timeFrame = 0;
//	_nFrame = 0;
//
//	return S_OK;
//}
//
//HRESULT button::init(const char* imageNameN, const char* imageNameO, const char* imageNameP, 
//	int x, int y, CALLBACK_FUNCTION_PARAMETER cbFunction, void * obj)
//{
//	_callbackFunction = NULL;
//	_callbackFunctionParameter = cbFunction;
//	_obj = obj;
//
//	_direction = BUTTONDIRECTION_NULL;
//
//	_x = x;
//	_y = y;
//
//	_imageN = IMAGEMANAGER->findImage(imageNameN);
//	_imageO = IMAGEMANAGER->findImage(imageNameO);
//	_imageP = IMAGEMANAGER->findImage(imageNameP);
//
//	_rc = RectMakeCenter(_x, _y, _imageN->getFrameWidth(),
//		_imageN->getFrameHeight());
//
//	_bFrameButton = true;
//	_bStringButton = false;
//	_border = false;
//	_timeFrame = 0;
//	_nFrame = 0;
//
//	return S_OK;
//}
//
//HRESULT button::init(const char * string, int x, int y, CALLBACK_FUNCTION_PARAMETER cbFunction, void * obj)
//{
//	_callbackFunction = NULL;
//	_callbackFunctionParameter = cbFunction;
//	_obj = obj;
//
//	_direction = BUTTONDIRECTION_NULL;
//
//	_x = x;
//	_y = y;
//
//	_string = string;
//	_rc = RectMake(_x, _y, _string.size() * 10, 20);
//
//	_bFrameButton = false;
//	_bStringButton = true;
//	_border = false;
//	_timeFrame = 0;
//	_nFrame = 0;
//
//	return S_OK;
//}
//
//HRESULT button::init(const char * btnString, int x, int y, CALLBACK_FUNCTION_PARAMETER cbFunction, void * obj, bool border)
//{
//	_callbackFunction = NULL;
//	_callbackFunctionParameter = cbFunction;
//	_obj = obj;
//
//	_direction = BUTTONDIRECTION_NULL;
//
//	_x = x;
//	_y = y;
//	
//	_string = btnString;
//	_rc = RectMake(_x, _y, _string.size() * 10, 20);
//
//	_bFrameButton = false;
//	_bStringButton = true;
//	_border = border;
//	_timeFrame = 0;
//	_nFrame = 0;
//
//	return S_OK;
//}
//
//void button::release()
//{
//
//}
//
//void button::update()
//{	
//	//Button Update
//	if (PtInRect(&_rc, _ptMouse))
//	{
//		if (_leftButtonDown)
//		{
//			_direction = BUTTONDIRECTION_DOWN;
//		}
//		else if (!_leftButtonDown && _direction == BUTTONDIRECTION_DOWN)
//		{
//			_direction = BUTTONDIRECTION_UP;
//			if (_obj == NULL) _callbackFunction();
//			else _callbackFunctionParameter(_obj);
//		}
//		else _direction = BUTTONDIRECTION_OVER;
//	}
//	else _direction = BUTTONDIRECTION_NULL;
//
//	//Frame Button Update 
//	if (_bFrameButton)
//	{
//		_timeFrame++;
//		if (_timeFrame % 5 == 0)
//		{
//			switch (_direction)
//			{
//			case BUTTONDIRECTION_UP: case BUTTONDIRECTION_NULL:
//				if (_nFrame > _imageN->getMaxFrameX())
//				{
//					_nFrame = 0;
//				}
//				_imageN->setFrameX(_nFrame);
//				_nFrame++;
//				break;
//
//			case BUTTONDIRECTION_DOWN:
//				if (_nFrame > _imageP->getMaxFrameX())
//				{
//					_nFrame = 0;
//				}
//				_imageP->setFrameX(_nFrame);
//				_nFrame++;
//				break;
//
//			case BUTTONDIRECTION_OVER:
//				if (_nFrame > _imageO->getMaxFrameX())
//				{
//					_nFrame = 0;
//				}
//				_imageO->setFrameX(_nFrame);
//				_nFrame++;
//				break;
//			default:
//				break;
//			}
//		}
//	}
//
//	
//}
//
//
//void button::render()
//{
//	if (_bStringButton)
//	{
//		switch (_direction)
//		{
//		case BUTTONDIRECTION_NULL: case BUTTONDIRECTION_UP:
//			DrawText(getMemDC(), _string.c_str(), -1, &_rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
//			break;
//		case BUTTONDIRECTION_DOWN:
//			DrawText(getMemDC(), _string.c_str(), -1, &_rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
//			break;
//		case BUTTONDIRECTION_OVER:
//			DrawText(getMemDC(), _string.c_str(), -1, &_rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
//			break;
//		default:
//			break;
//		}
//		if (_border)
//		{
//			HPEN myPen, oldPen;
//			HBRUSH myBrush, oldBrush;
//			myPen = CreatePen(PS_SOLID, 1, RGB(0, 200, 0));
//			myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
//			oldBrush = (HBRUSH)SelectObject(getMemDC(), myBrush);
//			oldPen = (HPEN)SelectObject(getMemDC(), myPen);
//			Rectangle(getMemDC(), _rc.left, _rc.top, _rc.right, _rc.bottom);
//			SelectObject(getMemDC(), oldPen);
//			SelectObject(getMemDC(), oldBrush);
//			DeleteObject(myPen);
//			DeleteObject(myBrush);
//		}
//		else
//		{
//			HPEN myPen, oldPen;
//			HBRUSH myBrush, oldBrush;
//			HFONT myFont, oldFont;
//			myPen = CreatePen(PS_SOLID, 1, RGB(0, 200, 0));
//			myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
//			myFont = CreateFont(300, 100, 0, 0, 1000, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("consolas"));
//			oldBrush = (HBRUSH)SelectObject(getMemDC(), myBrush);
//			oldPen = (HPEN)SelectObject(getMemDC(), myPen);
//			oldFont = (HFONT)SelectObject(getMemDC(), myFont);
//			SelectObject(getMemDC(), oldPen);
//			SelectObject(getMemDC(), oldBrush);
//			SelectObject(getMemDC(), oldFont);
//			DeleteObject(myPen);
//			DeleteObject(myBrush);
//			DeleteObject(myFont);
//		}
//	}
//	else if (!_bFrameButton)
//	{
//		switch (_direction)
//		{
//		case BUTTONDIRECTION_NULL: case BUTTONDIRECTION_UP:
//			_image->frameRender(getMemDC(), _rc.left, _rc.top,
//				_btnUpFramePoint.x, _btnUpFramePoint.y);
//			break;
//
//		case BUTTONDIRECTION_DOWN:
//			_image->frameRender(getMemDC(), _rc.left, _rc.top,
//				_btnDownFramePoint.x, _btnDownFramePoint.y);
//			break;
//		case BUTTONDIRECTION_OVER:
//			_image->frameRender(getMemDC(), _rc.left, _rc.top,
//				_btnOverFramePoint.x, _btnOverFramePoint.y);
//			break;
//		}
//	}	
//	else
//	{
//		switch (_direction)
//		{
//		case BUTTONDIRECTION_NULL: case BUTTONDIRECTION_UP:
//			_imageN->frameRender(getMemDC(), _rc.left, _rc.top,
//				_imageN->getFrameX(), _imageN->getFrameY());
//			break;
//		case BUTTONDIRECTION_DOWN:
//			_imageP->frameRender(getMemDC(), _rc.left, _rc.top,
//				_imageP->getFrameX(), _imageP->getFrameY());
//			break;
//		case BUTTONDIRECTION_OVER:
//			_imageO->frameRender(getMemDC(), _rc.left, _rc.top,
//				_imageO->getFrameX(), _imageO->getMaxFrameY());
//			break;
//		default:
//			break;
//		}
//
//	}
//}