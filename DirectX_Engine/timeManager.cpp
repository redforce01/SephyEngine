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
	//���� Ÿ�̸� ���� ����
	//QueryPerformanceFrequency �Լ��� �ʴ� ī��Ʈ ������ ���� ��´�.
	//���� Ÿ�̸� ���� �ȴٸ� TRUE �ȵȴٸ� FALSE
	if (QueryPerformanceFrequency((LARGE_INTEGER*)&m_nPreriodTime))
	{
		//���� Ÿ�̸Ӹ� �����Ѵٸ�...
		m_bHardWare = true;

		//1 ī��Ʈ�� �ʰ� �󸶳� �Ǵ���?
		m_TimeScaleSec = 1.0 / m_nPreriodTime;

		//�ʱ�ȭ ������ �ð��� LastTime ����...
		QueryPerformanceCounter((LARGE_INTEGER*)&m_nLastTime);
	}

	else
	{
		//���� Ÿ�̸Ӹ� �������� �ʴ´ٸ�...
		m_bHardWare = false;

		//1000 �и������� ������ �ð����� ��´�.
		//timeGetTime �� GetTickCount ���� ���� �����ϴ�.
		m_nLastTime = timeGetTime();

		//1 ī��Ʈ�� �ʰ� �󸶳� �Ǵ���?
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
	//���� �ð��� ��´�.
	if (m_bHardWare)
		QueryPerformanceCounter((LARGE_INTEGER*)&m_nCurTime);
	else
		m_nCurTime = timeGetTime();

	//���� �ð����� ������ ���
	m_nDeltaTime = m_nCurTime - m_nLastTime;


	//�������� ������ ���� �ʽð� ���
	m_FrameDeltaSec = m_nDeltaTime * m_TimeScaleSec;

	//������ ���� �����Ѵٸ�...( ������ ��Ű�� )
	if (frameLock > 0.0f) {

		//������ �ð�.
		float fLockTime = (1.0f / frameLock);

		while (m_FrameDeltaSec < fLockTime)
		{
			//���� �ð��� ��´�.
			if (m_bHardWare)
				QueryPerformanceCounter((LARGE_INTEGER*)&m_nCurTime);
			else
				m_nCurTime = timeGetTime();

			//���� �ð����� �ݸ� ���
			m_nDeltaTime = m_nCurTime - m_nLastTime;

			//�������� ������ ���� �ʽð� ���
			m_FrameDeltaSec = m_nDeltaTime * m_TimeScaleSec;
		}

	}

	//���� �ð� ����
	m_nLastTime = m_nCurTime;

	//������ �ð� ����
	m_TotalSec += m_FrameDeltaSec;

	//������ �� ����
	m_FrameCountSec += m_FrameDeltaSec;

	//1�ʰ� �����ٸ�....
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
