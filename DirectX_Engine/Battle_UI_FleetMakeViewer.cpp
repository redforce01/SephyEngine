#include "stdafx.h"
#include "Battle_UI_FleetMakeViewer.h"

CBattle_UI_FleetMakeViewer* pThis = nullptr;
CBattle_UI_FleetMakeViewer::CBattle_UI_FleetMakeViewer()
{
	::pThis = this;
	backColor = battleUIFleetMakeViewerNS::BACK_COLOR_ACTIVE;
	m_bVisibleView = false;
}


CBattle_UI_FleetMakeViewer::~CBattle_UI_FleetMakeViewer()
{
	SAFE_DELETE(m_pFleetMakeButton);
	SAFE_DELETE(m_pFleetRemoveButton);
	SAFE_DELETE(m_pFleetSetupButton);
	SAFE_DELETE(m_pFlagShipButton);
}

bool CBattle_UI_FleetMakeViewer::initialize(Graphics * g, Input * i)
{
	bool success = false;
	try
	{
		success = SystemUIDialog::initializeDialog(g, i,
			g_fScreenWidth - battleUIFleetMakeViewerNS::FLEET_MAKE_VIEW_WIDTH,
			battleUIFleetMakeViewerNS::FLEET_MAKE_VIEW_Y,
			battleUIFleetMakeViewerNS::FLEET_MAKE_VIEW_WIDTH,
			battleUIFleetMakeViewerNS::FLEET_MAKE_VIEW_HEIGHT, 0);
		
		m_pFleetMakeButton = new CBattle_UI_FleetMakeButton;
		m_pFleetMakeButton->initialize(g, i);
		m_pFleetMakeButton->setRegistFunction(std::bind(&CBattle_UI_FleetMakeViewer::functionFleetMake));
		
		m_pFleetRemoveButton = new CBattle_UI_FleetRemoveButton;
		m_pFleetRemoveButton->initialize(g, i);
		m_pFleetRemoveButton->setRegistFunction(std::bind(&CBattle_UI_FleetMakeViewer::functionFleetRemove));

		m_pFleetSetupButton = new CBattle_UI_FleetSetupButton;
		m_pFleetSetupButton->initialize(g, i);
		m_pFleetSetupButton->setRegistFunction(std::bind(&CBattle_UI_FleetMakeViewer::functionFleetSetup));

		m_pFlagShipButton = new CBattle_UI_FlagShipButton;
		m_pFlagShipButton->initialize(g, i);
		m_pFlagShipButton->setRegistFunction(std::bind(&CBattle_UI_FleetMakeViewer::functionSetFlagShip));

	}
	catch (...)
	{
		MessageBox(g_hWndEngine, battleUIFleetMakeViewerNS::ERROR_MESSAGE.c_str(), "Error", MB_OK);
	}

	return success;
}

void CBattle_UI_FleetMakeViewer::update(float frameTime)
{
	if (SystemUIDialog::getVisible() == false)
		return;

	SystemUIDialog::update(frameTime);

	if (SystemUIDialog::getMouseOver() == false)
		return;

	m_pFleetMakeButton->update(frameTime);
	m_pFleetRemoveButton->update(frameTime);
	m_pFleetSetupButton->update(frameTime);
	m_pFlagShipButton->update(frameTime);
}

void CBattle_UI_FleetMakeViewer::render()
{
	if (SystemUIDialog::getVisible() == false)
		return;

	SystemUIDialog::render();

	m_pFleetMakeButton->render();
	m_pFleetRemoveButton->render();
	m_pFleetSetupButton->render();
	m_pFlagShipButton->render();
}

void CBattle_UI_FleetMakeViewer::functionFleetMake()
{
	pThis->m_bVisibleView = !pThis->m_bVisibleView;
}

void CBattle_UI_FleetMakeViewer::functionFleetRemove()
{
	
}

void CBattle_UI_FleetMakeViewer::functionFleetSetup()
{

}

void CBattle_UI_FleetMakeViewer::functionSetFlagShip()
{
}
