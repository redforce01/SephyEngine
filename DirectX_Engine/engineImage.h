#ifndef _ENGINEIMAGE_H
#define _ENGINEIMAGE_H

class EngineImage;

#include <atlimage.h>

class EngineImage
{
public:
	enum class IMAGE_LOAD_KIND
	{
		LOAD_RESOURCE = 0,
		LOAD_FILE,
		LOAD_EMPTY,
		LOAD_END
	};

	typedef struct tagImageInfo
	{
		DWORD resID;
		HDC hMemDC;
		HBITMAP hBit;
		HBITMAP hOBit;
		float x, y;
		int width, height;

		int currentFrameX;
		int currentFrameY;
		int maxFrameX;
		int maxFrameY;
		int frameWidth;
		int frameHeight;

		BYTE loadType;
		RECT boundingBox;

		tagImageInfo()
		{
			resID = 0;
			hMemDC = nullptr;
			hBit = nullptr;
			hOBit = nullptr;
			x = y = 0;
			width = height = 0;
			currentFrameX = 0;
			currentFrameY = 0;
			maxFrameX = 0;
			maxFrameY = 0;
			frameWidth = frameHeight = 0;
			loadType = (BYTE)IMAGE_LOAD_KIND::LOAD_RESOURCE;
			boundingBox = RectMake(0, 0, 0, 0);			
		}
	} IMAGE_INFO, *LPIMAGE_INFO;
	

private:
	LPIMAGE_INFO	_imageInfo;
	CHAR*			_fileName;
	BOOL			_trans;
	COLORREF		_transColor;
	BLENDFUNCTION	_blendFunc;
	LPIMAGE_INFO	_blendImage;

public:
	EngineImage();
	virtual ~EngineImage();

	virtual HRESULT initImage(HWND hWnd, int width, int height);
	virtual HRESULT initImage(HWND hWnd, const DWORD resID, int width, int height, BOOL trans, COLORREF transColor);
	virtual HRESULT initImage(HWND hWnd, const char* fileName, int width, int height, BOOL trans, COLORREF transColor);
	virtual HRESULT initImage(HWND hWnd, const char* fileName, float x, float y, int width, int height, BOOL trans, COLORREF transColor);
	virtual HRESULT initImage(HWND hWnd, const char* fileName, float x, float y, int width, int height, int frameX, int frameY, BOOL trans, COLORREF transColor);
	virtual HRESULT initImage(HWND hWnd, const char* fileName, int width, int height, int frameX, int frameY, BOOL trans, COLORREF transColor);

	virtual void alphaInit(HWND hWnd);
	virtual void release(void);
	virtual void setTransColor(BOOL trans, COLORREF transColor);

	virtual void render(HDC hdc);
	virtual void render(HDC hdc, int destX, int destY);
	virtual void render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);

	virtual void alphaRender(HDC hdc, int destX, int destY, BYTE alpha);
	virtual void alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha);

	virtual void frameRender(HDC hdc, int destX, int destY);
	virtual void frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);

	virtual void loopRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY);

	inline HDC getMemDC(void) { return _imageInfo->hMemDC; }

	inline void setX(float x) { _imageInfo->x = x; }
	inline float getX() { return _imageInfo->x; }

	inline void setY(float y) { _imageInfo->y = y; }
	inline float getY() { return _imageInfo->y; }

	inline void setCenter(float x, float y)
	{
		_imageInfo->x = x - (_imageInfo->width / 2);
		_imageInfo->y = y - (_imageInfo->height / 2);
	}

	inline float getCenterX()
	{
		return _imageInfo->maxFrameX <= 0 ? _imageInfo->x + (_imageInfo->width / 2) :
			_imageInfo->x + (_imageInfo->frameWidth / 2);
	}

	inline float getCenterY()
	{
		return _imageInfo->maxFrameY <= 0 ? _imageInfo->y + (_imageInfo->height / 2) :
			_imageInfo->y + (_imageInfo->frameHeight / 2);
	}

	inline int getWidth() { return _imageInfo->width; }
	inline int getHeight() { return _imageInfo->height; }

	inline RECT boundingBox()
	{
		RECT rc = { int(_imageInfo->x), int(_imageInfo->y),
			int(_imageInfo->x + _imageInfo->frameWidth),
			int(_imageInfo->y + _imageInfo->frameHeight) };

		return rc;
	}

	inline void setFrameX(int frameX)
	{
		_imageInfo->currentFrameX = frameX;
		if (frameX > _imageInfo->maxFrameX) _imageInfo->currentFrameX = _imageInfo->maxFrameX;
	}

	inline void setFrameY(int frameY)
	{
		_imageInfo->currentFrameY = frameY;
		if (frameY > _imageInfo->maxFrameY) _imageInfo->currentFrameY = _imageInfo->maxFrameY;
	}

	inline int getMaxFrameX() { return _imageInfo->maxFrameX; }
	inline int getMaxFrameY() { return _imageInfo->maxFrameY; }

	inline int getFrameX() { return _imageInfo->currentFrameX; }
	inline int getFrameY() { return _imageInfo->currentFrameY; }

	inline int getFrameWidth() { return _imageInfo->frameWidth; }
	inline int getFrameHeight() { return _imageInfo->frameHeight; }
};

#endif // !_ENGINEIMAGE_H
