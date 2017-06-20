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
////�� ��Ʈ��  �̹��� �����
//HRESULT image::init( int width, int height )
//{
//	//�ʱ�ȭ�� �ٽ� �Ǵ� ���� ����
//	if ( _imageInfo != NULL ) release( );
//
//	//DC ���´�
//	HDC hdc = GetDC( _hWnd );
//
//	//CreateCompatibleDC
//	//��Ʈ���� ����ϱ� ���ؼ� �޸� DC�� ����� �ִ� ��
//
//	//CreateCompatibleBitMap
//	//���� DC�� ȣȯ�Ǵ� ��Ʈ�� ����
//
//	//�̹��� ���� ����
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
//	//���� �÷� ����
//	_trans = FALSE;
//	_transColor = RGB( 0, 0, 0 );
//
//	//���� ���� ��� ��������
//	_blendFunc.BlendFlags = 0;
//	_blendFunc.AlphaFormat = 0;
//	_blendFunc.BlendOp = AC_SRC_OVER;
//
//	//���� ���� ����� ���� �̹��� ����
//	/*_blendImage = new IMAGE_INFO;
//	_blendImage->loadType = LOAD_EMPTY;
//	_blendImage->resID = 0;
//	_blendImage->hMemDC = CreateCompatibleDC(hdc);
//	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
//	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
//	_blendImage->width = WINSIZEX;
//	_blendImage->height = WINSIZEY;*/
//	
//	//���� DC ����
//	ReleaseDC( _hWnd, hdc );
//
//	//���ҽ� ������ ���н� ó��
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
////���ҽ��κ��� �о�´�
//HRESULT image::init( const DWORD resID, int width,
//	int height, BOOL trans, COLORREF transColor )
//{
//	//���ʱ�ȭ�� ���
//	if ( _imageInfo != NULL ) release( );
//
//	//DC ��´�
//	HDC hdc = GetDC( _hWnd );
//
//	//�̹��� ���� ����
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
//	//���� �÷� ����
//	_trans = FALSE;
//	_transColor = RGB( 0, 0, 0 );
//
//	//���� ���� ��� ��������
//	_blendFunc.BlendFlags = 0;
//	_blendFunc.AlphaFormat = 0;
//	_blendFunc.BlendOp = AC_SRC_OVER;
//
//	//���� ���� ����� ���� �̹��� ����
//	/*_blendImage = new IMAGE_INFO;
//	_blendImage->loadType = LOAD_EMPTY;
//	_blendImage->resID = 0;
//	_blendImage->hMemDC = CreateCompatibleDC(hdc);
//	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
//	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
//	_blendImage->width = WINSIZEX;
//	_blendImage->height = WINSIZEY;*/
//
//	//���� DC ����
//	ReleaseDC( _hWnd, hdc );
//
//	//���ҽ� ��⿡ �����ϸ�
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
////�̹��� ���� (���Ϸκ��� �о�´�)
//HRESULT image::init( const char* fileName, int width, int height,
//	BOOL trans, COLORREF transColor )
//{
//	//���� ��ΰ� �߸� �Ǿ�����...
//	if ( fileName == NULL ) return E_FAIL;
//
//	//���ʱ�ȭ�� ���
//	if ( _imageInfo != NULL ) release( );
//
//	//DC ��´�
//	HDC hdc = GetDC( _hWnd );
//
//	//�̹��� ���� ����
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
//	//���� ��� �̸� ����
//	int len = strlen( fileName );
//	_fileName = new CHAR[len + 1];
//	strcpy_s( _fileName, len + 1, fileName );
//
//	//���� �÷� ����
//	_trans = trans;
//	_transColor = transColor;
//
//	//���� ���� ��� ��������
//	_blendFunc.BlendFlags = 0;
//	_blendFunc.AlphaFormat = 0;
//	_blendFunc.BlendOp = AC_SRC_OVER;
//
//	//���� ���� ����� ���� �̹��� ����
//	/*_blendImage = new IMAGE_INFO;
//	_blendImage->loadType = LOAD_EMPTY;
//	_blendImage->resID = 0;
//	_blendImage->hMemDC = CreateCompatibleDC(hdc);
//	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
//	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
//	_blendImage->width = WINSIZEX;
//	_blendImage->height = WINSIZEY;*/
//
//	//���� DC����
//	ReleaseDC( _hWnd, hdc );
//
//	//���ҽ� ��⿡ �����ϸ�
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
//	//���� ��ΰ� �߸� �Ǿ�����...
//	if (fileName == NULL) return E_FAIL;
//
//	//���ʱ�ȭ�� ���
//	if (_imageInfo != NULL) release();
//
//	//DC ��´�
//	HDC hdc = GetDC(_hWnd);
//
//	//�̹��� ���� ����
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
//	//���� ��� �̸� ����
//	int len = strlen(fileName);
//	_fileName = new CHAR[len + 1];
//	strcpy_s(_fileName, len + 1, fileName);
//
//	//���� �÷� ����
//	_trans = trans;
//	_transColor = transColor;
//
//	//���� ���� ��� ��������
//	_blendFunc.BlendFlags = 0;
//	_blendFunc.AlphaFormat = 0;
//	_blendFunc.BlendOp = AC_SRC_OVER;
//
//	//���� ���� ����� ���� �̹��� ����
//	/*_blendImage = new IMAGE_INFO;
//	_blendImage->loadType = LOAD_EMPTY;
//	_blendImage->resID = 0;
//	_blendImage->hMemDC = CreateCompatibleDC(hdc);
//	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
//	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
//	_blendImage->width = WINSIZEX;
//	_blendImage->height = WINSIZEY;*/
//
//	//���� DC����
//	ReleaseDC(_hWnd, hdc);
//
//	//���ҽ� ��⿡ �����ϸ�
//	if (_imageInfo->hBit == 0)
//	{
//		release();
//		return E_FAIL;
//	}
//
//	return S_OK;
//}
//
////�̹��� + ������ ���� �ʱ�ȭ
//HRESULT image::init(const char* fileName, float x, float y, int width, int height,
//	int frameX, int frameY, BOOL trans, COLORREF transColor)
//{
//	//���� ��ΰ� �߸� �Ǿ�����...
//	if (fileName == NULL) return E_FAIL;
//
//	//���ʱ�ȭ�� ���
//	if (_imageInfo != NULL) release();
//
//	//DC ��´�
//	HDC hdc = GetDC(_hWnd);
//
//	//�̹��� ���� ����
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
//	//���� ��� �̸� ����
//	int len = strlen(fileName);
//	_fileName = new CHAR[len + 1];
//	strcpy_s(_fileName, len + 1, fileName);
//
//	//���� �÷� ����
//	_trans = trans;
//	_transColor = transColor;
//
//	//���� ���� ��� ��������
//	_blendFunc.BlendFlags = 0;
//	_blendFunc.AlphaFormat = 0;
//	_blendFunc.BlendOp = AC_SRC_OVER;
//
//	//���� ���� ����� ���� �̹��� ����
//	/*_blendImage = new IMAGE_INFO;
//	_blendImage->loadType = LOAD_EMPTY;
//	_blendImage->resID = 0;
//	_blendImage->hMemDC = CreateCompatibleDC(hdc);
//	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
//	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
//	_blendImage->width = WINSIZEX;
//	_blendImage->height = WINSIZEY;*/
//
//	//���� DC����
//	ReleaseDC(_hWnd, hdc);
//
//	//���ҽ� ��⿡ �����ϸ�
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
//	//���� ��ΰ� �߸� �Ǿ�����...
//	if (fileName == NULL) return E_FAIL;
//
//	//���ʱ�ȭ�� ���
//	if (_imageInfo != NULL) release();
//
//	//DC ��´�
//	HDC hdc = GetDC(_hWnd);
//
//	//�̹��� ���� ����
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
//	//���� ��� �̸� ����
//	int len = strlen(fileName);
//	_fileName = new CHAR[len + 1];
//	strcpy_s(_fileName, len + 1, fileName);
//
//	//���� �÷� ����
//	_trans = trans;
//	_transColor = transColor;
//
//	//���� ���� ��� ��������
//	_blendFunc.BlendFlags = 0;
//	_blendFunc.AlphaFormat = 0;
//	_blendFunc.BlendOp = AC_SRC_OVER;
//
//	////���� ���� ����� ���� �̹��� ����
//	//_blendImage = new IMAGE_INFO;
//	//_blendImage->loadType = LOAD_EMPTY;
//	//_blendImage->resID = 0;
//	//_blendImage->hMemDC = CreateCompatibleDC(hdc);
//	//_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
//	//_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
//	//_blendImage->width = WINSIZEX;
//	//_blendImage->height = WINSIZEY;
//
//	//���� DC����
//	ReleaseDC(_hWnd, hdc);
//
//	//���ҽ� ��⿡ �����ϸ�
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
//	//���� ��ΰ� �߸� �Ǿ�����...
//	if (fileName == NULL) return E_FAIL;
//
//	//���ʱ�ȭ�� ���
//	if (_imageInfo != NULL) release();
//
//	//DC ��´�
//	HDC hdc = GetDC(_hWnd);
//
//	//�̹��� ���� ����
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
//	//���� ��� �̸� ����
//	int len = strlen(fileName);
//	_fileName = new CHAR[len + 1];
//	strcpy_s(_fileName, len + 1, fileName);
//
//	//���� �÷� ����
//	_trans = trans;
//	_transColor = transColor;
//
//	//���� ���� ��� ��������
//	_blendFunc.BlendFlags = 0;
//	_blendFunc.AlphaFormat = 0;
//	_blendFunc.BlendOp = AC_SRC_OVER;
//
//	////���� ���� ����� ���� �̹��� ����
//	//_blendImage = new IMAGE_INFO;
//	//_blendImage->loadType = LOAD_EMPTY;
//	//_blendImage->resID = 0;
//	//_blendImage->hMemDC = CreateCompatibleDC(hdc);
//	//_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
//	//_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
//	//_blendImage->width = WINSIZEX;
//	//_blendImage->height = WINSIZEY;
//
//	//���� DC����
//	ReleaseDC(_hWnd, hdc);
//
//	//���ҽ� ��⿡ �����ϸ�
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
//	//DC ��´�
//	HDC hdc = GetDC(_hWnd);
//
//	//���� ���� ����� ���� �̹��� ����
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
//	//DC ��´�
//	HDC hdc = GetDC(_hWnd);
//
//	//���� ���� ����� ���� �̹��� ����
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
////����
//void image::release( void )
//{
//	if (_imageInfo)
//	{
//		//�̹��� ����
//		SelectObject(_imageInfo->hMemDC, _imageInfo->hOBit);
//		DeleteObject(_imageInfo->hBit);
//		DeleteDC(_imageInfo->hMemDC);
//
//		//������ ����
//		SAFE_DELETE(_imageInfo);
//		SAFE_DELETE(_fileName);
//
//		//���� �÷� �ʱ�ȭ
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
////���� Ű��(RGB��) ���� == Ư�� ������ �׸��� �ʴ´�
//void image::setTransColor( BOOL trans, COLORREF transColor )
//{
//	_trans = trans;
//	_transColor = transColor;
//}
//
////����
//void image::render(HDC hdc)
//{
//	if (_trans)
//	{
//		GdiTransparentBlt(
//			hdc,				//������ ����� DC
//			_imageInfo->x,		//����� ��ǥ ����X
//			_imageInfo->y,		//����� ��ǥ ����Y
//			_imageInfo->width,	//����� ũ�� width
//			_imageInfo->height,	//����� ũ�� height
//			_imageInfo->hMemDC,	//������ DC
//			0, 0,				//���� �������� x, y
//			_imageInfo->width,	//������ ũ�� width
//			_imageInfo->height,	//������ ũ�� height
//			_transColor);		//���翡�� ������ ����
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
//			hdc,				//������ ����� DC
//			destX,				//����� ��ǥ ����X
//			destY,				//����� ��ǥ ����Y
//			_imageInfo->width,	//����� ũ�� width
//			_imageInfo->height,	//����� ũ�� height
//			_imageInfo->hMemDC,	//������ DC
//			0, 0,				//���� �������� x, y
//			_imageInfo->width,	//������ ũ�� width
//			_imageInfo->height,	//������ ũ�� height
//			_transColor);		//���翡�� ������ ����
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
//			hdc,				//������ ����� DC
//			destX,				//����� ��ǥ ����X
//			destY,				//����� ��ǥ ����Y
//			sourWidth,			//����� ũ�� width
//			sourHeight,			//����� ũ�� height
//			_imageInfo->hMemDC,	//������ DC
//			sourX, sourY,		//���� �������� x, y
//			sourWidth,			//������ ũ�� width
//			sourHeight,			//������ ũ�� height
//			_transColor);		//���翡�� ������ ����
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
//		//����ؾ� �� DC�� �׷��� �ִ� ������ blend�� �׷��ش�
//		BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
//			hdc, destX, destY, SRCCOPY);
//
//		//����ؾ� �� �̹����� blend�� �׷��ش�
//		GdiTransparentBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
//			_imageInfo->hMemDC, 0, 0,
//			_imageInfo->width, _imageInfo->height, _transColor);
//
//		//blendDC�� ����ؾ� �� DC�� �׸���
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
//		//����ؾ� �� DC�� �׷��� �ִ� ������ blend�� �׷��ش�
//		BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
//			hdc, destX, destY, SRCCOPY);
//
//		//����ؾ� �� �̹����� blend�� �׷��ش�
//		GdiTransparentBlt(_blendImage->hMemDC, 0, 0, sourWidth, sourHeight,
//			_imageInfo->hMemDC, sourX, sourY, sourWidth, sourHeight, _transColor);
//
//		//blendDC�� ����ؾ� �� DC�� �׸���
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
////������ ����
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
////���� ����
//void image::loopRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY)
//{
//	//offset ���� ������ ��쿡 �������ش�
//	if (offsetX < 0) offsetX = _imageInfo->width + (offsetX % _imageInfo->width);
//	if (offsetY < 0) offsetY = _imageInfo->height + (offsetY % _imageInfo->height);
//
//	//�׷����� �ҽ��� ����(image) ������ ����
//	RECT rcSour;
//	int sourWidth;
//	int sourHeight;
//
//	//�׷����� ������ DC
//	RECT rcDest;
//
//	//�׷����� ��ü ����
//	int drawAreaX = drawArea->left;
//	int drawAreaY = drawArea->top;
//	int drawAreaW = drawArea->right - drawArea->left;
//	int drawAreaH = drawArea->bottom - drawArea->top;
//
//	//���� ���� ����
//	for (int y = 0; y < drawAreaH; y += sourHeight)
//	{
//		//�ҽ�(�̹��� sour) ������ ���� ���
//		rcSour.top = (y + offsetY) % _imageInfo->height;
//		rcSour.bottom = _imageInfo->height;
//		sourHeight = rcSour.bottom - rcSour.top;
//
//		//�ҽ��� ������ �׸��� ȭ���� �Ѿ�ٸ� (ȭ������� �̹����� ��������)
//		if (y + sourHeight > drawAreaH)
//		{
//			//�Ѿ �׸��� ����ŭ ���� ���� �÷�����
//			rcSour.bottom -= (y + sourHeight) - drawAreaH;
//			sourHeight = rcSour.bottom - rcSour.top;
//		}
//
//		//�׷����� ����
//		rcDest.top = y + drawAreaY;
//		rcDest.bottom = rcDest.top + sourHeight;
//
//		//���� ���� ����
//		for (int x = 0; x < drawAreaW; x += sourWidth)
//		{
//			//�ҽ��� ���� ���� ���
//			rcSour.left = (x + offsetX) % _imageInfo->width;
//			rcSour.right = _imageInfo-> width;
//			sourWidth = rcSour.right - rcSour.left;
//
//			if (x + sourWidth > drawAreaW)
//			{
//				//�Ѿ ��ŭ right ���� ��������
//				rcSour.right -= (x + sourWidth) - drawAreaW;
//				sourWidth = rcSour.right - rcSour.left;
//			}
//
//			//�׷����� ����
//			rcDest.left = x + drawAreaX;
//			rcDest.right = rcDest.left + sourWidth;
//
//			//�׷�����
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
