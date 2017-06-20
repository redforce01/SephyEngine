//#pragma once
//
//class timer
//{
//private:
//	bool _isHardware;
//	float _timeScale;
//	float _timeElapsed;
//
//	__int64 _curTime;
//	__int64 _lastTime;
//	__int64 _periodFrequency;
//
//	unsigned long _frameRate;
//	unsigned long _FPSFrameCount;
//
//	float _FPSTimeElapsed;
//	float _worldTime;
//
//
//public:
//	timer();
//	~timer();
//
//	HRESULT init();
//	void tick(float lockFPS = 0.0f);
//
//	//함수 뒤에 const 가 붙으면 클래스의 멤버 변수의 변경을 허용하지 않겠다라는 거...
//	unsigned long getFrameRate(char* str = NULL) const;
//
//	inline float getElapsedTime() const { return _timeElapsed; }
//	inline float getWorldTime() const { return _worldTime; }
//
//};
//
