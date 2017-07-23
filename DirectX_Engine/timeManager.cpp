#include "stdafx.h"
#include "timeManager.h"

TimeManager::TimeManager() : initialized(FALSE)
{
}

TimeManager::~TimeManager()
{
}

HRESULT TimeManager::initialize()
{
	//고성능 타이머 지원 여부
	//QueryPerformanceFrequency 함수로 초당 카운트 가능한 값을 얻는다.
	//고성능 타이머 지원 된다면 TRUE 안된다면 FALSE
	if (QueryPerformanceFrequency((LARGE_INTEGER*)&m_nPreriodTime))
	{
		//고성능 타이머를 지원한다면...
		m_bHardWare = true;

		//1 카운트당 초가 얼마나 되느냐?
		m_TimeScaleSec = 1.0 / m_nPreriodTime;

		//초기화 시점의 시간을 LastTime 으로...
		QueryPerformanceCounter((LARGE_INTEGER*)&m_nLastTime);
	}

	else
	{
		//고성능 타이머를 지원하지 않는다면...
		m_bHardWare = false;

		//1000 밀리세컨드 단위의 시간값을 얻는다.
		//timeGetTime 이 GetTickCount 보다 좀더 정밀하다.
		m_nLastTime = timeGetTime();

		//1 카운트당 초가 얼마나 되느냐?
		m_TimeScaleSec = 1.0 / 1000.0;

	}

	m_TotalSec = 0.0f;
	m_FrameCountSec = 0.0f;
	m_FramePerSec = 0;
	m_FrameCount = 0;


	dxTimer.initialize(g_Graphics, timeManagerNS::POINT_SIZE, false, false, timeManagerNS::FONT);
	dxTimer.setFontColor(timeManagerNS::FONT_COLOR);

	initialized = true;

	return S_OK;
}

void TimeManager::release()
{
}

void TimeManager::UpdateTime(float frameLock)
{
	//현제 시간을 얻는다.
	if (m_bHardWare)
		QueryPerformanceCounter((LARGE_INTEGER*)&m_nCurTime);
	else
		m_nCurTime = timeGetTime();

	//지난 시간과의 격차를 계산
	m_nDeltaTime = m_nCurTime - m_nLastTime;


	//한프레임 간격의 지난 초시간 계산
	m_FrameDeltaSec = m_nDeltaTime * m_TimeScaleSec;

	//프레임 락이 존해한다면...( 프레임 스키핑 )
	if (frameLock > 0.0f) {

		//고여있을 시간.
		float fLockTime = (1.0f / frameLock);

		while (m_FrameDeltaSec < fLockTime)
		{
			//현제 시간을 얻는다.
			if (m_bHardWare)
				QueryPerformanceCounter((LARGE_INTEGER*)&m_nCurTime);
			else
				m_nCurTime = timeGetTime();

			//지난 시간과의 격를 계산
			m_nDeltaTime = m_nCurTime - m_nLastTime;

			//한프레임 간격의 지난 초시간 계산
			m_FrameDeltaSec = m_nDeltaTime * m_TimeScaleSec;
		}

	}

	//지난 시간 갱신
	m_nLastTime = m_nCurTime;

	//총지난 시간 누적
	m_TotalSec += m_FrameDeltaSec;

	//프레임 초 누적
	m_FrameCountSec += m_FrameDeltaSec;

	//1초가 지났다면....
	if (m_FrameCountSec >= 1.0) {
		m_FramePerSec = m_FrameCount;
		m_FrameCount = 0;
		m_FrameCountSec -= 1.0;
	}
	m_FrameCount++;
}

void TimeManager::drawTimeInfo()
{
	int BUFFER_SIZE = 30;
	char BUFFER[32];

	_snprintf_s(BUFFER, BUFFER_SIZE, "Total Sec : %.1f", (float)m_TotalSec);
	dxTimer.print(BUFFER, g_fScreenWidth - 150, 10);

	_snprintf_s(BUFFER, BUFFER_SIZE, "Frame Delta : %.4f", (float)m_FrameDeltaSec);
	dxTimer.print(BUFFER, g_fScreenWidth - 150, 30);

	_snprintf_s(BUFFER, BUFFER_SIZE, "fps : %d", (int)m_FramePerSec);
	dxTimer.print(BUFFER, g_fScreenWidth - 150, 50);

}

double TimeManager::getNowRealTimeSec()
{
	__int64 nowTime;

	if (m_bHardWare)
	{
		QueryPerformanceCounter((LARGE_INTEGER*)&nowTime);
	}
	else
	{
		nowTime = GetTickCount();
	}

	return nowTime * m_TimeScaleSec;
}
