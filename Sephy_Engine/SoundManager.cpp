#include "stdafx.h"
#include "SoundManager.h"


CSoundManager::CSoundManager()
{
	_system = nullptr;
	_channel = nullptr;
	_sound = nullptr;
}


CSoundManager::~CSoundManager()
{
}

void CSoundManager::loadSoundData()
{
	// EFFECT SOUND INITIALIZE
	auto vSoundEffects = FILEMANAGER->getFileListInFolder(soundManagerNS::SOUND_EFFECT_FOLDER_NAME);
	for (auto iter : *vSoundEffects)
	{
		std::string soundKey = iter->fileName;
		std::string soundFilePath = iter->projectPath;

		addSound(soundKey, soundFilePath, false, false);
	}

	// ALERT SOUND INITIALIZE
	auto vSoundNewSounds = FILEMANAGER->getFileListInFolder(soundManagerNS::SOUND_EFFECT_ALERT_FOLDER_NAME);
	for (auto iter : *vSoundNewSounds)
	{
		std::string soundKey = iter->fileName;
		std::string soundFilePath = iter->projectPath;

		addSound(soundKey, soundFilePath, false, false);
	}

	// BGM SOUND INITIALIZE
	auto vSoundBGMs = FILEMANAGER->getFileListInFolder(soundManagerNS::SOUND_BGM_FOLDER_NAME);
	for (auto iter : *vSoundBGMs)
	{
		std::string soundKey = iter->fileName;
		std::string soundFilePath = iter->projectPath;

		addSound(soundKey, soundFilePath, true, true);
	}

	// OPERATOR SOUND INITIALIZE
	auto vSoundOperators = FILEMANAGER->getFileListInFolder(soundManagerNS::SOUND_EFFECT_OPERATOR_FOLDER_NAME);
	for (auto iter : *vSoundOperators)
	{
		std::string soundKey = iter->fileName;
		std::string soundFilePath = iter->projectPath;

		addSound(soundKey, soundFilePath, false, false);
	}
	
}

bool CSoundManager::initialize()
{
	bool success = false;
	try
	{
		System_Create(&_system);

		_system->init(TOTAL_SOUND_CHANNEL, FMOD_INIT_NORMAL, 0);

		_sound = new Sound*[TOTAL_SOUND_CHANNEL];
		_channel = new Channel*[TOTAL_SOUND_CHANNEL];

		memset(_sound, 0, sizeof(Sound*) * (TOTAL_SOUND_CHANNEL));
		memset(_channel, 0, sizeof(Channel*) * (TOTAL_SOUND_CHANNEL));
		success = true;

		loadSoundData();
	}
	catch (...)
	{
		MessageBox(g_hWndEngine, "FMOD - SOUND CHANNEL INITIALIZE FAILED", "Error", MB_OK);
		success = false;
	}	

	return success;
}

void CSoundManager::release()
{
	if (_channel != nullptr || _sound != nullptr)
	{
		for (int i = 0; i < TOTAL_SOUND_CHANNEL; i++)
		{
			if (_channel != nullptr)
			{
				if(_channel[i])
					_channel[i]->stop();
			}

			if (_sound != nullptr)
			{
				if (_sound[i])
					_sound[i]->release();
			}
		}
	}
	SAFE_DELETE_ARRAY(_channel);
	SAFE_DELETE_ARRAY(_sound);

	if (_system != nullptr)
	{
		_system->release();
		_system->close();
	}
}

void CSoundManager::addSound(std::string keyName, std::string soundName, bool background, bool loop)
{
	// Loop Sound
	if (loop)
	{
		if (background)
		{
			_system->createStream(soundName.c_str(), FMOD_LOOP_NORMAL, 0, &_sound[_mTotalSounds.size()]);
		}
		else
		{
			_system->createStream(soundName.c_str(), FMOD_DEFAULT, 0, &_sound[_mTotalSounds.size()]);
		}
	}
	// No Loop Sound
	else
	{
		_system->createStream(soundName.c_str(), FMOD_DEFAULT, 0, &_sound[_mTotalSounds.size()]);
	}

	_mTotalSounds.emplace(keyName, &_sound[_mTotalSounds.size()]);
}

void CSoundManager::play(std::string keyName, float volume)
{
	auto iter = _mTotalSounds.begin();

	int count = 0;
	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_system->playSound(FMOD_CHANNEL_FREE, *iter->second, false, &_channel[count]);

			_channel[count]->setVolume(volume);
			break;
		}
	}
}

void CSoundManager::stop(std::string keyName)
{
	auto iter = _mTotalSounds.begin();

	int count = 0;
	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->stop();
			break;
		}
	}
}

void CSoundManager::pause(std::string keyName)
{
	auto iter = _mTotalSounds.begin();
	int count = 0;
	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->setPaused(true);
			break;
		}
	}
}

void CSoundManager::resume(std::string keyName)
{
	auto iter = _mTotalSounds.begin();

	int count = 0;
	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->setPaused(false);
			break;
		}
	}
}

bool CSoundManager::isPauseSound(std::string keyName)
{
	bool isPause;
	int count = 0;
	auto iter = _mTotalSounds.begin();

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->getPaused(&isPause);
			break;
		}
	}
	return isPause;
}

bool CSoundManager::isPlaySound(std::string keyName)
{
	bool isPlay;
	int count = 0;
	auto iter = _mTotalSounds.begin();

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->isPlaying(&isPlay);
			break;
		}
	}
	return isPlay;
}

void CSoundManager::update()
{
	_system->update();
}

UINT CSoundManager::getLength(std::string keyName)
{
	auto iter = _mTotalSounds.begin();

	for (iter; iter != _mTotalSounds.end(); ++iter)
	{
		if (keyName == iter->first)
		{
			unsigned int length = 0;
			(*iter->second)->getLength(&length, FMOD_TIMEUNIT_MS);
			return length;
		}
	}

	return 0;
}
