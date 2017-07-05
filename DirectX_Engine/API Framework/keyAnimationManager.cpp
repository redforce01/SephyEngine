#include "stdafx.h"
//#include "keyAnimationManager.h"
//
//
//keyAnimationManager::keyAnimationManager()
//{
//}
//
//
//keyAnimationManager::~keyAnimationManager()
//{
//}
//
//HRESULT keyAnimationManager::init()
//{
//	return S_OK;
//}
//
//void keyAnimationManager::release()
//{
//	deleteAll();
//}
//
//void keyAnimationManager::update()
//{
//	//프레임 애니메이션을 업데이트에서 돌려준다
//	iterAnimation iter = _mTotalAnimation.begin();
//
//	for ( ; iter != _mTotalAnimation.end(); ++iter )
//	{
//		if ( !iter->second->isPlay() )continue;
//		//초당 70프레임으로 돌리자
//		iter->second->frameUpdate( TIMEMANAGER->getElapsedTime() * 1.0f );
//	}
//
//}
//
//void keyAnimationManager::render()
//{
//}
//
//void keyAnimationManager::addDefaultFrameAnimation( string animationKeyName, char * imageKeyName, int fps, bool reverse, bool loop )
//{
//	image* img = IMAGEMANAGER->findImage( imageKeyName );
//	animation* ani = new animation;
//
//	ani->init( img->getWidth(), img->getHeight(), img->getFrameWidth(), img->getFrameHeight() );
//	ani->setDefPlayFrame( reverse, loop );
//	ani->setFPS( fps );
//
//	_mTotalAnimation[animationKeyName] = ani;
//}
//
//void keyAnimationManager::addDefaultFrameAnimation( string animationKeyName, char * imageKeyName, int fps, bool reverse, bool loop, void * cbFunction )
//{
//	image* img = IMAGEMANAGER->findImage( imageKeyName );
//	animation* ani = new animation;
//
//	ani->init( img->getWidth(), img->getHeight(), img->getFrameWidth(), img->getFrameHeight() );
//	ani->setDefPlayFrame( reverse, loop, (CALLBACK_FUNCTION)cbFunction );
//	ani->setFPS( fps );
//
//	_mTotalAnimation[animationKeyName] = ani;
//}
//
//void keyAnimationManager::addDefaultFrameAnimation( string animationKeyName, char * imageKeyName, int fps, bool reverse, bool loop, void * cbFunction, void * obj )
//{
//	image* img = IMAGEMANAGER->findImage( imageKeyName );
//	animation* ani = new animation;
//
//	ani->init( img->getWidth(), img->getHeight(), img->getFrameWidth(), img->getFrameHeight() );
//	ani->setDefPlayFrame( reverse, loop , (CALLBACK_FUNCTION_PARAMETER) cbFunction, obj );
//	ani->setFPS( fps );
//
//	_mTotalAnimation[animationKeyName] = ani;
//}
//
//void keyAnimationManager::addArrayFrameAnimation( string animationKeyName, char * imageKeyName, int * arr, int arrLen, int fps, bool loop )
//{
//	image* img = IMAGEMANAGER->findImage( imageKeyName );
//	animation* ani = new animation;
//
//	ani->init( img->getWidth(), img->getHeight(), img->getFrameWidth(), img->getFrameHeight() );
//	ani->setPlayFrame( arr, arrLen, loop );
//	ani->setFPS( fps );
//
//	_mTotalAnimation.insert( pair<string, animation*>( animationKeyName, ani ) );
//}
//
//void keyAnimationManager::addArrayFrameAnimation( string animationKeyName, char * imageKeyName, int * arr, int arrLen, int fps, bool loop, void * cbFunction )
//{
//	image* img = IMAGEMANAGER->findImage( imageKeyName );
//	animation* ani = new animation;
//
//	ani->init( img->getWidth(), img->getHeight(), img->getFrameWidth(), img->getFrameHeight() );
//	ani->setPlayFrame( arr, arrLen, loop, (CALLBACK_FUNCTION)cbFunction );
//	ani->setFPS( fps );
//
//	_mTotalAnimation.insert( pair<string, animation*>( animationKeyName, ani ) );
//}
//
//void keyAnimationManager::addArrayFrameAnimation( string animationKeyName, char * imageKeyName, int * arr, int arrLen, int fps, bool loop, void * cbFunction, void * obj )
//{
//	image* img = IMAGEMANAGER->findImage( imageKeyName );
//	animation* ani = new animation;
//
//	ani->init( img->getWidth(), img->getHeight(), img->getFrameWidth(), img->getFrameHeight() );
//	ani->setPlayFrame( arr, arrLen, loop, ( CALLBACK_FUNCTION_PARAMETER ) cbFunction, obj );
//	ani->setFPS( fps );
//
//	_mTotalAnimation.insert( pair<string, animation*>( animationKeyName, ani ) );
//}
//
//
//void keyAnimationManager::addCoordinateFrameAniamtion( string animationKeyName, char * imageKeyName, int start, int end, int fps, bool reverse, bool loop )
//{
//	image* img = IMAGEMANAGER->findImage( imageKeyName );
//	animation* ani = new animation;
//
//	ani->init( img->getWidth(), img->getHeight(), img->getFrameWidth(), img->getFrameHeight() );
//	ani->setPlayFrame( start, end, reverse, loop );
//	ani->setFPS( fps );
//
//	_mTotalAnimation.insert( pair<string, animation*>( animationKeyName, ani ) );
//}
//
//void keyAnimationManager::addCoordinateFrameAniamtion( string animationKeyName, char * imageKeyName, int start, int end, int fps, bool reverse, bool loop, void * cbFunction )
//{
//	image* img = IMAGEMANAGER->findImage( imageKeyName );
//	animation* ani = new animation;
//
//	ani->init( img->getWidth(), img->getHeight(), img->getFrameWidth(), img->getFrameHeight() );
//	ani->setPlayFrame( start, end, reverse, loop, (CALLBACK_FUNCTION) cbFunction );
//	ani->setFPS( fps );
//
//	_mTotalAnimation.insert( pair<string, animation*>( animationKeyName, ani ) );
//}
//
//void keyAnimationManager::addCoordinateFrameAniamtion( string animationKeyName, char * imageKeyName, int start, int end, int fps, bool reverse, bool loop, void * cbFunction, void * obj )
//{
//	image* img = IMAGEMANAGER->findImage( imageKeyName );
//	animation* ani = new animation;
//
//	ani->init( img->getWidth(), img->getHeight(), img->getFrameWidth(), img->getFrameHeight() );
//	ani->setPlayFrame( start, end, reverse, loop, (CALLBACK_FUNCTION_PARAMETER) cbFunction, obj );
//	ani->setFPS( fps );
//
//	_mTotalAnimation.insert( pair<string, animation*>( animationKeyName, ani ) );
//}
//
//void keyAnimationManager::start( string animationKeyName )
//{
//	iterAnimation iter = _mTotalAnimation.find( animationKeyName );
//	iter->second->start();
//}
//
//void keyAnimationManager::stop( string animationKeyName )
//{
//	iterAnimation iter = _mTotalAnimation.find( animationKeyName );
//	iter->second->stop();
//}
//
//void keyAnimationManager::pause( string animationKeyName )
//{
//	iterAnimation iter = _mTotalAnimation.find( animationKeyName );
//	iter->second->pause();
//}
//
//void keyAnimationManager::resume( string animationKeyName )
//{
//	iterAnimation iter = _mTotalAnimation.find( animationKeyName );
//	iter->second->resume();
//}
//
//animation * keyAnimationManager::findAnimation( string animationKeyName )
//{
//	iterAnimation iter = _mTotalAnimation.find( animationKeyName );
//
//	if ( iter != _mTotalAnimation.end() )
//	{
//		return iter->second;
//	}
//
//	return NULL;
//}
//
//void keyAnimationManager::deleteAll()
//{
//	iterAnimation iter = _mTotalAnimation.begin();
//
//	for ( ; iter != _mTotalAnimation.end(); )
//	{
//		if ( iter->second != NULL )
//		{
//			SAFE_DELETE( iter->second );
//			iter = _mTotalAnimation.erase( iter );
//		}
//		else
//		{
//			++iter;
//		}
//	}
//
//	_mTotalAnimation.clear();
//
//}
