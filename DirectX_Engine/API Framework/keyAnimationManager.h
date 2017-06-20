//#pragma once
//
//#include "singletonBase.h"
//#include <map>
//#include <algorithm>
//
//class image;
//class animation;
//
//class keyAnimationManager : public singletonBase<keyAnimationManager>
//{
//public:
//	typedef map<string, animation*> arrAnimation;
//	typedef map<string, animation*>::iterator iterAnimation;
//
//private:
//	arrAnimation _mTotalAnimation;
//
//public:
//	keyAnimationManager();
//	~keyAnimationManager();
//
//	HRESULT init();
//	void release();
//	void update();
//	void render();
//
//	//디폴트 애니메이션 3종
//	void addDefaultFrameAnimation( string animationKeyName, char* imageKeyName, int fps, bool reverse, bool loop );
//	void addDefaultFrameAnimation( string animationKeyName, char* imageKeyName, int fps, bool reverse, bool loop, void* cbFunction);
//	void addDefaultFrameAnimation( string animationKeyName, char* imageKeyName, int fps, bool reverse, bool loop, void* cbFunction, void* obj );
//
//	//배열 애니메이션 3종
//	void addArrayFrameAnimation( string animationKeyName, char* imageKeyName, int* arr, int arrLen, int fps, bool loop );
//	void addArrayFrameAnimation( string animationKeyName, char* imageKeyName, int* arr, int arrLen, int fps, bool loop, void* cbFunction );
//	void addArrayFrameAnimation( string animationKeyName, char* imageKeyName, int* arr, int arrLen, int fps, bool loop, void* cbFunction, void* obj );
//
//	//구간 애니메이션 3종
//	void addCoordinateFrameAniamtion( string animationKeyName, char* imageKeyName, int start, int end, int fps, bool reverse, bool loop );
//	void addCoordinateFrameAniamtion( string animationKeyName, char* imageKeyName, int start, int end, int fps, bool reverse, bool loop, void* cbFunction);
//	void addCoordinateFrameAniamtion( string animationKeyName, char* imageKeyName, int start, int end, int fps, bool reverse, bool loop, void* cbFunction, void* obj );
//
//	void start( string animationKeyName );
//	void stop( string animationKeyName );
//	void pause( string animationKeyName );
//	void resume( string animationKeyName );
//
//	animation* findAnimation( string animationKeyName );
//
//	void deleteAll();
//
//};
//
