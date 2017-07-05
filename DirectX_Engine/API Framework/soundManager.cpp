#include "stdafx.h"
//#include "soundManager.h"
//
//soundManager::soundManager( void )
//	:_system( NULL ),
//	_channel( NULL ),
//	_sound( NULL )
//{
//}
//
//soundManager ::~soundManager( void )
//{
//}
//
//HRESULT soundManager::init( void )
//{
//	//사운드 시스템 생성
//	System_Create( &_system );
//
//	//채널수 설정 및 초기화
//	_system->init( TOTAL_SOUND_CHANNEL, FMOD_INIT_NORMAL, 0 );
//
//	//채널과 사운드를 동적할당...
//	//메모리 버퍼 및 사운드 생성...
//	_sound = new Sound *[TOTAL_SOUND_CHANNEL];
//	_channel = new Channel *[TOTAL_SOUND_CHANNEL];
//
//	//초기화
//	memset( _sound, 0, sizeof( Sound* )* ( TOTAL_SOUND_CHANNEL ) );
//	memset( _channel, 0, sizeof( Channel* )* ( TOTAL_SOUND_CHANNEL ) );
//
//	return S_OK;
//}
//
//void soundManager::release( void )
//{
//	//사운드 삭제
//	if ( _channel != NULL || _sound != NULL )
//	{
//		for ( int i = 0; i < TOTAL_SOUND_CHANNEL; i++ )
//		{
//			if ( _channel != NULL )
//			{
//				if ( _channel[i] ) _channel[i]->stop();
//			}
//
//			if ( _sound != NULL )
//			{
//				if ( _sound != NULL ) _sound[i]->release();
//			}
//		}
//	}
//
//	//메모리 지우기
//	SAFE_DELETE_ARRAY( _channel );
//	SAFE_DELETE_ARRAY( _sound );
//
//	//시스템 닫기
//	if ( _system != NULL )
//	{
//		_system->release();
//		_system->close();
//	}
//}
//
////사운드 추가
//void soundManager::addSound( string keyName, string soundName, bool background, bool loop )
//{
//	//돌림노래냐?
//	if ( loop )
//	{
//		//배경음이냐?
//		if ( background )
//		{
//			_system->createStream( soundName.c_str(), FMOD_LOOP_NORMAL, 0, &_sound[_mTotalSounds.size()] );
//		}
//		else
//		{
//			_system->createSound( soundName.c_str(), FMOD_DEFAULT, 0, &_sound[_mTotalSounds.size()] );
//		}
//	}
//	//루프 아니다
//	else
//	{
//		//한번만 플레이~~
//		_system->createSound( soundName.c_str(), FMOD_DEFAULT, 0, &_sound[_mTotalSounds.size()] );
//	}
//
//	//맵에 사운드를 키값과 함께 넣어준다
//	_mTotalSounds.insert( make_pair( keyName, &_sound[_mTotalSounds.size()] ) );
//}
//
////사운드 플레이
//void soundManager::play( string keyName, float volume )
//{
//	arrSoundsIter iter = _mTotalSounds.begin();
//
//	int count = 0;
//	for ( iter; iter != _mTotalSounds.end(); ++iter, count++ )
//	{
//		if ( keyName == iter->first )
//		{
//			//사운드 플레이~~~
//			_system->playSound( FMOD_CHANNEL_FREE, *iter->second, false, &_channel[count] );
//
//			//볼륨 설정
//			_channel[count]->setVolume( volume );
//			break;
//		}
//	}
//}
//
////사운드 정지
//void soundManager::stop( string keyName )
//{
//	arrSoundsIter iter = _mTotalSounds.begin();
//
//	int count = 0;
//	for ( iter; iter != _mTotalSounds.end(); ++iter, count++ )
//	{
//		if ( keyName == iter->first )
//		{
//			//사운드 정지~~~
//			_channel[count]->stop();
//			break;
//		}
//	}
//}
//
////사운드 일시정지
//void soundManager::pause( string keyName )
//{
//	arrSoundsIter iter = _mTotalSounds.begin();
//
//	int count = 0;
//	for ( iter; iter != _mTotalSounds.end(); ++iter, count++ )
//	{
//		if ( keyName == iter->first )
//		{
//			//사운드 정지~~~
//			_channel[count]->setPaused( true );
//			break;
//		}
//	}
//}
//
////사운드 재시작
//void soundManager::resume( string keyName )
//{
//	arrSoundsIter iter = _mTotalSounds.begin();
//
//	int count = 0;
//	for ( iter; iter != _mTotalSounds.end(); ++iter, count++ )
//	{
//		if ( keyName == iter->first )
//		{
//			//사운드 정지~~~
//			_channel[count]->setPaused( false );
//			break;
//		}
//	}
//}
//
////일시정지 되었냐?
//bool soundManager::isPauseSound( string keyName )
//{
//	bool isPause;
//	int count = 0;
//	arrSoundsIter iter = _mTotalSounds.begin();
//
//	for ( iter; iter != _mTotalSounds.end(); ++iter, count++ )
//	{
//		if ( keyName == iter->first )
//		{
//			//사운드 정지~~~
//			_channel[count]->getPaused( &isPause );
//			break;
//		}
//	}
//	return isPause;
//}
//
////플레이 중이냐?
//bool soundManager::isPlaySound( string keyName )
//{
//	bool isPlay;
//	int count = 0;
//	arrSoundsIter iter = _mTotalSounds.begin();
//
//	for ( iter; iter != _mTotalSounds.end(); ++iter, count++ )
//	{
//		if ( keyName == iter->first )
//		{
//			//사운드 정지~~~
//			_channel[count]->isPlaying( &isPlay );
//			break;
//		}
//	}
//	return isPlay;
//}
//
////Fmod 시스템을 갱신
//void soundManager::update( void )
//{
//	//사운드 System 계속적으로 업데이트
//	_system->update();
//
//	//볼륨이 바뀌거나
//	//재생이 끝난 사운드를 채널에서 빼내는등의 다양한
//	//작업을 자동으로 해준다
//}
//
////몇 분 짜리냐?
//unsigned int soundManager::getLength( string keyName )
//{
//	arrSoundsIter iter = _mTotalSounds.begin();
//
//	for ( iter; iter != _mTotalSounds.end(); ++iter )
//	{
//		if ( keyName == iter->first )
//		{
//			unsigned int length = 0;
//			( *iter->second )->getLength( &length, FMOD_TIMEUNIT_MS );
//			return length;
//		}
//	}
//
//	return 0;
//}