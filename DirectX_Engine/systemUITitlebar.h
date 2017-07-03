#ifndef _SYSTEMUITITLEBAR_H
#define _SYSTEMUITITLEBAR_H

class SystemUITitlebar;

#include <string>
#include "systemUIDialog.h"
#include "graphics.h"
#include "input.h"

namespace systemUITitleBarNS
{
	const UINT BAISC_TITLEBAR_BUTTON_WIDTH= 30;
	const UINT BASIC_TITLEBAR_HEIGHT = 35;

	const std::string UI_IMAGE_NAME = "UIButton";
	const std::string MAXIMIZE_IMAGE_NAME = "MaximizeButton";
	const std::string MINIMIZE_IMAGE_NAME = "MinimizeButton";
	const std::string CLOSE_IMAGE_NAME = "CloseButton";

	const UINT CLOSE_WIDTH = 28;
	const UINT CLOSE_HEIGHT = 28;
	const UINT MAXIMIZE_WIDTH = 28;
	const UINT MAXIMIZE_HEIGHT = 28;
	const UINT MINIMIZE_WIDTH = 28;
	const UINT MINIMIZE_HEIGHT = 28;
	const UINT TITLE_UI_WIDTH = 32;
	const UINT TITLE_UI_HEIGHT = 28;
}

class SystemUITitlebar
{
private:
	Graphics* m_pGraphics;
	Input* m_pInput;
	SystemUIDialog* m_pDialog;
	Image* m_pFrameIcon;
	Image* m_pMinMaxButton;
	Image* m_pCloseButton;

	std::string m_strTitleName;
	int m_x, m_y;
	int m_width, m_height;
	RECT m_rcBoundingBox;
	RECT m_rcTitle;
	RECT m_rcMinimizeButton;
	RECT m_rcCloseButton;
	bool m_bMinimize;
	bool m_bVisible;
public:
	SystemUITitlebar();
	virtual ~SystemUITitlebar();

	bool initializeTitlebar(Graphics* g, Input* i, SystemUIDialog* pDialog, std::string title);
	void update(float frameTime);
	void render();
	
	void setMinimize();
	void setShowHide()
	{
		m_bVisible = !m_bVisible;
	}
};

#endif // !_SYSTEMUITITLEBAR_H
