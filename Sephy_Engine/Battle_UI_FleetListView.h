#ifndef _BATTLE_UI_FLEETLISTVIEW_H
#define _BATTLE_UI_FLEETLISTVIEW_H
#define WIN32_LEAN_AND_MEAN

class CBattle_UI_FleetListView;

#include "systemButton.h"
#include "systemUIDialog.h"

namespace battleFleetListViewNS
{
	const std::string ERROR_MESSAGE = "Battle UI FleetListView Initialize Failed";
	//======================================================================
	const float FLEET_VIEW_X						= 10;
	const float FLEET_VIEW_Y						= 10;
	const float FLEET_VIEW_ACTIVE_WIDTH				= 300;
	const float FLEET_VIEW_ACTIVE_HEIGHT			= 300;
	const float FLEET_VIEW_INACTIVE_WIDTH			= 55;
	const float FLEET_VIEW_INACTIVE_HEIGHT			= 18;
	const std::string FLEET_BUTTON_FILENAME			= "FleetButton";
	const float FLEET_BUTTON_X						= 15;
	const float FLEET_BUTTON_Y						= 15;
	//======================================================================
	const std::string SEND_BUTTON_FILENAME = "Send";
	const float SEND_BUTTON_X = FLEET_VIEW_X + FLEET_VIEW_ACTIVE_WIDTH - 100;
	const float SEND_BUTTON_Y = FLEET_VIEW_Y + FLEET_VIEW_ACTIVE_HEIGHT - 30;
	//======================================================================
	const std::string CLEAR_BUTTON_FILENAME = "Clear";
	const float CLEAR_BUTTON_X = FLEET_VIEW_X + FLEET_VIEW_ACTIVE_WIDTH - 50;
	const float CLEAR_BUTTON_Y = FLEET_VIEW_Y + FLEET_VIEW_ACTIVE_HEIGHT - 30;
	//======================================================================
	const std::string CLOSE_BUTTON_FILENAME = "Close";
	const float CLOSE_BUTTON_X = FLEET_VIEW_X + FLEET_VIEW_ACTIVE_WIDTH - 40;
	const float CLOSE_BUTTON_Y = FLEET_VIEW_Y + 5;
	//======================================================================
	const std::string PAGE_UP_BUTTON_FILENAME	= "ScrollUp";
	const std::string PAGE_DOWN_BUTTON_FILENAME = "ScrollDown";
	const float PAGE_UP_BUTTON_RELATE_X = 0;
	const float PAGE_UP_BUTTON_RELATE_Y = 0;
	const float PAGE_DOWN_BUTTON_RELATE_X = 0;
	const float PAGE_DOWN_BUTTON_RELATE_Y = 0;
	//======================================================================
	const float FLEET_LIST_GUIDE_START_X = FLEET_VIEW_X;
	const float FLEET_LIST_GUIDE_START_Y = FLEET_VIEW_Y + FLEET_VIEW_INACTIVE_HEIGHT + 10;
	const float FLEET_LIST_GUIDE_HEIGHT = 16;
	const std::string FLEET_LIST_GUIDE_SHIPNAME		= "NAME";
	const std::string FLEET_LIST_GUIDE_SHIPCOUNT	= "COUNT";
	const std::string FLEET_LIST_GUIDE_SHIPPHASE	= "PHASE";
	const std::string FLEET_LIST_GUIDE_SHIPTYPE		= "TYPE";
	const float FLEET_LIST_GUIDE_TYPE_WIDTH_RATE	= 1.5;
	const float FLEET_LIST_GUIDE_NAME_WIDTH_RATE	= 5;
	const float FLEET_LIST_GUIDE_PHASE_WIDTH_RATE	= 1.5;
	const float FLEET_LIST_GUIDE_COUNT_WIDTH_RATE	= 2;
	//======================================================================
	const float FLEET_LIST_ITEM_START_X				= FLEET_VIEW_X;
	const float FLEET_LIST_ITEM_START_Y				= 60;
	const float FLEET_LIST_ITEM_MARGIN				= 5;
	const float FLEET_LIST_ITEM_WIDTH				= FLEET_VIEW_ACTIVE_WIDTH - (FLEET_LIST_ITEM_MARGIN * 2);
	const float FLEET_LIST_ITEM_HEIGHT				= 16;
	const float FLEET_LIST_ITEM_PRINT_BOTTOM		= FLEET_VIEW_Y + FLEET_VIEW_ACTIVE_HEIGHT - 40;
	//======================================================================
	const char FONT[] = "Courier New";		// Viewer font
	const int FONT_HEIGHT = 14;				// height of the font in pixels
	const COLOR_ARGB FONT_COLOR = graphicsNS::WHITE;    // color of console text
	const COLOR_ARGB BACK_COLOR_ACTIVE = SETCOLOR_ARGB(192, 26, 32, 44);    // backdrop color
	const COLOR_ARGB BACK_COLOR_DEACTIVE = SETCOLOR_ARGB(255, 26, 32, 44);
}

