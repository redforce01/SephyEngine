#include "stdafx.h"
#include "engineINISetting.h"


EngineINISetting::EngineINISetting()
{
}


EngineINISetting::~EngineINISetting()
{
}

void EngineINISetting::checkSection()
{
	std::string section;
	for (int i = 0; i < sizeof(SETTINGSECTION); i++)
	{


		
		sections.emplace_back(section);
	}

}

void EngineINISetting::readSetting()
{
	char* szBuf;
	char* strINIPath;


	//GetPrivateProfileString("Engine", "Debug", _T(""), szBuf, MAX_PATH, strINIPath);
	

}

void EngineINISetting::writeSetting()
{
}
