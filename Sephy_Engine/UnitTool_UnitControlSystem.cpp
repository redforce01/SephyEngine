#include "stdafx.h"
#include "UnitTool_UnitControlSystem.h"


CUnitTool_UnitControlSystem::CUnitTool_UnitControlSystem()
{
	m_bUpdatable		= false;
	m_bClicked			= false;
	m_nSelectUnitNumber = -1;
	m_bSelectPlayerUnit = false;
}


CUnitTool_UnitControlSystem::~CUnitTool_UnitControlSystem()
{
	for (auto iter : m_vPlayerShips)
	{
		SAFE_DELETE(iter);
	}
	m_vPlayerShips.clear();
	for (auto iter : m_vComputerShips)
	{
		SAFE_DELETE(iter);
	}
	m_vComputerShips.clear();
	for (auto iter : m_vBulletInBattle)
	{
		SAFE_DELETE(iter);
	}
	m_vBulletInBattle.clear();
}

bool CUnitTool_UnitControlSystem::initialize(Game * gamePtr)
{
	bool success = false;
	try
	{
		m_pGraphics = gamePtr->getGraphics();
		m_pInput = gamePtr->getInput();

	}
	catch (...)
	{
		MessageBox(g_hWndEngine, "Unit Tool - UnitControl System Initialize Failed", "Error", MB_OK);
	}

	return success;
}

void CUnitTool_UnitControlSystem::update(float frameTime)
{
	updateUnitDelete(frameTime);

	if (m_bUpdatable == false)
		return;

	for (auto iter : m_vPlayerShips)
	{
		iter->update(frameTime);
	}
	for (auto iter : m_vComputerShips)
	{
		iter->update(frameTime);
	}

	//========================================
	// All Bullet Update 
	//  + Included Enemy Bullet & Player Bullet
	//  + Working InActive Bullet Deleting
	//  + Not Using Auto Iterator -> using std::vector<type>::iterator
	//========================================
	for (auto iter = m_vBulletInBattle.begin(); iter != m_vBulletInBattle.end(); )
	{
		(*iter)->update(frameTime);
		if ((*iter)->IsActive() == false)
		{
			SAFE_DELETE(*iter);
			m_vBulletInBattle.erase(iter);
		}
		else
			iter++;
	}

	updateUnitControl(frameTime);	
}

void CUnitTool_UnitControlSystem::render()
{
	for (auto iter : m_vPlayerShips)
	{
		iter->render();
	}
	for (auto iter : m_vComputerShips)
	{
		iter->render();
	}
	for (auto iter : m_vBulletInBattle)
	{
		iter->render();
	}
}

void CUnitTool_UnitControlSystem::ai()
{
	if (m_bUpdatable == false)
		return;

	for (auto iter : m_vPlayerShips)
	{
		iter->ai();
	}
	for (auto iter : m_vComputerShips)
	{
		iter->ai();
	}
}

void CUnitTool_UnitControlSystem::collision()
{
	if (m_bUpdatable == false)
		return;

	for (auto iter : m_vPlayerShips)
	{
		iter->collision();
	}
	for (auto iter : m_vComputerShips)
	{
		iter->collision();
	}
	for (auto iter : m_vBulletInBattle)
	{
		for (auto iterPlayer : m_vPlayerShips)
		{
			iter->collision(iterPlayer);
		}
		for (auto iterComputer : m_vComputerShips)
		{
			iter->collision(iterComputer);
		}
	}
}

