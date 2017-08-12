#ifndef _ENGINERESOURCEVIEW_H
#define _ENGINERESOURCEVIEW_H

class EngineResourceView;

#include "engineWindow.h"
#include <vector>
#include <string>

class EngineResourceView : public EngineWindow
{
private:
	HIMAGELIST treeImages;
	HWND hTree;
public:
	EngineResourceView();
	~EngineResourceView();

	virtual bool initialize(EngineInput * input, HWND hParent, HMENU hMenu, int startX, int startY, int width, int height) override;

	// Normal WndProc
	// default setting windows are Using this proc
	virtual LRESULT WndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam) override;
};

#endif // !_ENGINERESOURCEVIEW_H
