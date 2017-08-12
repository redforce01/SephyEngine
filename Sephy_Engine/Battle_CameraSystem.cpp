#include "stdafx.h"
#include "Battle_CameraSystem.h"
#include "Battle_MapSystem.h"
#include "Battle_UnitSystem.h"
#include "Battle_FogSystem.h"

CBattle_CameraSystem::CBattle_CameraSystem()
{
	m_fCameraX = 0.f;
	m_fCameraY = 0.f;
	m_fCameraMinX = m_fCameraMinY = 0.f;
	m_fCameraMaxX = m_fCameraMaxY = 0.f;
	m_fCameraSpeed = battleCameraSystemNS::CAMERA_NORMAL_SPEED;
	//==================================================
	m_pBattleMinimapView	= nullptr;


	//==================================================
	m_pBattleMapSystem		= nullptr;
	m_pBattleMinimapSystem	= nullptr;
	m_pBattleUnitSystem		= nullptr;
}


CBattle_CameraSystem::~CBattle_CameraSystem()
{
}

bool CBattle_CameraSystem::initialize(Game * gamePtr)
{
	bool success = false;
	try
	{
		m_pGraphics = gamePtr->getGraphics();
		m_pInput = gamePtr->getInput();

		m_pBattleMinimapView = new CBattle_MinimapView;
		success = m_pBattleMinimapView->initialize(m_pGraphics, m_pInput);
		m_pBattleMinimapView->setMemoryLinkBattleCameraSystem(this);
	}
	catch (...)
	{
		MessageBox(g_hWndEngine, battleCameraSystemNS::ERROR_MESSAGE.c_str(), "Error", MB_OK);
	}

	return success;
}

void CBattle_CameraSystem::update(float frameTime)
{
	if (m_pInput->isKeyDown(battleCameraSystemNS::CAMERA_BOOST_KEY))
	{
		m_fCameraSpeed = battleCameraSystemNS::CAMERA_BOOST_SPEED;
	}
	else
		m_fCameraSpeed = battleCameraSystemNS::CAMERA_NORMAL_SPEED;


	if (m_pInput->isKeyDown(battleCameraSystemNS::CAMERA_MOVE_LEFT_KEY))
	{
		moveLeft();
	}
	if (m_pInput->isKeyDown(battleCameraSystemNS::CAMERA_MOVE_RIGHT_KEY))
	{
		moveRight();
	}
	if (m_pInput->isKeyDown(battleCameraSystemNS::CAMERA_MOVE_UP_KEY))
	{
		moveUp();
	}
	if (m_pInput->isKeyDown(battleCameraSystemNS::CAMERA_MOVE_DOWN_KEY))
	{
		moveDown();
	}

	m_pBattleMinimapView->update(frameTime);
}


void CBattle_CameraSystem::render()
{
	m_pBattleMinimapView->render();
}

void CBattle_CameraSystem::moveLeft()
{
	if (m_fCameraX > m_fCameraMinX)
	{
		m_fCameraX -= m_fCameraSpeed;
		m_pBattleMapSystem->moveX(m_fCameraSpeed);
		m_pBattleUnitSystem->moveX(m_fCameraSpeed);
		m_pBattleFogSystem->moveX(m_fCameraSpeed);
		m_pBattleMinimapView->setUpCam(m_fCameraX, m_fCameraY);
	}
}

void CBattle_CameraSystem::moveRight()
{
	if (m_fCameraX < m_fCameraMaxX)
	{
		m_fCameraX += m_fCameraSpeed;
		m_pBattleMapSystem->moveX(-m_fCameraSpeed);
		m_pBattleUnitSystem->moveX(-m_fCameraSpeed);
		m_pBattleFogSystem->moveX(-m_fCameraSpeed);
		m_pBattleMinimapView->setUpCam(m_fCameraX, m_fCameraY);
	}
}

void CBattle_CameraSystem::moveUp()
{
	if (m_fCameraY > m_fCameraMinY)
	{
		m_fCameraY -= m_fCameraSpeed;
		m_pBattleMapSystem->moveY(m_fCameraSpeed);
		m_pBattleUnitSystem->moveY(m_fCameraSpeed);
		m_pBattleFogSystem->moveY(m_fCameraSpeed);
		m_pBattleMinimapView->setUpCam(m_fCameraX, m_fCameraY);
	}
}

void CBattle_CameraSystem::moveDown()
{
	if (m_fCameraY < m_fCameraMaxY)
	{
		m_fCameraY += m_fCameraSpeed;
		m_pBattleMapSystem->moveY(-m_fCameraSpeed);
		m_pBattleUnitSystem->moveY(-m_fCameraSpeed);
		m_pBattleFogSystem->moveY(-m_fCameraSpeed);
		m_pBattleMinimapView->setUpCam(m_fCameraX, m_fCameraY);
	}
}

void CBattle_CameraSystem::setCameraPos(float x, float y)
{
	int oldX, oldY;
	oldX = m_fCameraX, oldY = m_fCameraY;
	m_pBattleMapSystem->moveX(oldX - x);
	m_pBattleUnitSystem->moveX(oldX - x);
	m_pBattleFogSystem->moveX(oldX - x);
	m_pBattleMapSystem->moveY(oldY - y);
	m_pBattleUnitSystem->moveY(-oldY - y);
	m_pBattleFogSystem->moveY(-oldY - y);
	m_fCameraX = x, m_fCameraY = y;
	m_pBattleMinimapView->setUpCam(m_fCameraX, m_fCameraY);
}
