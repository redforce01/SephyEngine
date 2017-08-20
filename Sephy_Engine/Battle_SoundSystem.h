#ifndef _BATTLE_SOUNDSYSTEM_H
#define _BATTLE_SOUNDSYSTEM_H
#define WIN32_LEAN_AND_MEAN

class CBattle_SoundSystem;

#include <map>

namespace battleSoundSystemNS
{
	const std::string ERROR_MESSAGE = "Battle Sound System Initialize Failed";
	const std::string BATTLE_BGM_START		= "battle2";
	const std::string BATTLE_BGM_BATTLE		= "";
	const std::string BATTLE_BGM_WINNING	= "";
	const std::string BATTLE_BGM_LOSING		= "";
	const float SOUND_CHANGE_SPEED = 1.0f;	
}

enum class SOUND_SITUATION_TYPE
{
	BATTLE_SOUND_PEACE, BATTLE_SOUND_BATTLE, BATTLE_SOUND_WINNING, BATTLE_SOUND_LOSING
};
class CBattle_SoundSystem
{
private:
	std::map<std::string, std::string> m_mBGM;

private:
	bool m_bChange;
	float m_fCurrentVolume;
	std::string m_strCurrentBGM;
	std::string m_strNextBGM;
	SOUND_SITUATION_TYPE m_enSituationType;
public:
	CBattle_SoundSystem();
	~CBattle_SoundSystem();

	bool initialize();
	void update(float frameTime);

	void changeSituation(SOUND_SITUATION_TYPE situation);

	void changeBGM(std::string bgmKey);
	void stopBGM(std::string bgmKey);
	void pauseBGM(std::string bgmKey);
};

#endif // !_BATTLE_SOUNDSYSTEM_H
