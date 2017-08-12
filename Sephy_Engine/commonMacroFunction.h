#pragma once
#include <vector>

#define MOUSEX input->getMouseX()
#define MOUSEY input->getMouseY()
#define PT_MOUSE (PointMake(MOUSEX, MOUSEY))

inline POINT PointMake(int x, int y)
{
	POINT pt = { x, y };
	return pt;
}

inline void LineMake(HDC hdc, int x1, int y1, int x2, int y2)
{
	MoveToEx(hdc, x1, y1, NULL);
	LineTo(hdc, x2, y2);
}

inline void LineMake(HDC hdc, std::vector<POINT> vPt)
{
	std::vector<POINT>::iterator viPoint;
	int i = 0;
	for (viPoint = vPt.begin(); viPoint != vPt.end(); ++viPoint, i++)
	{
		if (i == 0) MoveToEx(hdc, viPoint->x, viPoint->y, NULL);
		else LineTo(hdc, viPoint->x, viPoint->y);
	}

	vPt.clear();
}
#define MUL(a) a * a

inline RECT RectMake(int x, int y, int width, int height)
{
	RECT rc = { x, y, x + width, y + height };
	return rc;
}

inline RECT RectMakeCenter(int x, int y, int width, int height)
{
	RECT rc = { x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2) };
	return rc;
}

inline void EllipseMake(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x, y, x + width, y + height);
}

inline void EllipseMakeCenter(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x - width / 2, y - height / 2, x + width / 2, y + height / 2);
}

inline void IsoRender(HDC hdc, RECT rc)
{
	HPEN myPen, oldPen;
	myPen = CreatePen(1, 1, RGB(255, 255, 255));
	oldPen = (HPEN)SelectObject(hdc, myPen);
	
	LineMake(hdc, (rc.right + rc.left) / 2, rc.top, rc.right, (rc.top + rc.bottom) / 2);	//12 -> 3
	LineMake(hdc, rc.right, (rc.top + rc.bottom) / 2, (rc.left + rc.right) / 2, rc.bottom);	//3 -> 6 
	LineMake(hdc, (rc.left + rc.right) / 2, rc.bottom, rc.left, (rc.top + rc.bottom) / 2);	//6 -> 9
	LineMake(hdc, rc.left, (rc.top + rc.bottom) / 2, (rc.right + rc.left) / 2, rc.top);		//9 -> 12

	SelectObject(hdc, oldPen);
	DeleteObject(myPen);
}

inline void WorldIsoRender(HDC hdc, RECT rc)
{
	HPEN myPen, oldPen;
	myPen = CreatePen(1, 1, RGB(255, 255, 255));
	oldPen = (HPEN)SelectObject(hdc, myPen);

	rc.left = rc.left + 15;
	rc.top = rc.top;
	rc.right = rc.right + 30;
	rc.bottom = rc.bottom + 30;
	

	LineMake(hdc, (rc.right + rc.left) / 2, rc.top, rc.right, (rc.top + rc.bottom) / 2);
	LineMake(hdc, rc.right, (rc.top + rc.bottom) / 2, (rc.left + rc.right) / 2, rc.bottom);
	LineMake(hdc, (rc.left + rc.right) / 2, rc.bottom, rc.left, (rc.top + rc.bottom) / 2);
	LineMake(hdc, rc.left, (rc.top + rc.bottom) / 2, (rc.right + rc.left) / 2, rc.top);

	SelectObject(hdc, oldPen);
	DeleteObject(myPen);
}

inline std::vector<RECT> makeNinePatch(LPRECT pSour)
{
	int fCenterW = pSour->left + (pSour->right - pSour->left) / 2;
	int fCenterH = pSour->top + (pSour->bottom - pSour->top) / 2;

	int defWidth = (pSour->left + (pSour->right - pSour->left)) / 3;
	int defHeight = (pSour->top + (pSour->bottom - pSour->top)) / 3;

	RECT rcSrcLeftTop = { 0,					0,		defWidth,						defHeight };
	RECT rcSrcTop = { rcSrcLeftTop.right, 0,		rcSrcLeftTop.right + defWidth,	defHeight };
	RECT rcSrcRightTop = { rcSrcTop.right,		0,		rcSrcTop.right + defWidth,		defHeight };

	RECT rcSrcLeftCenter = { 0,						rcSrcLeftTop.bottom,	defWidth,							rcSrcLeftTop.bottom + defHeight };
	RECT rcSrcCenter = { rcSrcLeftCenter.right,	rcSrcTop.bottom,		rcSrcLeftCenter.right + defWidth,	rcSrcTop.bottom + defHeight };
	RECT rcSrcRightCenter = { rcSrcTop.right,			rcSrcTop.top,			rcSrcCenter.right + defWidth,		rcSrcRightTop.bottom + defHeight };

	RECT rcSrcLeftBottom = { 0,							rcSrcLeftCenter.bottom,	defWidth,							rcSrcLeftCenter.bottom + defHeight };
	RECT rcSrcBottom = { rcSrcLeftBottom.right,		rcSrcCenter.bottom,		rcSrcLeftBottom.right + defWidth,	rcSrcCenter.bottom + defHeight };
	RECT rcSrcRightBottom = { rcSrcBottom.right,			rcSrcCenter.bottom,		rcSrcBottom.right + defWidth,		rcSrcCenter.bottom + defHeight };

	std::vector<RECT> result;
	result.emplace_back(rcSrcLeftTop);
	result.emplace_back(rcSrcTop);
	result.emplace_back(rcSrcRightTop);

	result.emplace_back(rcSrcLeftCenter);
	result.emplace_back(rcSrcCenter);
	result.emplace_back(rcSrcRightCenter);

	result.emplace_back(rcSrcLeftBottom);
	result.emplace_back(rcSrcBottom);
	result.emplace_back(rcSrcRightBottom);

	return result;
}

inline std::vector<RECT> makeNinePatch(LPRECT pSour, LPRECT pCenter)
{
	int fCenterW = pCenter->right - pCenter->left;
	int fCneterH = pCenter->bottom - pCenter->top;

	RECT rcSrcLeftTop = { 0,				0,				pCenter->left,		pCenter->top };
	RECT rcSrcTop = { pCenter->left,	0,				pCenter->right,		pCenter->top };
	RECT rcSrcRightTop = { pCenter->right, 0,				pSour->right,		pCenter->top };

	RECT rcSrcLeftCenter = { 0,				pCenter->top,	pCenter->left,		pCenter->bottom };
	RECT rcSrcCenter = { pCenter->left,	pCenter->top,	pSour->right,		pCenter->bottom };
	RECT rcSrcRightCenter = { pCenter->right, pCenter->top,	pSour->right,		pCenter->bottom };

	RECT rcSrcLeftBottom = { 0,				pCenter->bottom, pCenter->left,		pSour->bottom };
	RECT rcSrcBottom = { pCenter->left,	pCenter->bottom, pCenter->right,	pSour->bottom };
	RECT rcSrcRightBottom = { pCenter->right, pCenter->bottom, pSour->right,		pSour->bottom };

	std::vector<RECT> result;
	result.emplace_back(rcSrcLeftTop);
	result.emplace_back(rcSrcTop);
	result.emplace_back(rcSrcRightTop);

	result.emplace_back(rcSrcLeftCenter);
	result.emplace_back(rcSrcCenter);
	result.emplace_back(rcSrcRightCenter);

	result.emplace_back(rcSrcLeftBottom);
	result.emplace_back(rcSrcBottom);
	result.emplace_back(rcSrcRightBottom);

	return result;
}