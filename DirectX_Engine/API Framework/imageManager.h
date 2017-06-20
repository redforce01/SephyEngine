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
//	//typedef mapImageList::iterator mapImageIter; //���� �Ȱ���.
//
//private:
//	mapImageList _mImageList;	//������ ������ �̹��� ����Ʈ
//
//public:
//	imageManager();
//	~imageManager();
//
//	HRESULT init();
//	void release();
//
//	//Ű ������ �����ؼ� �ʱ�ȭ
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
//	//������ �̹��� �ʱ�ȭ
//	image* addFrameImage(string strKey, const char* fileName, float x, float y,
//		int width, int height, int frameX, int frameY, BOOL trans, COLORREF transColor);
//
//	image* addFrameImage(string strKey, const char* fileName, int width, int height,
//		int frameX, int frameY, BOOL trans, COLORREF transColor);
//
//	//�̹��� ã�� �Լ�
//	image* findImage(string strKey);
//
//	//�̹��� �����
//	BOOL deleteImage(string strKey);
//
//	//��ü �̹��� �����
//	BOOL deleteAll(void);
//
//	//���� �Լ�
//	void render(string strKey, HDC hdc);
//	void render(string strKey, HDC hdc, int destX, int destY);
//	void render(string strKey, HDC hdc, int destX, int destY,
//		int sourX, int sourY, int sourWidth, int sourHeight);
//
//	//���� ����
//	void alphaRender(string strKey, HDC hdc, int destX, int destY, BYTE alpha);
//	void alphaRender(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha);
//
//	//������ ����
//	void frameRender(string strKey, HDC hdc, int destX, int destY);
//	void frameRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);
//	
//	//���� ����
//	void loopRender(string strKey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY);
//
//};
//
