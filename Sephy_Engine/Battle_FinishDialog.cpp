#include "stdafx.h"
#include "Battle_FinishDialog.h"


CBattle_FinishDialog::CBattle_FinishDialog() : SystemUIDialog()
{
	m_pText = nullptr;
	m_pOKButton = nullptr;
	backColor = battleFinishDialogNS::DIALOG_BACK_COLOR;
}


CBattle_FinishDialog::~CBattle_FinishDialog()
{
	SAFE_DELETE(m_pText);
	SAFE_DELETE(m_pOKButton);
}

bool CBattle_FinishDialog::initialize(Graphics * g, Input * i)
{
	bool success = false;
	try
	{
		m_pGraphics = g;
		m_pInput = i;

		success = SystemUIDialog::initializeDialog(m_pGraphics, m_pInput,
			(g_fScreenWidth / 2) - (battleFinishDialogNS::DIALOG_WIDTH / 2),
			(g_fScreenHeight / 2) - (battleFinishDialogNS::DIALOG_HEIGHT / 2),
			battleFinishDialogNS::DIALOG_WIDTH,
			battleFinishDialogNS::DIALOG_HEIGHT);
		//==========================================================
		// Text Image Initialize
		//==========================================================
		m_pText = new Image;
		m_pText->initialize(m_pGraphics, 0, 0, 0, IMAGEMANAGER->getTexture(battleFinishDialogNS::WIN_TEXT_SPRITE_NAME));
		m_pText->setX(this->getDialogX());
		m_pText->setY(this->getDialogY());
		//==========================================================
		// OK Button Initialize
		//==========================================================
		m_pOKButton = new SystemButton;
		m_pOKButton->initialize(m_pGraphics, m_pInput,
			this->getDialogCenterX() + battleFinishDialogNS::OK_BUTTON_RELATE_X,
			this->getDialogCenterY() + battleFinishDialogNS::OK_BUTTON_RELATE_Y,
			battleFinishDialogNS::OK_BUTTON_NAME, true);
		m_pOKButton->setRegistFunction(std::bind(&CBattle_FinishDialog::functionOKButton));
	}
	catch (...)
	{
		MessageBox(g_hWndEngine, battleFinishDialogNS::ERROR_MESSAGE.c_str(), "Error", MB_OK);
	}
	return success;
}

void CBattle_FinishDialog::update(float frameTime)
{
	if (m_bVisible == false)
		return;

	SystemUIDialog::update(frameTime);
	m_pOKButton->update(frameTime);
}

void CBattle_FinishDialog::render()
{
	if (m_bVisible == false)
		return;

	SystemUIDialog::render();
	m_pGraphics->spriteBegin();
	m_pText->draw();
	m_pGraphics->spriteEnd();
	m_pOKButton->render();
}

void CBattle_FinishDialog::functionOKButton()
{
	SCENEMANAGER->changeScene("BattleResult");
	//SCENEMANAGER->changeSceneWithLoading("BattleResult", "BattleLoading");
}
