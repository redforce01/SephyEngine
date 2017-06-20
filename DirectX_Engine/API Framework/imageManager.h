//#pragma once
//
//#include "singletonBase.h"
//#include "image.h"
//#include <map>
//
//class imageManager : public singletonBase<imageManager>
//{
//public:
//	typedef map<string, image*> mapImageList;
//	typedef map<string, image*>::iterator mapImageIter;
//	//typedef mapImageList::iterator mapImageIter; //위와 똑같다.
//
//private:
//	mapImageList _mImageList;	//맵으로 구현된 이미지 리스트
//
//public:
//	imageManager();
//	~imageManager();
//
//	HRESULT init();
//	void release();
//
//	//키 값으로 설정해서 초기화
//	image* addImage(string strKey, int width, int height);
//
//	image* addImage(string strKey, const DWORD resID,
//		int width, int height, bool trans, COLORREF transColor);
//
//	image* addImage(string strKey, const char* fileName,
//		int width, int height, bool trans, COLORREF transColor);
//
//	image* addImage(string strKey, const char* fileName,
//		float x, float y, int width, int height, bool trans, COLORREF transColor);
//
//
//	//프레임 이미지 초기화
//	image* addFrameImage(string strKey, const char* fileName, float x, float y,
//		int width, int height, int frameX, int frameY, BOOL trans, COLORREF transColor);
//
//	image* addFrameImage(string strKey, const char* fileName, int width, int height,
//		int frameX, int frameY, BOOL trans, COLORREF transColor);
//
//	//이미지 찾는 함수
//	image* findImage(string strKey);
//
//	//이미지 지운다
//	BOOL deleteImage(string strKey);
//
//	//전체 이미지 지운다
//	BOOL deleteAll(void);
//
//	//렌더 함수
//	void render(string strKey, HDC hdc);
//	void render(string strKey, HDC hdc, int destX, int destY);
//	void render(string strKey, HDC hdc, int destX, int destY,
//		int sourX, int sourY, int sourWidth, int sourHeight);
//
//	//알파 렌더
//	void alphaRender(string strKey, HDC hdc, int destX, int destY, BYTE alpha);
//	void alphaRender(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha);
//
//	//프레임 렌더
//	void frameRender(string strKey, HDC hdc, int destX, int destY);
//	void frameRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);
//	
//	//루프 렌더
//	void loopRender(string strKey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY);
//
//};
//
