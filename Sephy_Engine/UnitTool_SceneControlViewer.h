#ifndef _UNITTOOL_SCENECONTROL_VIEWER_H
#define _UNITTOOL_SCENECONTROL_VIEWER_H
#define WIN32_LAEN_AND_MEAN

class CUnitTool_SceneControlViewer;

#include "systemUIDialog.h"
#include "systemButton.h"

namespace unitToolSceneControlViewerNS
{

	const std::string ERROR_MESSAGE = "Unit Tool Scene Control Viewer Initialize Failed";
	const UINT VIEWER_RELATE_X = 0; // (mean : centerX - VIEWER_WIDTH)
	const UINT VIEWER_RELATE_Y = 10;
	const UINT VIEWER_WIDTH = 150;
	const UINT VIEWER_HEIGHT = 50;

	const COLOR_ARGB BACK_COLOR = SETCOLOR_ARGB(192, 26, 32, 44);

	const std::string PLAY_STATUS_ICON_PAUSE_FILENAME = "PlayStatus_bPAUSE";
	const std::string PLAY_STATUS_ICON_PLAY_FILENAME = "PlayStatus_bPLAY";
	const std::string PLAY_STATUS_ICON_STOP_FILENAME = "PlayStatus_bSTOP";
	const std::string PLAY_STATUS_MSG_PAUSE_FILENAME = "PlayStatus_tPAUSE";
	const std::string PLAY_STATUS_MSG_PLAY_FILENAME = "PlayStatus_tPLAY";
	const std::string PLAY_STATUS_MSG_STOP_FILENAME = "PlayStatus_tSTOP";

	const std::string PLAY_BUTTON_FILENAME = "Replay";
	const std::string STOP_BUTTON_FILENAME = "PlayCancel";
	const UINT PLAY_BUTTON_RELATE_X = 5;
	const UINT PLAY_BUTTON_RELATE_Y = 25;
	const UINT STOP_BUTTON_RELATE_X = 75;
	const UINT STOP_BUTTON_RELATE_Y = 25;

	const UINT PLAY_STATUS_ICON_RELATE_X = 5;
	const UINT PLAY_STATUS_MSG_RELATE_Y = 5;
}

enum class SCENE_PLAY_STATE
{
	SCENE_STATE_PLAY, SCENE_STATE_STOP, SCENE_STATE_PAUSE
};

class CUnitTool_RespawnListViewer;
class CUnitTool_UnitControlSystem;
class CUnitTool_SceneControlViewer : public SystemUIDialog
{
private:
	CUnitTool_UnitControlSystem* m_pUnitControlSystem;
	CUnitTool_RespawnListViewer* m_pRespawnListViewer;
public:
	void setMemoryLinkUnitControlSystem(CUnitTool_UnitControlSystem* pUnitControlSystem)
	{
		m_pUnitControlSystem = pUnitControlSystem;
	}
	void setMemoryLinkRespawnListViewer(CUnitTool_RespawnListViewer* pRespawnListViewer)
	{
		m_pRespawnListViewer = pRespawnListViewer;
	}
private:
	bool m_bPlay;
	SCENE_PLAY_STATE m_enPlayStatus;

	std::string m_strStatusIconKey;
	std::string m_strStatusMessageKey;
	Image m_pPlayStateMessage;
	Image m_pPlayStateIcon;

	SystemButton m_PlayButton;
	SystemButton m_StopButton;

public:
	CUnitTool_SceneControlViewer();
	~CUnitTool_SceneControlViewer();


	virtual bool initialize(Graphics* g, Input* i) override;
	virtual void update(float frameTime) override;
	virtual void render() override;

	//===================================================
	// Member Functions
	//===================================================

	static void funcPlayButton();
	static void funcStopButton();

	//===================================================
	// Setter Functions
	//===================================================

	void setPlay(bool bPlay)
	{
		m_bPlay = bPlay;
	}

	//===================================================
	// Getter Functions
	//===================================================

	bool isPlay() const
	{
		return m_bPlay;
	}

};

#endif // !_UNITTOOL_SCENECONTROL_VIEWER_H
