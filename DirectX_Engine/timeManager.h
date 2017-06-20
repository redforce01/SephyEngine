#pragma once
#include "cSingletonBase.h"
#include "textDX.h"


namespace timeManagerNS
{
	const char FONT[] = "Courier New";  // font
	const int POINT_SIZE = 14;          // point size
	const COLOR_ARGB FONT_COLOR = SETCOLOR_ARGB(255, 255, 255, 255);    // white
}

class TimeManager : public cSingletonBase<TimeManager>
{
private:
	bool			initialized;
	TextDX			dxTimer;


private:
	bool			m_bHardWare;		//고성능 타이머 지원 여부

	__int64			m_nPreriodTime;		//1초에 몇번카운트 하는가?
	__int64			m_nLastTime;		//마지막 프레임 시간
	__int64			m_nCurTime;			//현재 시간
	__int64			m_nDeltaTime;		//이전 프레임과 지난시간

	double			m_TimeScaleSec;		//1카운트 당초.
	double			m_FrameDeltaSec;	//한프레임 경과 초
	double			m_TotalSec;			//프로그램 시작후 경과시간.

	double			m_FrameCountSec;	//프레임 갱신 시간
	DWORD			m_FrameCount;		//프레임 카운트
	DWORD			m_FramePerSec;		//초당 프레임


public:
	TimeManager();
	~TimeManager();

	HRESULT initialize();
	void release();

	void UpdateTime(float frameLock = 0.0f );

	void drawTimeInfo();

	double getFrameDeltaSec() { return (double)m_nDeltaTime; }
	double getTotalDeltaSec() { return m_TotalSec; }
	double getNowRealTimeSec();

	bool getInitialized() { return initialized; }
};

#define TIMEMANAGER TimeManager::GetInstance()