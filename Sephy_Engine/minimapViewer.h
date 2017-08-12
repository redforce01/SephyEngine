#ifndef _MINIMAPVIEWER_H
#define _MINIMAPVIEWER_H

class MinimapViewer;

#include "systemUIDialog.h"

namespace minimapViewerNS
{
	const UINT WIDTH = 400;					// width of treeViewer
	const UINT HEIGHT = 250;				// height of treeViewer
	const UINT X = 5;						// Viewer location X
	const UINT Y = HEIGHT - 5;	// Viewer location Y				(g_fScreenHeight - Height - 5)
	const UINT MARGIN = 4;					// text margin from Viewer edge
	const char FONT[] = "Courier New";		// Viewer font
	const int FONT_HEIGHT = 14;				// height of the font in pixels
	const COLOR_ARGB FONT_COLOR = graphicsNS::WHITE;    // color of console text
	const COLOR_ARGB BACK_COLOR = SETCOLOR_ARGB(192, 26, 32, 44);    // backdrop color
}

class CameraSystem;
class MinimapViewer : public SystemUIDialog
{
private:
	RECT m_rcMinimap;
	RECT m_rcCamera;

	float  m_Width;		// ¹Ì´Ï¸Ê UI Width
	float  m_Height;	// ¹Ì´Ï¸Ê UI Height
	float  m_MapWidth;	// ÀüÃ¼ ½ÇÁ¦ ¸Ê Width
	float  m_MapHeight;	// ÀüÃ¼ ½ÇÁ¦ ¸Ê Height
	float  m_CamWidth;	// ¹Ì´Ï¸Ê Ä· Width (RECT ±âÁØ)
	float  m_CamHeight;	// ¹Ì´Ï¸Ê Ä· Height(RECT ±âÁØ)

	bool m_bInitialized;
	bool m_bIsometric;

	CameraSystem* m_pCameraSystem;
public:
	MinimapViewer();
	~MinimapViewer();

	virtual bool initialize(Graphics* g, Input* i) override;
	virtual void update(float frameTime);
	virtual void render();
	
	void clickMinimap();
	void checkMinimapCamRect();
	void setUpCam();
	void setUpCam(float startMapX, float startMapY);
	void setMemoryLinkCameraSystem(CameraSystem* pCameraSystem) { m_pCameraSystem = pCameraSystem; }
	//========================================
	// Setter Functions
	//========================================
	inline void setMapWidth(int width)
	{
		m_MapWidth = width;
		setUpCam();
	}
	inline void setMapHeight(int height)
	{
		m_MapHeight = height;
		setUpCam();
	}
	inline void setIsoMetric(bool flag)
	{
		m_bIsometric = flag;
	}
};

#endif // !_MINIMAPVIEWER_H
