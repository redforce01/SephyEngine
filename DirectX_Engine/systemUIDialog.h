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
	Graphics* pGraphics;
	Input* pInput;
	TextDX dxFont;

	int m_x, m_y;
	int m_width, m_height;
	int m_margin;

	RECT m_rc;

	VertexC vtx[4];
	LP_VERTEXBUFFER vertexBuffer;
	COLOR_ARGB  fontColor;              // font color (a,r,g,b)
	COLOR_ARGB  backColor;              // background color (a,r,g,b)

private:
	bool m_bMouseOver;
public:
	SystemUIDialog();
	~SystemUIDialog();

	virtual bool initialize(Graphics* g, Input* i) PURE;
	virtual void update(float frameTime);
	virtual void render();

	//=====================================
	// Member Functions
	//=====================================	
	bool initialize(Graphics* g, Input* i, int x, int y, int w, int h, int m);
	bool vertexSetup(int x, int y, int w, int h);

	//=====================================
	// Setter Functions
	//=====================================	
	inline void setDialogPos(int startX, int startY)
	{
		m_x = startX, m_y = startY;
	}

	inline void setDialogSize(int w, int h)
	{
		m_width = w, m_height = h;
	}

	inline void setDialogMargin(int m)
	{
		m_margin = m;
	}

	inline void setDialogBackColor(COLOR_ARGB color)
	{
		backColor = color;
	}

	inline void setDialogFontColor(COLOR_ARGB color)
	{
		fontColor = color;
	}
	//=====================================
	// Getter Functions
	//=====================================
	inline POINT getDialogPos() const
	{
		return PointMake(m_x, m_y);
	}

	inline int getDialogWidth() const
	{
		return m_width;
	}

	inline int getDialogHeight() const
	{
		return m_height;
	}

	inline int getDialogMargin() const
	{
		return m_margin;
	}

	inline bool getMouseOver() const
	{
		return m_bMouseOver;
	}
};

#endif // !_SYSTEMUIDIALOG_H