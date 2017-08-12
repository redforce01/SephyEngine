#include "stdafx.h"
#include "UnitTool_SceneControlViewer.h"
#include "UnitTool_UnitControlSystem.h"
#include "UnitTool_RespawnListViewer.h"

CUnitTool_SceneControlViewer* pThis = nullptr;
CUnitTool_SceneControlViewer::CUnitTool_SceneControlViewer()
{
	::pThis = this;
	m_pUnitControlSystem	= nullptr;
	m_pRespawnListViewer	= nullptr;
	backColor				= unitToolSceneControlViewerNS::BACK_COLOR;
	m_bPlay					= false;
	m_strStatusIconKey		= unitToolSceneControlViewerNS::PLAY_STATUS_ICON_STOP_FILENAME;
	m_strStatusMessageKey	= unitToolSceneControlViewerNS::PLAY_STATUS_MSG_STOP_FILENAME;
	m_enPlayStatus			= SCENE_PLAY_STATE::SCENE_STATE_STOP;
}


CUnitTool_SceneControlViewer::~CUnitTool_SceneControlViewer()
{
}

bool CUnitTool_SceneControlViewer::initialize(Graphics * g, Input * i)
{
	bool success = false;
	try
	{
		success = SystemUIDialog::initializeDialog(g, i,
			(g_fScreenWidth / 2) - (unitToolSceneControlViewerNS::VIEWER_WIDTH / 2),
			unitToolSceneControlViewerNS::VIEWER_RELATE_Y,
			unitToolSceneControlViewerNS::VIEWER_WIDTH,
			unitToolSceneControlViewerNS::VIEWER_HEIGHT, 0);

		m_PlayButton.initialize(m_pGraphics, m_pInput,			
			this->getDialogX() + unitToolSceneControlViewerNS::PLAY_BUTTON_RELATE_X,
			unitToolSceneControlViewerNS::PLAY_BUTTON_RELATE_Y,
			unitToolSceneControlViewerNS::PLAY_BUTTON_FILENAME, true);
		m_PlayButton.setRegistFunction(std::bind(&CUnitTool_SceneControlViewer::funcPlayButton));

		m_StopButton.initialize(m_pGraphics, m_pInput,
			this->getDialogX() + unitToolSceneControlViewerNS::STOP_BUTTON_RELATE_X,
			unitToolSceneControlViewerNS::STOP_BUTTON_RELATE_Y,
			unitToolSceneControlViewerNS::STOP_BUTTON_FILENAME, true);
		m_StopButton.setRegistFunction(std::bind(&CUnitTool_SceneControlViewer::funcStopButton));
		
		m_pPlayStateMessage.initialize(m_pGraphics, 0, 0, 0, IMAGEMANAGER->getTexture(m_strStatusIconKey));
		m_pPlayStateMessage.setX(this->getDialogX() + unitToolSceneControlViewerNS::PLAY_STATUS_ICON_RELATE_X);
		m_pPlayStateMessage.setY(this->getDialogY() + unitToolSceneControlViewerNS::PLAY_STATUS_MSG_RELATE_Y);
		m_pPlayStateIcon.initialize(m_pGraphics, 0, 0, 0, IMAGEMANAGER->getTexture(m_strStatusMessageKey));
		m_pPlayStateIcon.setX(this->getDialogX() + unitToolSceneControlViewerNS::PLAY_STATUS_ICON_RELATE_X);
		m_pPlayStateIcon.setY(this->getDialogY() + unitToolSceneControlViewerNS::PLAY_STATUS_MSG_RELATE_Y);
	}
	catch (...)
	{
		MessageBox(g_hWndEngine, unitToolSceneControlViewerNS::ERROR_MESSAGE.c_str(), "Error", MB_OK);
	}
	return success;
}

void CUnitTool_SceneControlViewer::update(float frameTime)
{
	if (m_bVisible == false)
		return;

	SystemUIDialog::update(frameTime);

	m_PlayButton.update(frameTime);
	m_StopButton.update(frameTime);

	switch (m_enPlayStatus)
	{
	case SCENE_PLAY_STATE::SCENE_STATE_PLAY:
		m_strStatusIconKey = unitToolSceneControlViewerNS::PLAY_STATUS_ICON_PLAY_FILENAME;
		m_strStatusMessageKey = unitToolSceneControlViewerNS::PLAY_STATUS_MSG_PLAY_FILENAME;
		m_pPlayStateMessage.setTextureManager(IMAGEMANAGER->getTexture(m_strStatusIconKey));
		m_pPlayStateIcon.setTextureManager(IMAGEMANAGER->getTexture(m_strStatusMessageKey));
		break;
	case SCENE_PLAY_STATE::SCENE_STATE_STOP:
		m_strStatusIconKey = unitToolSceneControlViewerNS::PLAY_STATUS_ICON_STOP_FILENAME;
		m_strStatusMessageKey = unitToolSceneControlViewerNS::PLAY_STATUS_MSG_STOP_FILENAME;
		m_pPlayStateMessage.setTextureManager(IMAGEMANAGER->getTexture(m_strStatusIconKey));
		m_pPlayStateIcon.setTextureManager(IMAGEMANAGER->getTexture(m_strStatusMessageKey));
		break;
	case SCENE_PLAY_STATE::SCENE_STATE_PAUSE:
		m_strStatusIconKey = unitToolSceneControlViewerNS::PLAY_STATUS_ICON_PAUSE_FILENAME;
		m_strStatusMessageKey = unitToolSceneControlViewerNS::PLAY_STATUS_MSG_PAUSE_FILENAME;
		m_pPlayStateMessage.setTextureManager(IMAGEMANAGER->getTexture(m_strStatusIconKey));
		m_pPlayStateIcon.setTextureManager(IMAGEMANAGER->getTexture(m_strStatusMessageKey));
		break;
	}	
}

void CUnitTool_SceneControlViewer::render()
{
	if (m_bVisible == false)
		return;

	SystemUIDialog::render();

	m_pGraphics->spriteBegin();
	m_pPlayStateMessage.draw();
	m_pPlayStateIcon.draw();
	m_pGraphics->spriteEnd();

	m_PlayButton.render();
	m_StopButton.render();
}

void CUnitTool_SceneControlViewer::funcPlayButton()
{
	auto bPlay = pThis->isPlay();
	pThis->setPlay(!bPlay);
	if (pThis->isPlay())
	{
		pThis->m_enPlayStatus = SCENE_PLAY_STATE::SCENE_STATE_PLAY;
		pThis->m_pUnitControlSystem->setUpdatable(true);
	}
	else
	{
		pThis->m_enPlayStatus = SCENE_PLAY_STATE::SCENE_STATE_PAUSE;
		pThis->m_pUnitControlSystem->setUpdatable(false);
	}
}

void CUnitTool_SceneControlViewer::funcStopButton()
{
	pThis->setPlay(false);
	pThis->m_enPlayStatus = SCENE_PLAY_STATE::SCENE_STATE_STOP;
	pThis->m_pUnitControlSystem->resetAllUnits();
	pThis->m_pUnitControlSystem->setUpdatable(false);
	pThis->m_pRespawnListViewer->resetShipList();
}
