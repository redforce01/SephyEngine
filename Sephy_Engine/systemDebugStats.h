#ifndef _SYSTEMDEBUGSTATS_H
#define _SYSTEMDEBUGSTATS_H

class SystemDebugStats;

#include <map>
#include <string>
#include "systemUIDialog.h"

namespace debugStatsNS
{
	const UINT X = 5;
	const UINT Y = 5;
	const UINT WIDTH = 300;
	const UINT HEIGHT = 150;
	const UINT MARGIN = 4;
	const UINT TEXT_HEIGHT = 20;
	const std::string NAME = "STATS";
	const char FONT[] = "Courier New";
	const int FONT_SIZE = 14;
	const COLOR_ARGB FONT_COLOR = graphicsNS::WHITE;
	const COLOR_ARGB BACK_COLOR = SETCOLOR_ARGB(192, 26, 32, 44);
}

class SystemDebugStats : public SystemUIDialog
{
private:
	std::map<std::string, std::string> m_mapMessage;
	RECT m_rcText;
public:
	SystemDebugStats();
	virtual ~SystemDebugStats();

	virtual bool initialize(Graphics* g, Input* i) override;
	virtual void update(float frameTime) override;
	virtual void render() override;

	// ==========================================================
	// Member Functions
	// ==========================================================
	void addMessage(std::string key, std::string message)
	{
		m_mapMessage.emplace(key, message);
	}
	void setMessage(std::string key, std::string message)
	{
		m_mapMessage.find(key)->second = message;
	}
	void removeMessage(std::string key)
	{
		m_mapMessage.erase(key);
	}
};

#endif // !_SYSTEMDEBUGSTATS_H
