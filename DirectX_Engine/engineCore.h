#ifndef _ENGINECORE_H
#define _ENGINECORE_H

class EngineCore;

#include <map>
#include <thread>
#include <string>

class EngineCore
{
protected:
	bool bEngineStart;
	std::map<std::string, std::thread*> engineThread;

public:
	EngineCore();
	virtual ~EngineCore();

	virtual bool engineStart(HINSTANCE hInstance, int nCmdShow) PURE;
	virtual int run() PURE;
	virtual void addThread(std::string threadName);
	virtual void removeThread(std::string threadName);

	bool getEngineStart() { return bEngineStart; }
};

#endif // !_ENGINECORE_H
