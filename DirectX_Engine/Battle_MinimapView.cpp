#include "stdafx.h"
#include "Battle_MinimapView.h"
#include "Battle_CameraSystem.h"

CBattle_MinimapView::CBattle_MinimapView()
{
	m_pBattleCameraSystem = nullptr;
	m_Width = battleMinimapViewNS::WIDTH;
	m_Height = battleMinimapViewNS::HEIGHT;
	m_MapWidth = m_MapHeight = 0;
	m_CamWidth = m_CamHeight = 0;
	m_rcMinimap = RectMake(0, 0, 0, 0);
	m_rcCamera = RectMake(0, 0, 0, 0);
	m_bIsometric = true;
	fontColor = battleMinimapViewNS::FONT_COLOR;
	backColor = battleMinimapViewNS::BACK_COLOR;
}


CBattle_MinimapView::~CBattle_MinimapView()
{
}

bool CBattle_MinimapView::initialize(Graphics * g, Input * i)
{
	bool success = false;

	try
	{
		m_rcMinimap = RectMake(battleMinimapViewNS::X, g_fScreenHeight - battleMinimapViewNS::Y, battleMinimapViewNS::WIDTH, battleMinimapViewNS::HEIGHT);
		m_rcCamera = RectMake(battleMinimapViewNS::X, g_fScreenHeight - battleMinimapViewNS::Y, m_CamWidth, m_CamHeight);		
		success = SystemUIDialog::initializeDialog(g, i,
			battleMinimapViewNS::X,
			g_fScreenHeight - battleMinimapViewNS::Y,
			battleMinimapViewNS::WIDTH,
			battleMinimapViewNS::HEIGHT,
			battleMinimapViewNS::MARGIN);

	}
	catch (...)
	{
		MessageBox(g_hWndEngine, "Battle Minimap Viewer Initialized Failed", "Error", MB_OK);
	}

	return success;
}

void CBattle_MinimapView::update(float frameTime)
{
	SystemUIDialog::update(frameTime);

	if (m_bVisible == false)
		return;

	if (m_pInput->getMouseLButton())
	{
		if (getMouseOver())
		{
			clickMinimap();
		}
	}
}

void CBattle_MinimapView::render()
{
	if (m_bVisible == false)
		return;

	SystemUIDialog::render();
	m_pGraphics->drawRect(m_rcCamera, 1.0, graphicsNS::RED);
}

void CBattle_MinimapView::clickMinimap()
{
	float mouseX = m_pInput->getMouseX();
	float mouseY = m_pInput->getMouseY();
	float clickedX = abs(mouseX - m_rcMinimap.left);
	float clickedY = abs(mouseY - m_rcMinimap.top);

	//	x : m_MapWidth = posX : minimapViewerNS::WIDTH 
	// -> x = (posX / 400) * m_MapWidth
	//	y : m_MapHeight = posY : minimapViewerNS::HEIGHT
	// -> y = (posY / 300) * m_MapHeight	
	float targetX = (clickedX / battleMinimapViewNS::WIDTH) * m_MapWidth;
	float targetY = (clickedY / battleMinimapViewNS::HEIGHT) * m_MapHeight;
	if (m_bIsometric)
	{
		targetY = targetY / 2;
	}
	m_pBattleCameraSystem->setCameraPos(targetX, targetY);
}

void CBattle_MinimapView::checkMinimapCamRect()
{
	if (m_rcCamera.left < battleMinimapViewNS::X)
	{
		m_rcCamera.left = battleMinimapViewNS::X;
	}
	if (m_rcCamera.top < g_fScreenHeight - battleMinimapViewNS::Y)
	{
		m_rcCamera.top = g_fScreenHeight - battleMinimapViewNS::Y;
	}
	if (m_rcCamera.right > battleMinimapViewNS::X + battleMinimapViewNS::WIDTH)
	{
		m_rcCamera.right = battleMinimapViewNS::X + battleMinimapViewNS::WIDTH;
	}
	if (m_rcCamera.bottom > g_fScreenHeight - battleMinimapViewNS::Y + battleMinimapViewNS::HEIGHT)
	{
		m_rcCamera.bottom = g_fScreenHeight - battleMinimapViewNS::Y + battleMinimapViewNS::HEIGHT;
	}
}

void CBattle_MinimapView::setUpCam()
{
	if (m_bInitialized == false)
		return;

	float camX, camY;
	camX = 0;
	camY = 0;
	m_CamWidth = battleMinimapViewNS::WIDTH / (m_MapWidth / g_fScreenWidth);
	m_CamHeight = battleMinimapViewNS::HEIGHT / (m_MapHeight / g_fScreenHeight);

	if (m_bIsometric)
	{
		m_CamHeight = m_CamHeight * 2;
	}

	m_rcCamera = RectMake(battleMinimapViewNS::X + camX, g_fScreenHeight - battleMinimapViewNS::Y + camY, m_CamWidth, m_CamHeight);
	checkMinimapCamRect();
}

void CBattle_MinimapView::setUpCam(float startMapX, float startMapY)
{
	if (m_bInitialized == false)
		return;

	float camX, camY;
	m_CamWidth = battleMinimapViewNS::WIDTH / (m_MapWidth / g_fScreenWidth);
	m_CamHeight = battleMinimapViewNS::HEIGHT / (m_MapHeight / g_fScreenHeight);
	camX = battleMinimapViewNS::WIDTH * (startMapX / m_MapWidth);
	camY = battleMinimapViewNS::HEIGHT * (startMapY / m_MapHeight);
	if (m_bIsometric)
	{
		m_CamHeight = m_CamHeight * 2;
		camY = camY * 2;
	}
	m_rcCamera = RectMake(battleMinimapViewNS::X + camX, g_fScreenHeight - battleMinimapViewNS::Y + camY, m_CamWidth, m_CamHeight);
	checkMinimapCamRect();
}