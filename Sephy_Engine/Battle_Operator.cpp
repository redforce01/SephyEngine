#include "stdafx.h"
#include "Battle_Operator.h"


CBattle_Operator::CBattle_Operator() : SystemUIDialog()
{
	m_pOperator				= nullptr;
	m_nCurrentSpriteNumber	= 0;
	m_nMaxFrame				= 0;
	m_fOperatorTime			= 0.f;
	m_enOperatorType		= OPERATOR_TYPE::OPERATOR_TYPE_CAPTAIN;
	m_enSituationType		= OPERATOR_SITUATION_TYPE::OPERATOR_SITUATION_N;
	m_fEventX				= 0.f;
	m_fEventY				= 0.f;
	m_bEventPosition		= false;
	m_bSoundEffectPlayed	= false;
	//====================================================
	fontColor = battleOperatorNS::FONT_COLOR;
	backColor = battleOperatorNS::BACK_COLOR;
}


CBattle_Operator::~CBattle_Operator()
{
	SAFE_DELETE(m_pOperator);
}

bool CBattle_Operator::initialize(Graphics * g, Input * i)
{
	bool success = false;
	try
	{
		m_pGraphics = g;
		m_pInput = i;
		m_pOperator = new Image;
		if (m_pOperator == nullptr)
			return false;

		success = SystemUIDialog::initializeDialog(m_pGraphics, m_pInput,
			g_fScreenWidth + battleOperatorNS::OPERATOR_DIALOG_X,
			battleOperatorNS::OPERATOR_DIALOG_Y,
			battleOperatorNS::OPERATOR_DIALOG_WIDTH,
			battleOperatorNS::OPERATOR_DIALOG_HEIGHT, 0);
		m_rcMessage = RectMake(
			SystemUIDialog::getDialogX() + 10, SystemUIDialog::getDialogY() + 20,
			battleOperatorNS::OPERATOR_MESSAGE_BOX_WIDTH, battleOperatorNS::OPERATOR_MESSAGE_BOX_HEIGHT);

		success = m_dxFont.initialize(m_pGraphics, battleOperatorNS::FONT_HEIGHT, false, false, battleOperatorNS::FONT);
	}
	catch (...)
	{
		MessageBox(g_hWndEngine, battleOperatorNS::ERROR_MESSAGE.c_str(), "Error", MB_OK);
	}

	return success;
}

void CBattle_Operator::update(float frameTime)
{
	if (m_bVisible == false)
		return;
	
	SystemUIDialog::update(frameTime);
	
	if (m_bOperatorComplete)
		return;

	if (m_bSoundEffectPlayed == false)
	{
		SOUNDMANAGER->play(battleOperatorNS::OPERATOR_EFFECT_SOUND_NAME, g_fSoundMasterVolume * g_fSoundEffectVolume);
		m_bSoundEffectPlayed = true;
	}

	if (m_fOperatorTime > battleOperatorNS::OPERATOR_MESSAGE_TIME)
		m_bOperatorComplete = true;

	m_fOperatorTime += frameTime;

	std::string operatorKey;
	switch (m_enSituationType)
	{
	case OPERATOR_SITUATION_TYPE::OPERATOR_SITUATION_N:
		if (m_nCurrentSpriteNumber < battleOperatorNS::OPERATOR_N_MAX_FRAME)
		{
			operatorKey = recogOperatorKey(m_enOperatorType, m_enSituationType);
			if (m_nCurrentSpriteNumber < 10)
			{
				operatorKey += "00" + std::to_string(m_nCurrentSpriteNumber);
			}
			else
				operatorKey += "0" + std::to_string(m_nCurrentSpriteNumber);

			m_pOperator->setTextureManager(IMAGEMANAGER->getTexture(operatorKey));
			m_nCurrentSpriteNumber++;
		}
		break;
	case OPERATOR_SITUATION_TYPE::OPERATOR_SITUATION_O:
		if (m_nCurrentSpriteNumber < battleOperatorNS::OPERATOR_O_MAX_FRAME)
		{
			operatorKey = recogOperatorKey(m_enOperatorType, m_enSituationType);
			if (m_nCurrentSpriteNumber < 10)
			{
				operatorKey += "00" + std::to_string(m_nCurrentSpriteNumber);
			}
			else
				operatorKey += "0" + std::to_string(m_nCurrentSpriteNumber);

			m_pOperator->setTextureManager(IMAGEMANAGER->getTexture(operatorKey));
			m_nCurrentSpriteNumber++;
		}
		break;
	case OPERATOR_SITUATION_TYPE::OPERATOR_SITUATION_P:
		if (m_nCurrentSpriteNumber < battleOperatorNS::OPERATOR_P_MAX_FRAME)
		{
			operatorKey = recogOperatorKey(m_enOperatorType, m_enSituationType);
			if (m_nCurrentSpriteNumber < 10)
			{
				operatorKey += "00" + std::to_string(m_nCurrentSpriteNumber);
			}
			else
				operatorKey += "0" + std::to_string(m_nCurrentSpriteNumber);

			m_pOperator->setTextureManager(IMAGEMANAGER->getTexture(operatorKey));
			m_nCurrentSpriteNumber++;
		}
		break;
	}
}

