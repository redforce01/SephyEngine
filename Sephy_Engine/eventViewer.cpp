#include "stdafx.h"
#include "eventViewer.h"
#include "mapSystem.h"

EventViewer::EventViewer()
{
	fontColor = eventViewerNS::FONT_COLOR_INACTIVE;
	backColor = eventViewerNS::BACK_COLOR;
	m_bMaking = false;
	m_bClicked = false;
	m_ptStartPos = { 0, 0 };
	m_ptEndPos = { 0, 0 };
	m_nControlIDs = eventViewerControlNS::CONTROL_ID_START;
}


EventViewer::~EventViewer()
{
	SAFE_DELETE(m_pCollisionBoxButton);
	SAFE_DELETE(m_pCollisionCircleButton);
	SAFE_DELETE(m_pCollisionRotatedBoxButton);
	SAFE_DELETE(m_pBuildingObserverButton);
	SAFE_DELETE(m_pBuildingRefuelButton);
	SAFE_DELETE(m_pBuildingRepairButton);
	SAFE_DELETE(m_pWeatherFog_Button);
	SAFE_DELETE(m_pWeatherRain_Button);
	SAFE_DELETE(m_pGameRespawn_Button);
	SAFE_DELETE(m_pGameStarting_Button);
}

bool EventViewer::initialize(Graphics * g, Input * i)
{
	bool success = false;
	try
	{
		success = SystemUIDialog::initializeDialog(g, i, g_fScreenWidth - eventViewerNS::X, eventViewerNS::Y,
			eventViewerNS::WIDTH, eventViewerNS::HEIGHT, eventViewerNS::MARGIN);
		if (success == false)
			throw("Event Viewer SystemUIDialog Initialized Failed");

		success = m_dxFont.initialize(g, eventViewerNS::FONT_HEIGHT, false, false, eventViewerNS::FONT);
		if (success == false)
			throw("EventViewer DxFont initialized Failed");
		
#pragma region EVENT OBJECT VIEWER CONTROL INITIALIZE
		
		m_pCollisionBoxButton = new CollisionBox_Button;
		m_pCollisionBoxButton->initialize(g, i, m_nControlIDs++, this,
			eventViewerControlNS::COLLISION_BOX_BUTTON_X,
			eventViewerControlNS::COLLISION_BOX_BUTTON_Y,
			eventViewerControlNS::CONTROL_WIDTH,
			eventViewerControlNS::CONTROL_HEIGHT,
			eventViewerControlNS::CONTROL_MARGIN);

		m_pCollisionCircleButton = new CollisionCircle_Button;
		m_pCollisionCircleButton->initialize(g, i, m_nControlIDs++, this,
			eventViewerControlNS::COLLISION_CIRCLE_BUTTON_X,
			eventViewerControlNS::COLLISION_CIRCLE_BUTTON_Y,
			eventViewerControlNS::CONTROL_WIDTH,
			eventViewerControlNS::CONTROL_HEIGHT,
			eventViewerControlNS::CONTROL_MARGIN);
		
		m_pCollisionRotatedBoxButton = new CollisionRotatedBox_Button;
		m_pCollisionRotatedBoxButton->initialize(g, i, m_nControlIDs++, this,
			eventViewerControlNS::COLLISION_ROTATED_BOX_BUTTON_X,
			eventViewerControlNS::COLLISION_ROTATED_BOX_BUTTON_Y,
			eventViewerControlNS::CONTROL_WIDTH,
			eventViewerControlNS::CONTROL_HEIGHT,
			eventViewerControlNS::CONTROL_MARGIN);

		m_pBuildingObserverButton = new BuildingObserver_Button;
		m_pBuildingObserverButton->initialize(g, i, m_nControlIDs++, this,
			eventViewerControlNS::BUILDING_OBSERVOR_BUTTON_X,
			eventViewerControlNS::BUILDING_OBSERVOR_BUTTON_Y,
			eventViewerControlNS::CONTROL_WIDTH,
			eventViewerControlNS::CONTROL_HEIGHT,
			eventViewerControlNS::CONTROL_MARGIN);

		m_pBuildingRefuelButton = new BuildingRefuel_Button;
		m_pBuildingRefuelButton->initialize(g, i, m_nControlIDs++, this,
			eventViewerControlNS::BUILDING_REFUEL_BUTTON_X,
			eventViewerControlNS::BUILDING_REFUEL_BUTTON_Y,
			eventViewerControlNS::CONTROL_WIDTH,
			eventViewerControlNS::CONTROL_HEIGHT,
			eventViewerControlNS::CONTROL_MARGIN);

		m_pBuildingRepairButton = new BuildingRepair_Button;
		m_pBuildingRepairButton->initialize(g, i, m_nControlIDs++, this,
			eventViewerControlNS::BUILDING_REPAIR_BUTTON_X,
			eventViewerControlNS::BUILDING_REPAIR_BUTTON_Y,
			eventViewerControlNS::CONTROL_WIDTH,
			eventViewerControlNS::CONTROL_HEIGHT,
			eventViewerControlNS::CONTROL_MARGIN);


		m_pWeatherFog_Button = new WeatherFog_Button;
		m_pWeatherFog_Button->initialize(g, i, m_nControlIDs++, this,
			eventViewerControlNS::WEATHER_FOG_BUTTON_X,
			eventViewerControlNS::WEATHER_FOG_BUTTON_Y,
			eventViewerControlNS::CONTROL_WIDTH,
			eventViewerControlNS::CONTROL_HEIGHT,
			eventViewerControlNS::CONTROL_MARGIN);

		m_pWeatherRain_Button = new WeatherRain_Button;
		m_pWeatherRain_Button->initialize(g, i, m_nControlIDs++, this,
			eventViewerControlNS::WEATHER_RAIN_BUTTON_X,
			eventViewerControlNS::WEATHER_RAIN_BUTTON_Y,
			eventViewerControlNS::CONTROL_WIDTH,
			eventViewerControlNS::CONTROL_HEIGHT,
			eventViewerControlNS::CONTROL_MARGIN);

		m_pGameRespawn_Button = new GameRespawn_Button;
		m_pGameRespawn_Button->initialize(g, i, m_nControlIDs++, this,
			eventViewerControlNS::GAME_RESPAWN_BUTTON_X,
			eventViewerControlNS::GAME_RESPAWN_BUTTON_Y,
			eventViewerControlNS::CONTROL_WIDTH,
			eventViewerControlNS::CONTROL_HEIGHT,
			eventViewerControlNS::CONTROL_MARGIN);
		
		m_pGameStarting_Button = new GameStarting_Button;
		m_pGameStarting_Button->initialize(g, i, m_nControlIDs++, this,
			eventViewerControlNS::GAME_STARTING_BUTTON_X,
			eventViewerControlNS::GAME_STARTING_BUTTON_Y,
			eventViewerControlNS::CONTROL_WIDTH,
			eventViewerControlNS::CONTROL_HEIGHT,
			eventViewerControlNS::CONTROL_MARGIN);
#pragma endregion
		
	}
	catch (...)
	{
		MessageBox(g_hWndEngine, "EventViewer Initialize Failed", "Error", MB_OK);
	}

	return success;
}

