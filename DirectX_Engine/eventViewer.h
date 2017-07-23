#ifndef _EVENTVIEWER_H
#define _EVENTVIEWER_H

class EventViewer;

#include "systemUIDialog.h"
#include "collisionBox_Button.h"
#include "collisionCircle_Button.h"
#include "collisionRotatedBox_Button.h"
#include "buildingObserver_Button.h"
#include "buildingRefuel_Button.h"
#include "buildingRepair_Button.h"
#include "weatherFog_Button.h"
#include "weatherRain_Button.h"
#include "gameRespawn_Button.h"
#include "gameStarting_Button.h"

namespace eventViewerNS
{
	const UINT WIDTH = 180;						// width of treeViewer
	const UINT HEIGHT = 300;					// height of treeViewer
	const UINT X = 400 + WIDTH;					// Viewer location X			  (g_fScreenWidth - 400 + Width)
	const UINT Y = 0;							// Viewer location Y
	const UINT MARGIN = 4;						// text margin from Viewer edge
	const char FONT[] = "Courier New";			// Viewer font
	const int FONT_HEIGHT = 14;					// height of the font in pixels
	const COLOR_ARGB FONT_COLOR_INACTIVE = graphicsNS::WHITE;    // color of console text
	const COLOR_ARGB FONT_COLOR_ACTIVE = graphicsNS::GREEN;
	const COLOR_ARGB BACK_COLOR = SETCOLOR_ARGB(192, 26, 32, 44);    // backdrop color
	const std::string EVENT_VIEWER_TITLE = "EVENT OBJECT VIEWER";
}

namespace eventViewerControlNS
{
	const UINT CONTROL_ID_START = 1001;

	const UINT CONTROL_WIDTH = 160;
	const UINT CONTROL_HEIGHT = 20;
	const UINT CONTROL_MARGIN = 5;
	const UINT COLLISION_BOX_BUTTON_X = 5;
	const UINT COLLISION_BOX_BUTTON_Y = 20;
	const UINT COLLISION_CIRCLE_BUTTON_X = 5;
	const UINT COLLISION_CIRCLE_BUTTON_Y = COLLISION_BOX_BUTTON_Y + CONTROL_HEIGHT + CONTROL_MARGIN;
	const UINT COLLISION_ROTATED_BOX_BUTTON_X = 5;
	const UINT COLLISION_ROTATED_BOX_BUTTON_Y = COLLISION_CIRCLE_BUTTON_Y + CONTROL_HEIGHT + CONTROL_MARGIN;
	const UINT BUILDING_REPAIR_BUTTON_X = 5;
	const UINT BUILDING_REPAIR_BUTTON_Y = COLLISION_ROTATED_BOX_BUTTON_Y + CONTROL_HEIGHT + CONTROL_MARGIN;
	const UINT BUILDING_OBSERVOR_BUTTON_X = 5;
	const UINT BUILDING_OBSERVOR_BUTTON_Y = BUILDING_REPAIR_BUTTON_Y + CONTROL_HEIGHT + CONTROL_MARGIN;
	const UINT BUILDING_REFUEL_BUTTON_X = 5;
	const UINT BUILDING_REFUEL_BUTTON_Y = BUILDING_OBSERVOR_BUTTON_Y + CONTROL_HEIGHT + CONTROL_MARGIN;
	const UINT WEATHER_FOG_BUTTON_X = 5;
	const UINT WEATHER_FOG_BUTTON_Y = BUILDING_REFUEL_BUTTON_Y + CONTROL_HEIGHT + CONTROL_MARGIN;
	const UINT WEATHER_RAIN_BUTTON_X = 5;
	const UINT WEATHER_RAIN_BUTTON_Y = WEATHER_FOG_BUTTON_Y + CONTROL_HEIGHT + CONTROL_MARGIN;
	const UINT GAME_RESPAWN_BUTTON_X = 5;
	const UINT GAME_RESPAWN_BUTTON_Y = WEATHER_RAIN_BUTTON_Y + CONTROL_HEIGHT + CONTROL_MARGIN;
	const UINT GAME_STARTING_BUTTON_X = 5;
	const UINT GAME_STARTING_BUTTON_Y = GAME_RESPAWN_BUTTON_Y + CONTROL_HEIGHT + CONTROL_MARGIN;
}

class MapSystem;
class EventViewer : public SystemUIDialog
{
private: // For DragClicked
	bool m_bMaking;
	bool m_bClicked;
	POINT m_ptStartPos;
	POINT m_ptEndPos;

private:
	std::vector<RECT> m_vWorkableRECT;

private: // MapSystem Forward Pointer	
	MapSystem* m_pMapSystem;

private: // EVENT CONTROL BUTTONS
	UINT m_nControlIDs;
	CollisionBox_Button*			m_pCollisionBoxButton;
	CollisionCircle_Button*			m_pCollisionCircleButton;
	CollisionRotatedBox_Button*		m_pCollisionRotatedBoxButton;
	BuildingObserver_Button*		m_pBuildingObserverButton;
	BuildingRefuel_Button*			m_pBuildingRefuelButton;
	BuildingRepair_Button*			m_pBuildingRepairButton;
	WeatherFog_Button*				m_pWeatherFog_Button;
	WeatherRain_Button*				m_pWeatherRain_Button;
	GameRespawn_Button*				m_pGameRespawn_Button;
	GameStarting_Button*			m_pGameStarting_Button;

public:
	EventViewer();
	~EventViewer();

	virtual bool initialize(Graphics* g, Input* i) override;
	virtual void update(float frameTime) override;
	virtual void render() override;

	// =========================================
	// Member Functions
	// =========================================
	void setupEventObject();

	void addWorkableRECT(RECT rc)
	{
		m_vWorkableRECT.emplace_back(rc);
	}
	// =========================================
	// Getter Functions
	// =========================================
	bool getMakeEventModeActive() const
	{
		return m_bMaking;
	}

	// Set Forward Pointer Memory Link Functions
	void setMemoryLinkMapSystem(MapSystem* pMapSystem)
	{
		m_pMapSystem = pMapSystem;
		m_pCollisionBoxButton->setMemoryLinkMapSystem(pMapSystem);
		m_pCollisionCircleButton->setMemoryLinkMapSystem(pMapSystem);
		m_pCollisionRotatedBoxButton->setMemoryLinkMapSystem(pMapSystem);
		m_pBuildingObserverButton->setMemoryLinkMapSystem(pMapSystem);
		m_pBuildingRefuelButton->setMemoryLinkMapSystem(pMapSystem);
		m_pBuildingRepairButton->setMemoryLinkMapSystem(pMapSystem);
		m_pWeatherFog_Button->setMemoryLinkMapSystem(pMapSystem);
		m_pWeatherRain_Button->setMemoryLinkMapSystem(pMapSystem);
		m_pGameRespawn_Button->setMemoryLinkMapSystem(pMapSystem);
		m_pGameStarting_Button->setMemoryLinkMapSystem(pMapSystem);
	}
};

#endif // !_EVENTVIEWER_H
