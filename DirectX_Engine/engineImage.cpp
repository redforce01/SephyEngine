#include "stdafx.h"
#include "engineImage.h"


EngineImage::EngineImage()
{
}


EngineImage::~EngineImage()
{
	release();
}

// Create Image - Empty
HRESULT EngineImage::initImage(HWND hWnd, int width, int height)
{
	if (hWnd == nullptr) return E_FAIL;
	if (_imageInfo != nullptr) release();

	HDC hdc = GetDC(hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = (BYTE)IMAGE_LOAD_KIND::LOAD_EMPTY;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->x = 0;
	_imageInfo->y = 0;
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->currentFrameX = 0;
	_imageInfo->currentFrameY = 0;
	_imageInfo->maxFrameX = 0;
	_imageInfo->maxFrameY = 0;
	_imageInfo->frameWidth = width;
	_imageInfo->frameHeight = height;

	_fileName = nullptr;
	_trans = FALSE;
	_transColor = RGB(0, 0, 0);

	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;

	ReleaseDC(hWnd, hdc);

	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	return S_OK;
}

// Create Image - Load From Resource
HRESULT EngineImage::initImage(HWND hWnd, const DWORD resID, int width, int height, BOOL trans, COLORREF transColor)
{
	if (hWnd == nullptr) return E_FAIL;
	if (_imageInfo != nullptr) release();

	HDC hdc = GetDC(hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = (BYTE)IMAGE_LOAD_KIND::LOAD_RESOURCE;
	_imageInfo->resID = resID;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadBitmap(g_hInst, MAKEINTRESOURCE(_imageInfo->resID));
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->x = 0;
	_imageInfo->y = 0;
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->currentFrameX = 0;
	_imageInfo->currentFrameY = 0;
	_imageInfo->maxFrameX = 0;
	_imageInfo->maxFrameY = 0;
	_imageInfo->frameWidth = width;
	_imageInfo->frameHeight = height;

	_fileName = nullptr;
	_trans = trans;
	_transColor = transColor;

	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;

	ReleaseDC(hWnd, hdc);

	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	return S_OK;
}

// Create Image - Load From File (1)
HRESULT EngineImage::initImage(HWND hWnd, const char * fileName, int width, int height, BOOL trans, COLORREF transColor)
{
	if (hWnd == nullptr) return E_FAIL;
	const char* file = FILEMANAGER->getImageFile(fileName)->projectPath.c_str();
	if (file == nullptr) return E_FAIL;

	if (_imageInfo != nullptr) release();

	HDC hdc = GetDC(hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = (BYTE)IMAGE_LOAD_KIND::LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(g_hInst, file, IMAGE_BITMAP, width, height, LR_LOADFROMFILE );
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->x = 0;
	_imageInfo->y = 0;
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->currentFrameX = 0;
	_imageInfo->currentFrameY = 0;
	_imageInfo->maxFrameX = 0;
	_imageInfo->maxFrameY = 0;
	_imageInfo->frameWidth = width;
	_imageInfo->frameHeight = height;

	int len = strlen(file);
	_fileName = new CHAR[len +1];
	strcpy_s(_fileName, len + 1, file);

	_trans = trans;
	_transColor = transColor;

	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;

	ReleaseDC(hWnd, hdc);

	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	return S_OK;
}

// Create Image - Load From File (2)
HRESULT EngineImage::initImage(HWND hWnd, const char * fileName, float x, float y, int width, int height, BOOL trans, COLORREF transColor)
{
	if (hWnd == nullptr) return E_FAIL;
	const char* file = FILEMANAGER->getImageFile(fileName)->projectPath.c_str();
	if (file == nullptr) return E_FAIL;

	if (_imageInfo != nullptr) release();

	HDC hdc = GetDC(hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = (BYTE)IMAGE_LOAD_KIND::LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(g_hInst, file, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->x = x - (width / 2);
	_imageInfo->y = y - (height / 2);
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->currentFrameX = 0;
	_imageInfo->currentFrameY = 0;
	_imageInfo->maxFrameX = 0;
	_imageInfo->maxFrameY = 0;
	_imageInfo->frameWidth = width;
	_imageInfo->frameHeight = height;

	int len = strlen(file);
	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, file);

	_trans = trans;
	_transColor = transColor;

	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;

	ReleaseDC(hWnd, hdc);

	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	return S_OK;
}

// Create Image + Frame - Load From File (1)
HRESULT EngineImage::initImage(HWND hWnd, const char * fileName, float x, float y, int width, int height, int frameX, int frameY, BOOL trans, COLORREF transColor)
{
	if (hWnd == nullptr) return E_FAIL;
	const char* file = FILEMANAGER->getImageFile(fileName)->projectPath.c_str();
	if (file == nullptr) return E_FAIL;

	if (_imageInfo != nullptr) release();

	HDC hdc = GetDC(hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = (BYTE)IMAGE_LOAD_KIND::LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(g_hInst, file, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->x = x - (width / 2);
	_imageInfo->y = y - (height / 2);
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->currentFrameX = 0;
	_imageInfo->currentFrameY = 0;
	_imageInfo->maxFrameX = frameX - 1;
	_imageInfo->maxFrameY = frameY - 1;
	_imageInfo->frameWidth = width / frameX;
	_imageInfo->frameHeight = height / frameY;

	int len = strlen(file);
	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, file);

	_trans = trans;
	_transColor = transColor;

	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;

	ReleaseDC(hWnd, hdc);

	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	return S_OK;
}

// Create Image + Frame - Load From File (2)
HRESULT EngineImage::initImage(HWND hWnd, const char * fileName, int width, int height, int frameX, int frameY, BOOL trans, COLORREF transColor)
{
	if (hWnd == nullptr) return E_FAIL;
	const char* file = FILEMANAGER->getImageFile(fileName)->projectPath.c_str();
	if (file == nullptr) return E_FAIL;

	if (_imageInfo != nullptr) release();

	HDC hdc = GetDC(hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = (BYTE)IMAGE_LOAD_KIND::LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(g_hInst, file, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->x = 0;
	_imageInfo->y = 0;
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->currentFrameX = 0;
	_imageInfo->currentFrameY = 0;
	_imageInfo->maxFrameX = frameX - 1;
	_imageInfo->maxFrameY = frameY - 1;
	_imageInfo->frameWidth = width / frameX;
	_imageInfo->frameHeight = height / frameY;

	int len = strlen(file);
	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, file);

	_trans = trans;
	_transColor = transColor;

	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;

	ReleaseDC(hWnd, hdc);

	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	return S_OK;
}

void EngineImage::alphaInit(HWND hWnd)
{
	HDC hdc = GetDC(hWnd);

	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = (BYTE)IMAGE_LOAD_KIND::LOAD_EMPTY;
	_blendImage->resID = 0;
	_blendImage->hMemDC = CreateCompatibleDC(hdc);
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, this->_imageInfo->width, this->_imageInfo->height);
	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);

	RECT rc;
	GetClientRect(hWnd, &rc);
	_blendImage->width = rc.right - rc.left;
	_blendImage->height = rc.bottom - rc.top;

	ReleaseDC(hWnd, hdc);
}

void EngineImage::release(void)
{
	if (_imageInfo)
	{
		SelectObject(_imageInfo->hMemDC, _imageInfo->hOBit);
		DeleteObject(_imageInfo->hBit);
		DeleteDC(_imageInfo->hMemDC);

		SAFE_DELETE(_imageInfo);
		SAFE_DELETE(_fileName);

		_trans = false;
		_transColor = RGB(0, 0, 0);
	}

	if (_blendImage)
	{
		SelectObject(_blendImage->hMemDC, _blendImage->hOBit);
		DeleteObject(_blendImage->hBit);
		DeleteDC(_blendImage->hMemDC);

		SAFE_DELETE(_blendImage);
	}
}

void EngineImage::setTransColor(BOOL trans, COLORREF transColor)
{
	_trans = trans;
	_transColor = transColor;
}

void EngineImage::render(HDC hdc)
{
	if (_trans)
	{
		GdiTransparentBlt(
			hdc,				//copy to DC
			_imageInfo->x,		//copied point start X
			_imageInfo->y,		//copied point start Y
			_imageInfo->width,	//copied size (width)
			_imageInfo->height,	//copied size (height)
			_imageInfo->hMemDC,	//copied DC
			0, 0,				//copy start x, y
			_imageInfo->width,	//copy size (width)
			_imageInfo->height,	//copy size (height)
			_transColor);		//transColor
	}
	else
	{
		BitBlt(hdc, 0, 0, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, SRCCOPY);
	}
}

void EngineImage::render(HDC hdc, int destX, int destY)
{
	if (_trans)
	{
		GdiTransparentBlt(
			hdc,				//copy to DC
			destX,				//copied point start X
			destY,				//copied point start Y
			_imageInfo->width,	//copied size (width)
			_imageInfo->height,	//copied size (height)
			_imageInfo->hMemDC,	//copied DC
			0, 0,				//copy start x, y
			_imageInfo->width,	//copy size (width)
			_imageInfo->height,	//copy size (height)
			_transColor);		//transColor
	}
	else
	{
		BitBlt(hdc, destX, destY, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, SRCCOPY);
	}
}

void EngineImage::render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight)
{
	if (_trans)
	{
		GdiTransparentBlt(
			hdc,				//copy to DC
			destX,				//copied point start X
			destY,				//copied point start Y
			sourWidth,			//copied size (width)
			sourHeight,			//copied size (height)
			_imageInfo->hMemDC,	//copied DC
			sourX, sourY,		//copy start x, y
			sourWidth,			//copy size (width)
			sourHeight,			//copy size (height)
			_transColor);		//transColor
	}
	else
	{
		BitBlt(hdc, destX, destY, sourWidth, sourHeight,
			_imageInfo->hMemDC, sourX, sourY, SRCCOPY);
	}
}

void EngineImage::alphaRender(HDC hdc, int destX, int destY, BYTE alpha)
{
	//if (!_blendImage) alphaInit();
	//_blendFunc.SourceConstantAlpha = alpha;

	//if (_trans)
	//{
	//	//출력해야 될 DC에 그려져 있는 내용을 blend에 그려준다
	//	BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
	//		hdc, destX, destY, SRCCOPY);

	//	//출력해야 될 이미지를 blend에 그려준다
	//	GdiTransparentBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
	//		_imageInfo->hMemDC, 0, 0,
	//		_imageInfo->width, _imageInfo->height, _transColor);

	//	//blendDC를 출력해야 될 DC에 그린다
	//	AlphaBlend(hdc, destX, destY, _imageInfo->width, _imageInfo->height,
	//		_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _blendFunc);
	//}
	//else
	//{
	//	AlphaBlend(hdc, destX, destY, _imageInfo->width, _imageInfo->height,
	//		_imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _blendFunc);
	//}
}

void EngineImage::alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha)
{
	//if (!_blendImage) alphaInit();
	//_blendFunc.SourceConstantAlpha = alpha;

	//if (_trans)
	//{
	//	//출력해야 될 DC에 그려져 있는 내용을 blend에 그려준다
	//	BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
	//		hdc, destX, destY, SRCCOPY);

	//	//출력해야 될 이미지를 blend에 그려준다
	//	GdiTransparentBlt(_blendImage->hMemDC, 0, 0, sourWidth, sourHeight,
	//		_imageInfo->hMemDC, sourX, sourY, sourWidth, sourHeight, _transColor);

	//	//blendDC를 출력해야 될 DC에 그린다
	//	AlphaBlend(hdc, destX, destY, sourWidth, sourHeight,
	//		_blendImage->hMemDC, 0, 0, sourWidth, sourHeight, _blendFunc);
	//}
	//else
	//{
	//	AlphaBlend(hdc, destX, destY, sourWidth, sourHeight,
	//		_imageInfo->hMemDC, sourX, sourY, sourWidth, sourHeight, _blendFunc);
	//}
}

void EngineImage::frameRender(HDC hdc, int destX, int destY)
{
	if (_trans)
	{
		GdiTransparentBlt(hdc, destX, destY,
			_imageInfo->frameWidth, _imageInfo->frameHeight,
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth, _imageInfo->frameHeight, _transColor);
	}
	else
	{
		BitBlt(hdc, destX, destY, _imageInfo->frameWidth, _imageInfo->frameHeight,
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight, SRCCOPY);
	}
}

void EngineImage::frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY)
{
	_imageInfo->currentFrameX = currentFrameX;
	_imageInfo->currentFrameY = currentFrameY;

	if (currentFrameX > _imageInfo->maxFrameX) _imageInfo->currentFrameX = _imageInfo->maxFrameX;
	if (currentFrameY > _imageInfo->maxFrameY) _imageInfo->currentFrameY = _imageInfo->maxFrameY;

	if (_trans)
	{
		GdiTransparentBlt(hdc, destX, destY,
			_imageInfo->frameWidth, _imageInfo->frameHeight,
			_imageInfo->hMemDC,
			currentFrameX * _imageInfo->frameWidth,
			currentFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth, _imageInfo->frameHeight, _transColor);
	}
	else
	{
		BitBlt(hdc, destX, destY, _imageInfo->frameWidth, _imageInfo->frameHeight,
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight, SRCCOPY);
	}
}

void EngineImage::loopRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY)
{
	if (offsetX < 0) offsetX = _imageInfo->width + (offsetX % _imageInfo->width);
	if (offsetY < 0) offsetY = _imageInfo->height + (offsetY % _imageInfo->height);

	RECT rcSour;
	int sourWidth;
	int sourHeight;

	RECT rcDest;

	int drawAreaX = drawArea->left;
	int drawAreaY = drawArea->top;
	int drawAreaW = drawArea->right - drawArea->left;
	int drawAreaH = drawArea->bottom - drawArea->top;

	for (int y = 0; y < drawAreaH; y += sourHeight)
	{
		rcSour.top = (y + offsetY) % _imageInfo->height;
		rcSour.bottom = _imageInfo->height;
		sourHeight = rcSour.bottom - rcSour.top;

		if (y + sourHeight > drawAreaH)
		{
			rcSour.bottom -= (y + sourHeight) - drawAreaH;
			sourHeight = rcSour.bottom - rcSour.top;
		}

		rcDest.top = y + drawAreaY;
		rcDest.bottom = rcDest.top + sourHeight;

		for (int x = 0; x < drawAreaW; x += sourWidth)
		{
			rcSour.left = (x + offsetX) % _imageInfo->width;
			rcSour.right = _imageInfo->width;
			sourWidth = rcSour.right - rcSour.left;

			if (x + sourWidth > drawAreaW)
			{
				rcSour.right -= (x + sourWidth) - drawAreaW;
				sourWidth = rcSour.right - rcSour.left;
			}

			rcDest.left = x + drawAreaX;
			rcDest.right = rcDest.left + sourWidth;

			render(hdc, rcDest.left, rcDest.top, rcSour.left, rcSour.top, rcSour.right - rcSour.left, rcSour.bottom - rcSour.top);
		}
	}
}