void EventViewer::update(float frameTime)
{
	if (getVisible() == false)
		return;

	SystemUIDialog::update(frameTime);
	
	// ========================================================
	// Event Viewer Controls Update (Button)
	m_pCollisionBoxButton->update(frameTime);
	m_pCollisionCircleButton->update(frameTime);
	m_pCollisionRotatedBoxButton->update(frameTime);
	m_pBuildingObserverButton->update(frameTime);
	m_pBuildingRefuelButton->update(frameTime);
	m_pBuildingRepairButton->update(frameTime);
	m_pWeatherFog_Button->update(frameTime);
	m_pWeatherRain_Button->update(frameTime);
	m_pGameRespawn_Button->update(frameTime);
	m_pGameStarting_Button->update(frameTime);
	// ========================================================
	// Event Object Make Mode Check
	if (m_pCollisionBoxButton->getActive()
		|| m_pCollisionCircleButton->getActive()
		|| m_pCollisionRotatedBoxButton->getActive()
		|| m_pBuildingObserverButton->getActive()
		|| m_pBuildingRefuelButton->getActive()
		|| m_pBuildingRepairButton->getActive()
		|| m_pWeatherFog_Button->getActive()
		|| m_pWeatherRain_Button->getActive()
		|| m_pGameRespawn_Button->getActive()
		|| m_pGameStarting_Button->getActive())
	{
		m_bMaking = true;
	}
	else
		m_bMaking = false;
	// ========================================================

	// m_bMaking == false ? return
	if (m_bMaking == false)
		return;

	// ========================================================
	// Event Object Making
	if (m_pInput->getMouseLButton())
	{		
		if (m_bClicked == false)
		{
			for (auto iter : m_vWorkableRECT)
			{
				if (PtInRect(&iter, m_pInput->getMousePt()))
					return;
			}

			m_bClicked = true;
			m_ptStartPos = m_pInput->getMousePt();
			m_ptEndPos = m_pInput->getMousePt();
		}
		else
		{
			m_ptEndPos = m_pInput->getMousePt();
		}
	}
	else
	{
		if (m_bClicked)
		{
			setupEventObject();
			m_ptStartPos = { 0, 0 };
			m_ptEndPos = { 0, 0 };
			m_bClicked = false;
		}
	}
	// ========================================================
}