void CBattle_Operator::render()
{
	if (m_bVisible == false)
		return;

	if (m_bOperatorComplete)
		return;

	SystemUIDialog::render();

	m_pGraphics->spriteBegin();
	m_dxFont.print(m_strMessage, m_rcMessage, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
	m_pOperator->draw();
	m_pGraphics->spriteEnd();
}

void CBattle_Operator::setupOperator(OPERATOR_TYPE operatorType, OPERATOR_SITUATION_TYPE situationType, std::string message)
{
	m_strMessage = message;
	m_enOperatorType = operatorType;
	m_enSituationType = situationType;

	std::string operatorSpriteKey;
	operatorSpriteKey = recogOperatorKey(m_enOperatorType, m_enSituationType);

	if (m_nCurrentSpriteNumber < 10)
	{
		operatorSpriteKey += "00" + std::to_string(m_nCurrentSpriteNumber);
	}
	else
		operatorSpriteKey += "0" + std::to_string(m_nCurrentSpriteNumber);

	m_pOperator->initialize(m_pGraphics, 0, 0, 0, IMAGEMANAGER->getTexture(operatorSpriteKey));
	m_pOperator->setX(SystemUIDialog::getDialogX() - (m_pOperator->getWidth() / 2));
	m_pOperator->setY(SystemUIDialog::getDialogY() - (m_pOperator->getHeight() / 2));
}

void CBattle_Operator::setupEventPosition(float x, float y)
{
	m_bEventPosition = true;
	m_fEventX = x;
	m_fEventY = y;
}

std::string CBattle_Operator::recogOperatorKey(OPERATOR_TYPE operatorType, OPERATOR_SITUATION_TYPE situationType)
{
	m_enOperatorType = operatorType;
	m_enSituationType = situationType;

	std::string operatorSpriteKey;
	switch (m_enOperatorType)
	{
	case OPERATOR_TYPE::OPERATOR_TYPE_CAPTAIN:
		switch (m_enSituationType)
		{
		case OPERATOR_SITUATION_TYPE::OPERATOR_SITUATION_N:
			operatorSpriteKey = battleOperatorNS::OPERATOR_CAPTAIN_N_KEY;
			break;
		case OPERATOR_SITUATION_TYPE::OPERATOR_SITUATION_O:
			operatorSpriteKey = battleOperatorNS::OPERATOR_CAPTAIN_O_KEY;
			break;
		case OPERATOR_SITUATION_TYPE::OPERATOR_SITUATION_P:
			operatorSpriteKey = battleOperatorNS::OPERATOR_CAPTAIN_P_KEY;
			break;
		}
		break;
	case OPERATOR_TYPE::OPERATOR_TYPE_KAKI:
		switch (m_enSituationType)
		{
		case OPERATOR_SITUATION_TYPE::OPERATOR_SITUATION_N:
			operatorSpriteKey = battleOperatorNS::OPERATOR_KAKI_N_KEY;
			break;
		case OPERATOR_SITUATION_TYPE::OPERATOR_SITUATION_O:
			operatorSpriteKey = battleOperatorNS::OPERATOR_KAKI_O_KEY;
			break;
		case OPERATOR_SITUATION_TYPE::OPERATOR_SITUATION_P:
			operatorSpriteKey = battleOperatorNS::OPERATOR_KAKI_P_KEY;
			break;
		}
		break;
	case OPERATOR_TYPE::OPERATOR_TYPE_SAILOR:
		switch (m_enSituationType)
		{
		case OPERATOR_SITUATION_TYPE::OPERATOR_SITUATION_N:
			operatorSpriteKey = battleOperatorNS::OPERATOR_SAILOR_N_KEY;
			break;
		case OPERATOR_SITUATION_TYPE::OPERATOR_SITUATION_O:
			operatorSpriteKey = battleOperatorNS::OPERATOR_SAILOR_O_KEY;
			break;
		case OPERATOR_SITUATION_TYPE::OPERATOR_SITUATION_P:
			operatorSpriteKey = battleOperatorNS::OPERATOR_SAILOR_P_KEY;
			break;
		}
		break;
	case OPERATOR_TYPE::OPERATOR_TYPE_ENGINEER:
		switch (m_enSituationType)
		{
		case OPERATOR_SITUATION_TYPE::OPERATOR_SITUATION_N:
			operatorSpriteKey = battleOperatorNS::OPERATOR_ENGINEER_N_KEY;
			break;
		case OPERATOR_SITUATION_TYPE::OPERATOR_SITUATION_O:
			operatorSpriteKey = battleOperatorNS::OPERATOR_ENGINEER_O_KEY;
			break;
		case OPERATOR_SITUATION_TYPE::OPERATOR_SITUATION_P:
			operatorSpriteKey = battleOperatorNS::OPERATOR_ENGINEER_P_KEY;
			break;
		}
		break;
	case OPERATOR_TYPE::OPERATOR_TYPE_PILOT:
		switch (m_enSituationType)
		{
		case OPERATOR_SITUATION_TYPE::OPERATOR_SITUATION_N:
			operatorSpriteKey = battleOperatorNS::OPERATOR_PILOT_N_KEY;
			break;
		case OPERATOR_SITUATION_TYPE::OPERATOR_SITUATION_O:
			operatorSpriteKey = battleOperatorNS::OPERATOR_PILOT_O_KEY;
			break;
		case OPERATOR_SITUATION_TYPE::OPERATOR_SITUATION_P:
			operatorSpriteKey = battleOperatorNS::OPERATOR_PILOT_P_KEY;
			break;
		}
		break;
	case OPERATOR_TYPE::OPERATOR_TYPE_GUNNER:
		switch (m_enSituationType)
		{
		case OPERATOR_SITUATION_TYPE::OPERATOR_SITUATION_N:
			operatorSpriteKey = battleOperatorNS::OPERATOR_GUNNER_N_KEY;
			break;
		case OPERATOR_SITUATION_TYPE::OPERATOR_SITUATION_O:
			operatorSpriteKey = battleOperatorNS::OPERATOR_GUNNER_O_KEY;
			break;
		case OPERATOR_SITUATION_TYPE::OPERATOR_SITUATION_P:
			operatorSpriteKey = battleOperatorNS::OPERATOR_GUNNER_P_KEY;
			break;
		}
		break;
	}

	return operatorSpriteKey;
}
