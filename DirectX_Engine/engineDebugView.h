#ifndef _ENGINEDEBUGVIEW_H
#define _ENGINEDEBUGVIEW_H
#define WIN32_LEAN_AND_MEAN

class EngineDebugView;

#include <string>
#include <map>

class EngineDebugView
{
private:
	typedef std::map<std::string, std::string> MessageMap;

protected:
	std::string strViewName;		// viewname
	Graphics* pGraphics;				// graphics system
	Input* pInput;					// input system
	TextDX		dxFont;				// DirectX font
	float		posX, posY;			// console location (dynamic)
	float		width, height;		// view width, view height
	float		marginSize;			// view margin
	int         rows;				// number of rows of text that will fit on console
	MessageMap	message;			// message map
	int			messageMax;			// message map MAX Count
	RECT        textRect;			// text rectangle
	RECT		viewRect;			// view rectangle
	COLOR_ARGB  fontColor;			// font color (a,r,g,b)
	COLOR_ARGB  backColor;			// background color (a,r,g,b)
	VertexC vtx[4];					// vertex data for background
	LP_VERTEXBUFFER vertexBuffer;	// buffer to hold vertex data
	int         scrollAmount;		// number of lines to scroll the display up
	bool        initialized;		// true when initialized successfully
	bool        visible;			// true to display
		
public:
	EngineDebugView();
	~EngineDebugView();

	virtual bool initialize(
		std::string viewName, Graphics* g, Input* i,
		float x, float y, float w, float h,
		float margin, int msgMax);
	virtual void update(float frameTime);
	virtual void render();

	void draw();
	void showHide();
	void showHide(bool flag);

	void onLostDevice();
	void onResetDevice();

	
	void addMessage(const std::string &key, const std::string &str);
	void setMessageMax(int maxSize) { messageMax = maxSize; }
	
	std::string getViewName() { return strViewName; }

};

#endif // !_ENGINEDEBUGVIEW_H
