#ifndef _SOUNDMANAGER_H
#define _SOUNDMANAGER_H
#define WIN32_LEAN_AND_MEAN

#include "inc/fmod.hpp"
#pragma comment (lib, "lib/fmodex_vc.lib")

#include "cSingletonBase.h"
#include <map>
#include <string>

using namespace FMOD;

#define EXTRA_SOUND_CHANNEL 100
#define SOUND_BUFFER 100
#define TOTAL_SOUND_CHANNEL SOUND_BUFFER  + EXTRA_SOUND_CHANNEL

namespace soundManagerNS
{
	const std::string SOUND_EFFECT_FOLDER_NAME = "80_Sound_Effect";
	const std::string SOUND_BGM_FOLDER_NAME = "81_Sound_BGM";
	const std::string SOUND_EFFECT_ALERT_FOLDER_NAME = "82_Sound_Battle_Alert";
	const std::string SOUND_EFFECT_OPERATOR_FOLDER_NAME = "83_Sound_Operator";
}

class CSoundManager : public cSingletonBase<CSoundManager>
{
private:
	typedef std::map<std::string, Sound**> arrSounds;
	typedef std::map<std::string, Sound**>::iterator arrSoundsIter;
	typedef std::map<std::string, Channel**> arrChannels;
	typedef std::map<std::string, Channel**>::iterator arrChannelsIter;

private:
	System* _system;
	Sound** _sound;
	Channel** _channel;
	arrSounds _mTotalSounds;
public:
	void loadSoundData();

public:
	bool initialize();
	void release();

	void addSound(std::string keyName, std::string soundName, bool background = false, bool loop = false);
	void play(std::string keyName, float volume);
	void stop(std::string keyName);
	void pause(std::string keyName);
	void resume(std::string keyName);
	bool isPauseSound(std::string keyName);
	bool isPlaySound(std::string keyName);

	void update();
	UINT getLength(std::string keyName);

public:
	CSoundManager();
	~CSoundManager();
};

#define SOUNDMANAGER CSoundManager::GetInstance()
#endif // !_SOUNDMANAGER_H
