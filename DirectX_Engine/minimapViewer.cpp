#include "stdafx.h"
#include "minimapViewer.h"
#include "CameraSystem.h"

MinimapViewer::MinimapViewer()
{
	m_Width = minimapViewerNS::WIDTH;
	m_Height = minimapViewerNS::HEIGHT;
	m_MapWidth = m_MapHeight = 0;	
	m_CamWidth = m_CamHeight = 0;
	m_rcMinimap = RectMake(0, 0, 0, 0);
	m_rcCamera = RectMake(0, 0, 0, 0);
	m_bInitialized = false;
	m_bIsometric = false;
	m_pCameraSystem = nullptr;
	fontColor = minimapViewerNS::FONT_COLOR;
	backColor = minimapViewerNS::BACK_COLOR;
}


MinimapViewer::~MinimapViewer()
{
}

bool MinimapViewer::initialize(Graphics * g, Input * i)
{
	bool success = false;

	try
	{
		m_rcMinimap = RectMake(minimapViewerNS::X, g_fScreenHeight - minimapViewerNS::Y, minimapViewerNS::WIDTH, minimapViewerNS::HEIGHT);
		m_rcCamera = RectMake(minimapViewerNS::X, g_fScreenHeight - minimapViewerNS::Y, m_CamWidth, m_CamHeight);
		m_bInitialized = true;
		success = SystemUIDialog::initializeDialog(g, i,
			minimapViewerNS::X,
			g_fScreenHeight - minimapViewerNS::Y,
			minimapViewerNS::WIDTH,
			minimapViewerNS::HEIGHT,
			minimapViewerNS::MARGIN);
	}
	catch (...)
	{
		MessageBox(g_hWndEngine, "Minimap Viewer Initialized Failed", "Error", MB_OK);
	}

	return success;
}

void MinimapViewer::update(float frameTime)
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

void MinimapViewer::render()
{
	if (m_bVisible == false)
		return;

	SystemUIDialog::render();	
	m_pGraphics->drawRect(m_rcCamera, 1.0, graphicsNS::RED);
}

void MinimapViewer::clickMinimap()
{
	float mouseX = m_pInput->getMouseX();
	float mouseY = m_pInput->getMouseY();
	float clickedX = abs(mouseX - m_rcMinimap.left);
	float clickedY = abs(mouseY - m_rcMinimap.top);
	
	//	x : m_MapWidth = posX : minimapViewerNS::WIDTH 
	// -> x = (posX / 400) * m_MapWidth
	//	y : m_MapHeight = posY : minimapViewerNS::HEIGHT
	// -> y = (posY / 300) * m_MapHeight	
	float targetX = (clickedX / minimapViewerNS::WIDTH) * m_MapWidth;
	float targetY = (clickedY / minimapViewerNS::HEIGHT) * m_MapHeight;
	if (m_bIsometric)
	{
		targetY = targetY / 2;
	}
	m_pCameraSystem->setCameraPos(targetX, targetY);
}

void MinimapViewer::checkMinimapCamRect()
{
	if (m_rcCamera.left < minimapViewerNS::X)
	{
		m_rcCamera.left = minimapViewerNS::X;
	}
	if (m_rcCamera.top < g_fScreenHeight - minimapViewerNS::Y)
	{
		m_rcCamera.top = g_fScreenHeight - minimapViewerNS::Y;
	}
	if (m_rcCamera.right > minimapViewerNS::X + minimapViewerNS::WIDTH)
	{
		m_rcCamera.right = minimapViewerNS::X + minimapViewerNS::WIDTH;
	}
	if (m_rcCamera.bottom > g_fScreenHeight - minimapViewerNS::Y + minimapViewerNS::HEIGHT)
	{
		m_rcCamera.bottom = g_fScreenHeight - minimapViewerNS::Y + minimapViewerNS::HEIGHT;
	}
}

void MinimapViewer::setUpCam()
{
	if (m_bInitialized == false)
		return;
	
	float camX, camY;
	camX = 0;
	camY = 0;
	m_CamWidth = minimapViewerNS::WIDTH / (m_MapWidth / g_fScreenWidth);
	m_CamHeight = minimapViewerNS::HEIGHT / (m_MapHeight / g_fScreenHeight);

	if (m_bIsometric)
	{
		m_CamHeight = m_CamHeight * 2;
	}

	m_rcCamera = RectMake(minimapViewerNS::X + camX, g_fScreenHeight - minimapViewerNS::Y + camY, m_CamWidth, m_CamHeight);
	checkMinimapCamRect();
}

void MinimapViewer::setUpCam(float startMapX, float startMapY)
{
	if (m_bInitialized == false)
		return;
	
	float camX, camY;
	m_CamWidth = minimapViewerNS::WIDTH / (m_MapWidth / g_fScreenWidth);
	m_CamHeight = minimapViewerNS::HEIGHT / (m_MapHeight / g_fScreenHeight);
	camX = minimapViewerNS::WIDTH * (startMapX / m_MapWidth);
	camY = minimapViewerNS::HEIGHT * (startMapY / m_MapHeight);
	if (m_bIsometric)
	{
		m_CamHeight = m_CamHeight * 2;
		camY = camY * 2;
	}	
	m_rcCamera = RectMake(minimapViewerNS::X + camX, g_fScreenHeight - minimapViewerNS::Y + camY, m_CamWidth, m_CamHeight);
	checkMinimapCamRect();
}