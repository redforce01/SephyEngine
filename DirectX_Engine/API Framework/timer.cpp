#include "stdafx.h"
//#include "timer.h"
//#include <mmsystem.h>
//
////TimeGetTime 함수를 사용하기 위한 라이브러리
////윈도우가 실행중인 시간을 알려주는 API다
//#pragma comment (lib, "winmm.lib")
//
//timer::timer()
//{
//}
//
//
//timer::~timer()
//{
//}
//
//
//HRESULT timer::init()
//{
//	//고성능 타이머 지원여부 체크
//	//동시에 고성능 타이머 지원이 된다면 _periodFrequency 값에 초당 파악할 수 있는 시간의 값이 들어온다
//	//예를 들면 초당 밀리세컨드까지 계산이 가능하다면 1000 값이 들어온다.
//	if (QueryPerformanceFrequency((LARGE_INTEGER*)&_periodFrequency))
//	{
//		_isHardware = true;
//		QueryPerformanceCounter((LARGE_INTEGER*)&_lastTime);
//
//		//초당 시간을 계산 할 수 있는 여력 // 초당 시간 계산 범위
//		_timeScale = 1.0f / _periodFrequency;
//	}
//	else
//	{
//		_isHardware = false;
//
//		//밀리세컨드 단위로 초를 강제로 맞춘다.
//		_lastTime = timeGetTime();	//timeGetTime() 은 밀리 세컨드 단위의 시간으로 초당 1000 카운트
//		_timeScale = 0.001f;
//	}
//
//	_frameRate = 0;
//	_FPSFrameCount = 0;
//	_FPSTimeElapsed = 0.f;
//	_worldTime = 0.0f;
//
//	return S_OK;
//}
//
//void timer::tick(float lockFPS /*= 0.0f*/)
//{
//	//고성능 타이머 지원하니
//	if (_isHardware)
//	{
//		QueryPerformanceCounter((LARGE_INTEGER*)&_curTime);
//	}
//	else
//	{
//		_curTime = timeGetTime();
//	}
//
//	//마지막 시간과 현재 시간의 경과량
//	_timeElapsed = (_curTime - _lastTime) * _timeScale;
//
//	//고정 프레임 처리 해주자 
//	if (lockFPS > 0.0f)
//	{
//		//고정 프레임의 시간을 만족할 때까지 루프
//		while (_timeElapsed < (1.0f / lockFPS))
//		{
//			if (_isHardware) QueryPerformanceCounter((LARGE_INTEGER*)&_curTime);
//			else _curTime = timeGetTime();
//
//			//마지막 시간과 현재 시간의 경과량
//			_timeElapsed = (_curTime - _lastTime) * _timeScale;
//		}
//	}
//
//	_lastTime = _curTime;
//	_FPSFrameCount++;
//	_FPSTimeElapsed += _timeElapsed;
//	_worldTime += _timeElapsed;
//
//	//프레임 초기화 1초마다 진행하자
//	if (_FPSTimeElapsed > 1.0f)
//	{
//		_frameRate = _FPSFrameCount;
//		_FPSFrameCount = 0;
//		_FPSTimeElapsed = 0.0f;
//	}
//}
//
////함수 뒤에 const 가 붙으면 클래스의 멤버 변수의 변경을 허용하지 않겠다라는 거...
//unsigned long timer::getFrameRate(char* str /*= NULL*/) const
//{
//	if (str != NULL)
//	{
//		wsprintf(str, "FPS : %d", _frameRate);
//	}
//
//	return _frameRate;
//}