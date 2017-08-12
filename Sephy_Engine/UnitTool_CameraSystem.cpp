#include "stdafx.h"
#include "UnitTool_CameraSystem.h"
#include "UnitTool_MapSystem.h"
#include "UnitTool_UnitControlSystem.h"

CUnitTool_CameraSystem::CUnitTool_CameraSystem()
{
	m_fCameraX = 0.f;
	m_fCameraY = 0.f;
	m_fCameraMinX = m_fCameraMinY = 0.f;
	m_fCameraMaxX = m_fCameraMaxY = 0.f;
	m_fCameraSpeed = unitToolCameraSystemNS::CAMERA_NORMAL_SPEED;

	m_pMapSystem = nullptr;
	m_pUnitControlSystem = nullptr;
}


CUnitTool_CameraSystem::~CUnitTool_CameraSystem()
{
}

bool CUnitTool_CameraSystem::initialize(Game * gamePtr)
{
	bool success = false;
	try
	{
		m_pGraphics = gamePtr->getGraphics();
		m_pInput = gamePtr->getInput();


	}
	catch (...)
	{
		MessageBox(g_hWndEngine, unitToolCameraSystemNS::ERROR_MESSAGE.c_str(), "Error", MB_OK);
	}

	return success;
}

void CUnitTool_CameraSystem::update(float frameTime)
{
	if (m_pInput->isKeyDown(unitToolCameraSystemNS::CAMERA_BOOST_KEY))
	{
		m_fCameraSpeed = unitToolCameraSystemNS::CAMERA_BOOST_SPEED;
	}
	else
		m_fCameraSpeed = unitToolCameraSystemNS::CAMERA_NORMAL_SPEED;

	if (m_pInput->isKeyDown(unitToolCameraSystemNS::CAMERA_MOVE_LEFT_KEY))
	{
		moveLeft();
	}
	if (m_pInput->isKeyDown(unitToolCameraSystemNS::CAMERA_MOVE_RIGHT_KEY))
	{
		moveRight();
	}
	if (m_pInput->isKeyDown(unitToolCameraSystemNS::CAMERA_MOVE_UP_KEY))
	{
		moveUp();
	}
	if (m_pInput->isKeyDown(unitToolCameraSystemNS::CAMERA_MOVE_DOWN_KEY))
	{
		moveDown();
	}
}

void CUnitTool_CameraSystem::render()
{
}

void CUnitTool_CameraSystem::moveLeft()
{
	if (m_fCameraX > m_fCameraMinX)
	{
		m_fCameraX -= m_fCameraSpeed;
		m_pMapSystem->moveX(m_fCameraSpeed);
		m_pUnitControlSystem->moveX(m_fCameraSpeed);
		//m_pBattleMinimapView->setUpCam(m_fCameraX, m_fCameraY);
	}
}

void CUnitTool_CameraSystem::moveRight()
{
	if (m_fCameraX < m_fCameraMaxX)
	{
		m_fCameraX += m_fCameraSpeed;
		m_pMapSystem->moveX(-m_fCameraSpeed);
		m_pUnitControlSystem->moveX(-m_fCameraSpeed);
		//m_pBattleMinimapView->setUpCam(m_fCameraX, m_fCameraY);
	}
}

void CUnitTool_CameraSystem::moveUp()
{
	if (m_fCameraY > m_fCameraMinY)
	{
		m_fCameraY -= m_fCameraSpeed;
		m_pMapSystem->moveY(m_fCameraSpeed);
		m_pUnitControlSystem->moveY(m_fCameraSpeed);
		//m_pBattleMinimapView->setUpCam(m_fCameraX, m_fCameraY);
	}
}

void CUnitTool_CameraSystem::moveDown()
{

	if (m_fCameraY < m_fCameraMaxY)
	{
		m_fCameraY += m_fCameraSpeed;
		m_pMapSystem->moveY(-m_fCameraSpeed);
		m_pUnitControlSystem->moveY(-m_fCameraSpeed);
		//m_pBattleMinimapView->setUpCam(m_fCameraX, m_fCameraY);
	}
}

void CUnitTool_CameraSystem::setCameraPos(float x, float y)
{
	int oldX, oldY;
	oldX = m_fCameraX, oldY = m_fCameraY;
	m_pMapSystem->moveX(oldX - x);
	m_pMapSystem->moveY(oldY - y);
	m_fCameraX = x, m_fCameraY = y;
	//m_pBattleMinimapView->setUpCam(m_fCameraX, m_fCameraY);
}
