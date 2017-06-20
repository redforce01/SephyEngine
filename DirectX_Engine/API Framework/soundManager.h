//#pragma once
//#include "singletonBase.h"
//
//#include <map>
//#include <string>
//
////fmod.hpp 추가
//#include "inc/fmod.hpp"
//
////lib 링크
//#pragma comment ( lib, "lib/fmodex_vc.lib" )
//
////여유분의 채널 갯수 설정(버퍼)
//#define EXTRA_SOUND_CHANNEL 5
//#define SOUNDBUFFER 10
//
////총 사운드 갯수
//#define TOTAL_SOUND_CHANNEL SOUNDBUFFER + EXTRA_SOUND_CHANNEL
//
//using namespace FMOD;
//using namespace std;
//
//class soundManager : public singletonBase <soundManager>
//{
//private:
//	typedef map <string, Sound**> arrSounds;
//	typedef map <string, Sound**>::iterator arrSoundsIter;
//	typedef map <string, Channel**> arrChannels;
//	typedef map <string, Channel**>::iterator arrChannelIter;
//
//private:
//	System* _system;
//	Sound** _sound;
//
//	Channel** _channel;
//
//	arrSounds _mTotalSounds;
//
//
//public:
//	HRESULT init( void );
//	void release( void );
//
//	//사운드 추가
//	void addSound( string keyName, string soundName, bool background = false, bool loop = false );
//
//	//재생
//	void play( string keyName, float volume );
//
//	//종료
//	void stop( string keyName );
//
//	//정지
//	void pause( string keyName );
//
//	//다시 재생
//	void resume( string keyName );
//
//	//멈춰있니?
//	bool isPauseSound( string keyName );
//
//	//재생중이니?
//	bool isPlaySound( string keyName );
//
//	//Fmod 시스템을 갱신
//	void update( void );
//
//	//몇 분 짜리냐?
//	unsigned int getLength( string keyName );
//
//
//	soundManager();
//	~soundManager();
//};
