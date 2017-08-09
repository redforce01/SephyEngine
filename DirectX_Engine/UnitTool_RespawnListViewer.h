#ifndef _UNITTOOL_RESPAWN_LIST_VIEWER_H
#define _UNITTOOL_RESPAWN_LIST_VIEWER_H
#define WIN32_LEAN_AND_MEAN

class CUnitTool_RespawnListViewer;

#include "systemUIDialog.h"
#include "systemButton.h"

namespace unitToolRespawnListViewerNs
{
	const std::string ERROR_MESSAGE = "Unit Tool Respawn Viewer Initialize Failed";
	const char	FONT[] = "Courier New";
	const int	FONT_HEIGHT = 14;
	const COLOR_ARGB FONT_COLOR = graphicsNS::WHITE;
	const COLOR_ARGB BACK_COLOR = SETCOLOR_ARGB(192, 26, 32, 44);
	const COLOR_ARGB PLAYER_LIST_COLOR = graphicsNS::BLUE;
	const COLOR_ARGB COMPUTER_LIST_COLOR = graphicsNS::RED;

	const UINT VIEWER_X = 10;
	const UINT VIEWER_Y = 310;
	const UINT VIEWER_WIDTH = 300;
	const UINT VIEWER_HEIGHT = 400;

	const UINT ITEM_BOX_RELATE_START_Y = 10;
	const UINT ITEM_BOX_TAG_NUMBER_RELATE_X = 10;
	const UINT ITEM_BOX_TAG_NUMBER_RELATE_WIDTH = 40;
	const UINT ITEM_BOX_SHIP_TYPE_RELATE_X = ITEM_BOX_TAG_NUMBER_RELATE_X + ITEM_BOX_TAG_NUMBER_RELATE_WIDTH;
	const UINT ITEM_BOX_SHIP_TYPE_RELATE_WIDTH = 40;
	const UINT ITEM_BOX_SHIP_NAME_RELATE_X = ITEM_BOX_SHIP_TYPE_RELATE_X + ITEM_BOX_SHIP_TYPE_RELATE_WIDTH;
	const UINT ITEM_BOX_SHIP_NAME_RELATE_WIDTH = 200;
	const UINT ITEM_BOX_HEIGHT = 15;

	const UINT PLAYER_LIST_BOX_RELATE_X = 10;
	const UINT PLAYER_LIST_BOX_RELATE_Y = 25;
	const UINT COMPUTER_LIST_BOX_RELATE_X = 10;
	const UINT COMPUTER_LIST_BOX_RELATE_Y = 220;
	const UINT LIST_BOX_WIDTH = 280;
	const UINT LIST_BOX_HEIGHT = 170;

	const std::string PLAYER_LIST_TITLE = "Respawned Player Ship List";
	const std::string COMPUTER_LIST_TITLE = "Respawned Computer Ship List";
	const UINT PLAYER_LIST_TITLE_RECT_X = 10;
	const UINT PLAYER_LIST_TITLE_RECT_Y = 5;
	const UINT COMPUTER_LIST_TITLE_RECT_X = 10;
	const UINT COMPUTER_LIST_TITLE_RECT_Y = 200;
	const UINT LIST_TITLE_WIDTH = 280;
	const UINT LIST_TITLE_HEIGHT = 15;
}

struct tagRespawnShipInfo
{
	int tagNumber;
	std::string shipName;
	std::string shipType;
};

class CUnitTool_UnitControlSystem;
class CUnitTool_RespawnListViewer : public SystemUIDialog
{
private:
	CUnitTool_UnitControlSystem* m_pUnitControlSystem;

public:
	void setMemoryLinkUnitControlSystem(CUnitTool_UnitControlSystem* pUnitControlSystem)
	{
		m_pUnitControlSystem = pUnitControlSystem;
	}

private:
	std::vector<tagRespawnShipInfo> m_vPlayerUnitList;
	std::vector<tagRespawnShipInfo> m_vComputerUnitList;
	RECT m_rcPlayerInfoRect;
	RECT m_rcComputerInfoRect;
	RECT m_rcPlayerInfoTitle;
	RECT m_rcComputerInfoTitle;

	SystemButton m_ScrollUpButton;
	SystemButton m_ScrollDownButton;
public:
	CUnitTool_RespawnListViewer();
	~CUnitTool_RespawnListViewer();

	virtual bool initialize(Graphics* g, Input* i) override;
	virtual void update(float frameTime) override;
	virtual void render() override;

	//===================================================
	// Member Functions
	//===================================================

	void addPlayerShipInfo(tagRespawnShipInfo shipInfo)
	{
		shipInfo.tagNumber = m_vPlayerUnitList.size();
		m_vPlayerUnitList.emplace_back(shipInfo);
	}
	void addComputerShipInfo(tagRespawnShipInfo shipInfo)
	{		
		shipInfo.tagNumber = m_vComputerUnitList.size();
		m_vComputerUnitList.emplace_back(shipInfo);
	}

	void resetShipList()
	{
		m_vPlayerUnitList.clear();
		m_vComputerUnitList.clear();
	}
};

#endif // !_UNITTOOL_RESPAWN_LIST_VIEWER_H
