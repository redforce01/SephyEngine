#include "stdafx.h"
#include "CameraSystem.h"
#include "mapSystem.h"
#include "minimapViewer.h"

CameraSystem::CameraSystem()
{
	cameraX = cameraY = 0;
	cameraSpeed = CameraSystemNS::CAMERA_SPEED;
	cameraAngle = 0;
	cameraZoomRate = 0;
	cameraZoomSpeed = CameraSystemNS::CAMERA_ZOOM_RATE;
	m_pInput = nullptr;
	m_pMapSystem = nullptr;
	m_pMinimap = nullptr;
	m_bCameraBoost = false;
}

CameraSystem::~CameraSystem()
{
}

bool CameraSystem::initialize(Game* gamePtr)
{
	bool success = false;
	try
	{
		m_pInput = gamePtr->getInput();
		success = true;
	}
	catch (...)
	{
		
	}

	return success;
}

void CameraSystem::update(float frameTime)
{
	if (m_pInput->isKeyDown(CameraSystemNS::CAMERA_MOVE_LEFT_KEY))
	{
		moveLeft();
	}
	if (m_pInput->isKeyDown(CameraSystemNS::CAMERA_MOVE_RIGHT_KEY))
	{
		moveRight();
	}
	if (m_pInput->isKeyDown(CameraSystemNS::CAMERA_MOVE_UP_KEY))
	{
		moveUp();
	}
	if (m_pInput->isKeyDown(CameraSystemNS::CAMERA_MOVE_DOWN_KEY))
	{
		moveDown();
	}
	if (m_pInput->isKeyDown(CameraSystemNS::CAMERA_BOOST_KEY))
	{
		m_bCameraBoost = true;
		cameraSpeed = CameraSystemNS::CAMERA_SPEED * CameraSystemNS::CAMERA_BOOST;
	}
	else
	{
		m_bCameraBoost = false;
		cameraSpeed = CameraSystemNS::CAMERA_SPEED;
	}

	//if (pInput->isMouseWheelUp() || pInput->isKeyDown(CameraSystemNS::CAMERA_ZOOM_IN_KEY))
	//{
	//	zoomIn();
	//}
	//if (pInput->isMouseWheelDown() || pInput->isKeyDown(CameraSystemNS::CAMERA_ZOOM_OUT_KEY))
	//{
	//	zoomOut();
	//}
}

void CameraSystem::render()
{
}

void CameraSystem::moveLeft()
{
	cameraX -= cameraSpeed;
	m_pMapSystem->moveX(cameraSpeed);
	m_pMinimap->setUpCam(cameraX, cameraY);
}

void CameraSystem::moveRight()
{
	cameraX += cameraSpeed;
	m_pMapSystem->moveX(-cameraSpeed);
	m_pMinimap->setUpCam(cameraX, cameraY);
}

void CameraSystem::moveUp()
{
	cameraY -= cameraSpeed;
	m_pMapSystem->moveY(cameraSpeed);
	m_pMinimap->setUpCam(cameraX, cameraY);
}

void CameraSystem::moveDown()
{
	cameraY += cameraSpeed;
	m_pMapSystem->moveY(-cameraSpeed);
	m_pMinimap->setUpCam(cameraX, cameraY);
}

void CameraSystem::zoomIn()
{
	if (cameraZoomRate < 1.0f)
	{
		cameraZoomRate += cameraZoomSpeed;
	}
}

void CameraSystem::zoomOut()
{
	if (cameraZoomRate > 0)
	{
		cameraZoomRate -= cameraZoomSpeed;
	}
}

void CameraSystem::setCameraPos(float x, float y)
{
	int oldX, oldY;
	oldX = cameraX, oldY = cameraY;
	m_pMapSystem->moveX(oldX - x);
	m_pMapSystem->moveY(oldY - y);
	cameraX = x, cameraY = y;
	m_pMinimap->setUpCam(cameraX, cameraY);
}
