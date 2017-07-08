#include "stdafx.h"
#include "CameraSystem.h"
#include "mapSystem.h"
#include "minimapViewer.h"

CameraSystem::CameraSystem()
{
	cameraX = cameraY = 0;
	cameraSpeed = 0;
	cameraAngle = 0;
	cameraZoomRate = 0;
	cameraZoomSpeed = 0;
	m_pInput = nullptr;
	m_pMapSystem = nullptr;
	m_pMinimap = nullptr;
}

CameraSystem::~CameraSystem()
{
}

bool CameraSystem::initialize(Game* gamePtr)
{
	bool success = false;
	try
	{
		cameraSpeed = 10.f;
		cameraZoomSpeed = 0.1f;
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
		m_pMapSystem->scaleUp();
	}
}

void CameraSystem::zoomOut()
{
	if (cameraZoomRate > 0)
	{
		cameraZoomRate -= cameraZoomSpeed;
		m_pMapSystem->scaleDown();
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
