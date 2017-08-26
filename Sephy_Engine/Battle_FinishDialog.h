#ifndef _BATTLE_FINISH_DIALOG_H
#define _BATTLE_FINISH_DIALOG_H
#define WIN32_LEAN_AND_MEAN

class CBattle_FinishDialog;

#include "systemUIDialog.h"
#include "systemButton.h"

namespace battleFinishDialogNS
{
	const std::string ERROR_MESSAGE = "Battle Finish Dialog Initialize Failed";
	//========================================================
	const std::string WIN_TEXT_SPRITE_NAME = "Finish_Win";
	const std::string LOSE_TEXT_SPRITE_NAME = "Finish_Lose";
	const float DIALOG_WIDTH = 250.f;
	const float DIALOG_HEIGHT = 120.f;
	//========================================================
	const std::string OK_BUTTON_NAME = "OK";
	const float OK_BUTTON_RELATE_X = -45.f; // (mean : dialog centerX - (buttonWidth / 2))
	const float OK_BUTTON_RELATE_Y = 20;	// (mean : dialog centerY + 20)
	//========================================================
	const COLOR_ARGB DIALOG_BACK_COLOR = SETCOLOR_ARGB(255, 26, 32, 44);
}

class CBattle_FinishDialog : public SystemUIDialog
{
private:
	Image* m_pText;
	SystemButton* m_pOKButton;

public:
	CBattle_FinishDialog();
	~CBattle_FinishDialog();

	virtual bool initialize(Graphics* g, Input* i) override;
	virtual void update(float frameTime) override;
	virtual void render() override;

	static void functionOKButton();

	void setupWinLose(bool bWin)
	{
		if (bWin)
		{
			m_pText->setTextureManager(IMAGEMANAGER->getTexture(battleFinishDialogNS::WIN_TEXT_SPRITE_NAME));
		}
		else
			m_pText->setTextureManager(IMAGEMANAGER->getTexture(battleFinishDialogNS::LOSE_TEXT_SPRITE_NAME));
	}
};

#endif // !_BATTLE_FINISH_DIALOG_H
