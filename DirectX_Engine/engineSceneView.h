#ifndef _ENGINESCENEVIEW_H
#define _ENGINESCENEVIEW_H

class EngineSceneView;

#include "engineWindow.h"
#include "engineResourceView.h"
#include "engineInspectorView.h"


class EngineSceneView : public EngineWindow
{
public:
	EngineSceneView();
	~EngineSceneView();

	virtual bool initialize(EngineInput * input, HWND hParent, HMENU hMenu, int startX, int startY, int width, int height) override;

	// Normal WndProc
	// default setting windows are Using this proc
	virtual LRESULT WndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam) override;
};

#endif // !_ENGINESCENEVIEW_H
