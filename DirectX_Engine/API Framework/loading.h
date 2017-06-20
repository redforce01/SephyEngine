//#pragma once
//
//#include "gameNode.h"
//#include "progressBar.h"
//#include <vector>
//
////로딩 아이템 종류
//enum LOADING_KIND
//{
//	LOADING_KIND_IMAGE_00,
//	LOADING_KIND_IMAGE_01,
//	LOADING_KIND_IMAGE_02,
//	LOADING_KIND_FRAMEIMAGE_00,
//	LOADING_KIND_FRAMEIMAGE_01,
//	LOADING_KIND_SOUND_00,
//	LOADING_KIND_END
//};
//
//struct tagSoundResource
//{
//	string keyName;
//	const char* fileName;
//	bool loop;
//	bool background;
//};
//
////이미지 리소스 구조체
//struct tagImageResource
//{
//	string keyName;
//	const char* fileName;
//	int x, y;
//	int width, height;
//	int frameX, frameY;
//	bool trans;
//	COLORREF transColor;
//};
//
//class loadItem
//{
//private:
//	LOADING_KIND _kind;
//	tagImageResource _imageResource;
//	tagSoundResource _soundResource;
//
//public:
//	loadItem();
//	~loadItem();
//
//	//이미지 로드 아이템
//	HRESULT initForImage( string keyName, int width, int height );
//	HRESULT initForImage( string keyName, const char* fileName, int x, int y, int width, int height, bool trans, COLORREF transColor );
//	HRESULT initForImage( string keyName, const char* fileName, int width, int height, bool trnas, COLORREF transColor );
//	HRESULT initForFrameImage( string keyName, const char* fileName, int x, int y, int width, int height, int frameX, int frameY, bool trans, COLORREF transColor );
//	HRESULT initForFrameImage( string keyName, const char* fileName, int width, int height, int frameX, int frameY, bool trans, COLORREF transColor );
//
//	HRESULT initForSound(string keyName, const char* fileName, bool loop, bool background);
//
//	LOADING_KIND getLoadingKind() { return _kind; }
//	tagImageResource getImageResource() { return _imageResource; }
//	tagSoundResource getSoundResource() { return _soundResource; }
//};
//
//class loading : public gameNode
//{
//private:
//	typedef vector<loadItem*> arrLoadItem;
//	typedef vector<loadItem*>::iterator arrLoadItemIter;
//
//private:
//	arrLoadItem _vLoadItem;
//
//	image* _background;
//	progressBar* _loadingBar;
//
//	int _current;
//
//public:
//	loading();
//	~loading();
//
//	HRESULT init();
//	void release();
//	void update();
//	void render();
//
//	void loadImage( string keyName, int width, int height );
//	void loadImage( string keyName, const char* fileName, int x, int y, int width, int height, bool trans, COLORREF transColor );
//	void loadImage( string keyName, const char* fileName, int width, int height, bool trans, COLORREF transColor );
//	void loadFrameImage( string keyName, const char* fileName, int x, int y, int width, int height, int frameX, int frameY, bool trans, COLORREF transColor );
//	void loadFrameImage( string keyName, const char* fileName, int width, int height, int frameX, int frameY, bool trans, COLORREF transColor );
//
//	void loadSound(string keyName, const char* fileName, bool loop, bool background);
//
//	//로딩이 되는 중이면 true, 다되면 false
//	BOOL loadNext();
//
//	vector<loadItem*> getLoadItem() { return _vLoadItem; }
//};
//
