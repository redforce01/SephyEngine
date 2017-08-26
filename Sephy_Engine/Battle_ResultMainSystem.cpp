#include "stdafx.h"
#include "Battle_ResultMainSystem.h"


CBattle_ResultMainSystem::CBattle_ResultMainSystem()
{
	m_pBlackBack				= nullptr;
	m_pResultBackground			= nullptr;
	m_pResultSystem				= nullptr;
	m_pOKButton					= nullptr;
	m_pResultPlayerView			= nullptr;
	m_pResultEnemyView			= nullptr;
	m_pResultPanelText			= nullptr;
	m_pResultPanelTextShadow	= nullptr;
	//===========================================
	m_fBackgroundTime			= 0.f;
	m_fAlphaValue				= 0.f;
	m_bChangeImage				= false;
	m_bBackVisible				= true;
}


CBattle_ResultMainSystem::~CBattle_ResultMainSystem()
{
	SAFE_DELETE(m_pResultSystem);
	SAFE_DELETE(m_pBlackBack);
	SAFE_DELETE(m_pResultBackground);
	SAFE_DELETE(m_pOKButton);
	SAFE_DELETE(m_pResultPlayerView);
	SAFE_DELETE(m_pResultEnemyView);
	SAFE_DELETE(m_pResultPanelText);
	SAFE_DELETE(m_pResultPanelTextShadow);
}

bool CBattle_ResultMainSystem::initialize(Game * gamePtr)
{
	bool success = false;
	try
	{
		m_pGraphics = gamePtr->getGraphics();
		m_pInput = gamePtr->getInput();
		//=================================================================
		// Battle Result System Load
		//=================================================================
		m_pResultSystem = new CBattle_ResultSystem;
		m_pResultSystem->loadBattleResult();
		//=================================================================
		// Background Iamge & Black Panel Initialize
		//=================================================================
		m_pBlackBack = new Image;
		success = m_pBlackBack->initialize(m_pGraphics, 0, 0, 0, IMAGEMANAGER->getTexture(battleResultMainSystemNS::LOADING_BLACK_BACKGROUND));
		m_pBlackBack->setColorFilter(battleResultMainSystemNS::LOADING_BLACK_BACK_COLOR_FILTER);
		m_pResultBackground = new Image;
		success = m_pResultBackground->initialize(m_pGraphics, 0, 0, 0, IMAGEMANAGER->getTexture(battleResultMainSystemNS::BATTLE_RESULT_BACKGROUND_0));
		m_pResultBackground->setX((g_fScreenWidth / 2) - (m_pResultBackground->getWidth() / 2));
		m_pResultBackground->setY((g_fScreenHeight / 2) - (m_pResultBackground->getHeight() / 2));
		//=================================================================
		// OK BUTTON INITIALIZE
		//=================================================================
		m_pOKButton = new SystemButton;
		success = m_pOKButton->initialize(m_pGraphics, m_pInput,
			g_fScreenWidth + battleResultMainSystemNS::OK_BUTTON_RELATE_X,
			g_fScreenHeight + battleResultMainSystemNS::OK_BUTTON_RELATE_Y,
			battleResultMainSystemNS::OK_BUTTON_NAME, true);
		m_pOKButton->setRegistFunction(std::bind(&CBattle_ResultMainSystem::functionOKButton));
		//=================================================================
		// PLAYER View Initialize
		//=================================================================
		m_pResultPlayerView = new CBattle_ResultPlayerView;
		m_pResultPlayerView->initialize(m_pGraphics, m_pInput);
		auto vPlayerShipList = m_pResultSystem->getResultPlayerShips();
		auto playerScore = m_pResultSystem->getResultPlayerScore();
		for (auto iter : vPlayerShipList)
		{
			m_pResultPlayerView->addListItem(iter);
		}
		m_pResultPlayerView->setupDamageScore(playerScore);
		//=================================================================
		// ENEMY View Initialize
		//=================================================================
		m_pResultEnemyView = new CBattle_ResultEnemyView;
		m_pResultEnemyView->initialize(m_pGraphics, m_pInput);
		auto vEnemyShipList = m_pResultSystem->getResultComputerShips();
		float enemyScore = m_pResultSystem->getResultComputerScore();
		for (auto iter : vEnemyShipList)
		{
			m_pResultEnemyView->addListItem(iter);
		}
		//=================================================================
		// Result Text Image & Shadow Image Initialize
		//=================================================================
		m_pResultPanelText = new Image;
		m_pResultPanelText->initialize(m_pGraphics, 0, 0, 0, IMAGEMANAGER->getTexture(battleResultMainSystemNS::RESULT_PANEL_TEXT));
		m_pResultPanelText->setX(battleResultMainSystemNS::RESULT_PANEL_RELATE_X);
		m_pResultPanelText->setY(battleResultMainSystemNS::RESULT_PANEL_RELATE_Y);
		m_pResultPanelTextShadow = new Image;
		m_pResultPanelTextShadow->initialize(m_pGraphics, 0, 0, 0, IMAGEMANAGER->getTexture(battleResultMainSystemNS::RESULT_PANEL_TEXT_SHADOW));
		m_pResultPanelTextShadow->setX(battleResultMainSystemNS::RESULT_PANEL_RELATE_X);
		m_pResultPanelTextShadow->setY(battleResultMainSystemNS::RESULT_PANEL_RELATE_Y);
		m_pResultPanelTextShadow->setColorFilter(battleResultMainSystemNS::RESULT_PANEL_SHADOW_COLOR_FILTER);
	}
	catch (...)
	{
		MessageBox(g_hWndEngine, battleResultMainSystemNS::ERROR_MESSAGE.c_str(), "Error", MB_OK);
	}
	return success;
}

