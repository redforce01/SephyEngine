#ifndef _ENGINE_BOOTLOG_H
#define _ENGINE_BOOTLOG_H
#define WIN32_LEAN_AND_MEAN

#include "cSingletonBase.h"

class EngineBootLog : public cSingletonBase<EngineBootLog>
{
	std::string bootLog;
public:
	EngineBootLog();
	~EngineBootLog();

	void setLog(std::string log)
	{
		bootLog = log;
	}
	std::string getLog() const
	{
		return bootLog;
	}
};
#define ENGINE_BOOT_LOG EngineBootLog::GetInstance()
#endif // !_ENGINE_BOOTLOG_H