struct tagFleetItem
{
	float x, y;
	float width, height;
	RECT rcType;
	RECT rcName;
	RECT rcPhase;
	RECT rcCount;
	std::string shipName;
	std::string shipType;
	int shipCount;
	int shipPhase;
	RECT rcTotal;

	tagFleetItem()
	{
		x = y = 0.f;
		width = height = 0.f;
		rcType = { 0, };
		rcName = { 0, };
		rcPhase = { 0, };
		rcCount = { 0, };
		rcTotal = { 0, };
		shipPhase = 0;
		shipCount = 1;
	}
	tagFleetItem(std::string strShipType, std::string strShipName, int nShipPhase)
	{
		x = y = 0.f;
		width = height = 0.f;
		rcType = { 0, };
		rcName = { 0, };
		rcPhase = { 0, };
		rcCount = { 0, };
		rcTotal = { 0, };
		shipType = strShipType;
		shipName = strShipName;
		shipPhase = nShipPhase;
		shipCount = 1;
	}
};

class CBattle_UnitSystem;
class CBattle_UI_FleetListView : public SystemUIDialog
{
	typedef std::vector<tagFleetItem*> FLEET_LIST_ITEM;

private:
	Graphics*	m_pGraphics;
	Input*		m_pInput;

private:
	FLEET_LIST_ITEM m_vFleetListItems;
	std::string		m_strSelectItemName;
	int				m_nSelectItemPhase;
	int				m_nSelectItemCount;
	//===========================================
	std::string m_strGuideShipType;
	std::string m_strGuideShipName;
	std::string m_strGuideShipPhase;
	std::string m_strGuideShipCount;
	RECT		m_rcGuideShipType;
	RECT		m_rcGuideShipName;
	RECT		m_rcGuideShipPhase;
	RECT		m_rcGuideShipCount;
	int			m_nSelectItemNumber;
	//===========================================
private:
	bool		m_bInitialized;
	bool		m_bActive;

private:
	SystemButton* m_pFleetButton;	
	SystemButton* m_pSendButton;
	SystemButton* m_pClearButton;
	SystemButton* m_pCloseButton;

private:
	int m_nItemStart;
	int m_nItemEnd;
	SystemButton* m_pPageUpButton;
	SystemButton* m_pPageDownButton;
public:
	CBattle_UI_FleetListView();
	~CBattle_UI_FleetListView();

	virtual bool initialize(Graphics* g, Input* i) override;
	virtual void update(float frameTime) override;
	virtual void render() override;

	//=================================================
	// Member Functions
	//=================================================

private: // Button static Function
	static void functionFleetButton();
	static void functionSendButton();
	static void functionClearButton();
	static void functionCloseButton();

	static void functionPageUpButton();
	static void functionPageDownButton();
public:
	void addShipToFleetList(std::string strShipType, std::string strShipName, int nPhase);

private: // Forward Declaration
	CBattle_UnitSystem* m_pBattleUnitSystem;

public:
	void setMemoryLinkBattleUnitSystem(CBattle_UnitSystem* pBattleUnitSystem)
	{
		m_pBattleUnitSystem = pBattleUnitSystem;
	}


	//=================================================
	// Getter Functions
	//=================================================

	FLEET_LIST_ITEM getFleetListItems() const
	{
		return m_vFleetListItems;
	}

	std::string getSelectItemName() const
	{
		return m_strSelectItemName;
	}

	int getSelectItemPhase() const
	{
		return m_nSelectItemPhase;
	}

	int getSelectItemCount() const
	{
		return m_nSelectItemCount;
	}

};

#endif // !_BATTLE_UI_FLEETLISTVIEW_H