void CUnitTool_UnitControlSystem::updateUnitControl(float frameTime)
{
	if (m_pInput->getMouseLButton())
	{
		m_bClicked = true;
	}
	else
	{
		if (m_bClicked)
		{
			auto mouseX = m_pInput->getMouseX();
			auto mouseY = m_pInput->getMouseY();
			int selectCount = 0;
			for (auto iter : m_vPlayerShips)
			{
				auto touchData = iter->getShipTouchData();
				if (MyUtil::ptInCircle(touchData.x, touchData.y, touchData.radius, mouseX, mouseY))
				{
					m_bSelectPlayerUnit = true;
					m_nSelectUnitNumber = selectCount;
					m_bClicked = false;
					iter->setUnitSelected(true);
					break;
				}
				else
					iter->setUnitSelected(false);
				selectCount++;
			}
			selectCount = 0;
			for (auto iter : m_vComputerShips)
			{
				auto touchData = iter->getShipTouchData();
				if (MyUtil::ptInCircle(touchData.x, touchData.y, touchData.radius, mouseX, mouseY))
				{
					m_bSelectPlayerUnit = false;
					m_nSelectUnitNumber = selectCount;
					m_bClicked = false;
					iter->setUnitSelected(true);
					break;
				}
				else
					iter->setUnitSelected(false);
				selectCount++;
			}
			m_bClicked = false;
		}
	}

	if (m_pInput->getMouseRButton())
	{
		if (m_nSelectUnitNumber != -1)
		{
			auto mouseX = m_pInput->getMouseX();
			auto mouseY = m_pInput->getMouseY();

			if (m_bSelectPlayerUnit)
			{
				m_vPlayerShips[m_nSelectUnitNumber]->setTargetX(mouseX);
				m_vPlayerShips[m_nSelectUnitNumber]->setTargetY(mouseY);
			}
			else
			{
				m_vComputerShips[m_nSelectUnitNumber]->setTargetX(mouseX);
				m_vComputerShips[m_nSelectUnitNumber]->setTargetY(mouseY);
			}
		}
	}
}

void CUnitTool_UnitControlSystem::updateUnitDelete(float frameTime)
{
	if (m_pInput->isKeyDown(VK_DELETE))
	{
		auto mouseX = m_pInput->getMouseX();
		auto mouseY = m_pInput->getMouseY();
		int selectCount = 0;
		for (auto iter = m_vPlayerShips.begin(); iter != m_vPlayerShips.end(); )
		{
			auto touchData = (*iter)->getShipTouchData();
			if (MyUtil::ptInCircle(touchData.x, touchData.y, touchData.radius, mouseX, mouseY))
			{
				SAFE_DELETE(*iter);
				m_vPlayerShips.erase(iter);
				break;
			}
			else
				iter++;
		}
		for (auto iter = m_vComputerShips.begin(); iter != m_vComputerShips.end(); )
		{
			auto touchData = (*iter)->getShipTouchData();
			if (MyUtil::ptInCircle(touchData.x, touchData.y, touchData.radius, mouseX, mouseY))
			{
				SAFE_DELETE(*iter);
				m_vComputerShips.erase(iter);
				break;
			}
			else
				iter++;
		}
	}
}

void CUnitTool_UnitControlSystem::resetAllUnits()
{
	for (auto iter : m_vPlayerShips)
	{
		SAFE_DELETE(iter);
	}
	m_vPlayerShips.clear();
	for (auto iter : m_vComputerShips)
	{
		SAFE_DELETE(iter);
	}
	m_vComputerShips.clear();
	for (auto iter : m_vBulletInBattle)
	{
		SAFE_DELETE(iter);
	}
	m_vBulletInBattle.clear();
}

void CUnitTool_UnitControlSystem::moveX(float distance)
{
	for (auto iter : m_vPlayerShips)
	{
		iter->moveX(distance);
	}
	for (auto iter : m_vComputerShips)
	{
		iter->moveX(distance);
	}
	for (auto iter : m_vBulletInBattle)
	{
		iter->moveX(distance);
	}
}

void CUnitTool_UnitControlSystem::moveY(float distance)
{
	for (auto iter : m_vPlayerShips)
	{
		iter->moveY(distance);
	}
	for (auto iter : m_vComputerShips)
	{
		iter->moveY(distance);
	}
	for (auto iter : m_vBulletInBattle)
	{
		iter->moveY(distance);
	}
}
