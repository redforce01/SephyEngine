#ifndef _ENGINEWINDOW_H
#define _ENGINEWINDOW_H
#define WIN32_LEAN_AND_MEAN

class EngineWindow;

#include "engineInput.h"
#include "engineError.h"
#include <memory>

struct WindowStruct
{
	const char*				viewName;
	const char*				className;
	const char*				titleName;
	const char*				propName;
	int						width;
	int						height;
	int						startX;
	int						startY;
	int						basicX;
	int						basicY;
	DWORD					dwstyle;
	HWND					hParent;
	HMENU					hMenu;
	
};

class EngineWindow
{
protected:
	HWND hWndThis;
	HWND hWndParent;
	RECT rcThis;
	bool bChildWindow;
	bool bShowHide;

	EngineInput* pEngineInput;		// Engine View Input* (class from Input.h)
	WindowStruct engineViewWS;		// Engine View WindowStruct about View Information
public:
	EngineWindow();
	~EngineWindow();
	
	// virtual function. PURE( mean : = 0 )
	virtual bool initialize(EngineInput * input, HWND hParent, HMENU hMenu, int startX, int startY, int width, int height) PURE;

	// Normal WndProc
	// default setting windows are Using this proc
	virtual LRESULT WndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam) PURE;

	// Create New WNDCLASSEX
	// if bNewWindow ? 
	// (TRUE)This Functions will Attach to Parent WNDCLASSEX
	// (FALSE) create New WindowClass 
	bool createWindowClass(
		const char * const ClassName,
		EngineInput * input,
		bool bNewWindow,
		WNDCLASSEX wndClassEx, EngineWindow* pEngineWindow);

	bool createNewWindow(WindowStruct &ws, bool bNewWindow = false)
	{ 
		engineViewWS = ws;

		return createNewWindow(
			engineViewWS.titleName, engineViewWS.propName,
			engineViewWS.dwstyle,
			engineViewWS.startX, engineViewWS.startY,
			engineViewWS.width, engineViewWS.height,
			engineViewWS.hParent, engineViewWS.hMenu);
	}

	// create New Window
	bool createNewWindow(
		const char* const TitleName,
		const char* const PropertyName,
		DWORD style,
		int x, int y, int width, int height,
		HWND hParentWnd, HMENU hMenu = NULL);
	
	bool createNewTabControl(
		DWORD dwStyle,
		int x, int y,
		int width, int height,
		HWND hParent,
		HMENU hMenu);

	void windowPosUpdate();
	
	////////////////////////////////////////
	//           Get functions            //
	////////////////////////////////////////

	// Get This->hWndThis (HWND)
	HWND getHwnd() { return hWndThis; }

	RECT getRect() { return rcThis; }

	const char* getViewName() { return engineViewWS.viewName; }

	int getStartX() { return engineViewWS.startX; }

	int getStartY() { return engineViewWS.startY; }

	int getWidth() { return engineViewWS.width; }

	int getHeight() { return engineViewWS.height; }

	int getBasicX() { return engineViewWS.basicX; }

	int getBasicY() { return engineViewWS.basicY; }

	WindowStruct getWindowEx() { return engineViewWS; }

	EngineInput* getEngineInput() { return pEngineInput; }

	////////////////////////////////////////
	//           Set functions            //
	////////////////////////////////////////

	void setStartX(int x) { engineViewWS.startX = x; }

	void setStartY(int y) { engineViewWS.startY = y; }
	
	void setWidth(int width) { engineViewWS.width = width; }

	void setHeight(int height) { engineViewWS.height = height; }

	void setDwStyle(DWORD dwStyle) { engineViewWS.dwstyle = dwStyle; }

	// Set this hWnd->ShowWindow Show/Hide Function
	// this->bShowHide ? ShowWindow(hWndThis, SW_SHOW) : ShowWindow(hWndThis, SW_HIDE)
	void setShowHide();

};

#endif // !_ENGINEWINDOW_H
