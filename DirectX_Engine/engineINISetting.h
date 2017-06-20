#ifndef _ENGINEINISETTING_H
#define _ENGINEINISETTING_H

class EngineINISetting;

#include <string>
#include <vector>

enum class SETTINGSECTION
{
	SETTINGSECTION_ENGINE,
	SETTINGSECTION_RESOURCE
};

class EngineINISetting
{
private:
	SETTINGSECTION section;
	std::vector<std::string> sections;

public:
	EngineINISetting();
	~EngineINISetting();

	void checkSection();

	void readSetting();
	void writeSetting();
};

#endif // !_ENGINEINISETTING_H
