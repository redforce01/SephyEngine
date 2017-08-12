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
	bool			m_bHardWare;		//���� Ÿ�̸� ���� ����

	__int64			m_nPreriodTime;		//1�ʿ� ���ī��Ʈ �ϴ°�?
	__int64			m_nLastTime;		//������ ������ �ð�
	__int64			m_nCurTime;			//���� �ð�
	__int64			m_nDeltaTime;		//���� �����Ӱ� �����ð�

	double			m_TimeScaleSec;		//1ī��Ʈ ����.
	double			m_FrameDeltaSec;	//�������� ��� ��
	double			m_TotalSec;			//���α׷� ������ ����ð�.

	double			m_FrameCountSec;	//������ ���� �ð�
	DWORD			m_FrameCount;		//������ ī��Ʈ
	DWORD			m_FramePerSec;		//�ʴ� ������


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