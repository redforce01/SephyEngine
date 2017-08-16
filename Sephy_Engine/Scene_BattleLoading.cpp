#include "stdafx.h"
#include "Scene_BattleLoading.h"


CScene_BattleLoading::CScene_BattleLoading() : Game()
{
	m_pBlackBack			= nullptr;
	m_pLoadingBackground	= nullptr;
	m_pProgressBarBack		= nullptr;
	m_pProgressBar			= nullptr;
	m_bLoadingStart			= false;
	//================================
	m_fBackAlpha	= 0;
	m_bVisible		= true;
}


CScene_BattleLoading::~CScene_BattleLoading()
{
	SAFE_DELETE(m_pBlackBack);
	SAFE_DELETE(m_pLoadingBackground);
	SAFE_DELETE(m_pProgressBarBack);
	SAFE_DELETE(m_pProgressBar);

	releaseAll();
}

void CScene_BattleLoading::initialize(HWND hwnd)
{
	Game::initialize(hwnd);

	m_pBlackBack = new Image;
	m_pBlackBack->initialize(graphics, 0, 0, 0, IMAGEMANAGER->getTexture(sceneBattleLoadingNS::LOADING_BLACK_BACKGROUND));
	m_pBlackBack->setColorFilter(sceneBattleLoadingNS::LOADING_BLACK_BACK_COLOR_FILTER);
	
	int random = RANDOM_MAKER->GetInt(1, 3);
	std::string loadingBackKey = sceneBattleLoadingNS::LOADING_BACKGROUND_KEY + std::to_string(random);
	m_pLoadingBackground = new Image;
	m_pLoadingBackground->initialize(graphics, 0, 0, 0, IMAGEMANAGER->getTexture(loadingBackKey));
	m_pLoadingBackground->setX((g_fScreenWidth / 2) - (m_pLoadingBackground->getWidth() / 2));
	m_pLoadingBackground->setY((g_fScreenHeight / 2) - (m_pLoadingBackground->getHeight() / 2) + sceneBattleLoadingNS::LOADING_BACKGROUND_RELATE_Y);

	m_pProgressBarBack = new Image;
	m_pProgressBarBack->initialize(graphics, 0, 0, 0, IMAGEMANAGER->getTexture(sceneBattleLoadingNS::LOADING_PROGRESS_BACK_FILENAME));
	m_pProgressBarBack->setX((g_fScreenWidth / 2) - (m_pProgressBarBack->getWidth() / 2));
	m_pProgressBarBack->setY(g_fScreenHeight - (m_pProgressBarBack->getHeight() / 2) + sceneBattleLoadingNS::LOADING_PROGRESS_BACK_RELATE_Y);
	m_pProgressBar = new Image;
	m_pProgressBar->initialize(graphics, 0, 0, 0, IMAGEMANAGER->getTexture(sceneBattleLoadingNS::LOADING_PROGRESS_FILENAME));
	m_pProgressBar->setX((g_fScreenWidth / 2) - (m_pProgressBar->getWidth() / 2));
	m_pProgressBar->setY(g_fScreenHeight - (m_pProgressBar->getHeight() / 2) + sceneBattleLoadingNS::LOADING_PROGRESS_BAR_RELATE_Y);
	auto spriteRect = m_pProgressBar->getSpriteDataRect();
	spriteRect.right = spriteRect.left;
	m_pProgressBar->setSpriteDataRect(spriteRect);
}

void CScene_BattleLoading::update()
{
	m_fLoadingTime += frameTime;
	if (m_bLoadingStart == false)
	{
		if (m_bVisible)
		{
			m_fBackAlpha += sceneBattleLoadingNS::LOADING_BACKGROUND_ALPHA_SPEED;
			m_pLoadingBackground->setColorFilter(SETCOLOR_ARGB((int)m_fBackAlpha, 255, 255, 255));
			if (m_fBackAlpha >= 255)
			{
				m_fBackAlpha = 255.f;
				m_bVisible = false;
			}
		}
		else
		{
			m_fBackAlpha -= sceneBattleLoadingNS::LOADING_BACKGROUND_ALPHA_SPEED;
			m_pLoadingBackground->setColorFilter(SETCOLOR_ARGB((int)m_fBackAlpha, 255, 255, 255));
			if (m_fBackAlpha <= 0)
			{
				int random = RANDOM_MAKER->GetInt(1, 3);
				std::string loadingBackKey = sceneBattleLoadingNS::LOADING_BACKGROUND_KEY + std::to_string(random);
				m_bVisible = true;
				m_fBackAlpha = 0.f;
				m_pLoadingBackground->setTextureManager(IMAGEMANAGER->getTexture(loadingBackKey));
			}
		}
	}
}

void CScene_BattleLoading::release()
{
}

void CScene_BattleLoading::ai()
{
}

void CScene_BattleLoading::collisions()
{
}

void CScene_BattleLoading::render()
{
	graphics->spriteBegin();
	m_pBlackBack->draw();
	m_pLoadingBackground->draw();
	m_pProgressBarBack->draw();
	m_pProgressBar->draw();
	graphics->spriteEnd();
}

void CScene_BattleLoading::releaseAll()
{
	Game::releaseAll();
	return;
}

void CScene_BattleLoading::resetAll()
{
	Game::resetAll();
	return;
}
