#ifndef _ENGINEINSPECTORVIEW_H
#define _ENGINEINSPECTORVIEW_H

class EngineInspectorView;

#include "engineWindow.h"
#include "engineButton.h"
#include "engineEditControl.h"


class MapSystem;
class EngineInspectorView : public EngineWindow
{
private:
	EngineButton* saveButton;
	EngineButton* loadButton;
	EngineEditControl* TileNameEdit;
	EngineEditControl* TileLocationEdit;
	EngineEditControl* TileImageSize;

	MapSystem* pMapSys;
public:
	EngineInspectorView();
	~EngineInspectorView();

	virtual bool initialize(EngineInput * input, HWND hParent, HMENU hMenu, int startX, int startY, int width, int height) override;

	// Normal WndProc
	// default setting windows are Using this proc
	virtual LRESULT WndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam) override;
	
	bool saveMapData();
	bool loadMapData();
};

#endif // !_ENGINEINSPECTORVIEW_H
