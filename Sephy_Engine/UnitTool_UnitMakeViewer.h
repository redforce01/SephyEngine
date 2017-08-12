#ifndef _UNITTOOL_UNITMAKE_VIEWER_H
#define _UNITTOOL_UNITMAKE_VIEWER_H
#define WIN32_LEAN_AND_MEAN

class CUnitTool_UnitMakeViewer;

#include "systemUIDialog.h"
#include "UnitTool_UnitListParser.h"
#include "systemButton.h"

namespace unitToolUnitMakeViewerNS
{
	const std::string ERROR_MESSAGE = "Unit Tool MakerViewer Initialize Failed";

	const UINT VIEWER_RELATE_X = 10;
	const UINT VIEWER_RELATE_Y = 10;
	const UINT VIEWER_WIDTH = 300;
	const UINT VIEWER_HEIGHT = 300;

	const UINT LIST_ITEM_BOX_START_X = 20;
	const UINT LIST_ITEM_BOX_START_Y = 15;
	const UINT LIST_ITEM_BOX_WIDTH = 270;
	const UINT LIST_ITEM_BOX_HEIGHT = 18;

	const char	FONT[] = "Courier New";
	const int	FONT_HEIGHT = 14;
	const COLOR_ARGB FONT_COLOR = graphicsNS::WHITE;
	const COLOR_ARGB BACK_COLOR = SETCOLOR_ARGB(192, 26, 32, 44);

	const std::string OK_BUTTON_FILENAME = "OK";
	const std::string CANCEL_BUTTON_FILENAME = "Cancel";
	const UINT OK_BUTTON_X = 20;
	const UINT OK_BUTTON_Y = 270;
	const UINT CANCEL_BUTTON_X = 110;
	const UINT CANCEL_BUTTON_Y = 270;
}

class CUnitTool_ShipDataSetter;
class CUnitTool_UnitMakeViewer : public SystemUIDialog
{
	CUnitTool_ShipDataSetter* m_pUnitToolShipDataSetter;
public:
	void setMemoryLinkShipDataSetter(CUnitTool_ShipDataSetter* pUnitToolShipDataSetter)
	{
		m_pUnitToolShipDataSetter = pUnitToolShipDataSetter;
	}
private:
	CUnitTool_UnitListParser m_unitParser;

	SystemButton m_OKButton;
	SystemButton m_CancelButton;

private:
	std::vector<std::string> m_vShipList;
	std::vector<RECT> m_vListRect;

	int m_nSelectNumber;
public:
	CUnitTool_UnitMakeViewer();
	~CUnitTool_UnitMakeViewer();

	virtual bool initialize(Graphics* g, Input* i) override;
	virtual void update(float frameTime) override;
	virtual void render() override;


	void setupShipList(std::vector<std::string> vArray);

	static void functionOKButton();
	static void functionCancelButton();
};

#endif // !_UNITTOOL_UNITMAKE_VIEWER_H
