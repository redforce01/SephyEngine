#pragma once
#include "systemUIDialog.h"


namespace battleMinimapViewNS
{
	const UINT WIDTH = 400;					// width of treeViewer
	const UINT HEIGHT = 250;				// height of treeViewer
	const UINT X = 5;						// Viewer location X
	const UINT Y = HEIGHT - 5;				// Viewer location Y				(g_fScreenHeight - Height - 5)
	const UINT MARGIN = 4;					// text margin from Viewer edge
	const char FONT[] = "Courier New";		// Viewer font
	const int FONT_HEIGHT = 14;				// height of the font in pixels
	const COLOR_ARGB FONT_COLOR = graphicsNS::WHITE;    // color of console text
	const COLOR_ARGB BACK_COLOR = SETCOLOR_ARGB(192, 26, 32, 44);    // backdrop color
}

class CBattle_CameraSystem;
class CBattle_MinimapView : public SystemUIDialog
{
private: // Forward Declaration
	CBattle_CameraSystem* m_pBattleCameraSystem;

private:
	RECT	m_rcMinimap;
	RECT	m_rcCamera;
	float	m_Width;		// ¹Ì´Ï¸Ê UI Width
	float	m_Height;	// ¹Ì´Ï¸Ê UI Height
	float	m_MapWidth;	// ÀüÃ¼ ½ÇÁ¦ ¸Ê Width
	float	m_MapHeight;	// ÀüÃ¼ ½ÇÁ¦ ¸Ê Height
	float	m_CamWidth;	// ¹Ì´Ï¸Ê Ä· Width (RECT ±âÁØ)
	float	m_CamHeight;	// ¹Ì´Ï¸Ê Ä· Height(RECT ±âÁØ)
	bool	m_bIsometric; // Is IsoMetric ?
public:
	CBattle_MinimapView();
	~CBattle_MinimapView();

	virtual bool initialize(Graphics* g, Input* i) override;
	virtual void update(float frameTime) override;
	virtual void render() override;

	//==================================================
	// Setter Functions
	//==================================================

	void clickMinimap();
	void checkMinimapCamRect();
	void setUpCam();
	void setUpCam(float startMapX, float startMapY);


	void setMemoryLinkBattleCameraSystem(CBattle_CameraSystem* pBattleCameraSystem)
	{
		m_pBattleCameraSystem = pBattleCameraSystem;
	}

	//==================================================
	// Setter Functions
	//==================================================
	void setMapWidth(int width)
	{
		m_MapWidth = width;
		setUpCam();
	}
	void setMapHeight(int height)
	{
		m_MapHeight = height;
		setUpCam();
	}
};