void CBattle_ResultMainSystem::update(float frameTime)
{
	m_fBackgroundTime += frameTime;
	if (m_bBackVisible)
	{
		m_fAlphaValue += 1.0f;
		m_pResultBackground->setColorFilter(SETCOLOR_ARGB((int)m_fAlphaValue, 255, 255, 255));
		if (m_fAlphaValue >= 255)
		{
			m_fAlphaValue = 255.f;
			m_bBackVisible = false;
		}
	}
	else
	{
		m_fAlphaValue -= 1.0f;
		m_pResultBackground->setColorFilter(SETCOLOR_ARGB((int)m_fAlphaValue, 255, 255, 255));
		if (m_fAlphaValue <= 0)
		{
			int random = RANDOM_MAKER->GetInt(0, 2);
			std::string loadingBackKey = battleResultMainSystemNS::BATTLE_RESULT_BACKGROUND_KEY + std::to_string(random);
			m_bBackVisible = true;
			m_fAlphaValue = 0.f;
			m_pResultBackground->setTextureManager(IMAGEMANAGER->getTexture(loadingBackKey));
			if (random == 0)
			{
				m_pResultBackground->setX((g_fScreenWidth / 2) - (battleResultMainSystemNS::BATTLE_BACKGROUND_TYPE_A_WIDTH / 2));
				m_pResultBackground->setY((g_fScreenHeight / 2) - (battleResultMainSystemNS::BATTLE_BACKGROUND_TYPE_A_HEIGHT / 2));
				RECT rc = RectMake(0, 0, battleResultMainSystemNS::BATTLE_BACKGROUND_TYPE_A_WIDTH, battleResultMainSystemNS::BATTLE_BACKGROUND_TYPE_A_HEIGHT);
				m_pResultBackground->setSpriteDataRect(rc);
			}
			else
			{
				m_pResultBackground->setX((g_fScreenWidth / 2) - (battleResultMainSystemNS::BATTLE_BACKGROUND_TYPE_B_WIDTH / 2));
				m_pResultBackground->setY((g_fScreenHeight / 2) - (battleResultMainSystemNS::BATTLE_BACKGROUND_TYPE_B_HEIGHT / 2));
				RECT rc = RectMake(0, 0, battleResultMainSystemNS::BATTLE_BACKGROUND_TYPE_B_WIDTH, battleResultMainSystemNS::BATTLE_BACKGROUND_TYPE_B_HEIGHT);
				m_pResultBackground->setSpriteDataRect(rc);
			}
		}
	}

	m_pResultPlayerView->update(frameTime);
	m_pResultEnemyView->update(frameTime);
	m_pOKButton->update(frameTime);
}

void CBattle_ResultMainSystem::render()
{
	m_pGraphics->spriteBegin();
	m_pBlackBack->draw();
	m_pResultBackground->draw();
	m_pResultPanelTextShadow->draw();
	m_pResultPanelText->draw();
	m_pGraphics->spriteEnd();
	m_pResultPlayerView->render();
	m_pResultEnemyView->render();
	m_pOKButton->render();
}

void CBattle_ResultMainSystem::functionOKButton()
{
	SCENEMANAGER->changeScene("World");
	//SCENEMANAGER->changeSceneWithLoading("World", "BattleLoading");
}
