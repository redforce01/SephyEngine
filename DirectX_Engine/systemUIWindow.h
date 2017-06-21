#ifndef _SYSTEMUIWINDOW_H
#define _SYSTEMUIWINDOW_H

class SystemUIWindow;


class SystemUIWindow
{
protected:
	Graphics* pGraphics;
	Input* pInput;
	TextDX dxFont;

	float x, y;
	float width, height;
	float margin;

	RECT rcWindow;
	VertexC vtx[4];
	LP_VERTEXBUFFER vertexBuffer;

	COLOR_ARGB  fontColor;              // font color (a,r,g,b)
	COLOR_ARGB  backColor;              // background color (a,r,g,b)

	bool initialized;
	bool visible;
public:
	SystemUIWindow();
	~SystemUIWindow();

	virtual bool initialize(Graphics* g, Input* i, int x, int y, int w, int h, int m);
	virtual void update(float frameTime) PURE;
	virtual void render() PURE;

	
};

#endif // !_SYSTEMUIWINDOW_H
