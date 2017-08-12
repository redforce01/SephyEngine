#include "stdafx.h"
#include "Battle_ShipUI_DPNumber.h"
#include "Battle_Ship.h"

CBattle_ShipUI_DPNumber::CBattle_ShipUI_DPNumber()
{
	m_pMaster = nullptr;
	m_fCurrentDP = 0.f;
	m_fMaxDP = 0.f;
}


CBattle_ShipUI_DPNumber::~CBattle_ShipUI_DPNumber()
{
	for (auto iter : m_vCurrentDP)
	{
		SAFE_DELETE(iter);
	}
	m_vCurrentDP.clear();
	for (auto iter : m_vMaxDP)
	{
		SAFE_DELETE(iter);
	}
	m_vMaxDP.clear();
	SAFE_DELETE(m_Slash);
}

bool CBattle_ShipUI_DPNumber::initialize(Graphics * g, CBattle_Ship * pMaster)
{
	bool success = false;
	try
	{
		m_pMaster = pMaster;
		m_fCurrentDP = pMaster->getCurrentHealth();
		m_fMaxDP = pMaster->getMaxHealth();

		for (int i = 0; i < battleShipUIDPNumberNS::DP_IMAGE_SIZE; i++)
		{
			Image* dpImage = new Image;
			std::string imageKey = battleShipUIDPNumberNS::DP_KEY_NORMAL + "0";
			success = dpImage->initialize(g, 0, 0, 0, IMAGEMANAGER->getTexture(imageKey));
			m_vCurrentDP.emplace_back(dpImage);
		}
		for (int i = 0; i < battleShipUIDPNumberNS::DP_IMAGE_SIZE; i++)
		{
			Image* dpImage = new Image;
			std::string imageKey = battleShipUIDPNumberNS::DP_KEY_NORMAL + "0";
			success = dpImage->initialize(g, 0, 0, 0, IMAGEMANAGER->getTexture(imageKey));
			m_vMaxDP.emplace_back(dpImage);
		}

		m_Slash = new Image;
		m_Slash->initialize(g, 0, 0, 0, IMAGEMANAGER->getTexture(battleShipUIDPNumberNS::DP_SLASH_FILENAME));
	}
	catch (...)
	{
		MessageBox(g_hWndEngine, battleShipUIDPNumberNS::ERROR_MESSAGE.c_str(), "Error", MB_OK);
	}	

	return success;
}

void CBattle_ShipUI_DPNumber::update(float frameTime)
{
	
}

void CBattle_ShipUI_DPNumber::draw()
{
	for (auto iter : m_vCurrentDP)
	{
		iter->draw();
	}
	m_Slash->draw();
	for (auto iter : m_vMaxDP)
	{
		iter->draw();
	}
}

void CBattle_ShipUI_DPNumber::setDPNumberPos(float startX, float startY)
{
	int imageCount = 0;
	for (auto iter : m_vCurrentDP)
	{
		if (iter->getVisible() == false)
			continue;

		if (imageCount > 0)
		{
			iter->setX(startX + (iter->getWidth() * imageCount));
			iter->setY(startY);
			imageCount++;
		}
		else
		{
			iter->setX(startX);
			iter->setY(startY);
			imageCount++;
		}
	}
	int lastCurDPItem = m_vCurrentDP.size() - 1;
	m_Slash->setX(m_vCurrentDP[lastCurDPItem]->getX() + m_vCurrentDP[lastCurDPItem]->getWidth());
	m_Slash->setY(startY);
	imageCount = 0;
	float maxDPStartX = m_Slash->getX() + m_Slash->getWidth();
	for (auto iter : m_vMaxDP)
	{
		if (iter->getVisible() == false)
			continue;

		if (imageCount > 0)
		{
			iter->setX(maxDPStartX + (iter->getWidth() * imageCount));
			iter->setY(startY);
			imageCount++;
		}
		else
		{
			iter->setX(maxDPStartX);
			iter->setY(startY);
			imageCount++;
		}
	}
}

void CBattle_ShipUI_DPNumber::setupDP(float currentDP, float maxDP)
{
	m_fCurrentDP = currentDP;
	m_fMaxDP = maxDP;

	if (m_fCurrentDP <= 0)
		m_fCurrentDP = 0;

	if (m_fMaxDP <= 0)
		m_fMaxDP = 0;

	setupCurrentDP(m_fCurrentDP);
	setupMaxDP(m_fMaxDP);
}

void CBattle_ShipUI_DPNumber::moveX(float distance)
{
	for (auto iter : m_vCurrentDP)
	{
		iter->moveX(distance);
	}
	m_Slash->moveX(distance);
	for (auto iter : m_vMaxDP)
	{
		iter->moveX(distance);
	}
}

void CBattle_ShipUI_DPNumber::moveY(float distance)
{
	for (auto iter : m_vCurrentDP)
	{
		iter->moveY(distance);
	}
	m_Slash->moveY(distance);
	for (auto iter : m_vMaxDP)
	{
		iter->moveY(distance);
	}
}

void CBattle_ShipUI_DPNumber::setupCurrentDP(float currentDP)
{
	std::vector<int> vDigits;
	if (currentDP <= 0)
	{
		vDigits.push_back(0);
	}
	else
	{
		int number = currentDP;
		while (number != 0)
		{
			int last = number % 10;
			vDigits.push_back(last);
			number = (number - last) / 10;
		}
	}

	int digitVectorLastIndex = vDigits.size() - 1;
	int startDigit = m_vCurrentDP.size() - vDigits.size();
	if (startDigit <= 0)
		startDigit = 0;

	int digitIndex = 0;
	int digitNumber = 0;
	for (auto iter : m_vCurrentDP)
	{
		if (digitIndex < startDigit)
		{
			iter->setVisible(false);
		}
		else
		{
			m_vCurrentDP[digitIndex]->setVisible(true);
			std::string imageKey = battleShipUIDPNumberNS::DP_KEY_NORMAL + std::to_string(vDigits[digitVectorLastIndex - digitNumber]);
			m_vCurrentDP[digitIndex]->setTextureManager(IMAGEMANAGER->getTexture(imageKey));
			digitNumber++;
		}
		digitIndex++;
	}
}

void CBattle_ShipUI_DPNumber::setupMaxDP(float maxDP)
{
	std::vector<int> vDigits;
	if (maxDP <= 0)
	{
		vDigits.push_back(0);
	}
	else
	{
		int number = maxDP;
		while (number != 0)
		{
			int last = number % 10;
			vDigits.push_back(last);
			number = (number - last) / 10;
		}
	}

	int digitVectorLastIndex = vDigits.size() - 1;
	int startDigit = m_vMaxDP.size() - vDigits.size();
	if (startDigit <= 0)
		startDigit = 0;

	int digitIndex = 0;
	int digitNumber = 0;
	for (auto iter : m_vMaxDP)
	{
		if (digitIndex < startDigit)
		{
			iter->setVisible(false);
		}
		else
		{
			m_vMaxDP[digitIndex]->setVisible(true);
			std::string imageKey = battleShipUIDPNumberNS::DP_KEY_NORMAL + std::to_string(vDigits[digitVectorLastIndex - digitNumber]);
			m_vMaxDP[digitIndex]->setTextureManager(IMAGEMANAGER->getTexture(imageKey));
			digitNumber++;
		}
		digitIndex++;
	}
}
