#include "stdafx.h"
//#include "image.h"
//
//#pragma comment( lib, "msimg32.lib" )
//
//image::image( ) :
//_imageInfo( NULL ),
//_blendImage(NULL),
//_fileName( NULL ),
//_trans( false ),
//_transColor( RGB( 0, 0, 0 ) )
//{
//}
//
//
//image::~image()
//{
//}
//
////빈 비트맵  이미지 만든다
//HRESULT image::init( int width, int height )
//{
//	//초기화가 다시 되는 것을 방지
//	if ( _imageInfo != NULL ) release( );
//
//	//DC 얻어온다
//	HDC hdc = GetDC( _hWnd );
//
//	//CreateCompatibleDC
//	//비트맵을 출력하기 위해서 메모리 DC를 만들어 주는 것
//
//	//CreateCompatibleBitMap
//	//원본 DC와 호환되는 비트맵 생성
//
//	//이미지 정보 생성
//	_imageInfo = new IMAGE_INFO;
//	_imageInfo->loadType = LOAD_EMPTY;
//	_imageInfo->resID = 0;
//	_imageInfo->hMemDC = CreateCompatibleDC( hdc );
//	_imageInfo->hBit = (HBITMAP)CreateCompatibleBitmap( hdc, width, height );
//	_imageInfo->hOBit = (HBITMAP)SelectObject( _imageInfo->hMemDC, _imageInfo->hBit );
//	_imageInfo->x = 0;
//	_imageInfo->y = 0;
//	_imageInfo->width = width;
//	_imageInfo->height = height;
//	_imageInfo->currentFrameX = 0;
//	_imageInfo->currentFrameY = 0;
//	_imageInfo->maxFrameX = 0;
//	_imageInfo->maxFrameY = 0;
//	_imageInfo->frameWidth = width;
//	_imageInfo->frameHeight = height;
//
//	_fileName = NULL;
//
//	//투명 컬러 셋팅
//	_trans = FALSE;
//	_transColor = RGB( 0, 0, 0 );
//
//	//알파 블렌드 욥션 설정하자
//	_blendFunc.BlendFlags = 0;
//	_blendFunc.AlphaFormat = 0;
//	_blendFunc.BlendOp = AC_SRC_OVER;
//
//	//알파 블렌드 사용을 위한 이미지 설정
//	/*_blendImage = new IMAGE_INFO;
//	_blendImage->loadType = LOAD_EMPTY;
//	_blendImage->resID = 0;
//	_blendImage->hMemDC = CreateCompatibleDC(hdc);
//	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
//	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
//	_blendImage->width = WINSIZEX;
//	_blendImage->height = WINSIZEY;*/
//	
//	//얻은 DC 해제
//	ReleaseDC( _hWnd, hdc );
//
//	//리소스 얻어오기 실패시 처리
//	if ( _imageInfo->hBit == 0 )
//	{
//		release( );
//
//		return E_FAIL;
//	}
//
//	return S_OK;
//}
//
////리소스로부터 읽어온다
//HRESULT image::init( const DWORD resID, int width,
//	int height, BOOL trans, COLORREF transColor )
//{
//	//재초기화에 대비
//	if ( _imageInfo != NULL ) release( );
//
//	//DC 얻는다
//	HDC hdc = GetDC( _hWnd );
//
//	//이미지 정보 생성
//	_imageInfo = new IMAGE_INFO;
//	_imageInfo->loadType = LOAD_RESOURCE;
//	_imageInfo->resID = resID;
//	_imageInfo->hMemDC = CreateCompatibleDC( hdc );
//	_imageInfo->hBit = (HBITMAP)LoadBitmap( _hInstance, MAKEINTRESOURCE( _imageInfo->resID ) );
//	_imageInfo->hOBit = (HBITMAP)SelectObject( _imageInfo->hMemDC, _imageInfo->hBit );
//	_imageInfo->x = 0;
//	_imageInfo->y = 0;
//	_imageInfo->width = width;
//	_imageInfo->height = height;
//	_imageInfo->currentFrameX = 0;
//	_imageInfo->currentFrameY = 0;
//	_imageInfo->maxFrameX = 0;
//	_imageInfo->maxFrameY = 0;
//	_imageInfo->frameWidth = width;
//	_imageInfo->frameHeight = height;
//
//	_fileName = NULL;
//
//	//투명 컬러 셋팅
//	_trans = FALSE;
//	_transColor = RGB( 0, 0, 0 );
//
//	//알파 블렌드 욥션 설정하자
//	_blendFunc.BlendFlags = 0;
//	_blendFunc.AlphaFormat = 0;
//	_blendFunc.BlendOp = AC_SRC_OVER;
//
//	//알파 블렌드 사용을 위한 이미지 설정
//	/*_blendImage = new IMAGE_INFO;
//	_blendImage->loadType = LOAD_EMPTY;
//	_blendImage->resID = 0;
//	_blendImage->hMemDC = CreateCompatibleDC(hdc);
//	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
//	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
//	_blendImage->width = WINSIZEX;
//	_blendImage->height = WINSIZEY;*/
//
//	//얻은 DC 해제
//	ReleaseDC( _hWnd, hdc );
//
//	//리소스 얻기에 실패하면
//	if ( _imageInfo->hBit == 0 )
//	{
//		release( );
//		return E_FAIL;
//	}
//
//	return S_OK;
//}
//
//
////이미지 설정 (파일로부터 읽어온다)
//HRESULT image::init( const char* fileName, int width, int height,
//	BOOL trans, COLORREF transColor )
//{
//	//파일 경로가 잘못 되었으면...
//	if ( fileName == NULL ) return E_FAIL;
//
//	//재초기화에 대비
//	if ( _imageInfo != NULL ) release( );
//
//	//DC 얻는다
//	HDC hdc = GetDC( _hWnd );
//
//	//이미지 정보 생성
//	_imageInfo = new IMAGE_INFO;
//	_imageInfo->loadType = LOAD_FILE;
//	_imageInfo->resID = 0;
//	_imageInfo->hMemDC = CreateCompatibleDC( hdc );
//	_imageInfo->hBit = (HBITMAP)LoadImage( _hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE );
//	_imageInfo->hOBit = (HBITMAP)SelectObject( _imageInfo->hMemDC, _imageInfo->hBit );
//	_imageInfo->x = 0;
//	_imageInfo->y = 0;
//	_imageInfo->width = width;
//	_imageInfo->height = height;
//	_imageInfo->currentFrameX = 0;
//	_imageInfo->currentFrameY = 0;
//	_imageInfo->maxFrameX = 0;
//	_imageInfo->maxFrameY = 0;
//	_imageInfo->frameWidth = width;
//	_imageInfo->frameHeight = height;
//
//	//파일 경로 이름 복사
//	int len = strlen( fileName );
//	_fileName = new CHAR[len + 1];
//	strcpy_s( _fileName, len + 1, fileName );
//
//	//투명 컬러 셋팅
//	_trans = trans;
//	_transColor = transColor;
//
//	//알파 블렌드 욥션 설정하자
//	_blendFunc.BlendFlags = 0;
//	_blendFunc.AlphaFormat = 0;
//	_blendFunc.BlendOp = AC_SRC_OVER;
//
//	//알파 블렌드 사용을 위한 이미지 설정
//	/*_blendImage = new IMAGE_INFO;
//	_blendImage->loadType = LOAD_EMPTY;
//	_blendImage->resID = 0;
//	_blendImage->hMemDC = CreateCompatibleDC(hdc);
//	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
//	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
//	_blendImage->width = WINSIZEX;
//	_blendImage->height = WINSIZEY;*/
//
//	//얻은 DC해제
//	ReleaseDC( _hWnd, hdc );
//
//	//리소스 얻기에 실패하면
//	if ( _imageInfo->hBit == 0 )
//	{
//		release( );
//		return E_FAIL;
//	}
//
//	return S_OK;
//}
//
//HRESULT image::init(const char* fileName, float x, float y, int width, int height, BOOL trans, COLORREF transColor)
//{
//	//파일 경로가 잘못 되었으면...
//	if (fileName == NULL) return E_FAIL;
//
//	//재초기화에 대비
//	if (_imageInfo != NULL) release();
//
//	//DC 얻는다
//	HDC hdc = GetDC(_hWnd);
//
//	//이미지 정보 생성
//	_imageInfo = new IMAGE_INFO;
//	_imageInfo->loadType = LOAD_FILE;
//	_imageInfo->resID = 0;
//	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
//	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
//	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
//	_imageInfo->x = x - (width / 2);
//	_imageInfo->y = y - (height / 2);
//	_imageInfo->width = width;
//	_imageInfo->height = height;
//	_imageInfo->currentFrameX = 0;
//	_imageInfo->currentFrameY = 0;
//	_imageInfo->maxFrameX = 0;
//	_imageInfo->maxFrameY = 0;
//	_imageInfo->frameWidth = width;
//	_imageInfo->frameHeight = height;
//
//	//파일 경로 이름 복사
//	int len = strlen(fileName);
//	_fileName = new CHAR[len + 1];
//	strcpy_s(_fileName, len + 1, fileName);
//
//	//투명 컬러 셋팅
//	_trans = trans;
//	_transColor = transColor;
//
//	//알파 블렌드 욥션 설정하자
//	_blendFunc.BlendFlags = 0;
//	_blendFunc.AlphaFormat = 0;
//	_blendFunc.BlendOp = AC_SRC_OVER;
//
//	//알파 블렌드 사용을 위한 이미지 설정
//	/*_blendImage = new IMAGE_INFO;
//	_blendImage->loadType = LOAD_EMPTY;
//	_blendImage->resID = 0;
//	_blendImage->hMemDC = CreateCompatibleDC(hdc);
//	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
//	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
//	_blendImage->width = WINSIZEX;
//	_blendImage->height = WINSIZEY;*/
//
//	//얻은 DC해제
//	ReleaseDC(_hWnd, hdc);
//
//	//리소스 얻기에 실패하면
//	if (_imageInfo->hBit == 0)
//	{
//		release();
//		return E_FAIL;
//	}
//
//	return S_OK;
//}
//
////이미지 + 프레임 파일 초기화
//HRESULT image::init(const char* fileName, float x, float y, int width, int height,
//	int frameX, int frameY, BOOL trans, COLORREF transColor)
//{
//	//파일 경로가 잘못 되었으면...
//	if (fileName == NULL) return E_FAIL;
//
//	//재초기화에 대비
//	if (_imageInfo != NULL) release();
//
//	//DC 얻는다
//	HDC hdc = GetDC(_hWnd);
//
//	//이미지 정보 생성
//	_imageInfo = new IMAGE_INFO;
//	_imageInfo->loadType = LOAD_FILE;
//	_imageInfo->resID = 0;
//	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
//	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
//	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
//	_imageInfo->x = x - (width / 2);
//	_imageInfo->y = y - (height / 2);
//	_imageInfo->width = width;
//	_imageInfo->height = height;
//	_imageInfo->currentFrameX = 0;
//	_imageInfo->currentFrameY = 0;
//	_imageInfo->maxFrameX = frameX - 1;
//	_imageInfo->maxFrameY = frameY - 1;
//	_imageInfo->frameWidth = width / frameX;
//	_imageInfo->frameHeight = height / frameY;
//
//	//파일 경로 이름 복사
//	int len = strlen(fileName);
//	_fileName = new CHAR[len + 1];
//	strcpy_s(_fileName, len + 1, fileName);
//
//	//투명 컬러 셋팅
//	_trans = trans;
//	_transColor = transColor;
//
//	//알파 블렌드 욥션 설정하자
//	_blendFunc.BlendFlags = 0;
//	_blendFunc.AlphaFormat = 0;
//	_blendFunc.BlendOp = AC_SRC_OVER;
//
//	//알파 블렌드 사용을 위한 이미지 설정
//	/*_blendImage = new IMAGE_INFO;
//	_blendImage->loadType = LOAD_EMPTY;
//	_blendImage->resID = 0;
//	_blendImage->hMemDC = CreateCompatibleDC(hdc);
//	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
//	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
//	_blendImage->width = WINSIZEX;
//	_blendImage->height = WINSIZEY;*/
//
//	//얻은 DC해제
//	ReleaseDC(_hWnd, hdc);
//
//	//리소스 얻기에 실패하면
//	if (_imageInfo->hBit == 0)
//	{
//		release();
//		return E_FAIL;
//	}
//
//	return S_OK;
//}
//
//HRESULT image::init(const char* fileName, int width, int height, int frameX, int frameY,
//	BOOL trans, COLORREF transColor)
//{
//	//파일 경로가 잘못 되었으면...
//	if (fileName == NULL) return E_FAIL;
//
//	//재초기화에 대비
//	if (_imageInfo != NULL) release();
//
//	//DC 얻는다
//	HDC hdc = GetDC(_hWnd);
//
//	//이미지 정보 생성
//	_imageInfo = new IMAGE_INFO;
//	_imageInfo->loadType = LOAD_FILE;
//	_imageInfo->resID = 0;
//	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
//	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
//	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
//	_imageInfo->x = 0;
//	_imageInfo->y = 0;
//	_imageInfo->width = width;
//	_imageInfo->height = height;
//	_imageInfo->currentFrameX = 0;
//	_imageInfo->currentFrameY = 0;
//	_imageInfo->maxFrameX = frameX - 1;
//	_imageInfo->maxFrameY = frameY - 1;
//	_imageInfo->frameWidth = width / frameX;
//	_imageInfo->frameHeight = height / frameY;
//
//	//파일 경로 이름 복사
//	int len = strlen(fileName);
//	_fileName = new CHAR[len + 1];
//	strcpy_s(_fileName, len + 1, fileName);
//
//	//투명 컬러 셋팅
//	_trans = trans;
//	_transColor = transColor;
//
//	//알파 블렌드 욥션 설정하자
//	_blendFunc.BlendFlags = 0;
//	_blendFunc.AlphaFormat = 0;
//	_blendFunc.BlendOp = AC_SRC_OVER;
//
//	////알파 블렌드 사용을 위한 이미지 설정
//	//_blendImage = new IMAGE_INFO;
//	//_blendImage->loadType = LOAD_EMPTY;
//	//_blendImage->resID = 0;
//	//_blendImage->hMemDC = CreateCompatibleDC(hdc);
//	//_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
//	//_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
//	//_blendImage->width = WINSIZEX;
//	//_blendImage->height = WINSIZEY;
//
//	//얻은 DC해제
//	ReleaseDC(_hWnd, hdc);
//
//	//리소스 얻기에 실패하면
//	if (_imageInfo->hBit == 0)
//	{
//		release();
//		return E_FAIL;
//	}
//
//	return S_OK;
//}
//
//HRESULT image::init(const char * fileName, int width, int height, int frameX, int frameY, BOOL trans, COLORREF transColor, BOOL shadow)
//{
//	//파일 경로가 잘못 되었으면...
//	if (fileName == NULL) return E_FAIL;
//
//	//재초기화에 대비
//	if (_imageInfo != NULL) release();
//
//	//DC 얻는다
//	HDC hdc = GetDC(_hWnd);
//
//	//이미지 정보 생성
//	_imageInfo = new IMAGE_INFO;
//	_imageInfo->loadType = LOAD_FILE;
//	_imageInfo->resID = 0;
//	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
//	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE | LR_LOADMAP3DCOLORS | COLOR_3DLIGHT);
//	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
//	_imageInfo->x = 0;
//	_imageInfo->y = 0;
//	_imageInfo->width = width;
//	_imageInfo->height = height;
//	_imageInfo->currentFrameX = 0;
//	_imageInfo->currentFrameY = 0;
//	_imageInfo->maxFrameX = frameX - 1;
//	_imageInfo->maxFrameY = frameY - 1;
//	_imageInfo->frameWidth = width / frameX;
//	_imageInfo->frameHeight = height / frameY;
//
//	//파일 경로 이름 복사
//	int len = strlen(fileName);
//	_fileName = new CHAR[len + 1];
//	strcpy_s(_fileName, len + 1, fileName);
//
//	//투명 컬러 셋팅
//	_trans = trans;
//	_transColor = transColor;
//
//	//알파 블렌드 욥션 설정하자
//	_blendFunc.BlendFlags = 0;
//	_blendFunc.AlphaFormat = 0;
//	_blendFunc.BlendOp = AC_SRC_OVER;
//
//	////알파 블렌드 사용을 위한 이미지 설정
//	//_blendImage = new IMAGE_INFO;
//	//_blendImage->loadType = LOAD_EMPTY;
//	//_blendImage->resID = 0;
//	//_blendImage->hMemDC = CreateCompatibleDC(hdc);
//	//_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
//	//_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
//	//_blendImage->width = WINSIZEX;
//	//_blendImage->height = WINSIZEY;
//
//	//얻은 DC해제
//	ReleaseDC(_hWnd, hdc);
//
//	//리소스 얻기에 실패하면
//	if (_imageInfo->hBit == 0)
//	{
//		release();
//		return E_FAIL;
//	}
//
//	return S_OK;
//}
//
//void image::alphaInit()
//{
//	//DC 얻는다
//	HDC hdc = GetDC(_hWnd);
//
//	//알파 블렌드 사용을 위한 이미지 설정
//	_blendImage = new IMAGE_INFO;
//	_blendImage->loadType = LOAD_EMPTY;
//	_blendImage->resID = 0;
//	_blendImage->hMemDC = CreateCompatibleDC(hdc);
//	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, this->_imageInfo->width, this->_imageInfo->height);
//	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
//	_blendImage->width = WINSIZEX;
//	_blendImage->height = WINSIZEY;
//
//	ReleaseDC(_hWnd, hdc);
//}
//
//void image::shadowInit()
//{
//	//DC 얻는다
//	HDC hdc = GetDC(_hWnd);
//
//	//알파 블렌드 사용을 위한 이미지 설정
//	_shadowImage = new IMAGE_INFO;
//	_shadowImage->loadType = LOAD_EMPTY;
//	_shadowImage->resID = 0;
//	_shadowImage->hMemDC = CreateCompatibleDC(hdc);
//	_shadowImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, this->_imageInfo->width, this->_imageInfo->height);
//	_shadowImage->hOBit = (HBITMAP)SelectObject(_shadowImage->hMemDC, _shadowImage->hBit);
//	_shadowImage->width = WINSIZEX;
//	_shadowImage->height = WINSIZEY;
//
//	ReleaseDC(_hWnd, hdc);
//}
//
////삭제
//void image::release( void )
//{
//	if (_imageInfo)
//	{
//		//이미지 삭제
//		SelectObject(_imageInfo->hMemDC, _imageInfo->hOBit);
//		DeleteObject(_imageInfo->hBit);
//		DeleteDC(_imageInfo->hMemDC);
//
//		//포인터 삭제
//		SAFE_DELETE(_imageInfo);
//		SAFE_DELETE(_fileName);
//
//		//투명 컬러 초기화
//		_trans = false;
//		_transColor = RGB(0, 0, 0);
//	}
//
//	if (_blendImage)
//	{
//		SelectObject(_blendImage->hMemDC, _blendImage->hOBit);
//		DeleteObject(_blendImage->hBit);
//		DeleteDC(_blendImage->hMemDC);
//
//		SAFE_DELETE(_blendImage);
//	}
//}
//
////투명 키값(RGB값) 셋팅 == 특정 색상을 그리지 않는다
//void image::setTransColor( BOOL trans, COLORREF transColor )
//{
//	_trans = trans;
//	_transColor = transColor;
//}
//
////렌더
//void image::render(HDC hdc)
//{
//	if (_trans)
//	{
//		GdiTransparentBlt(
//			hdc,				//복사할 장소의 DC
//			_imageInfo->x,		//복사될 좌표 시작X
//			_imageInfo->y,		//복사될 좌표 시작Y
//			_imageInfo->width,	//복사될 크기 width
//			_imageInfo->height,	//복사될 크기 height
//			_imageInfo->hMemDC,	//복사할 DC
//			0, 0,				//복사 시작지점 x, y
//			_imageInfo->width,	//복사할 크기 width
//			_imageInfo->height,	//복사할 크기 height
//			_transColor);		//복사에서 제외할 색상
//	}
//	else
//	{
//		BitBlt(hdc, 0, 0, _imageInfo->width, _imageInfo->height,
//			_imageInfo->hMemDC, 0, 0, SRCCOPY);
//	}
//}
//
//void image::render( HDC hdc, int destX, int destY )
//{
//	if (_trans)
//	{
//		GdiTransparentBlt(
//			hdc,				//복사할 장소의 DC
//			destX,				//복사될 좌표 시작X
//			destY,				//복사될 좌표 시작Y
//			_imageInfo->width,	//복사될 크기 width
//			_imageInfo->height,	//복사될 크기 height
//			_imageInfo->hMemDC,	//복사할 DC
//			0, 0,				//복사 시작지점 x, y
//			_imageInfo->width,	//복사할 크기 width
//			_imageInfo->height,	//복사할 크기 height
//			_transColor);		//복사에서 제외할 색상
//	}
//	else
//	{
//		BitBlt(hdc, destX, destY, _imageInfo->width, _imageInfo->height,
//			_imageInfo->hMemDC, 0, 0, SRCCOPY);
//	}
//}
//
//void image::render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight)
//{
//	if (_trans)
//	{
//		GdiTransparentBlt(
//			hdc,				//복사할 장소의 DC
//			destX,				//복사될 좌표 시작X
//			destY,				//복사될 좌표 시작Y
//			sourWidth,			//복사될 크기 width
//			sourHeight,			//복사될 크기 height
//			_imageInfo->hMemDC,	//복사할 DC
//			sourX, sourY,		//복사 시작지점 x, y
//			sourWidth,			//복사할 크기 width
//			sourHeight,			//복사할 크기 height
//			_transColor);		//복사에서 제외할 색상
//	}
//	else
//	{
//		BitBlt(hdc, destX, destY, sourWidth, sourHeight,
//			_imageInfo->hMemDC, sourX, sourY, SRCCOPY);
//	}
//}
//
//void image::alphaRender(HDC hdc, int destX, int destY, BYTE alpha)
//{
//	if (!_blendImage) alphaInit();
//	_blendFunc.SourceConstantAlpha = alpha;
//
//	if (_trans)
//	{
//		//출력해야 될 DC에 그려져 있는 내용을 blend에 그려준다
//		BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
//			hdc, destX, destY, SRCCOPY);
//
//		//출력해야 될 이미지를 blend에 그려준다
//		GdiTransparentBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
//			_imageInfo->hMemDC, 0, 0,
//			_imageInfo->width, _imageInfo->height, _transColor);
//
//		//blendDC를 출력해야 될 DC에 그린다
//		AlphaBlend(hdc, destX, destY, _imageInfo->width, _imageInfo->height,
//			_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _blendFunc);
//	}
//	else
//	{
//		AlphaBlend(hdc, destX, destY, _imageInfo->width, _imageInfo->height,
//			_imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _blendFunc);
//	}
//}
//
//
//void image::alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha)
//{
//	if (!_blendImage) alphaInit();
//	_blendFunc.SourceConstantAlpha = alpha;
//
//	if (_trans)
//	{
//		//출력해야 될 DC에 그려져 있는 내용을 blend에 그려준다
//		BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
//			hdc, destX, destY, SRCCOPY);
//
//		//출력해야 될 이미지를 blend에 그려준다
//		GdiTransparentBlt(_blendImage->hMemDC, 0, 0, sourWidth, sourHeight,
//			_imageInfo->hMemDC, sourX, sourY, sourWidth, sourHeight, _transColor);
//
//		//blendDC를 출력해야 될 DC에 그린다
//		AlphaBlend(hdc, destX, destY, sourWidth, sourHeight,
//			_blendImage->hMemDC, 0, 0, sourWidth, sourHeight, _blendFunc);
//	}
//	else
//	{
//		AlphaBlend(hdc, destX, destY, sourWidth, sourHeight,
//			_imageInfo->hMemDC, sourX, sourY, sourWidth, sourHeight, _blendFunc);
//	}
//}
//
//
////프레임 렌더
//void image::frameRender(HDC hdc, int destX, int destY)
//{
//	if (_trans)
//	{
//		GdiTransparentBlt(hdc, destX, destY, 
//			_imageInfo->frameWidth, _imageInfo->frameHeight,
//			_imageInfo->hMemDC, 
//			_imageInfo->currentFrameX * _imageInfo->frameWidth, 
//			_imageInfo->currentFrameY * _imageInfo->frameHeight, 
//			_imageInfo->frameWidth, _imageInfo->frameHeight, _transColor);
//	}
//	else
//	{
//		BitBlt(hdc, destX, destY, _imageInfo->frameWidth, _imageInfo->frameHeight,
//			_imageInfo->hMemDC,
//			_imageInfo->currentFrameX * _imageInfo->frameWidth,
//			_imageInfo->currentFrameY * _imageInfo->frameHeight, SRCCOPY);
//	}
//}
//
//void image::frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY)
//{
//	_imageInfo->currentFrameX = currentFrameX;
//	_imageInfo->currentFrameY = currentFrameY;
//
//	if (currentFrameX > _imageInfo->maxFrameX) _imageInfo->currentFrameX = _imageInfo->maxFrameX;
//	if (currentFrameY > _imageInfo->maxFrameY) _imageInfo->currentFrameY = _imageInfo->maxFrameY;
//
//	if (_trans)
//	{
//		GdiTransparentBlt(hdc, destX, destY,
//			_imageInfo->frameWidth, _imageInfo->frameHeight,
//			_imageInfo->hMemDC,
//			currentFrameX * _imageInfo->frameWidth,
//			currentFrameY * _imageInfo->frameHeight,
//			_imageInfo->frameWidth, _imageInfo->frameHeight, _transColor);
//	}
//	else
//	{
//		BitBlt(hdc, destX, destY, _imageInfo->frameWidth, _imageInfo->frameHeight,
//			_imageInfo->hMemDC,
//			_imageInfo->currentFrameX * _imageInfo->frameWidth,
//			_imageInfo->currentFrameY * _imageInfo->frameHeight, SRCCOPY);
//	}
//
//}
//
//
////Alpha Frame Render
//void image::alphaFrameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, BYTE alpha)
//{
//	if (!_blendImage) alphaInit();
//	_blendFunc.SourceConstantAlpha = alpha;
//
//	_imageInfo->currentFrameX = currentFrameX;
//	_imageInfo->currentFrameY = currentFrameY;
//
//	if (currentFrameX > _imageInfo->maxFrameX) _imageInfo->currentFrameX = _imageInfo->maxFrameX;
//	if (currentFrameY > _imageInfo->maxFrameY) _imageInfo->currentFrameY = _imageInfo->maxFrameY;
//
//	if (_trans)
//	{
//		BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
//			hdc, destX, destY, SRCCOPY);
//
//		GdiTransparentBlt(_blendImage->hMemDC, destX, destY,
//			_imageInfo->frameWidth, _imageInfo->frameHeight,
//			_imageInfo->hMemDC,
//			currentFrameX * _imageInfo->frameWidth,
//			currentFrameY * _imageInfo->frameHeight,
//			_imageInfo->frameWidth, _imageInfo->frameHeight, _transColor);
//
//		AlphaBlend(hdc, destX, destY, _imageInfo->frameWidth, _imageInfo->frameHeight,
//			_blendImage->hMemDC, 0, 0,
//			_imageInfo->currentFrameX * _imageInfo->frameWidth,
//			_imageInfo->currentFrameY * _imageInfo->frameHeight, _blendFunc);
//	}
//	else
//	{
//		AlphaBlend(hdc, destX, destY, _imageInfo->frameWidth, _imageInfo->frameHeight,
//			_imageInfo->hMemDC, 0, 0,
//			_imageInfo->currentFrameX * _imageInfo->frameWidth,
//			_imageInfo->currentFrameY * _imageInfo->frameHeight, _blendFunc);
//	}
//}
//
//
////Shadow Render
//void image::shadowRender(HDC hdc, int destX, int destY)
//{
//}
//
//void image::shadowRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY)
//{
//	if (!_shadowImage) shadowInit();
//
//	_imageInfo->currentFrameX = currentFrameX;
//	_imageInfo->currentFrameY = currentFrameY;
//
//	if (currentFrameX > _imageInfo->maxFrameX) _imageInfo->currentFrameX = _imageInfo->maxFrameX;
//	if (currentFrameY > _imageInfo->maxFrameY) _imageInfo->currentFrameY = _imageInfo->maxFrameY;
//
//	if (_trans)
//	{
//		//BitBlt(hdc, destX, destY, _imageInfo->frameWidth, _imageInfo->frameHeight,
//		//	_imageInfo->hMemDC,
//		//	_imageInfo->currentFrameX * _imageInfo->frameWidth,
//		//	_imageInfo->currentFrameY * _imageInfo->frameHeight, MERGEPAINT);
//
//		_shadowImage->hMemDC = makeBlackAndWhite(_imageInfo->hMemDC, 
//			_imageInfo->frameWidth * _imageInfo->currentFrameX,
//			_imageInfo->frameHeight * _imageInfo->currentFrameY,
//			_imageInfo->currentFrameX * _imageInfo->frameWidth,
//			_imageInfo->currentFrameY * _imageInfo->frameHeight);
//
//		GdiTransparentBlt(hdc, destX, destY,
//			_imageInfo->frameWidth, _imageInfo->frameHeight,
//			_shadowImage->hMemDC,
//			currentFrameX * _imageInfo->frameWidth,
//			currentFrameY * _imageInfo->frameHeight,
//			_imageInfo->frameWidth, _imageInfo->frameHeight, _transColor);
//	}
//	else
//	{
//		BitBlt(hdc, destX, destY, _imageInfo->frameWidth, _imageInfo->frameHeight,
//			_imageInfo->hMemDC,
//			_imageInfo->currentFrameX * _imageInfo->frameWidth,
//			_imageInfo->currentFrameY * _imageInfo->frameHeight, SRCCOPY);
//	}
//}
//
////루프 렌더
//void image::loopRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY)
//{
//	//offset 값이 음수인 경우에 보정해준다
//	if (offsetX < 0) offsetX = _imageInfo->width + (offsetX % _imageInfo->width);
//	if (offsetY < 0) offsetY = _imageInfo->height + (offsetY % _imageInfo->height);
//
//	//그려지는 소스의 영역(image) 셋팅할 변수
//	RECT rcSour;
//	int sourWidth;
//	int sourHeight;
//
//	//그려지는 영역의 DC
//	RECT rcDest;
//
//	//그려야할 전체 영역
//	int drawAreaX = drawArea->left;
//	int drawAreaY = drawArea->top;
//	int drawAreaW = drawArea->right - drawArea->left;
//	int drawAreaH = drawArea->bottom - drawArea->top;
//
//	//세로 루프 셋팅
//	for (int y = 0; y < drawAreaH; y += sourHeight)
//	{
//		//소스(이미지 sour) 영역의 높이 계산
//		rcSour.top = (y + offsetY) % _imageInfo->height;
//		rcSour.bottom = _imageInfo->height;
//		sourHeight = rcSour.bottom - rcSour.top;
//
//		//소스의 영역이 그리기 화면을 넘어갔다면 (화면밖으로 이미지가 나갔으면)
//		if (y + sourHeight > drawAreaH)
//		{
//			//넘어간 그림의 값만큼 바텀 값을 올려주자
//			rcSour.bottom -= (y + sourHeight) - drawAreaH;
//			sourHeight = rcSour.bottom - rcSour.top;
//		}
//
//		//그려지는 영역
//		rcDest.top = y + drawAreaY;
//		rcDest.bottom = rcDest.top + sourHeight;
//
//		//가로 루프 셋팅
//		for (int x = 0; x < drawAreaW; x += sourWidth)
//		{
//			//소스의 영역 가로 계산
//			rcSour.left = (x + offsetX) % _imageInfo->width;
//			rcSour.right = _imageInfo-> width;
//			sourWidth = rcSour.right - rcSour.left;
//
//			if (x + sourWidth > drawAreaW)
//			{
//				//넘어간 만큼 right 값을 왼쪽으로
//				rcSour.right -= (x + sourWidth) - drawAreaW;
//				sourWidth = rcSour.right - rcSour.left;
//			}
//
//			//그려지는 영역
//			rcDest.left = x + drawAreaX;
//			rcDest.right = rcDest.left + sourWidth;
//
//			//그려주자
//			render(hdc, rcDest.left, rcDest.top, rcSour.left, rcSour.top, rcSour.right - rcSour.left, rcSour.bottom - rcSour.top);
//		}
//	}
//
//}
//
//void image::aniRender(HDC hdc, int destX, int destY, animation* ani)
//{
//	render(hdc, destX, destY, ani->getFramePos().x, ani->getFramePos().y, ani->getFrameWidth(), ani->getFrameHeight());
//}
