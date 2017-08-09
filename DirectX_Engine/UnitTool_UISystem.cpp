#include "stdafx.h"
#include "UnitTool_UISystem.h"


CUnitTool_UISystem::CUnitTool_UISystem()
{
}


CUnitTool_UISystem::~CUnitTool_UISystem()
{
	SAFE_DELETE(m_pUIViewer);
	SAFE_DELETE(m_pUnitMakerViewer);
	SAFE_DELETE(m_pShipDataSetter);
	SAFE_DELETE(m_pRespawnListViewer);
	SAFE_DELETE(m_pMouseOverShip);
}

bool CUnitTool_UISystem::initialize(Game * gamePtr)
{
	bool success = false;
	try
	{
		m_pGraphics = gamePtr->getGraphics();
		m_pInput = gamePtr->getInput();

		//========================================================
		// Each Viewer Initialize
		//========================================================
		m_pUIViewer = new CUnitTool_UIViewer;
		success = m_pUIViewer->initialize(m_pGraphics, m_pInput);
		m_pUIViewer->setupGamePointer(gamePtr);
		m_pUnitMakerViewer = new CUnitTool_UnitMakeViewer;
		success = m_pUnitMakerViewer->initialize(m_pGraphics, m_pInput);
		m_pShipDataSetter = new CUnitTool_ShipDataSetter;
		success = m_pShipDataSetter->initialize(gamePtr);
		m_pRespawnListViewer = new CUnitTool_RespawnListViewer;
		success = m_pRespawnListViewer->initialize(m_pGraphics, m_pInput);
		m_pMouseOverShip = new CUnitTool_MouseOverShip;
		success = m_pMouseOverShip->initialize(m_pGraphics, m_pInput);
		//========================================================
		// Forward Declaration Setup
		//========================================================
		m_pShipDataSetter->setMemoryLinkUIViewer(m_pUIViewer);
		m_pUnitMakerViewer->setMemoryLinkShipDataSetter(m_pShipDataSetter);
		m_pUIViewer->setMemoryLinkMouseOverShip(m_pMouseOverShip);
		m_pMouseOverShip->setMemoryLinkRespawnListViewer(m_pRespawnListViewer);
	}
	catch (const std::exception&)
	{
		MessageBox(g_hWndEngine, "UNIT TOOL UISystem Initialize Failed", "Error", MB_OK);
	}

	return success;
}

void CUnitTool_UISystem::update(float frameTime)
{
	m_pUIViewer->update(frameTime);
	m_pUnitMakerViewer->update(frameTime);
	m_pRespawnListViewer->update(frameTime);
	m_pMouseOverShip->update(frameTime);
}

void CUnitTool_UISystem::render()
{
	m_pUIViewer->render();
	m_pUnitMakerViewer->render();
	m_pRespawnListViewer->render();
	m_pMouseOverShip->render();
}
