#include "stdafx.h"
#include "CameraSystem.h"
#include "mapSystem.h"

CameraSystem::CameraSystem()
{
	cameraX = cameraY = 0;
	cameraSpeed = 0;
	cameraAngle = 0;
	cameraZoomRate = 0;
	cameraZoomSpeed = 0;
}

CameraSystem::~CameraSystem()
{
}

bool CameraSystem::initialize()
{
	cameraSpeed = 10.f;
	cameraZoomSpeed = 0.1f;

	return true;
}

void CameraSystem::update(Input* input)
{
	if (input->isKeyDown(CameraSystemNS::CAMERA_MOVE_LEFT_KEY))
	{
		moveLeft();
	}
	if (input->isKeyDown(CameraSystemNS::CAMERA_MOVE_RIGHT_KEY))
	{
		moveRight();
	}
	if (input->isKeyDown(CameraSystemNS::CAMERA_MOVE_UP_KEY))
	{
		moveUp();
	}
	if (input->isKeyDown(CameraSystemNS::CAMERA_MOVE_DOWN_KEY))
	{
		moveDown();
	}

	if (input->isMouseWheelUp() || input->isKeyDown(CameraSystemNS::CAMERA_ZOOM_IN_KEY))
	{
		zoomIn();
	}
	if (input->isMouseWheelDown() || input->isKeyDown(CameraSystemNS::CAMERA_ZOOM_OUT_KEY))
	{
		zoomOut();
	}
}

void CameraSystem::moveLeft()
{
	cameraX -= cameraSpeed;
	pMapSystem->moveX(cameraSpeed);
}

void CameraSystem::moveRight()
{
	cameraX += cameraSpeed;
	pMapSystem->moveX(-cameraSpeed);
}

void CameraSystem::moveUp()
{
	cameraY -= cameraSpeed;
	pMapSystem->moveY(cameraSpeed);
}

void CameraSystem::moveDown()
{
	cameraY += cameraSpeed;
	pMapSystem->moveY(-cameraSpeed);
}

void CameraSystem::zoomIn()
{
	if (cameraZoomRate < 1.0f)
	{
		cameraZoomRate += cameraZoomSpeed;
		pMapSystem->scaleUp();
	}
}

void CameraSystem::zoomOut()
{
	if (cameraZoomRate > 0)
	{
		cameraZoomRate -= cameraZoomSpeed;
		pMapSystem->scaleDown();
	}
}
