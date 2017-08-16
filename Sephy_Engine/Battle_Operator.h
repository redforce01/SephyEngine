#ifndef _BATTLE_OPERATOR_H
#define _BATTLE_OPERATOR_H
#define WIN32_LEAN_AND_MEAN

class CBattle_Operator;

#include <string>
#include "image.h"
#include "systemUIDialog.h"

namespace battleOperatorNS
{
	const std::string ERROR_MESSAGE = "Battle Operator Initialize Failed";
	//==================================================================
	// OPERATOR - FRAME SIZE
	const UINT OPERATOR_N_MAX_FRAME = 30;
	const UINT OPERATOR_O_MAX_FRAME = 30;
	const UINT OPERATOR_P_MAX_FRAME = 15;
	// OPERATOR - IMAGE SIZE
	const float OPERATOR_IMAGE_WIDTH = 63;
	const float OPERATOR_IMAGE_HEIGHT = 50;
	//==================================================================
	// OPERATOR - CAPTAIN LIST
	const std::string OPERATOR_CAPTAIN_N_KEY = "OperatorBreathN_";
	const std::string OPERATOR_CAPTAIN_O_KEY = "OperatorOrderO_";
	const std::string OPERATOR_CAPTAIN_P_KEY = "OperatorSaluteP_";
	// OPERATOR - SAILOR
	const std::string OPERATOR_SAILOR_N_KEY = "SailorBreathN_";
	const std::string OPERATOR_SAILOR_O_KEY = "SailorHeadO_";
	const std::string OPERATOR_SAILOR_P_KEY = "SailorAttentionP_";
	// OPERATOR - KAKI
	const std::string OPERATOR_KAKI_N_KEY = "KakiBreathN_";
	const std::string OPERATOR_KAKI_O_KEY = "KakiHeadO_";
	const std::string OPERATOR_KAKI_P_KEY = "KakiAttentionP_";
	// OPERATOR - GUNNER
	const std::string OPERATOR_GUNNER_N_KEY = "AAGunnerBreathN_";
	const std::string OPERATOR_GUNNER_O_KEY = "AAGunnerAirO_";
	const std::string OPERATOR_GUNNER_P_KEY = "AAGunnerAttentionP_";
	// OPERATOR - ENGINEER
	const std::string OPERATOR_ENGINEER_N_KEY = "EngineerBreathN_";
	const std::string OPERATOR_ENGINEER_O_KEY = "EngineerWeldR_";
	const std::string OPERATOR_ENGINEER_P_KEY = "EngineerAttention_";
	// OPERATOR - PILOT
	const std::string OPERATOR_PILOT_N_KEY = "PilotBreathN_";
	const std::string OPERATOR_PILOT_O_KEY = "PilotShoulderO_";
	const std::string OPERATOR_PILOT_P_KEY = "PilotAttentionP_";
	//==================================================================
	const float OPERATOR_MESSAGE_TIME = 5.0f;
	const float OPERATOR_RELATE_X = 0;
	const float OPERATOR_RELATE_Y = 0;
	//==================================================================
	const float OPERATOR_DIALOG_X = -210.f;
	const float OPERATOR_DIALOG_Y = 500;
	const float OPERATOR_DIALOG_WIDTH = 200.f;
	const float OPERATOR_DIALOG_HEIGHT = 50.f;
	const float OPERATOR_MESSAGE_BOX_WIDTH = 280;
	const float OPERATOR_MESSAGE_BOX_HEIGHT = 35.f;
	//==================================================================
	const char FONT[] = "Courier New";
	const int FONT_HEIGHT = 14;
	const COLOR_ARGB FONT_COLOR = graphicsNS::WHITE;
	const COLOR_ARGB BACK_COLOR = SETCOLOR_ARGB(192, 26, 32, 44);
	//==================================================================
	const std::string OPERATOR_EFFECT_SOUND_NAME = "operator_message_effect";
}

namespace battleOperatorMessageNS
{
	const std::string SHIP_RESPAWN_COMPLETE = " Ready to Battle";
}

//=========================================
// Enum Class - OPERATOR TYPE
//  + OPERATOR_TYPE_CAPTAIN
//  + OPERATOR_TYPE_KAKI
//  + OPERATOR_TYPE_SAILOR
//  + OPERATOR_TYPE_ENGINEER
//  + OPERATOR_TYPE_PILOT
//  + OPERATOR_TYPE_GUNNER
//=========================================
enum class OPERATOR_TYPE
{
	OPERATOR_TYPE_CAPTAIN, OPERATOR_TYPE_KAKI, OPERATOR_TYPE_SAILOR,
	OPERATOR_TYPE_ENGINEER, OPERATOR_TYPE_PILOT, OPERATOR_TYPE_GUNNER
};

//=========================================
// Enum Class - OPERATOR SITUATION TYPE
//  + SITUATION_N : Normal Case
//  + SITUATION_O : Operating Case
//  + SITUATION_P : Setup Unit Case
//=========================================
enum class OPERATOR_SITUATION_TYPE
{ OPERATOR_SITUATION_N, OPERATOR_SITUATION_O, OPERATOR_SITUATION_P };

class CBattle_Operator : public SystemUIDialog
{
private:
	Image*					m_pOperator;
	int						m_nCurrentSpriteNumber;
	int						m_nMaxFrame;
	float					m_fOperatorTime;
	RECT					m_rcMessage;
	std::string				m_strMessage;
	OPERATOR_TYPE			m_enOperatorType;
	OPERATOR_SITUATION_TYPE m_enSituationType;
private:
	float	m_fEventX, m_fEventY;
	bool	m_bEventPosition;
private:
	bool m_bOperatorComplete;
	bool m_bSoundEffectPlayed;
public:
	CBattle_Operator();
	~CBattle_Operator();

	virtual bool initialize(Graphics* g, Input* i) override;
	virtual void update(float frameTime) override;
	virtual void render() override;

	//======================================================
	// Member Functions
	//======================================================

	void setupOperator(OPERATOR_TYPE operatorType, OPERATOR_SITUATION_TYPE situationType, std::string message);
	void setupEventPosition(float x, float y);

	void moveX(float distance)
	{
		m_fEventX += distance;
	}
	void moveY(float distance)
	{
		m_fEventY += distance;
	}

private:
	std::string recogOperatorKey(OPERATOR_TYPE operatorType, OPERATOR_SITUATION_TYPE situationType);

public:
	//======================================================
	// Getter Functions
	//======================================================

	bool IsOperatorComplete() const
	{
		return m_bOperatorComplete;
	}
};

#endif // !_BATTLE_OPERATOR_H