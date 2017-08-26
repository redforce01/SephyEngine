#ifndef _SYSTEMUIDIALOG_H
#define _SYSTEMUIDIALOG_H

class SystemUIDialog;

#include "graphics.h"
#include "input.h"

namespace systemUIDialogNS
{
	const COLOR_ARGB basicFontColor = graphicsNS::WHITE;
	const COLOR_ARGB basicBackColor = SETCOLOR_ARGB(192, 128, 128, 128);
}

class SystemUIDialog
{
protected:
	Graphics* m_pGraphics;
	Input* m_pInput;
	TextDX m_dxFont;
	
	float m_x, m_y;
	float m_width, m_height;
	float m_margin;
	RECT m_rcBoundingBox;
	bool m_bVisible;
	bool m_bInitialized;

	// Vertex & Background
	VertexC vtx[4];
	LP_VERTEXBUFFER vertexBuffer;
	COLOR_ARGB  fontColor;              // font color (a,r,g,b)
	COLOR_ARGB  backColor;              // background color (a,r,g,b)
private:
	bool m_bMouseOver;
	bool m_bHasFocus;
	bool m_bDrawBorder;
public:
	SystemUIDialog();
	virtual ~SystemUIDialog();

	virtual bool initialize(Graphics* g, Input* i) PURE;
	virtual void update(float frameTime);
	virtual void render();

// protected Member Functions
protected:
	bool initializeDialog(Graphics* g, Input* i, int x, int y, int w, int h, int m = 0);
	bool vertexSetup(int x, int y, int w, int h);

private:
	void setUpRect()
	{
		m_rcBoundingBox = RectMake(m_x, m_y, m_width, m_height);
	}
public:

	void moveDialogX(float distance)
	{
		m_x += distance;
		vertexSetup(m_x, m_y, m_width, m_height);
		setUpRect();
	}
	void moveDialogY(float distance)
	{
		m_y += distance;
		vertexSetup(m_x, m_y, m_width, m_height);
		setUpRect();
	}

	//=====================================
	// Setter Functions
	//=====================================	
	void setDialogPos(int startX, int startY)
	{
		m_x = startX, m_y = startY;
		vertexSetup(m_x, m_y, m_width, m_height);
		setUpRect();
	}
	void setDialogX(float x)
	{
		m_x = x;
		vertexSetup(m_x, m_y, m_width, m_height);
		setUpRect();
	}
	void setDialogY(float y)
	{
		m_y = y;
		vertexSetup(m_x, m_y, m_width, m_height);
		setUpRect();
	}
	void setDialogSize(int w, int h)
	{
		m_width = w, m_height = h;
		vertexSetup(m_x, m_y, m_width, m_height);
		setUpRect();
	}
	void setDialogWidth(float width)
	{
		m_width = width;
		vertexSetup(m_x, m_y, m_width, m_height);
		setUpRect();
	}
	void setDialogHeight(float height)
	{
		m_height = height;
		vertexSetup(m_x, m_y, m_width, m_height);
		setUpRect();
	}
	void setDialogMargin(int m)
	{
		m_margin = m;
	}
	void setDialogBackColor(COLOR_ARGB color)
	{
		backColor = color;
	}
	void setDialogFontColor(COLOR_ARGB color)
	{
		fontColor = color;
	}
	void setVisible(bool v)
	{
		m_bVisible = v;
	}
	void setShowHide()
	{
		m_bVisible = !m_bVisible;
	}
	void setOnFocus(bool b)
	{
		m_bHasFocus = b;
	}
	void setFont(TextDX font)
	{
		m_dxFont = font;
	}
	void setDrawBorder(bool bBorder)
	{
		m_bDrawBorder = bBorder;
	}
	//=====================================
	// Getter Functions
	//=====================================
	POINT getDialogPos() const
	{
		return PointMake(m_x, m_y);
	}
	float getDialogX() const
	{
		return m_x;
	}
	float getDialogY() const
	{
		return m_y;
	}
	float getDialogCenterX() const
	{
		return m_x + (m_width / 2);
	}
	float getDialogCenterY() const
	{
		return m_y + (m_height / 2);
	}
	float getDialogWidth() const
	{
		return m_width;
	}
	float getDialogHeight() const
	{
		return m_height;
	}
	float getDialogMargin() const
	{
		return m_margin;
	}
	bool getMouseOver() const
	{
		return m_bMouseOver;
	}
	bool getVisible() const
	{
		return m_bVisible;
	}
	RECT getDialogRECT() const
	{
		return m_rcBoundingBox;
	}
	bool getOnFocus() const
	{
		return m_bHasFocus;
	}
	bool getOnDrawBorder() const
	{
		return m_bDrawBorder;
	}
};

#endif // !_SYSTEMUIDIALOG_H