void EventViewer::render()
{
	if (m_bVisible == false)
		return;

	SystemUIDialog::render();

	m_pCollisionBoxButton->render();
	m_pCollisionCircleButton->render();
	m_pCollisionRotatedBoxButton->render();
	m_pBuildingObserverButton->render();
	m_pBuildingRefuelButton->render();
	m_pBuildingRepairButton->render();
	m_pWeatherFog_Button->render();
	m_pWeatherRain_Button->render();
	m_pGameRespawn_Button->render();
	m_pGameStarting_Button->render();

	RECT rcTitle;
	rcTitle.left = this->getDialogRECT().left + 5;
	rcTitle.right = this->getDialogRECT().right;
	rcTitle.top = this->getDialogRECT().top;
	rcTitle.bottom = rcTitle.top + 20;

	m_pGraphics->spriteBegin();
	m_dxFont.print(eventViewerNS::EVENT_VIEWER_TITLE, rcTitle, DT_LEFT | DT_VCENTER);
	m_pGraphics->spriteEnd();

	RECT rc = { m_ptStartPos.x, m_ptStartPos.y, m_ptEndPos.x, m_ptEndPos.y };
	if (m_bClicked)
	{
		m_pGraphics->drawRect(rc);
	}
}

void EventViewer::setupEventObject()
{
	EVENT_OBJECT_TYPE eventType;
	if (m_pCollisionBoxButton->getActive()) eventType = EVENT_OBJECT_TYPE::EVENT_OBJECT_COLLISION_BOX;
	else if(m_pCollisionCircleButton->getActive()) eventType = EVENT_OBJECT_TYPE::EVENT_OBJECT_COLLISION_CIRCLE;
	else if (m_pCollisionRotatedBoxButton->getActive()) eventType = EVENT_OBJECT_TYPE::EVENT_OBJECT_COLLISION_ROTATE_BOX;
	else if (m_pBuildingObserverButton->getActive()) eventType = EVENT_OBJECT_TYPE::EVENT_OBJECT_BUILDING_OBSERVER;
	else if (m_pBuildingRefuelButton->getActive()) eventType = EVENT_OBJECT_TYPE::EVENT_OBJECT_BUILDING_REFUEL;
	else if (m_pBuildingRepairButton->getActive()) eventType = EVENT_OBJECT_TYPE::EVENT_OBJECT_BUILDING_REPAIR;
	else if (m_pWeatherFog_Button->getActive()) eventType = EVENT_OBJECT_TYPE::EVENT_OBJECT_WEATHER_FOG;
	else if (m_pWeatherRain_Button->getActive()) eventType = EVENT_OBJECT_TYPE::EVENT_OBJECT_WEATHER_RAIN;
	else if (m_pGameRespawn_Button->getActive()) eventType = EVENT_OBJECT_TYPE::EVENT_OBJECT_GAME_RESPAWN;
	else if (m_pGameStarting_Button->getActive()) eventType = EVENT_OBJECT_TYPE::EVENT_OBJECT_GAME_STARTING;

	MapEventObject* newEventObj;
	newEventObj = new MapEventObject;
	newEventObj->initialize(m_pGraphics, m_ptStartPos.x, m_ptStartPos.y,
		m_ptEndPos.x - m_ptStartPos.x,
		m_ptEndPos.y - m_ptStartPos.y,
		eventType);
	newEventObj->setDebugMode(true);

	m_pMapSystem->addEventObject(newEventObj);
}
