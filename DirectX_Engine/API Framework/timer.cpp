#include "stdafx.h"
//#include "timer.h"
//#include <mmsystem.h>
//
////TimeGetTime �Լ��� ����ϱ� ���� ���̺귯��
////�����찡 �������� �ð��� �˷��ִ� API��
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
//	//���� Ÿ�̸� �������� üũ
//	//���ÿ� ���� Ÿ�̸� ������ �ȴٸ� _periodFrequency ���� �ʴ� �ľ��� �� �ִ� �ð��� ���� ���´�
//	//���� ��� �ʴ� �и���������� ����� �����ϴٸ� 1000 ���� ���´�.
//	if (QueryPerformanceFrequency((LARGE_INTEGER*)&_periodFrequency))
//	{
//		_isHardware = true;
//		QueryPerformanceCounter((LARGE_INTEGER*)&_lastTime);
//
//		//�ʴ� �ð��� ��� �� �� �ִ� ���� // �ʴ� �ð� ��� ����
//		_timeScale = 1.0f / _periodFrequency;
//	}
//	else
//	{
//		_isHardware = false;
//
//		//�и������� ������ �ʸ� ������ �����.
//		_lastTime = timeGetTime();	//timeGetTime() �� �и� ������ ������ �ð����� �ʴ� 1000 ī��Ʈ
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
//	//���� Ÿ�̸� �����ϴ�
//	if (_isHardware)
//	{
//		QueryPerformanceCounter((LARGE_INTEGER*)&_curTime);
//	}
//	else
//	{
//		_curTime = timeGetTime();
//	}
//
//	//������ �ð��� ���� �ð��� �����
//	_timeElapsed = (_curTime - _lastTime) * _timeScale;
//
//	//���� ������ ó�� ������ 
//	if (lockFPS > 0.0f)
//	{
//		//���� �������� �ð��� ������ ������ ����
//		while (_timeElapsed < (1.0f / lockFPS))
//		{
//			if (_isHardware) QueryPerformanceCounter((LARGE_INTEGER*)&_curTime);
//			else _curTime = timeGetTime();
//
//			//������ �ð��� ���� �ð��� �����
//			_timeElapsed = (_curTime - _lastTime) * _timeScale;
//		}
//	}
//
//	_lastTime = _curTime;
//	_FPSFrameCount++;
//	_FPSTimeElapsed += _timeElapsed;
//	_worldTime += _timeElapsed;
//
//	//������ �ʱ�ȭ 1�ʸ��� ��������
//	if (_FPSTimeElapsed > 1.0f)
//	{
//		_frameRate = _FPSFrameCount;
//		_FPSFrameCount = 0;
//		_FPSTimeElapsed = 0.0f;
//	}
//}
//
////�Լ� �ڿ� const �� ������ Ŭ������ ��� ������ ������ ������� �ʰڴٶ�� ��...
//unsigned long timer::getFrameRate(char* str /*= NULL*/) const
//{
//	if (str != NULL)
//	{
//		wsprintf(str, "FPS : %d", _frameRate);
//	}
//
//	return _frameRate;
//}